/**
  ******************************************************************************
  * @file    spi_pmd.c
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    26/giu/2015
  * @brief   TODO: brief for spi_pmd.c
  ******************************************************************************
  */

/* Includes ********************************************************************/
#include "spi_pmd.h"

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
 * @addtogroup CAL_PHY_PMD_SPI Livello SPI del PMD
 * @brief Livello che gestisce periferiche di tipo SPI
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/

/* Private Variables ***********************************************************/

/**
 * @defgroup CAL_PHY_PMD_SPI_Private_Variables Private Variables
 * @brief Variabili private
 * @{
 */

// Chi scrive il port, sa quante interfacce vuole mettere a disposizione e conserva i puntatori
static PMD_Interface* ptrIf1;
static PMD_Chunk* ptrIf1TxChunk;
static PMD_Chunk* ptrIf1RxChunk;

static SPI_HandleTypeDef* spiTxHandle;
static SPI_HandleTypeDef* spiRxHandle;

#if SPI_IF1_USE_DMA == 1
	static DMA_HandleTypeDef dmaTx;
	static DMA_HandleTypeDef dmaRx;
#endif

/**
 * @}
 */

/* Private Functions ***********************************************************/

/**
 * @defgroup CAL_PHY_PMD_SPI_Private_Functions Private Functions
 * @brief Funzioni private
 * @{
 */

static PMD_Status halStatusToPmdStatus(HAL_StatusTypeDef hs)
{
	switch (hs)
	{
	case HAL_OK:
		return PMD_OK;
		break;
	case HAL_ERROR:
		return PMD_ERROR;
		break;
	case HAL_BUSY:
		return PMD_BUSY;
		break;
	case HAL_TIMEOUT:
		return PMD_TIMEOUT;
		break;
	default:
		// This default will never reached
		return PMD_ERROR;
		break;
	}
}

#if SPI_IF1_USE_DMA == 1

// Call the HAL_DMA_IRQHandler on the dma TX and RX interrupts
void SPI_IF1_DMA_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(spiTxHandle->hdmatx);
}

void SPI_IF1_DMA_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(spiRxHandle->hdmarx);
}

#endif

/**
 * @}
 */

/**
 * @defgroup CAL_PHY_PMD_SPI_Callback SPI Callback
 * @brief PMD SPI Callback
 * @{
 */

// The HAL_RxCpltCallback will be called by the HAL on both DMA or IT mode
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi)
{
	if (hspi == spiRxHandle)
	{
		// il data del chunk è stato riempito dall'hal
		pmdChunkReceivedCallback(ptrIf1RxChunk);
	}
}

// The HAL_TxCpltCallback will be called by the HAL on both DMA or IT mode
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi)
{
	if (hspi == spiTxHandle)
	{
		// il data del chunk è stato riempito dall'hal
		pmdChunkSentCallback(ptrIf1TxChunk);
	}
}

// The HAL_SPI_ErrorCallback will be called when an error will occur on both RX or TX and on both DMA or IT mode
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef* hspi)
{
	// Select the TX or RX peripheral
	if (hspi->Instance == spiTxHandle->Instance)
	{
		// The error happened on the send attempt
		pmdChunkSendErrorCallback(ptrIf1TxChunk);
	} else if (hspi->Instance == spiRxHandle->Instance)
	{
		// The error happened on the receive attempt
		pmdChunkReceiveErrorCallback(ptrIf1RxChunk);
	}
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
 * @addtogroup CAL_PHY_PMD_SPI_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

PMD_Status pmdConfigSpi(PMD_Interface* pmdifx)
{
	calAssertTrue(PMD_isTypeSpi(pmdifx));

	// il livello PLCP mi fornirà l'interfaccia con id 1, dato che SPI_NUM_INTERFACES=1
	if (pmdifx->id == SPI_IF1_ID)
	{
		// questo puntatore sarà restituito al livello PLCP in fase di ricezione
		ptrIf1 = pmdifx;

		return PMD_OK;
	}

	return PMD_ERROR;
}

PMD_Status pmdInitSpi(PMD_Interface* pmdifx)
{
	calAssertTrue(PMD_isTypeSpi(pmdifx));

	// Qua inizializzerò l'interfaccia SPI
	// Siccome SPI necessita di due periferiche, inizializzerà le due periferiche
	if (pmdifx==ptrIf1) // la chiamata a portSpiInit avviene dopo quella portSpiConfig (ho già salvato il puntatore)
	{
		HAL_StatusTypeDef status,status_tx,status_rx;

		// initialize the peripherals
		status_tx = HELPER_SPI_Init(SPI_IF1_TX);
		status_rx = HELPER_SPI_Init(SPI_IF1_RX);
		if (status_tx != HAL_OK || status_rx != HAL_OK){
			return PMD_ERROR;
		}

		// get handlers
		spiTxHandle = HELPER_SPI_GetHandle(SPI_IF1_TX);
		spiRxHandle = HELPER_SPI_GetHandle(SPI_IF1_RX);

		// initialize the DMA if configured
		if (SPI_IF1_USE_DMA==1)
		{
			// if the DMA is enabled, disable the peripheral interrupts
			HAL_NVIC_DisableIRQ(SPI_IF1_TX_IRQn);
			HAL_NVIC_DisableIRQ(SPI_IF1_RX_IRQn);

			// ***** initialize the tx dma ******
			SPI_IF1_DMA_TX_CLK_EN();

			dmaTx.Instance                 = SPI_IF1_DMA_TX_STREAM;
			dmaTx.Init.Channel             = SPI_IF1_DMA_TX_CHANNEL;
			dmaTx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
			dmaTx.Init.PeriphInc           = DMA_PINC_DISABLE;
			dmaTx.Init.MemInc              = DMA_MINC_ENABLE;
			dmaTx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
			dmaTx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
			dmaTx.Init.Mode                = DMA_NORMAL;
			dmaTx.Init.Priority            = DMA_PRIORITY_LOW;
			dmaTx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
			dmaTx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
			dmaTx.Init.MemBurst            = DMA_MBURST_INC4;
			dmaTx.Init.PeriphBurst         = DMA_PBURST_INC4;

			status = HAL_DMA_Init(&dmaTx);
			__HAL_LINKDMA(spiTxHandle, hdmatx, dmaTx);
			HAL_NVIC_SetPriority(SPI_IF1_DMA_TX_IRQn, SPI_IF1_DMA_TX_INT_PRI, SPI_IF1_DMA_TX_INT_SUBPRI);
			HAL_NVIC_EnableIRQ(SPI_IF1_DMA_TX_IRQn);

			// ***** initialize the rx dma ******
			SPI_IF1_DMA_RX_CLK_EN();

			dmaRx.Instance                 = SPI_IF1_DMA_RX_STREAM;
			dmaRx.Init.Channel             = SPI_IF1_DMA_RX_CHANNEL;
			dmaRx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
			dmaRx.Init.PeriphInc           = DMA_PINC_DISABLE;
			dmaRx.Init.MemInc              = DMA_MINC_ENABLE;
			dmaRx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
			dmaRx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
			dmaRx.Init.Mode                = DMA_NORMAL;
			dmaRx.Init.Priority            = DMA_PRIORITY_HIGH;
			dmaRx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
			dmaRx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
			dmaRx.Init.MemBurst            = DMA_MBURST_INC4;
			dmaRx.Init.PeriphBurst         = DMA_PBURST_INC4;

			status = HAL_DMA_Init(&dmaRx);
			__HAL_LINKDMA(spiRxHandle, hdmarx, dmaRx);
			HAL_NVIC_SetPriority(SPI_IF1_DMA_RX_IRQn, SPI_IF1_DMA_RX_INT_PRI, SPI_IF1_DMA_RX_INT_SUBPRI);
			HAL_NVIC_EnableIRQ(SPI_IF1_DMA_RX_IRQn);
		}
		return halStatusToPmdStatus(status);
	}

	return PMD_ERROR;
}

PMD_Status pmdDeInitSpi(PMD_Interface* pmdifx)
{
	calAssertTrue(PMD_isTypeSpi(pmdifx));

	if (pmdifx == ptrIf1)
	{
		HAL_StatusTypeDef status;
		status = HELPER_SPI_DeInit(SPI_IF1_TX);
		status = HELPER_SPI_DeInit(SPI_IF1_RX);

		if (SPI_IF1_USE_DMA == 1)
		{
			status = HAL_DMA_DeInit(&dmaTx);
			status = HAL_DMA_DeInit(&dmaRx);

			HAL_NVIC_DisableIRQ(SPI_IF1_DMA_TX_IRQn);
			HAL_NVIC_DisableIRQ(SPI_IF1_DMA_RX_IRQn);
		}

		return halStatusToPmdStatus(status);
	}
	return PMD_ERROR;
}

PMD_Status pmdSendSpi(PMD_Chunk* chunk)
{
	calAssertTrue(PMD_isTypeSpi(chunk->pmdIfx));

	if (chunk->pmdIfx == ptrIf1)
	{
		ptrIf1TxChunk = chunk;

		HAL_StatusTypeDef status;

		// Enable the chunk receipt
		if (SPI_IF1_USE_DMA == 1)
		{
			status = HAL_SPI_Transmit_DMA(spiTxHandle, ptrIf1TxChunk->data,
					CHUNK_LENGTH);
		}
		else
		{
			status = HAL_SPI_Transmit_IT(spiTxHandle, ptrIf1TxChunk->data,
					CHUNK_LENGTH);
		}

		return halStatusToPmdStatus(status);
	}

	return PMD_ERROR;
}

PMD_Status pmdReceiveSpi(PMD_Chunk* chunk)
{
	calAssertTrue(PMD_isTypeSpi(chunk->pmdIfx));

	if (chunk->pmdIfx == ptrIf1)
	{
		// copio il chunk nel ptr locale (così che nella callback del DMA posso restituirlo)
		ptrIf1RxChunk = chunk;

		// declare the status
		HAL_StatusTypeDef status;

		// Enable the chunk receipt
		if (SPI_IF1_USE_DMA == 1)
		{
			status = HAL_SPI_Receive_DMA(spiRxHandle, ptrIf1RxChunk->data,
					CHUNK_LENGTH);
		}
		else
		{
			status = HAL_SPI_Receive_IT(spiRxHandle, ptrIf1RxChunk->data,
					CHUNK_LENGTH);
		}

		return halStatusToPmdStatus(status);
	}
	return PMD_ERROR;
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
