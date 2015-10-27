/**
 ******************************************************************************
 * @file    pmd.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   Physical Medium Dependant source file.
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "pmd.h"

#ifdef CAL_USE_OS
#if (CAL_USE_OS == 1)
#include "freertos_tasks.h"
#endif
#else
#define CAL_USE_OS	0
#endif

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @addtogroup CAL_PHY Livello Fisico
 * @brief Livello fisico di CAL
 * @{
 */

/**
 * @defgroup CAL_PHY_PMD_Module Sottolivello PMD
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/

/**
 * @addtogroup CAL_PHY_PMD_UART_Exported_Functions Exported Functions
 * @{
 */

#if (UART_NUM_INTERFACES <=0 )
#define pmdConfigUart(x)		PMD_ERROR
#define pmdInitUart(x)			PMD_ERROR
#define pmdDeInitUart(x)		PMD_ERROR
#define pmdSendUart(x)			PMD_ERROR
#define pmdReceiveUart(x)		PMD_ERROR
#else
extern PMD_Status pmdConfigUart(PMD_Interface*);
extern PMD_Status pmdInitUart(PMD_Interface*);
extern PMD_Status pmdDeInitUart(PMD_Interface*);
extern PMD_Status pmdSendUart(PMD_Chunk*) CAL_UNUSED_FUNCTION;
extern PMD_Status pmdReceiveUart(PMD_Chunk*) CAL_UNUSED_FUNCTION;
#endif

/**
 * @}
 * @return
 */

/**
 * @addtogroup CAL_PHY_PMD_I2C_Exported_Functions Exported Functions
 * @brief PMD I2C Exported Functions
 * @{
 */

#if (I2C_NUM_INTERFACES <=0 )
#define pmdConfigI2c(x)			PMD_ERROR
#define pmdInitI2c(x)			PMD_ERROR
#define pmdDeInitI2c(x)			PMD_ERROR
#define pmdSendI2c(x)			PMD_ERROR
#define pmdReceiveI2c(x)		PMD_ERROR
#else
extern PMD_Status pmdConfigI2c(PMD_Interface*);
extern PMD_Status pmdInitI2c(PMD_Interface*);
extern PMD_Status pmdDeInitI2c(PMD_Interface*);
extern PMD_Status pmdSendI2c(PMD_Chunk*) CAL_UNUSED_FUNCTION;
extern PMD_Status pmdReceiveI2c(PMD_Chunk*) CAL_UNUSED_FUNCTION;
#endif

/**
 * @}
 */

/**
 * @addtogroup CAL_PHY_PMD_SPI_Exported_Functions Exported Functions
 * @{
 */

#if (SPI_NUM_INTERFACES <=0 )
#define pmdConfigSpi(x)			PMD_ERROR
#define pmdInitSpi(x)			PMD_ERROR
#define pmdDeInitSpi(x)			PMD_ERROR
#define pmdSendSpi(x)			PMD_ERROR
#define pmdReceiveSpi(x)		PMD_ERROR
#else
extern PMD_Status pmdConfigSpi(PMD_Interface*);
extern PMD_Status pmdInitSpi(PMD_Interface*);
extern PMD_Status pmdDeInitSpi(PMD_Interface*);
extern PMD_Status pmdSendSpi(PMD_Chunk*) CAL_UNUSED_FUNCTION;
extern PMD_Status pmdReceiveSpi(PMD_Chunk*) CAL_UNUSED_FUNCTION;
#endif

/**
 * @}
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @addtogroup CAL_PHY_PMD_Exported_Functions Exported Functions
 * @brief PMD Exported Functions
 * @{
 */

/**
 * @brief Configure the PMD_Interface doing the mapping between the PMD_Interface
 * 		  and the actual physical one.
 * @param in pmdIfx Pointer to the PMD_Interface to configure.
 * @retval PMD Status
 */
PMD_Status pmdConfig(PMD_Interface* pmdIfx)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdConfig", "FUN-CALLED", 0);
	calLogInt(CAL_LOG_DEBUG, "pmdConfig", "PMD-IF-ID", pmdIfx->id);
	calLogInt(CAL_LOG_DEBUG, "pmdConfig", "PMD-IF-IFTYPE", pmdIfx->type);
	calLogInt(CAL_LOG_DEBUG, "pmdConfig", "PMD-IF-IFCAL", pmdIfx->ifxNumber);

	// If the interface is already configured
	if (PMD_isInterfaceConfigured(pmdIfx))
	{
		calLogInt(CAL_LOG_NOTICE, "pmdConfig", "ALREADY-CONFIGURED-CAL-IFX",
				pmdIfx->ifxNumber);
		calLogInt(CAL_LOG_NOTICE, "pmdConfig", "ALREADY-CONFIGURED-PMD-IDX",
				pmdIfx->id);
		calLogInt(CAL_LOG_NOTICE, "pmdConfig", "ALREADY-CONFIGURED-PMD-TYPE",
				pmdIfx->type);
		return PMD_ALREADY_CONFIGURED;
	}

	// Handle the status
	PMD_Status status;

	/* Call the type-specific function */
	switch (pmdIfx->type)
	{
	case PMD_SPI:
		status = pmdConfigSpi(pmdIfx);
		break;
	case PMD_I2C:
		status = pmdConfigI2c(pmdIfx);
		break;
	case PMD_UART:
		status = pmdConfigUart(pmdIfx);
		break;
	default:
		return PMD_ERROR;
		break;
	}

	if (status == PMD_OK)
	{
		pmdIfx->status = PMD_IF_STATUS_CONFIGURED;
	}

	return status;
}

/**
 * @brief Initialize the pyhisical interface abstracted by the PMD_Interface
 * @param in pmdIfx Pointer to the PMD_Interface to initialize.
 * @retval PMD Status
 */
PMD_Status pmdInit(PMD_Interface* pmdIfx)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdInit", "FUN-CALLED", 0);
	calLogInt(CAL_LOG_DEBUG, "pmdInit", "PMD-IF-ID", pmdIfx->id);
	calLogInt(CAL_LOG_DEBUG, "pmdInit", "PMD-IF-IFTYPE", pmdIfx->type);
	calLogInt(CAL_LOG_DEBUG, "pmdInit", "PMD-IF-IFCAL", pmdIfx->ifxNumber);

	// Do not initialize the pmd if already initialized before
	if (PMD_isInterfaceInitialized(pmdIfx))
	{
		calLogInt(CAL_LOG_NOTICE, "pmdInit", "ALREADY-INITIALIZED-CAL-IFX",
				pmdIfx->ifxNumber);
		calLogInt(CAL_LOG_NOTICE, "pmdInit", "ALREADY-INITIALIZED-PMD-IDX",
				pmdIfx->id);
		calLogInt(CAL_LOG_NOTICE, "pmdInit", "ALREADY-INITIALIZED-PMD-TYPE",
				pmdIfx->type);
		return PMD_ALREADY_INITIALIZED;
	}

	// Handle the status
	PMD_Status status;

	/* Call the type-specific function */
	switch (pmdIfx->type)
	{
	case PMD_SPI:
		status = pmdInitSpi(pmdIfx);
		break;
	case PMD_I2C:
		status = pmdInitI2c(pmdIfx);
		break;
	case PMD_UART:
		status = pmdInitUart(pmdIfx);
		break;
	default:
		return PMD_ERROR;
		break;
	}

	if (status == PMD_OK)
	{
		pmdIfx->status = PMD_IF_STATUS_INITIALIZED;
	}

	return status;
}

/**
 * @brief De-Initialize the pyhisical interface abstracted by the PMD_Interface
 * @param in pmdIfx Pointer to the PMD_Interface to initialize.
 * @retval PMD Status
 */
PMD_Status pmdDeInit(PMD_Interface* pmdIfx)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdDeInit", "FUN-CALLED", 0);
	calLogInt(CAL_LOG_DEBUG, "pmdDeInit", "PMD-IF-ID", pmdIfx->id);
	calLogInt(CAL_LOG_DEBUG, "pmdDeInit", "PMD-IF-IFTYPE", pmdIfx->type);
	calLogInt(CAL_LOG_DEBUG, "pmdDeInit", "PMD-IF-IFCAL", pmdIfx->ifxNumber);

	// DeInitialize the pmd only if it was initialized before
	if (!PMD_isInterfaceInitialized(pmdIfx))
	{
		calLogInt(CAL_LOG_NOTICE, "pmdDeInit", "NOT-INITIALIZED-CAL-IFX",
				pmdIfx->ifxNumber);
		calLogInt(CAL_LOG_NOTICE, "pmdDeInit", "NOT-INITIALIZED-PMD-IDX",
				pmdIfx->id);
		calLogInt(CAL_LOG_NOTICE, "pmdDeInit", "NOT-INITIALIZED-PMD-TYPE",
				pmdIfx->type);
		// Return PMD_OK because it was not initialized
		return PMD_OK;
	}

	// Handle the status
	PMD_Status status;

	/* Call the type-specific function */
	switch (pmdIfx->type)
	{
	case PMD_SPI:
		status = pmdDeInitSpi(pmdIfx);
		break;
	case PMD_I2C:
		status = pmdDeInitI2c(pmdIfx);
		break;
	case PMD_UART:
		status = pmdDeInitUart(pmdIfx);
		break;
	default:
		return PMD_ERROR;
		break;
	}

	if (status == PMD_OK)
	{
		// The interface is only configured now
		pmdIfx->status = PMD_IF_STATUS_CONFIGURED;
	}

	return status;
}

/**
 * @brief Send a PMD_Chunk through a PMD_Interface.
 * @param in pmdIfx Pointer to the PMD_Interface to initialize.
 * @retval PMD Status
 */
PMD_Status pmdSend(PMD_Chunk* chunk)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdSend", "FUN-CALLED", 0);
	calLogInt(CAL_LOG_DEBUG, "pmdSend", "CHUNK-ID", chunk->pmdIfx->id);
	calLogInt(CAL_LOG_DEBUG, "pmdSend", "CHUNK-IFTYPE", chunk->pmdIfx->type);
	calLogInt(CAL_LOG_DEBUG, "pmdSend", "CHUNK-IFCAL",
			chunk->pmdIfx->ifxNumber);

	/* Call the type-specific function */
	switch (chunk->pmdIfx->type)
	{
	case PMD_SPI:
		return pmdSendSpi(chunk);
		break;
	case PMD_I2C:
		return pmdSendI2c(chunk);
		break;
	case PMD_UART:
		return pmdSendUart(chunk);
		break;
	default:
		return PMD_ERROR;
		break;
	}
}

/**
 * @brief Receive a PMD_Chunk through a PMD_Interface.
 * @param in pmdIfx Pointer to the PMD_Interface to initialize.
 * @retval PMD Status
 */
PMD_Status pmdReceive(PMD_Chunk* chunk)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdReceive", "FUN-CALLED", 0);
	calLogInt(CAL_LOG_DEBUG, "pmdReceive", "CHUNK-ID", chunk->pmdIfx->id);
	calLogInt(CAL_LOG_DEBUG, "pmdReceive", "CHUNK-IFTYPE", chunk->pmdIfx->type);
	calLogInt(CAL_LOG_DEBUG, "pmdReceive", "CHUNK-IFCAL",
			chunk->pmdIfx->ifxNumber);

	/* Call the type-specific function */
	switch (chunk->pmdIfx->type)
	{
	case PMD_SPI:
		return pmdReceiveSpi(chunk);
		break;
	case PMD_I2C:
		return pmdReceiveI2c(chunk);
		break;
	case PMD_UART:
		return pmdReceiveUart(chunk);
		break;
	default:
		return PMD_ERROR;
		break;
	}
}

/**
 * @}
 */

/**
 * @addtogroup CAL_PHY_PMD_Callback Exported Callback
 * @brief Callback
 * @{
 */

/**
 * @brief Callback called when a PMD_Chunk is receive upon an PMD_Interface.
 * @param out chunk The PMD_Chunk received.
 * @retval none
 */
void pmdChunkReceivedCallback(PMD_Chunk* chunk)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdChunkReceivedCallback", "FUN-CALLED", 0);
	calLogInt(CAL_LOG_DEBUG, "pmdChunkReceivedCallback", "CHUNK-ID",
			chunk->pmdIfx->id);
	calLogInt(CAL_LOG_DEBUG, "pmdChunkReceivedCallback", "CHUNK-IFTYPE",
			chunk->pmdIfx->type);
	calLogInt(CAL_LOG_DEBUG, "pmdChunkReceivedCallback", "CHUNK-IFCAL",
			chunk->pmdIfx->ifxNumber);

#if (CAL_USE_OS == 0)
	extern void plcpChunkReceivedCallback(PMD_Chunk*);

	plcpChunkReceivedCallback(chunk);
#else
	BaseType_t xTaskWokenByReceive = pdFALSE;
	FREERTOS_CAL_Message message;
	message.type = CAL_RECEIVED;
	message.paramLength = 1;
	message.parameters = chunk;

	xQueueSendFromISR(vPlcpUpstreamQueue_handle, &message,
			&xTaskWokenByReceive);

	if (xTaskWokenByReceive != pdFALSE)
	{
		taskYIELD ();
	}

#endif
}

/**
 * @brief Callback called when a PMD_Chunk has been sent through an PMD_Interface.
 * @param out chunk The PMD_Chunk received.
 * @retval none
 */
void pmdChunkSentCallback(PMD_Chunk* chunk)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdChunkSentCallback", "FUN-CALLED", 0);
	calLogInt(CAL_LOG_DEBUG, "pmdChunkSentCallback", "CHUNK-ID",
			chunk->pmdIfx->id);
	calLogInt(CAL_LOG_DEBUG, "pmdChunkSentCallback", "CHUNK-IFTYPE",
			chunk->pmdIfx->type);
	calLogInt(CAL_LOG_DEBUG, "pmdChunkSentCallback", "CHUNK-IFCAL",
			chunk->pmdIfx->ifxNumber);

#if (CAL_USE_OS == 0)
	extern void plcpChunkSentCallback(PMD_Chunk*);

	plcpChunkSentCallback(chunk);
#else
	BaseType_t xTaskWokenByReceive = pdFALSE;
	FREERTOS_CAL_Message message;
	message.type = CAL_SENT;
	message.paramLength = 1;
	message.parameters = chunk;

	xQueueSendFromISR(vPlcpUpstreamQueue_handle, &message,
			&xTaskWokenByReceive);

	if (xTaskWokenByReceive != pdFALSE)
	{
		taskYIELD ();
	}
#endif
}

/**
 * @brief Callback called when cannot be configured a reception.
 * @param out chunk The PMD_Chunk would-be received.
 * @retval none
 */
void pmdChunkReceiveErrorCallback(PMD_Chunk* chunk)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdChunkReceiveErrorCallback", "FUN-CALLED",
	0);

	calLogInt(CAL_LOG_ERROR, "pmdChunkReceiveErrorCallback", "CHUNK-RCV-FAILED",
			chunk->pmdIfx->ifxNumber);

#if (CAL_USE_OS == 0)
	extern void plcpChunkReceiveErrorCallback(PMD_Chunk*);

	plcpChunkReceiveErrorCallback(chunk);
#else
	BaseType_t xTaskWokenByReceive = pdFALSE;
	FREERTOS_CAL_Message message;
	message.type = CAL_RECEIVE_ERROR;
	message.paramLength = 1;
	message.parameters = chunk;

	xQueueSendFromISR(vPlcpUpstreamQueue_handle, &message,
			&xTaskWokenByReceive);

	if (xTaskWokenByReceive != pdFALSE)
	{
		taskYIELD ();
	}
#endif
}

/**
 * @brief Callback called when there is a send error
 * @param out chunk The PMD_Chunk failed to send.
 * @retval none
 */
void pmdChunkSendErrorCallback(PMD_Chunk* chunk)
{
	//Log Code
	calLogInt(CAL_LOG_DEBUG, "pmdChunkSendErrorCallback", "FUN-CALLED",
	0);

	calLogInt(CAL_LOG_ERROR, "pmdChunkSendErrorCallback", "CHUNK-SENT-FAILED",
			chunk->pmdIfx->ifxNumber);

#if (CAL_USE_OS == 0)
	extern void plcpChunkSendErrorCallback(PMD_Chunk*);

	plcpChunkSendErrorCallback(chunk);
#else
	BaseType_t xTaskWokenByReceive = pdFALSE;
	FREERTOS_CAL_Message message;
	message.type = CAL_SEND_ERROR;
	message.paramLength = 1;
	message.parameters = chunk;

	xQueueSendFromISR(vPlcpUpstreamQueue_handle, &message,
			&xTaskWokenByReceive);

	if (xTaskWokenByReceive != pdFALSE)
	{
		taskYIELD ();
	}
#endif
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
