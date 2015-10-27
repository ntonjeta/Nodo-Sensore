/**
 ******************************************************************************
 * @file    stm32f4xx_hal_i2c.h
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    26-December-2014
 * @brief   Header file of I2C HAL module.
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
#ifndef __STM32F4xx_I2C_HELPER_HAL_H
#define __STM32F4xx_I2C_HELPER_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_hal_conf.h"

/** @addtogroup I2C_Helper
 * @{
 */

/** @defgroup I2C_Helper_HAL Modified HAL
 * @{
 */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup I2C_Exported_Constants I2C Exported Constants
 * @{
 */

/** @defgroup I2C_Error_Code I2C Error Code
 * @brief    I2C Error Code
 * @{
 */
/* Added PEC Error */
#define HAL_I2C_ERROR_PEC    	 ((uint32_t)0x00000030)    /*!< PEC Error          */

/**
 * @}
 */

/*******************************************************************************************/
/* New Define */
/** @defgroup I2C_pec_mode I2C pec mode
 * @{
 */
#define I2C_PECMODE_DISABLE          ((uint32_t)0x00000000)
#define I2C_PECMODE_ENABLE           I2C_CR1_ENPEC
/**
 * @}
 */
/*******************************************************************************************/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup I2C_Exported_Functions
 * @{
 */

/** @addtogroup I2C_Exported_Functions_Group2
 * @{
 */
/* I/O operation functions  *****************************************************/
/******* Blocking mode: Polling */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_withPEC(
		I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData,
		uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive_withPEC(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_withPEC(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_withPEC(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size, uint32_t Timeout);
/******* Blocking mode: Polling on the same board */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_onBoard(I2C_HandleTypeDef *hi2c_master,
		I2C_HandleTypeDef *hi2c_slave, uint8_t *txData, uint8_t *rxData,
		uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_onBoard(I2C_HandleTypeDef *hi2c_master,
		I2C_HandleTypeDef *hi2c_slave, uint8_t *txData, uint8_t *rxData,
		uint16_t Size, uint32_t Timeout);
/******* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT_withPEC(
		I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData,
		uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT_withPEC(
		I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData,
		uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT_withPEC(
		I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT_withPEC(
		I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);

/******* Non-Blocking mode: DMA */
/* New Functions *********************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA_IT(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size);
/*************************************************************************************/

/******* I2C IRQHandler and Callbacks used in non blocking modes (Interrupt and DMA) */
void I2C_HELPER_EV_IRQHandler(I2C_HandleTypeDef *hi2c);
void I2C_HELPER_ER_IRQHandler(I2C_HandleTypeDef *hi2c);
/**
 * @}
 */

/**
 * @}
 */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_I2C_HELPER_HAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
