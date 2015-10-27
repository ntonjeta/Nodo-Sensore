/**
 ******************************************************************************
 * @file    datalink.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    02/lug/2015
 * @brief   TODO: brief for datalink.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "datalink.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

#if (CAL_USE_OS == 1)
#include "freertos_tasks.h"
#include "frame.h"
#include "datalink_utils.h"

/**
 * @defgroup CAL_FREERTOS_DATALINK_TASKS
 * @brief Task del livello datalink
 * @{
 */

/* Private Constants ***********************************************************/

/**
 * @defgroup CAL_FREERTOS_DATALINK_TASKS_Private_Constants Private Constants
 * @brief Costanti private
 * @{
 */

#define DL_SEND_PARAM_LENGTH 2

/**
 * @}
 */

/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/

extern void sendErrorCallback(CAL_InterfaceNumber ifx, uint8_t* packet);

/* Private Declarations ***********************************************************/
void _dlTaskExtractFrameToSend(CAL_InterfaceNumber ifx);

/* Private Functions ***********************************************************/

/**
 * @defgroup CAL_FREERTOS_DATALINK_TASKS_Private_Functions Private Functions
 * @brief Funzioni private
 * @{
 */

void _dlTaskExtractFrameToSend(CAL_InterfaceNumber ifx)
{

	//Try to send the frame
	if (xDlInterfaceStatusSemaphore_handle == 0
			|| xDlQueueTxSemaphore_handle == 0)
		return;
	else
	{
		//Try to enter into critical section ( interfaceStatus + txStaging)
		if (xSemaphoreTake(xDlInterfaceStatusSemaphore_handle,
				portMAX_DELAY) == pdTRUE)
		{

			DL_Frame *frame = 0;
			DL_NumChunks_Type numChunks = 0;

			if (xSemaphoreTake(xDlQueueTxSemaphore_handle,
					portMAX_DELAY) == pdTRUE)
			{
				//This is a Critical section because this function handles status and queue for IFx
				//This solution is quite restrictive, but the semaphore usage overhead is low.
				frame = _dlPrepareToSendFrameOverInterface(ifx);

				//Releases the semaphores
				xSemaphoreGive(xDlQueueTxSemaphore_handle);
				xSemaphoreGive(xDlInterfaceStatusSemaphore_handle);

				if (frame != 0)
				{
					numChunks = frame->data[DL_NUMCHUNKS_FIELD];

					//Send Frame through PLCP Downstream Channel
					FREERTOS_CAL_Message msg;
					msg.type = CAL_SEND;
					msg.paramLength = DL_SEND_PARAM_LENGTH;
					msg.parameters = calMalloc(
							sizeof(DL_Frame*) + sizeof(uint8_t));
					*((uint32_t*) msg.parameters) = (DL_Frame*) frame;
					*((uint8_t*) (msg.parameters + sizeof(DL_Frame*))) =
							numChunks;
					if (vPlcpDownstreamQueue_handle != 0)
						xQueueSend(vPlcpDownstreamQueue_handle, &msg, portMAX_DELAY);
				}
			}
			else
				xSemaphoreGive(xDlInterfaceStatusSemaphore_handle);	//Gives the sem because it isn't released yet.
//			}
//			else
//				xSemaphoreGive(xDlInterfaceStatusSemaphore_handle);	//Gives the sem because it isn't released yet.
		}
	}
}

void _dlTaskNotifySendingFailure(DL_Frame *frame)
{

	if (frame->ifx < GET_MAX_INTERFACES())
	{
		uint8_t *packet = _dlGetPacketFromFrame(frame);
		sendErrorCallback(frame->ifx, packet);

		calFree(packet);

		//In all cases frees resources (the upper layer MUST copy the packet).
		_dlFreeResources(frame->data[DL_SEQNUMBER_FIELD], 0, 0);
	}
	else
		_dlFreeResources(-1, 0, frame);
}

void _dlTaskNotifySentFrame(DL_Frame *frame)
{

	if (frame->ifx < GET_MAX_INTERFACES())
	{
		uint8_t *packet = _dlGetPacketFromFrame(frame);
		sentPacketCallback(frame->ifx, packet);

		calFree(packet);
		//In all cases frees resources (the upper layer MUST copy the packet).
		_dlFreeResources(frame->data[DL_SEQNUMBER_FIELD], 0, 0);
	}
	else
		_dlFreeResources(-1, 0, frame);

}

SemaphoreHandle_t _dlTaskEnqueueAndTryToSend(CAL_InterfaceNumber ifx,
		DL_Frame *frame)
{

	if (xDlQueueTxSemaphore_handle != 0)
	{
		//The TxQueue Is critical (shared among Upstream and Downstream tasks).
		if (xSemaphoreTake(xDlQueueTxSemaphore_handle,portMAX_DELAY) == pdTRUE)
		{
			//Enqueue The Frame
			_dlEnqueueTxFrameQueue(ifx, frame);
			xSemaphoreGive(xDlQueueTxSemaphore_handle);
			//Tries to send Now The frame
			if (xSemaphoreTake(xDlInterfaceStatusSemaphore_handle,
					portMAX_DELAY) == pdTRUE)
			{
				if (_dlGetInterfaceReadyStatus(ifx) == DL_READY)
				{
					xSemaphoreGive(xDlInterfaceStatusSemaphore_handle);
					_dlTaskExtractFrameToSend(ifx);
				}
				else
					xSemaphoreGive(xDlInterfaceStatusSemaphore_handle);
			}
		}
	}
	return xDlQueueTxSemaphore_handle;
}

/**
 * @}
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_FREERTOS_DATALINK_TASKS_Exported_Functions Exported Functions
 * @brief Funzioni esportate. Task di freertos.
 * @{
 */

/**
 * @brief Task di freertos. Controlla periodicamente se sono arrivati degli ack
 * 		  per alcune frame, le rimuove quindi dalla 'staging area' e notifica l'avvenuto
 * 		  invio ai livelli superiori.
 * @param pvParameters Parametro di ingresso.
 * @retval none
 */
void vDlCheckTimeoutTask(void* pvParameters)
{
	//Unused parameters
	calUnused(pvParameters);

	for (;;)
	{
		_dlScanWaitingStagingArea();

		vTaskDelay(DL_TIMEOUT_PERIOD_MS);
	}
}

/**
 * @brief Task di freertos. Gestisce il flusso di dati verso il livello superiore.
 * @param pvParameters Parametro di ingresso.
 * @retval none
 */
void vDlUpstreamTask(void* pvParameters)
{
	//Unused parameters
	calUnused(pvParameters);

	//Init the UpStream Queue
	vDlUpstreamQueue_handle = xQueueCreate(IFX_TYPES_COUNT,
			sizeof(FREERTOS_CAL_Message));

	FREERTOS_CAL_Message msgFromQueue;
	for (;;)
	{
		if (vDlUpstreamQueue_handle != 0)
		{
			if (xQueueReceive(vDlUpstreamQueue_handle, &msgFromQueue,
					portMAX_DELAY))
			{

				FREERTOS_CAL_MessageType messageType = msgFromQueue.type;
				switch (messageType)
				{
				case CAL_RECEIVED: //Frame received from PLCP: we should check the frame type
				{
					//Extract Message parameters
					DL_Frame *frame = ((DL_Frame*) msgFromQueue.parameters); //The received frame
					_dlSwitchReceivedFrame(frame);
				}
					break;

				case CAL_SENT: //Frame Sent callback from PLCP (but the Ack isn't received yet)
				{
					CAL_InterfaceNumber ifx =
							*((CAL_InterfaceNumber*) msgFromQueue.parameters);

					calFree(msgFromQueue.parameters);

					if (xDlWaitingStageSemaphore_handle != 0)
					{
						//Critical section: the Waiting Stage is shared among Upstream and Downstream tasks.
						if (xSemaphoreTake(xDlWaitingStageSemaphore_handle,
								portMAX_DELAY) == pdTRUE)
						{
							_dlFrameSent(ifx);
							xSemaphoreGive(xDlWaitingStageSemaphore_handle);
							_dlTaskExtractFrameToSend(ifx);
						}
					}
					/*
					 * If sem_handle == 0 doesn't matter if the upper layer isn't notified about the SENT event
					 * because it could decide to resend the packet ( if it implements
					 */
				}
					break;

				case CAL_SEND_ERROR: //Trasmission Error
				{
					CAL_InterfaceNumber ifx =
							*((CAL_InterfaceNumber*) msgFromQueue.parameters);

					calFree(msgFromQueue.parameters);

					DL_SeqNumber_Type seqNumber = _dlGetSequenceNumber(ifx);
					DL_Frame *frame = _dlGetFrameFromTxStage(seqNumber);
					_dlEvaluateNumRetry(frame, seqNumber);
				}
					break;
				default:
					break;
				}
			}
		}
	}
}

/**
 * @brief Task di freertos. Gestisce il flusso di dati verso i livelli inferiori.
 * @param pvParameters Parametro di ingresso.
 * @retval none
 */
void vDlDownstreamTask(void* pvParameters)
{
	calUnused(pvParameters);
	//Init the Downstream Queue
	vDlDownstreamQueue_handle = xQueueCreate(IFX_TYPES_COUNT,
			sizeof(FREERTOS_CAL_Message));

	//Msg from queue element
	FREERTOS_CAL_Message msgFromQueue;
	for (;;)
	{
		if (vDlDownstreamQueue_handle != 0)
		{
			if (xQueueReceive(vDlDownstreamQueue_handle, &msgFromQueue,
					portMAX_DELAY))
			{
				FREERTOS_CAL_MessageType messageType = msgFromQueue.type;
				// At least one parameter the interface number
				CAL_InterfaceNumber ifx =
						*((CAL_InterfaceNumber*) msgFromQueue.parameters);
				switch (messageType)
				{
				case CAL_SEND:	//send A Packet
				{
					//Extract Message parameters
					uint8_t *packet = *((uint32_t*) (msgFromQueue.parameters
							+ sizeof(CAL_InterfaceNumber)));
					uint16_t packetLength =
							*((uint16_t*) (msgFromQueue.parameters
									+ sizeof(CAL_InterfaceNumber)
									+ sizeof(uint8_t*)));
					uint8_t numRetry = *((uint8_t*) (msgFromQueue.parameters
							+ sizeof(CAL_InterfaceNumber) + sizeof(uint8_t*)
							+ sizeof(uint16_t)));

					dlSendFrame(ifx, packet, packetLength, numRetry);
				}
					break;

				case CAL_ENABLE_IF: //enableInterface
				{
					dlEnableInterface(ifx);
				} //case
					break;

				case CAL_DISABLE_IF: //disableInterface by sending a BYE messages
				{
					dlDisableInterface(ifx);
					//When receives an Upstream CAL_SENT message check if it is a BYE and call plcpDisableInterface(ifx).
				}
					break;
				default:
					break;

				}

				// Free the parameters
				calFree(msgFromQueue.parameters);
			}
		}
	}
}

/**
 * @}
 */

/**
 * @}
 */

#endif

/**
 * @}
 */
