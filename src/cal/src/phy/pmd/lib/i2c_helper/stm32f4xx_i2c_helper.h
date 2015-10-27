/**
 ******************************************************************************
 * @file    stm32f4xx_i2c_helper.h
 * @author  Federico Iannucci - SE4
 * @version V0.3
 * @date    17-April-2015
 * @brief   I2C Helper Header File
 *          This file contains all base definition.
 *          This file is the only to be included.

 @verbatim
 ===============================================================================
 ##### I2C Helper Configuration #####
 ===============================================================================
 To use I2C HELPER include the stm32f4xx_i2c_helper.h in your file, create
 a stm32f4xx_i2c_helper_conf.h (you can use the template .example) header
 file and make sure that it's in a "include" directory.
 [..] In order to use an I2C component, you need to (for each component) :
 (+) Configure the desired peripheral by using the defines into the stm32f4xx_i2c_helper_conf.h:
 (++) Communication Speed
 (++) Duty cycle
 (++) Addressing mode
 (++) Own Address 1
 (++) Dual Addressing mode
 (++) Own Address 2
 (++) General call mode
 (++) Nostretch mode
 (+) Call the @ref HELPER_I2C_Init passing the reference (@ref HELPER_I2C_TypeDef) to the peripheral desired.
 Example :
 @endverbatim
 @code {.c}
 Example :
 // Init the I2C peripheral number 2 (I2C2)
 if (HELPER_I2C_Init(HELPER_I2C2) != HAL_OK)
 {
 // do something if errors
 }
 @endcode
 @verbatim
 ===============================================================================
 ##### I2C Helper I/O Operations #####
 ===============================================================================
 [..] When the peripheral is configured, you can get the internal managed handler
 and use the HAL functions for I/O operations

 @ref stm32f4xx_hal_i2c.h

 (+)Polling Examples :
 @endverbatim
 @code {.c}

 // get the internal managed handler from the SPI Helper Module
 I2C_HandleTypeDef* I2c1Handle = HELPER_I2C_GetHandle(HELPER_I2C2);

 uint8_t *txBuffer;

 while (HAL_I2C_Master_Transmit(&I2c1Handle, (uint16_t) DevAddress,
 (uint8_t*) pData, TXBUFFERSIZE, (uint32_t) Timeout) != HAL_OK) {
 // When Acknowledge failure occurs is because
 // Slave don't acknowledge it's address!
 if (HAL_I2C_GetError(&I2cHandle) != HAL_I2C_ERROR_AF) {
 // Some error occured.
 }
 }
 while (HAL_I2C_Slave_Transmit(&I2c1Handle, (uint8_t*) txBuffer, RXBUFFERSIZE,
 10000) != HAL_OK) {
 //Some error occured.
 }
 @endcode
 @verbatim

 (+)Interrupt Examples:
 In order to use the interrupts, set the correspondent flag (EV and ER) and define one of
 these in your application, as your need :
 @endverbatim
 @code {.c}
 void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
 void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
 void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
 void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
 void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);
 void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c);
 void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
 @endcode
 @verbatim
 Usage :
 @endverbatim
 @code {.c}

 // get the internal managed handler from the SPI Helper Module
 I2C_HandleTypeDef* I2c1Handle = HELPER_I2C_GetHandle(HELPER_I2C2);

 while (HAL_I2C_Master_Transmit_IT(&I2c1Handle,
 (uint16_t) I2C_HELPER_I2Cx_ADDRESS, (uint8_t*) txBuffer, TXBUFFERSIZE)
 != HAL_OK) {
 if (HAL_I2C_GetError(&I2c1Handle) != HAL_I2C_ERROR_AF) {
 teardown();
 }
 }
 or
 if (HAL_I2C_Slave_Receive_IT(&I2c1Handle, (uint8_t *) sRxData,
 RXBUFFERSIZE) != HAL_OK) {
 //Transfer error in reception process
 teardown();
 }
 // Wait before another transmission
 while (HAL_I2C_GetState(&I2c1Handle) != HAL_I2C_STATE_READY) {
 }
 @endcode

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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_I2C_HELPER_H
#define __STM32F4xx_I2C_HELPER_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_i2c_helper_hal.h"
#include "../conf/stm32f4xx_i2c_helper_conf.h"
//#include "stm32f4xx_i2c_self/stm32f4xx_self_i2c.h"

/** @defgroup STM32F4xx_Helper_Library Helper Library
 * @brief STM32F4xx Peripheral Helper library
 * @{
 */

/** @defgroup I2C_Helper I2C Helper
 * @brief I2C Helper Module
 * @{
 */

/* Exported variable ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/**
 * @defgroup I2C_Helper_Exported_Types Exported Types
 * @brief The @ref HELPER_I2C_TypeDef should be used by the user to refer to the specific peripheral to configure, instantiate and to work with.
 * @{
 */
typedef enum
{
	HELPER_I2C1 = 1,
	HELPER_I2C2 = 2,
	HELPER_I2C3 = 3
}HELPER_I2C_TypeDef;
/**
 * @}
 */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
 * @defgroup SPI_Helper_Exported_Functions Exported Functions
 * @brief These functions can be used by the final user in order to initialize the I2C peripheral according to the configuration file stm32f4xx_i2c_helper_conf.h
 * @{
 */

I2C_HandleTypeDef* HELPER_I2C_GetHandle(HELPER_I2C_TypeDef HELPER_I2Cx);
HELPER_I2C_TypeDef HELPER_I2C_GetNum(I2C_HandleTypeDef* hi2c);
HAL_StatusTypeDef HELPER_I2C_Init(HELPER_I2C_TypeDef HELPER_I2Cx);
HAL_StatusTypeDef HELPER_I2C_DeInit(HELPER_I2C_TypeDef HELPER_I2Cx);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
