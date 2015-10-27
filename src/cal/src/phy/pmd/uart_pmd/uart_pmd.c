/**
 ******************************************************************************
 * @file    uart_pmd.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    26/giu/2015
 * @brief   TODO
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "uart_pmd.h"

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
 * @addtogroup CAL_PHY_PMD_UART Livello UART del PMD
 * @brief Livello che gestisce periferiche di tipo UART
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/

/**
 * @defgroup CAL_PHY_PMD_UART_Private_Variables Private Variables
 * @brief PMD UART Variabili private
 * @{
 */

static USART_HandleTypeDef* huart[UART_NUM_INTERFACES]; /**< UART handles */

/**
 * @}
 */

/* Private Functions ***********************************************************/

/**
 * @defgroup CAL_PHY_PMD_UART_Private_Functions Private Functions
 * @brief PMD UART Funzioni private
 * @{
 */

/**
 * @brief Match a given id with an Uartx peripheral
 * @param	id: an id
 * @return	The HELPER_UART_Typedef of the matched peripheral or 0.
 */

HELPER_UART_TypeDef pmdUartGetNumberInterface(PMD_InterfaceId id)
{
	if (id > 0 && id < UART_NUM_INTERFACES + 1)
	{
		return uart_pmd_interfaces[id - 1].uart;
	}
	return 0;
}

UART_HandleTypeDef * pmdUartGetHandleInterface(PMD_InterfaceId id)
{
	if (id > 0 && id < UART_NUM_INTERFACES + 1)
	{
		return HELPER_UART_GetHandle(uart_pmd_interfaces[id - 1].uart);
	}
	return NULL;
}

PMD_Interface* pmdUartGetInterface(UART_HandleTypeDef *huart)
{

	if (huart == NULL)
		return NULL;
	else
	{
		UART_HandleTypeDef* thuart;

		for (uint8_t i = 0; i < UART_NUM_INTERFACES; i++)
		{
			thuart = HELPER_UART_GetHandle(uart_pmd_interfaces[i].uart);
			if (thuart->Instance == huart->Instance)
			{
				return uart_pmd_interfaces[i].pmdIfx;
			}
		}
	}

	return NULL;

}

/**
 * @}
 */

/**
 * @defgroup CAL_PHY_PMD_UART_Callback Callback
 * @brief PMD UART Callback
 * @{
 */

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

	PMD_InterfaceId id = (pmdUartGetInterface(huart))->id;
	pmdChunkSentCallback(uart_pmd_interfaces[id - 1].chunkToSend);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	PMD_InterfaceId id = (pmdUartGetInterface(huart))->id;
	pmdChunkReceivedCallback(uart_pmd_interfaces[id - 1].chunkToReceive);
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	//calUnused(huart);
	PMD_InterfaceId id = (pmdUartGetInterface(huart))->id;
	pmdChunkReceiveErrorCallback(uart_pmd_interfaces[id - 1].chunkToReceive);

//
//		PMD_Interface *ifx= uart_pmd_interfaces[id - 1].pmdIfx;
//		PMD_Chunk *chunk=uart_pmd_interfaces[id - 1].chunkToReceive;
//		pmdDeInitUart(ifx);
//		pmdInitUart(ifx);
//		pmdChunkReceiveErrorCallback(chunk);
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
 * @addtogroup CAL_PHY_PMD_UART_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/**
 * @brief Configura la periferica di tipo UART collegata ad una interfaccia
 * @param pmdIfx Puntatore all'interfaccia
 * @return PMD_Status
 */
PMD_Status pmdConfigUart(PMD_Interface* pmdIfx)
{
	if (pmdIfx == NULL)
	{
		return PMD_ERROR;
	}

	if (pmdIfx->type == PMD_UART && pmdIfx->id > 0
			&& pmdIfx->id < UART_NUM_INTERFACES + 1)
	{
		uart_pmd_interfaces[pmdIfx->id - 1].pmdIfx = pmdIfx;
		uart_pmd_interfaces[pmdIfx->id - 1].hdma_uart_tx =
				&(hdma_uart_tx[pmdIfx->id - 1]);
		uart_pmd_interfaces[pmdIfx->id - 1].hdma_uart_rx =
				&(hdma_uart_rx[pmdIfx->id - 1]);
		return PMD_OK;
	}
	else
		return PMD_ERROR;
}

/**
 * @brief Inizializza la periferica di tipo UART collegata ad una interfaccia
 * @param pmdIfx Puntatore all'interfaccia
 * @return PMD_Status
 */
PMD_Status pmdInitUart(PMD_Interface* ifx)
{
	if (ifx->id > 0 && ifx->id < UART_NUM_INTERFACES + 1)
	{
		HELPER_UART_TypeDef numUart = uart_pmd_interfaces[ifx->id - 1].uart;
		if ((HAL_StatusTypeDef)HELPER_UART_Init(numUart) == HAL_OK)
		{
			((UART_HandleTypeDef**)huart)[ifx->id - 1] = HELPER_UART_GetHandle(numUart);

			if (pmdUartUseDma(ifx->id) == 1)
				pmdUartInitDma(ifx->id);
			return PMD_OK;
		}
		else
			return PMD_ERROR;
	}

	return PMD_ERROR;
}

/**
 * @brief De-inizializza la periferica di tipo UART collegata ad una interfaccia
 * @param pmdIfx Puntatore all'interfaccia
 * @return PMD_Status
 */
PMD_Status pmdDeInitUart(PMD_Interface* ifx)
{
	PMD_InterfaceId id = ifx->id;
	HELPER_UART_TypeDef numUart = uart_pmd_interfaces[id - 1].uart;
	if (numUart != 0)
	{
		if (HELPER_UART_DeInit(numUart) == HAL_OK)
		{
			if (pmdUartUseDma(id) == 1)
				pmdUartDeInitDma(id);

			return PMD_OK;
		}
		else
			return PMD_ERROR;
	}
	else
		return PMD_ERROR;
}

/**
 * @brief Invia un chunk attraverso una periferica UART
 * @param chunk Puntatore alla struttura di chunk
 * @return PMD_Status
 */
PMD_Status pmdSendUart(PMD_Chunk* chunk)
{
	PMD_InterfaceId id = (chunk->pmdIfx->id);
	UART_HandleTypeDef *uart = (UART_HandleTypeDef*)huart[id - 1];
	if (huart != NULL)
	{
		uart_pmd_interfaces[id - 1].chunkToSend = chunk;
		HAL_StatusTypeDef status;
		if (pmdUartUseDma(id) == 1)
			status = HAL_UART_Transmit_DMA(uart, chunk->data, CHUNK_LENGTH);
		else
			status = HAL_UART_Transmit_IT(uart, chunk->data, CHUNK_LENGTH);

		if (status == HAL_OK)
			return PMD_OK;
		else
			return PMD_ERROR;
	}
	else
		return PMD_ERROR;
}

/**
 * @brief Si mette in ricezione di un chunk attraverso una periferica UART
 * @param chunk Puntatore alla struttura di chunk
 * @return PMD_Status
 */
PMD_Status pmdReceiveUart(PMD_Chunk* chunk)
{
	uint16_t id = (chunk->pmdIfx->id);
	UART_HandleTypeDef *uart = (UART_HandleTypeDef*)huart[id - 1];

	if (uart != NULL)
	{
		uart_pmd_interfaces[id - 1].chunkToReceive = chunk;
		HAL_StatusTypeDef status;
		if (pmdUartUseDma(id) == 1)
			status = HAL_UART_Receive_DMA(uart, chunk->data, CHUNK_LENGTH);
		else
			status = HAL_UART_Receive_IT(uart, chunk->data, CHUNK_LENGTH);

		if (status == HAL_OK)
			return PMD_OK;
		else
			return PMD_ERROR;
	}
	else
		return PMD_ERROR;

}

/* DMA *************************************************************************/

/**
 * @brief De-init del DMA
 * @param id : Id dell'interfaccia
 * @retval none
 */
void pmdUartDeInitDma(PMD_InterfaceId id)
{
	HAL_DMA_DeInit(uart_pmd_interfaces[id - 1].hdma_uart_tx);
	HAL_DMA_DeInit(uart_pmd_interfaces[id - 1].hdma_uart_rx);
}

/**
 * @brief Init del DMA
 * @param id : Id dell'interfaccia
 * @retval none
 */
void pmdUartInitDma(PMD_InterfaceId id)
{

	/**
	 * NOTA: la configurazione � custom per le periferiche Uart1,2,3 e Uart6.
	 * Se si desidera cambiare le periferiche � necessario cambiare il codice
	 * di configurazione del DMA (es. stream, canale, DMA1 o DMA2 etc.) e
	 * le ridefinizioni delle IRQHandler del tipo DMAx_StreamY_IRQHandler(void).
	 * Consultare il manuale per ulteriori dettagli.
	 */

	//Puntatori agli HandleTypeDef per ciascun "istanza" DMA
	DMA_HandleTypeDef *hdma_tx, *hdma_rx;
	//#IRQ
	IRQn_Type irq_tx = 100, irq_rx = 100;
	/*
	 * A seconda della periferica Uart configuro gli hdma_tx/rx in maniera opportuna.
	 * Importanti sono Instance (quindi DMAx e StreamY), Channel e IRQNumber
	 * associato allo StreamY del DMAx.
	 * (NOTA BENE: Uno stream Y non pu� essere usato da pi� di una canale sullo stesso DMAx!)
	 */

	if (uart_pmd_interfaces[id - 1].useDMA == 1)
	{
		hdma_tx = (uart_pmd_interfaces[id - 1].hdma_uart_tx);
		hdma_rx = (uart_pmd_interfaces[id - 1].hdma_uart_rx);

		switch (id)
		{
#if (UART1_ID > 0)
		case UART1_ID: // UART1
		{
			/* Enable DMA2 clock */
			__HAL_RCC_DMA2_CLK_ENABLE();

			hdma_tx->Instance = DMA2_Stream7;
			hdma_tx->Init.Channel = DMA_CHANNEL_4;
			irq_tx = DMA2_Stream7_IRQn;

			hdma_rx->Instance = DMA2_Stream2;
			hdma_rx->Init.Channel = DMA_CHANNEL_4;
			irq_rx = DMA2_Stream2_IRQn;
		}
		break;
#endif
#if (UART2_ID > 0)
		case UART2_ID: // UART2
		{
			/* Enable DMA1 clock */
			__HAL_RCC_DMA1_CLK_ENABLE();

			hdma_tx->Instance = DMA1_Stream6;
			hdma_tx->Init.Channel = DMA_CHANNEL_4;
			irq_tx = DMA1_Stream6_IRQn;

			hdma_rx->Instance = DMA1_Stream5;
			hdma_rx->Init.Channel = DMA_CHANNEL_4;
			irq_rx = DMA1_Stream5_IRQn;
		}
			break;
#endif

#if (UART3_ID > 0)
		case UART3_ID: //UART3
		{
			/* Enable DMA1 clock */
			__HAL_RCC_DMA1_CLK_ENABLE();

			hdma_tx->Instance = DMA1_Stream3;
			hdma_tx->Init.Channel = DMA_CHANNEL_4;
			irq_tx = DMA1_Stream3_IRQn;

			hdma_rx->Instance = DMA1_Stream1;
			hdma_rx->Init.Channel = DMA_CHANNEL_4;
			irq_rx = DMA1_Stream1_IRQn;
		}
			break;
#endif

#if 0
			case UART_IF4_ID:
			{
				//DMA On UART4 Can't be used in this release.
			}
			break;
#endif
#if 0
			case UART_IF5_ID:
			{
				//DMA On UART5 Can't be used in this release.
			}
			break;
#endif

#if (UART6_ID > 0)
		case UART6_ID: //UART6
		{
			/* Enable DMA2 clock */
			__HAL_RCC_DMA2_CLK_ENABLE();

			hdma_rx->Instance = DMA2_Stream1;
			hdma_rx->Init.Channel = DMA_CHANNEL_5;
			irq_tx = DMA2_Stream1_IRQn;

			hdma_tx->Instance = DMA2_Stream6;
			hdma_tx->Init.Channel = DMA_CHANNEL_5;
			irq_rx = DMA2_Stream6_IRQn;
		}
			break;
#endif
		default:
			return ; // Error
			break;
		}

		/*
		 * Creo il vettore di DMA_HandleTypeDef perch� essendo le configurazioni per rx e tx
		 * quasi simili allora conviene configurare in un ciclo iterativo.
		 */

		DMA_HandleTypeDef* hdma_vett[2] =
		{ hdma_tx, hdma_rx };

		/*##-1- Configure the DMA streams ##########################################*/
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				//Caso hdma_tx
				hdma_vett[i]->Init.Direction = DMA_MEMORY_TO_PERIPH;
				hdma_vett[i]->Init.Priority = DMA_PRIORITY_LOW;
			}
			else
			{ //Caso hdma_rx
				hdma_vett[i]->Init.Direction = DMA_PERIPH_TO_MEMORY;
				hdma_vett[i]->Init.Priority = DMA_PRIORITY_HIGH;
			}
			//Parametri configurazione DMA: modalit� Normal, single transfer.
			hdma_vett[i]->Init.PeriphInc = DMA_PINC_DISABLE;
			hdma_vett[i]->Init.MemInc = DMA_MINC_ENABLE;
			hdma_vett[i]->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
			hdma_vett[i]->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
			hdma_vett[i]->Init.Mode = DMA_NORMAL;
			hdma_vett[i]->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
			hdma_vett[i]->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
			hdma_vett[i]->Init.MemBurst = DMA_MBURST_SINGLE;
			hdma_vett[i]->Init.PeriphBurst = DMA_PBURST_SINGLE;

			HAL_DMA_Init(hdma_vett[i]);

			/* Associate the initialized DMA handle to the the UART handle */
			HELPER_UART_TypeDef numUart = pmdUartGetNumberInterface(id);
			if (i == 0)
				__HAL_LINKDMA((HELPER_UART_GetHandle(numUart)), hdmatx,
						*(hdma_vett[i]));
			else
				__HAL_LINKDMA((HELPER_UART_GetHandle(numUart)), hdmarx,
						*(hdma_vett[i]));
		}

		/*##-2- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for DMA transfer/Receive complete interrupt */
		HAL_NVIC_SetPriority(irq_tx, UART_DMA_TX_PRIO, UART_DMA_TX_SUBPRIO);
		HAL_NVIC_EnableIRQ(irq_tx);
		HAL_NVIC_SetPriority(irq_rx, UART_DMA_RX_PRIO, UART_DMA_RX_SUBPRIO);
		HAL_NVIC_EnableIRQ(irq_rx);
	}
}

uint8_t pmdUartUseDma(PMD_InterfaceId id)
{
	if (id > 0 && id < UART_NUM_INTERFACES + 1)
		return (uart_pmd_interfaces[id - 1].useDMA == 1);

	return 0;
}

#if (UART1_USE_DMA > 0 && UART1_ID > 0)
void DMA2_Stream7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART1)->hdmatx);
}

void DMA2_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART1)->hdmarx);
}
#endif

#if (UART2_USE_DMA>0 && UART2_ID > 0)
void DMA1_Stream6_IRQHandler(void)
{
	//printf("\r\nDMAU2 Tx Callback!\n");
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART2)->hdmatx);
}

void DMA1_Stream5_IRQHandler(void)
{
	//printf("\r\nDMAU2 Rx Callback!\n");
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART2)->hdmarx);
}
#endif

#if (UART3_USE_DMA>0 && UART3_ID > 0)
void DMA1_Stream3_IRQHandler(void)
{
	//printf("\r\nDMAU3 Tx Callback!\n");
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART3)->hdmatx);
}

void DMA1_Stream1_IRQHandler(void)
{
	//printf("\r\nDMAU3 Rx Callback!\n");
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART3)->hdmarx);
}
#endif

#if (UART6_USE_DMA>0 && UART6_ID > 0)

void DMA2_Stream1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART6)->hdmarx);
}

void DMA2_Stream6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(HELPER_UART_GetHandle(HELPER_UART6)->hdmatx);
}

#endif

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
