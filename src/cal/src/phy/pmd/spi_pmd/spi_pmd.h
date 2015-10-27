/**
  ******************************************************************************
  * @file    spi_pmd.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    28/giu/2015
  * @brief   TODO: brief for spi_pmd.h
  ******************************************************************************
  */
#ifndef CAL_SRC_PHY_PMD_SPI_PMD_SPI_PMD_H_
#define CAL_SRC_PHY_PMD_SPI_PMD_SPI_PMD_H_

/* Includes ********************************************************************/
#include "pmd.h"
#include "../lib/spi_helper/include/stm32f4xx_spi_helper.h"

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
 * @defgroup CAL_PHY_PMD_SPI Livello SPI del PMD
 * @brief Livello che gestisce periferiche di tipo SPI
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_PHY_PMD_SPI_Exported_Constants Exported Constants
 * @brief PMD SPI Costanti Esportate
 * @{
 */

#define SPI_IF1_ID					1								//!< configure the interface on the PLCP id number 1
#define SPI_IF1_TX					HELPER_SPI2						//!< use SPI2 for tx
#define SPI_IF1_RX					HELPER_SPI3						//!< use SPI3 for rx

// ----- DMA Configuration -----
#define SPI_IF1_USE_DMA				1								//!< set 1 (dma enabled) or 0 (dma disabled). If dma is disabled, the IT Mode will be used
#define SPI_IF1_DMA_TX_CLK_EN()		__HAL_RCC_DMA1_CLK_ENABLE()		//!< set the clock enable on DMAx
#define SPI_IF1_DMA_TX_STREAM		DMA1_Stream4					//!< set the dma tx stream
#define SPI_IF1_DMA_TX_CHANNEL		DMA_CHANNEL_0					//!< set the dma tx channel
#define SPI_IF1_DMA_TX_IRQn			DMA1_Stream4_IRQn				//!< set the dma IRQn on the selected stream
#define SPI_IF1_DMA_TX_IRQHandler	DMA1_Stream4_IRQHandler			//!< set the dma IRQHandler
#define SPI_IF1_DMA_TX_INT_PRI		0x02							//!< set the dma interrupt priority
#define SPI_IF1_DMA_TX_INT_SUBPRI	0								//!< set the dma interrupt sub priority

#define SPI_IF1_DMA_RX_CLK_EN()		__HAL_RCC_DMA1_CLK_ENABLE()		//!< set the clock enable on DMAx
#define SPI_IF1_DMA_RX_STREAM		DMA1_Stream0					//!< set the dma RX stream
#define SPI_IF1_DMA_RX_CHANNEL		DMA_CHANNEL_0					//!< set the dma RX channel
#define SPI_IF1_DMA_RX_IRQn			DMA1_Stream0_IRQn				//!< set the dma IRQn on the selected stream
#define SPI_IF1_DMA_RX_IRQHandler	DMA1_Stream0_IRQHandler			//!< set the dma IRQHandler on the selected stream
#define SPI_IF1_DMA_RX_INT_PRI		0x02							//!< set the dma interrupt priority
#define SPI_IF1_DMA_RX_INT_SUBPRI	0								//!< set the dma interrupt sub priority

// ----- IT Mode configuration -----
#define SPI_IF1_TX_IRQn				SPI2_IRQn
#define SPI_IF1_RX_IRQn				SPI3_IRQn

/**
 * @}
 */

/* Exported Macros *************************************************************/

/**
 * @defgroup CAL_PHY_PMD_SPI_Exported_Macros Exported Macros
 * @brief PMD SPI Macro esportate
 * @{
 */

#define PMD_isTypeSpi(ptr)			PMD_isType(ptr,PMD_SPI)

/**
 * @}
 */

/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_PHY_PMD_SPI_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

PMD_Status pmdConfigSpi(PMD_Interface* ifx);
PMD_Status pmdInitSpi(PMD_Interface* ifx);
PMD_Status pmdDeInitSpi(PMD_Interface* ifx);
PMD_Status pmdSendSpi(PMD_Chunk* chunk);
PMD_Status pmdReceiveSpi(PMD_Chunk* chunk);

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

#endif /* CAL_SRC_PHY_PMD_SPI_PMD_SPI_PMD_H_ */
