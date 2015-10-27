/**
 ******************************************************************************
 * @file    cal.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   TODO: brief for cal.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "cal.h"

#ifdef CAL_USE_OS
#if (CAL_USE_OS == 1)
#include "freertos_tasks.h"
#endif
#else
#define CAL_USE_OS	0
#endif

/**
 * @addtogroup CAL_Module CAL Module
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/
/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @addtogroup CAL_CAL_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/**
 * @brief Funzione di inizializzazione di CAL
 * @retval none
 */
void calInit()
{

	calLogInt(CAL_LOG_INFORMATIONAL,"calInit","FUN-CALLED",0);
	// Datalink init
	dlInit();
	// PLCP init
	plcpInit();

#if ( CAL_USE_OS == 1)
    // OS-dependant functions
	//Create Semaphores
	vSemaphoreCreateBinary(xDlInterfaceStatusSemaphore_handle);
	vSemaphoreCreateBinary(xDlQueueTxSemaphore_handle);
	vSemaphoreCreateBinary(xDlSequenceNumberSemaphore_handle);
	vSemaphoreCreateBinary(xDlWaitingStageSemaphore_handle);

	// Create all tasks, from higher priority to lower
	xTaskCreate(vPmdDownstreamTask, "PMD Downstream Task", CAL_TASKS_STACK_SIZE,
			NULL, tskIDLE_PRIORITY+3, &vPmdDownstreamTask_handle);

	xTaskCreate(vPlcpDownstreamTask, "PLCP Downstream Task",
			CAL_TASKS_STACK_SIZE, NULL, tskIDLE_PRIORITY+2,
			&vPlcpDownstreamTask_handle);

	xTaskCreate(vPlcpUpstreamTask, "PLCP Upstream Task", CAL_TASKS_STACK_SIZE,
			NULL, tskIDLE_PRIORITY+3, &vPlcpUpstreamTask_handle);

	xTaskCreate(vDlDownstreamTask, "DL Downstream Task", CAL_TASKS_STACK_SIZE,
			NULL, tskIDLE_PRIORITY+1, &vPmdDownstreamTask_handle);

	xTaskCreate(vDlUpstreamTask, "DL Upstream Task", CAL_TASKS_STACK_SIZE, NULL,
			tskIDLE_PRIORITY+2, &vDlUpstreamTask_handle);

	xTaskCreate(vDlCheckTimeoutTask, "DL Check Timeout Task",
			CAL_TASKS_STACK_SIZE, NULL, tskIDLE_PRIORITY,
			&vDlCheckTimeoutTask_handle);
#endif
}

/**
 * @brief Recupera lo stato delle interfacce gestite da CAL
 * @return CAL_Option_Type
 */
CAL_Option_Type *getInterfaceStatusMap() //map[i] = CAL_YES => interfaccia i è enabled, altrimenti CAL_NO.
{

	calLogInt(CAL_LOG_INFORMATIONAL,"getInterfaceStatusMap","FUN-CALLED",0);
	return (CAL_Option_Type*) dlGetInterfaceStatusMap();
}

/**
 * @brief Recupera lo stato di attach delle interfacce gestite da CAL
 * @retval CAL_Option_Type
 */
CAL_Option_Type getInterfaceAttachStatus(CAL_InterfaceNumber ifx)
{
	if (ifx == IF_ALL){
		return CAL_NO;
	}else return dlGetInterfaceAttachStatus(ifx);
}
/**
 * @brief Abilita un interfaccia gestita da CAL
 * @param ifx Numero dell'interfaccia
 * @retval none
 */
void enableInterface(CAL_InterfaceNumber ifx)
{

	calLogInt(CAL_LOG_INFORMATIONAL,"enableInterface","FUN-CALLED-IFx",ifx);
	if (ifx < GET_MAX_INTERFACES() || ifx == IF_ALL)
	{
#if ( CAL_USE_OS == 0)
		dlEnableInterface(ifx);
#else
		// OS-dependant functions
		FREERTOS_CAL_Message msg;
		msg.type = CAL_ENABLE_IF;
		msg.paramLength = 1;
		msg.parameters = &ifx;

		if (vDlDownstreamQueue_handle != 0)
			xQueueSend(vDlDownstreamQueue_handle, &msg, portMAX_DELAY);
#endif
	}

}

/**
 * @brief Disabilita un interfaccia gestita da CAL
 * @param ifx Numero dell'interfaccia
 * @retval none
 */
void disableInterface(CAL_InterfaceNumber ifx)
{

	calLogInt(CAL_LOG_INFORMATIONAL,"disableInterface","FUN-CALLED-IFx",ifx);
	if (ifx < GET_MAX_INTERFACES() || ifx == IF_ALL)
	{
#if ( CAL_USE_OS == 0)
		dlDisableInterface(ifx);
#else
		// OS-dependant functions
		FREERTOS_CAL_Message msg;
		msg.type = CAL_DISABLE_IF;
		msg.paramLength = 1;
		msg.parameters = &ifx;

		if (vDlDownstreamQueue_handle != 0)
			xQueueSend(vDlDownstreamQueue_handle, &msg, portMAX_DELAY);
#endif
	}

}

/**
 * @brief Invia un pacchetto packet di lunghezza packetLength sull'interfaccia ifx con un numero di
 * 		  tentativi numRetry
 * @param ifx Numero dell'interfaccia
 * @param packet Puntatore al pacchetto da inviare
 * @param packetLength Lunghezza del pacchetto
 * @param numRetry Numero di tentativi
 * @retval none
 */
void sendPacketTo(CAL_InterfaceNumber ifx, uint8_t *packet,
		uint16_t packetLength, uint8_t numRetry)
{


	if (ifx < GET_MAX_INTERFACES()
			&& packetLength <= CHUNK_LENGTH * 255 - HEADER_LENGTH - 4)
	{
		calLogString(CAL_LOG_INFORMATIONAL,"sendPacketTo","FUN-CALLED"," ");
#if ( CAL_USE_OS == 0)
		dlSendFrame(ifx, packet, packetLength, numRetry);
#else
		// OS-dependant functions
		//Send Frame through DL Downstream Channel
		FREERTOS_CAL_Message msg;
		msg.type = CAL_SEND;
		msg.paramLength = 4;
		msg.parameters = calMalloc(
				sizeof(CAL_InterfaceNumber) + sizeof(uint8_t*)
						+ sizeof(packetLength) + sizeof(numRetry));
		*((CAL_InterfaceNumber*)msg.parameters) = ifx;
		*((uint32_t*)(msg.parameters+sizeof(CAL_InterfaceNumber))) = packet;
		*((uint16_t*)(msg.parameters+sizeof(CAL_InterfaceNumber)+sizeof(uint8_t*))) = packetLength;
		*((uint8_t*)(msg.parameters+sizeof(CAL_InterfaceNumber)+sizeof(uint8_t*)+sizeof(uint16_t))) = numRetry;

		if (vDlDownstreamQueue_handle != 0)
			xQueueSend(vDlDownstreamQueue_handle, &msg, portMAX_DELAY);
#endif
	}
	else
		{

			calLogInt(CAL_LOG_INFORMATIONAL,"sendPacketTo","SEND-ERROR-IFx",ifx);
			sendErrorCallback(ifx, packet,packetLength);
		}
}

/**
 * @brief Invia un pacchetto packet di lunghezza packetLength con numero di tentativi numRetry,
 *        su tutte le interfacce
 * @param packet Puntatore del pacchetto
 * @param packetLength Lunghezza del pacchetto
 * @param numRetry Numero di tentativi
 * @retval none
 */
void sendPacketBroadcast(uint8_t *packet, uint16_t packetLength,
		uint8_t numRetry)
{

	calLogString(CAL_LOG_INFORMATIONAL,"sendPacketBroadcast","FUN-CALLED"," ");
	CAL_InterfaceNumber i = 0;
	CAL_Option_Type *map = dlGetInterfaceStatusMap();
	while (i < GET_MAX_INTERFACES())
	{
		if (dlGetInterfaceAttachStatus(i)==CAL_YES && map[i] == CAL_YES)
			sendPacketTo(i, packet, packetLength, numRetry);
		i++;

	}

}

/**
 * @brief Invia un pacchetto packet di lunghezza packetLength con numero di tentativi numRetry,
 *        su un sottinsieme ifxVector di interfacce
 * @param ifxVector Vettore di numeri di interfacce
 * @param packet Puntatore del pacchetto
 * @param packetLength Lunghezza del pacchetto
 * @param numRetry Numero di tentativi
 * @retval none
 */
void sendPacketMulticast(CAL_InterfaceNumber *ifxVector, uint8_t ifxVettLength,
		uint8_t *packet, uint16_t packetLength, uint8_t numRetry)
{
	calLogString(CAL_LOG_INFORMATIONAL,"sendPacketMulticast","FUN-CALLED"," ");
	int i = 0;
	CAL_Option_Type *map = dlGetInterfaceStatusMap();
	while (i < ifxVettLength)
	{
		if (dlGetInterfaceAttachStatus(ifxVector[i])==CAL_YES && map[ifxVector[i]] == CAL_YES)
			sendPacketTo(ifxVector[i], packet, packetLength, numRetry);
		i++;

	}
}

/**
 * @brief Callback interfaccia attaccata
 * @param ifx Numero dell'interfaccia
 * @retval none
 */
__attribute__((weak)) void interfaceAttachedCallback(CAL_InterfaceNumber ifx)
{
	// Unused parameters
	calUnused(ifx);
}

/**
 * @brief Callback interfaccia staccata
 * @param ifx Numero dell'interfaccia
 * @retval none
 */
__attribute__((weak)) void interfaceDetachedCallback(CAL_InterfaceNumber ifx)
{
	// Unused parameters
	calUnused(ifx);
}

/**
 * @brief Callback pacchetto correttamente inviato
 * @param ifx Numero dell'interfaccia
 * @param packet Puntatore del pacchetto
 * @retval none
 */
__attribute__((weak)) void sentPacketCallback(CAL_InterfaceNumber ifx,
		uint8_t *packet,uint16_t packetLength)
{
	// Unused parameters
	calUnused(ifx);
	calUnused(packet);
	calUnused(packetLength);
}

/**
 * @brief Callback pacchetto ricevuto
 * @param ifx Numero dell'interfaccia
 * @param packet Puntatore del pacchetto
 * @param packetLength Lunghezza del pacchetto
 * @retval none
 */
__attribute__((weak)) void receivedPacketCallback(CAL_InterfaceNumber ifx,
		uint8_t* packet, uint16_t packetLength)
{
	// Unused parameters
	calUnused(ifx);
	calUnused(packet);
	calUnused(packetLength);
}


/**
 * @brief Callback pacchetto non correttamente inviato. NumRetry esauriti
 * @param ifx Numero dell'interfaccia
 * @param packet Puntatore del pacchetto
 * @param packetLength Lunghezza del pacchetto
 * @retval none
 */
__attribute__((weak)) void sendErrorCallback(CAL_InterfaceNumber ifx,
		uint8_t* packet,uint16_t packetLength)
{
	// Unused parameters
	calUnused(ifx);
	calUnused(packet);
	calUnused(packetLength);
}

/**
 * @}
 */

/**
 * @}
 */
