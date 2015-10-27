/**
 ******************************************************************************
 * @file    uart_pmd.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   TODO: brief for uart_pmd.h
 ******************************************************************************
 */
#ifndef CAL_SRC_PHY_PMD_UART_PMD_UART_PMD_H_
#define CAL_SRC_PHY_PMD_UART_PMD_UART_PMD_H_

/* Includes ********************************************************************/
#include "pmd.h"
#include "../lib/uart_helper/stm32f4xx_uart_helper.h"

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
 * @defgroup CAL_PHY_PMD_UART Livello UART del PMD
 * @brief Livello che gestisce periferiche di tipo UART
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_PHY_PMD_UART_Exported_Constants Exported Constants
 * @brief PMD UART Costanti Esportate
 * @{
 */

// il porting di UART ha dichiarato di esporre una sola interfaccia di comunicazione al livello PLCP (dichiarato in port_conf.h)
// le interfacce dichiarate sono identificate sequenzialmente dal livello PLCP da 1 a UART_NUM_INTERFACES
// UARTx_ID = 0 => UARTx non attiva; UARTx_ID = 0 => UARTx attiva.
//NOTA: GLI ID DEVONO ESSERE UNIVOCI, SEQUENZIALI E DEVONO RISPETTARE L'ORDINE DI ASSEGNAMENTO DELL'UART_INTERFACES_VECTOR!
#define UART1_ID				0
#define UART2_ID				1
#define UART3_ID				2
#define UART4_ID				0
#define UART5_ID				0
#define UART6_ID				3

#define UART1_USE_DMA		0
#define UART2_USE_DMA		1
#define UART3_USE_DMA		1
#define UART4_USE_DMA		0 //!< MUST BE KEPT TO 0! (not implemented yet - highly related to other PMD DMA Configurations)
#define UART5_USE_DMA		0 //!< MUST BE KEPT TO 0! (not implemented yet - highly related to other PMD DMA Configurations)
#define UART6_USE_DMA		1


#define UART_DMA_TX_PRIO		0x02
#define UART_DMA_TX_SUBPRIO		1
#define UART_DMA_RX_PRIO		0x02
#define UART_DMA_RX_SUBPRIO		0

/**
 * @}
 */

/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/

/**
 * @defgroup CAL_PHY_PMD_UART_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief UART PMD Interface type
 */
typedef struct
{
	PMD_Interface* pmdIfx;
	HELPER_UART_TypeDef uart;
	DMA_HandleTypeDef *hdma_uart_tx;
	DMA_HandleTypeDef *hdma_uart_rx;
	uint8_t useDMA;
	PMD_Chunk* chunkToSend;
	PMD_Chunk* chunkToReceive;
} UART_PMD_Interface;

/**
 * @}
 */
/* Exported Variables **********************************************************/

/**
 * @defgroup CAL_PHY_PMD_UART_Exported_Variables Exported Variables
 * @brief Variabili esportate
 * @{
 */

static DMA_HandleTypeDef hdma_uart_tx[UART_NUM_INTERFACES];
static DMA_HandleTypeDef hdma_uart_rx[UART_NUM_INTERFACES];

/**
 * @brief Local Uart interfaces vector.
 */
static UART_PMD_Interface uart_pmd_interfaces[UART_NUM_INTERFACES] =
{
//	{ NULL, HELPER_UART4, NULL, NULL, UART4_USE_DMA, NULL, NULL },
	{ NULL, HELPER_UART2, NULL, NULL, UART2_USE_DMA, NULL, NULL },
	{ NULL, HELPER_UART3, NULL, NULL, UART3_USE_DMA, NULL, NULL },
	{ NULL, HELPER_UART6, NULL, NULL, UART6_USE_DMA, NULL, NULL },
//	{ NULL, HELPER_UART5, NULL, NULL, UART5_USE_DMA, NULL, NULL },
//	{ NULL, HELPER_UART1, NULL, NULL, UART1_USE_DMA, NULL, NULL },
//	{ NULL, HELPER_UARTx, NULL, NULL, UARTx_USE_DMA, NULL, NULL } and be sure that UARTx_ID is correct
};

/**
 * @}
 */

/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_PHY_PMD_UART_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

PMD_Status pmdConfigUart(PMD_Interface* ifx);
PMD_Status pmdSendUart(PMD_Chunk* chunk);
PMD_Status pmdInitUart(PMD_Interface* ifx);
PMD_Status pmdDeInitUart(PMD_Interface* ifx);
PMD_Status pmdReceiveUart(PMD_Chunk* chunk);

uint8_t pmdUartUseDma(PMD_InterfaceId id);
void pmdUartInitDma(PMD_InterfaceId id);
void pmdUartDeInitDma(PMD_InterfaceId id);

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
#endif /* CAL_SRC_PHY_PMD_UART_PMD_UART_PMD_H_ */
