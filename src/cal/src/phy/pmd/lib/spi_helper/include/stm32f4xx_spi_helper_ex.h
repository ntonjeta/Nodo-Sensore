/* @file    stm32f4xx_i2c_conf.h
 * @author  Giovanni Di Fiore - SE4
 * @version V0.1
 * @date    17-April-2015
 * @brief   PPP  file
 *          This file should be modified by the user when it's necessary. The
 *          file contains configuration defines
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/**
 @verbatim
 ===============================================================================
 ##### SPI Helper Example of use ####
 ===============================================================================
 [..] In order to use a SPI component, you need to:
 (+) Configure the desired peripheral by using the defines into the stm32f4xx_spi_helper_conf.h:
  (++) Mode (master or slave)
  (++) Baudrate prescaler
  (++) Direction
  (++) Clock phase
  (++) Clock polarity
  (++) CRC calculation
  (++) CRC polinomyal
  (++) Data size
  (++) First bit (MSB or LSB)
  (++) Slave select management
  (++) TI mode
 (+) Call the @ref HELPER_SPI_Init passing the reference (@ref HELPER_SPI_TypeDef) to the peripheral desired.

 Example :
 // Init the SPI peripheral number 2 (SPI2)
 if (HELPER_SPI_Init(HELPER_SPI2) != HAL_OK)
 {
	// do something if errors
 }

 ===============================================================================
 ##### SPI Helper I/O Operations #####
 ===============================================================================
 [..] When the peripheral is configured, you can get the internal managed handler and use the HAL functions for I/O operations
 
 Example:
 
 // get the internal managed handler from the SPI Helper Module
 SPI_HandleTypeDef* SpiHandle2 = HELPER_SPI_GetHandle(HELPER_SPI2);
 
 // perform the transmit operation provided into the HAL by using the handle
 HAL_SPI_Transmit(SpiHandle2, uint8_t *pData, uint16_t Size, uint32_t Timeout);
 
 @endverbatim
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_SPI_HELPER_EX_H
#define __STM32F4xx_SPI_HELPER_EX_H

/** @defgroup STM32F4xx_Helper_Library Helper Library
 * @brief STM32F4xx Peripheral Helper library
 * @{
 */
 
 /** @defgroup SPI_Helper SPI Helper
 * @brief	This module helps the user to use (configure, initialize and process) the SPI
 *			peripherals on STM32F4xx boards giving a simple interface with just two functions: the first one used
 *			for the initialization, and the second one used to get the internal managed handler.
 *			
 * @{
 */

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/


/**
 * @defgroup SPI_Helper_Exported_Functions_Extended Extended Functions
 * @brief These functions can be used by the final user in order to initialize the SPI peripheral according to the configuration file stm32f4xx_spi_helper_conf.h
 * @{
 */
 
HAL_StatusTypeDef	HELPER_SPI_HalfDuplex_OnBoard_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef 	HELPER_SPI_MasterReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pRxData, uint16_t Size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
 
 /**
 * @}
 */

#endif /* __STM32F4xx_SPI_HELPER_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
