/**
 ******************************************************************************
 * @file    i2c_pmd.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    27/giu/2015
 * @brief   I2C Physical Medium Dependant Module
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "i2c_pmd.h"

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
 * @addtogroup CAL_PHY_PMD_Module Sottolivello PMD
 * @{
 */

/**
 * @addtogroup CAL_PHY_PMD_I2C Livello I2C del PMD
 * @brief Livello che gestisce periferiche di tipo I2C
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/

/**
 * @defgroup CAL_PHY_PMD_I2C_Private_Variables Private Variables
 * @brief PMD I2C Variabili private
 * @{
 */

static I2C_HandleTypeDef* hi2c_tx[I2C_NUM_INTERFACES]; /**< Tx Handlers */
static I2C_HandleTypeDef* hi2c_rx[I2C_NUM_INTERFACES]; /**< Rx handlers */

/**
 * @}
 */

/* Private Functions Declaration ***********************************************/

/**
 * @defgroup CAL_PHY_PMD_I2C_Private_Functions Private Functions
 * @brief PMD I2C Funzioni private
 * @{
 */

I2C_PMD_Interface* pmdGetI2cInterfaceFromHandle(I2C_HandleTypeDef*);

/* Private Functions ***********************************************************/

/**
 * @brief Get the PMD_Interface ptr from i2c interfaces using HELPER_I2C_TypeDef
 * @param in i2c handle
 * @param in direction 1-tx 0-rx
 * @retval PMD_Interface or NULL
 */
I2C_PMD_Interface* pmdGetI2cInterfaceFromHandle(I2C_HandleTypeDef* i2c) {
	I2C_HandleTypeDef* thi2c_tx, *thi2c_rx;

	for (uint8_t i = 0; i < I2C_NUM_INTERFACES; i++) {
		thi2c_tx = HELPER_I2C_GetHandle(i2c_pmd_interfaces[i].i2c_tx);
		thi2c_rx = HELPER_I2C_GetHandle(i2c_pmd_interfaces[i].i2c_rx);
		if (thi2c_tx->Instance == i2c->Instance
				|| thi2c_rx->Instance == i2c->Instance) {
			return &i2c_pmd_interfaces[i];
		}
	}

	return NULL;
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
 * @addtogroupp CAL_PHY_PMD_I2C_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief Configure the mapping between the PMD_Interface and the actual
 * @param in pmd_ifx PMD_Interface data structure.
 * @retval PMD Status
 */
PMD_Status pmdConfigI2c(PMD_Interface* pmd_ifx) {
	if (pmd_ifx == NULL) {
		return PMD_ERROR;
	}

	calAssertTrue(PMD_isTypeI2c(pmd_ifx));

	if (pmd_ifx->id > 0 && pmd_ifx->id < I2C_NUM_INTERFACES + 1) {
		i2c_pmd_interfaces[pmd_ifx->id - 1].pmd_ifx = pmd_ifx;
		return PMD_OK;
	}

	return PMD_ERROR;
}

/**
 * @brief Initialize an I2C Interface
 * @param in pmd_ifx PMD_Interface data structure.
 * @retval PMD Status
 */
PMD_Status pmdInitI2c(PMD_Interface* pmd_ifx) {
	if (pmd_ifx == NULL) {
		return PMD_ERROR;
	}

	calAssertTrue(PMD_isTypeI2c(pmd_ifx));

	if (pmd_ifx->id > 0 && pmd_ifx->id < I2C_NUM_INTERFACES + 1) {
		I2C_PMD_Interface i2c_if = i2c_pmd_interfaces[pmd_ifx->id - 1];
		hi2c_tx[pmd_ifx->id - 1] = HELPER_I2C_GetHandle(i2c_if.i2c_tx);
		hi2c_rx[pmd_ifx->id - 1] = HELPER_I2C_GetHandle(i2c_if.i2c_rx);

		HAL_StatusTypeDef statusTx, statusRx;

		if (i2c_if.pmd_ifx != NULL) {
			statusTx = HELPER_I2C_Init(i2c_if.i2c_tx);
			statusRx = HELPER_I2C_Init(i2c_if.i2c_rx);
			if (statusTx == HAL_OK && statusRx == HAL_OK) {
				return PMD_OK;
			} else
				return PMD_ERROR;
		}
	}
	return PMD_ERROR;
}

/**
 * @brief De-initialize an I2C peripheral
 * @param in pmd_ifx PMD_Interface data structure.
 * @retval PMD Status
 */
PMD_Status pmdDeInitI2c(PMD_Interface* pmd_ifx) {
	if (pmd_ifx == NULL) {
		return PMD_ERROR;
	}

	calAssertTrue(PMD_isTypeI2c(pmd_ifx));

	if (pmd_ifx->id > 0 && pmd_ifx->id < I2C_NUM_INTERFACES + 1) {
		I2C_PMD_Interface i2c_if = i2c_pmd_interfaces[pmd_ifx->id - 1];
		HAL_StatusTypeDef statusTx, statusRx;

		if (i2c_if.pmd_ifx != NULL) {
			statusTx = HELPER_I2C_DeInit(i2c_if.i2c_tx);
			statusRx = HELPER_I2C_DeInit(i2c_if.i2c_rx);
			if (statusTx == HAL_OK && statusRx == HAL_OK) {
				return PMD_OK;
			} else
				return PMD_ERROR;
		}
	}

	return PMD_ERROR;
}

/**
 * @brief Send data using an I2C peripheral
 * @param in chunk The chunk that contains the data to send
 * @retval PMD Status
 */
PMD_Status pmdSendI2c(PMD_Chunk* chunk) {
	if (chunk->pmdIfx == NULL) {
		return PMD_ERROR;
	}

	calAssertTrue(PMD_isTypeI2c(chunk->pmdIfx));

	if (chunk->pmdIfx->id > 0 && chunk->pmdIfx->id < I2C_NUM_INTERFACES + 1) {
		i2c_pmd_interfaces[chunk->pmdIfx->id - 1].chunkToSend = chunk;
		I2C_PMD_Interface i2c_if = i2c_pmd_interfaces[chunk->pmdIfx->id - 1];

		if (i2c_if.pmd_ifx != NULL) {
			I2C_HandleTypeDef* i2c_tx = hi2c_tx[chunk->pmdIfx->id - 1];
			I2C_HandleTypeDef* i2c_rx = hi2c_rx[chunk->pmdIfx->id - 1];

			uint8_t devAddress = i2c_rx->Init.OwnAddress1;

#if (USE_DMA == 1)
			if (HAL_I2C_Master_Transmit_DMA(i2c_tx, devAddress,
					i2c_if.chunkToSend->data, CHUNK_LENGTH)
					== HAL_OK)
#else
					if (HAL_I2C_Master_Transmit_IT(i2c_tx, devAddress,
									i2c_if.chunkToSend->data, CHUNK_LENGTH) == HAL_OK)
#endif
					{
				return PMD_OK;
			} else {
				/* Error_Handler() function is called when Timeout error occurs.
				 When Acknowledge failure occurs (Slave don't acknowledge it's address)
				 Master restarts communication */
				if (HAL_I2C_GetError(i2c_tx) != HAL_I2C_ERROR_AF) {
					return PMD_ERROR;
				}
				// Send failed free the periph
				pmdChunkSentCallback(i2c_if.chunkToSend);
				return PMD_OK;
			}
		}
	}

	return PMD_ERROR;
}

/**
 * @brief Receive data using an I2C peripheral
 * @param in chunk The chunk that contains the data ptr in which save the data received
 * @retval PMD Status
 */
PMD_Status pmdReceiveI2c(PMD_Chunk* chunk) {
	if (chunk->pmdIfx == NULL) {
		return PMD_ERROR;
	}

	calAssertTrue(PMD_isTypeI2c(chunk->pmdIfx));

	if (chunk->pmdIfx->id > 0 && chunk->pmdIfx->id < I2C_NUM_INTERFACES + 1) {
		i2c_pmd_interfaces[chunk->pmdIfx->id - 1].chunkToReceive = chunk;
		I2C_PMD_Interface i2c_if = i2c_pmd_interfaces[chunk->pmdIfx->id - 1];

		if (i2c_if.pmd_ifx != NULL) {
			I2C_HandleTypeDef* i2c_rx = hi2c_rx[chunk->pmdIfx->id - 1];

#if (USE_DMA == 1)
			if (HAL_I2C_Slave_Receive_DMA_IT(i2c_rx,
					i2c_if.chunkToReceive->data,
					CHUNK_LENGTH)
					== HAL_OK)
#else
					if (HAL_I2C_Slave_Receive_IT(i2c_rx, i2c_if.chunkToReceive->data,
									CHUNK_LENGTH) == HAL_OK)
#endif
					{
				return PMD_OK;
			} else
				return PMD_ERROR;
		}
	}
	return PMD_ERROR;
}

/**
 * @}
 */

/**
 * @defgroup CAL_PHY_PMD_I2C_Callback I2C Callback
 * @brief PMD I2C Callback
 * @{
 */

/**
 * @brief MasterTransmit callback handler
 * @param hi2c I2c handler
 * @retval none
 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	I2C_PMD_Interface *i2c_ifx = pmdGetI2cInterfaceFromHandle(hi2c);
	if (i2c_ifx != NULL) {
		pmdChunkSentCallback(i2c_ifx->chunkToSend);
	}
}

/**
 * @brief SlaveReceive callback handler
 * @param hi2c I2c handler
 * @retval none
 */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	I2C_PMD_Interface *i2c_ifx = pmdGetI2cInterfaceFromHandle(hi2c);
	if (i2c_ifx != NULL) {
		pmdChunkReceivedCallback(i2c_ifx->chunkToReceive);
	}
}

/**
 * @brief Error callback handler
 * @param hi2c I2c handler
 * @retval none
 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
	I2C_PMD_Interface *i2c_ifx = pmdGetI2cInterfaceFromHandle(hi2c);
	if (i2c_ifx != NULL) {
		// Select the TX or RX peripheral
		if (HELPER_I2C_GetHandle(i2c_ifx->i2c_tx)->Instance == hi2c->Instance) {
			// The error happened on the send attempt
			pmdChunkSendErrorCallback(i2c_ifx->chunkToSend);
		} else if (HELPER_I2C_GetHandle(i2c_ifx->i2c_rx)->Instance
				== hi2c->Instance) {
			// The error happened on the receive attempt
			pmdChunkReceiveErrorCallback(i2c_ifx->chunkToReceive);
		}
	}
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

/**
 * @}
 */

