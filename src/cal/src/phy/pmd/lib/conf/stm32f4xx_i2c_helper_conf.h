/**
 ******************************************************************************
 * @file    stm32f4xx_i2c_helper_conf.h
 * @author  Federico Iannucci - SE4
 * @version V0.3
 * @date    17-April-2015
 * @brief   I2C Configuration file
 *          This file is the only that SHOULD be modified by the user when
 *          it's necessary.
 *          This file contains the default configuration settings.
 *			Remove .example to use it.
 *

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
#ifndef __STM32F4xx_I2C_HELPER_CONF_H
#define __STM32F4xx_I2C_HELPER_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef uint8_t I2C_Address;

/* Exported constants --------------------------------------------------------*/
/* TX/RX buffer size */
#define TXBUFFERSIZE								50
#define RXBUFFERSIZE								TXBUFFERSIZE

/* I2Cx Configuration --------------------------------------------------------*/
/* I2C1 Configuration (Alternatives) */
#define I2C_HELPER_I2C1_CLOCK_SPEED					400000 /* in Hz */
#define I2C_HELPER_I2C1_DUTY_CYCLE					I2C_DUTYCYCLE_16_9 /*(I2C_DUTYCYCLE_2)*/
#define I2C_HELPER_I2C1_ADDRESSING_MODE				I2C_ADDRESSINGMODE_7BIT /*(I2C_ADDRESSINGMODE_10BIT)*/
#define I2C_HELPER_I2C1_OWN_ADDRESS_1				0x0A /* 7 or 10 bit*/
#define I2C_HELPER_I2C1_DUAL_ADDRESSING				I2C_DUALADDRESS_DISABLED /*(I2C_DUALADDRESS_ENABLE)*/
#define I2C_HELPER_I2C1_OWN_ADDRESS_2				0x0A /* 7 or 10 bit*/
#define I2C_HELPER_I2C1_GENERAL_CALL_MODE			I2C_GENERALCALL_DISABLED /*(I2C_GENERALCALL_ENABLE)*/
#define I2C_HELPER_I2C1_NO_STRETCH_MODE				I2C_NOSTRETCH_DISABLED /*(I2C_NOSTRETCH_ENABLE)*/
#define I2C_HELPER_I2C1_PEC_MODE					I2C_PECMODE_DISABLE /*(I2C_PECMODE_DISABLE)*/
/* I2C2 Configuration (same as I2C1) */
#define I2C_HELPER_I2C2_CLOCK_SPEED					400000 /* in Hz */
#define I2C_HELPER_I2C2_DUTY_CYCLE					I2C_DUTYCYCLE_16_9
#define I2C_HELPER_I2C2_ADDRESSING_MODE				I2C_ADDRESSINGMODE_7BIT
#define I2C_HELPER_I2C2_OWN_ADDRESS_1				0x0E
#define I2C_HELPER_I2C2_DUAL_ADDRESSING				I2C_DUALADDRESS_DISABLED
#define I2C_HELPER_I2C2_OWN_ADDRESS_2				0x0E
#define I2C_HELPER_I2C2_GENERAL_CALL_MODE			I2C_GENERALCALL_DISABLED
#define I2C_HELPER_I2C2_NO_STRETCH_MODE				I2C_NOSTRETCH_DISABLED
#define I2C_HELPER_I2C2_PEC_MODE					I2C_PECMODE_DISABLE /*(I2C_PECMODE_DISABLE)*/
/* I2C3 Configuration (same as I2C1) */
#define I2C_HELPER_I2C3_CLOCK_SPEED					400000 /* in Hz */
#define I2C_HELPER_I2C3_DUTY_CYCLE					I2C_DUTYCYCLE_16_9
#define I2C_HELPER_I2C3_ADDRESSING_MODE				I2C_ADDRESSINGMODE_7BIT
#define I2C_HELPER_I2C3_OWN_ADDRESS_1				0x0C
#define I2C_HELPER_I2C3_DUAL_ADDRESSING				I2C_DUALADDRESS_DISABLED
#define I2C_HELPER_I2C3_OWN_ADDRESS_2				0x0C
#define I2C_HELPER_I2C3_GENERAL_CALL_MODE			I2C_GENERALCALL_DISABLED
#define I2C_HELPER_I2C3_NO_STRETCH_MODE				I2C_NOSTRETCH_DISABLED
#define I2C_HELPER_I2C3_PEC_MODE					I2C_PECMODE_DISABLE /*(I2C_PECMODE_DISABLE)*/

/* Interrupt enabler flags, 0-No 1-Yes
 * EV : Event.
 * ER : Error.
 */
#define I2C_HELPER_I2C1_EV_IT_ENABLE	1
#define I2C_HELPER_I2C1_ER_IT_ENABLE	I2C_HELPER_I2C1_EV_IT_ENABLE

#define I2C_HELPER_I2C2_EV_IT_ENABLE	1
#define I2C_HELPER_I2C2_ER_IT_ENABLE	I2C_HELPER_I2C2_EV_IT_ENABLE

#define I2C_HELPER_I2C3_EV_IT_ENABLE	0
#define I2C_HELPER_I2C3_ER_IT_ENABLE	I2C_HELPER_I2C3_EV_IT_ENABLE

/* Interrupt priority */
#define I2C_HELPER_I2C1_EV_IT_PRIORITY					0x02
#define I2C_HELPER_I2C1_EV_IT_SUBPRIORITY				0x00
#define I2C_HELPER_I2C1_ER_IT_PRIORITY					0x02
#define I2C_HELPER_I2C1_ER_IT_SUBPRIORITY				0x00

#define I2C_HELPER_I2C2_EV_IT_PRIORITY					0x02
#define I2C_HELPER_I2C2_EV_IT_SUBPRIORITY				0x00
#define I2C_HELPER_I2C2_ER_IT_PRIORITY					0x02
#define I2C_HELPER_I2C2_ER_IT_SUBPRIORITY				0x00

#define I2C_HELPER_I2C3_EV_IT_PRIORITY					0x0F
#define I2C_HELPER_I2C3_EV_IT_SUBPRIORITY				0x00
#define I2C_HELPER_I2C3_ER_IT_PRIORITY					0x0F
#define I2C_HELPER_I2C3_ER_IT_SUBPRIORITY				0x00

/* DMA */
#define I2C_HELPER_I2Cx_DMA_CLK_ENABLE() 	__HAL_RCC_DMA1_CLK_ENABLE()

#define I2C_HELPER_I2C1_DMA_TX_ENABLE		1 /* Tx Stream */
#define I2C_HELPER_I2C1_DMA_TX_CHANNEL		DMA_CHANNEL_1
#define I2C_HELPER_I2C1_DMA_TX_STREAM		DMA1_Stream7
#define I2C_HELPER_I2C1_DMA_TX_IRQn			DMA1_Stream7_IRQn
#define I2C_HELPER_I2C1_DMA_TX_IRQHandler	DMA1_Stream7_IRQHandler
#define I2C_HELPER_I2C1_DMA_TX_PRIORITY		0x02
#define I2C_HELPER_I2C1_DMA_TX_SUBPRIORITY	0x00
#define I2C_HELPER_I2C1_DMA_RX_ENABLE		0 /* Rx Stream */
#define I2C_HELPER_I2C1_DMA_RX_CHANNEL		DMA_CHANNEL_1
#define I2C_HELPER_I2C1_DMA_RX_STREAM		DMA1_Stream5
#define I2C_HELPER_I2C1_DMA_RX_IRQn			DMA1_Stream5_IRQn
#define I2C_HELPER_I2C1_DMA_RX_IRQHandler	DMA1_Stream5_IRQHandler
#define I2C_HELPER_I2C1_DMA_RX_PRIORITY		0x0F
#define I2C_HELPER_I2C1_DMA_RX_SUBPRIORITY	0x00

#define I2C_HELPER_I2C2_DMA_TX_ENABLE		0 /* Tx Stream */
#define I2C_HELPER_I2C2_DMA_TX_CHANNEL		DMA_CHANNEL_7
#define I2C_HELPER_I2C2_DMA_TX_STREAM		DMA1_Stream7
#define I2C_HELPER_I2C2_DMA_TX_IRQn			DMA1_Stream7_IRQn
#define I2C_HELPER_I2C2_DMA_TX_IRQHandler	DMA1_Stream7_IRQHandler
#define I2C_HELPER_I2C2_DMA_TX_PRIORITY		0x0F
#define I2C_HELPER_I2C2_DMA_TX_SUBPRIORITY	0x00
#define I2C_HELPER_I2C2_DMA_RX_ENABLE		1 /* Rx Stream */
#define I2C_HELPER_I2C2_DMA_RX_CHANNEL		DMA_CHANNEL_7
#define I2C_HELPER_I2C2_DMA_RX_STREAM		DMA1_Stream2
#define I2C_HELPER_I2C2_DMA_RX_IRQn			DMA1_Stream2_IRQn
#define I2C_HELPER_I2C2_DMA_RX_IRQHandler	DMA1_Stream2_IRQHandler
#define I2C_HELPER_I2C2_DMA_RX_PRIORITY		0x02
#define I2C_HELPER_I2C2_DMA_RX_SUBPRIORITY	0x00

#define I2C_HELPER_I2C3_DMA_TX_ENABLE		0 /* Tx Stream */
#define I2C_HELPER_I2C3_DMA_TX_CHANNEL		DMA_CHANNEL_3
#define I2C_HELPER_I2C3_DMA_TX_STREAM		DMA1_Stream4
#define I2C_HELPER_I2C3_DMA_TX_IRQn			DMA1_Stream4_IRQn
#define I2C_HELPER_I2C3_DMA_TX_IRQHandler	DMA1_Stream4_IRQHandler
#define I2C_HELPER_I2C3_DMA_TX_PRIORITY		0x0F
#define I2C_HELPER_I2C3_DMA_TX_SUBPRIORITY	0x00
#define I2C_HELPER_I2C3_DMA_RX_ENABLE		0 /* Rx Stream */
#define I2C_HELPER_I2C3_DMA_RX_CHANNEL		DMA_CHANNEL_3
#define I2C_HELPER_I2C3_DMA_RX_STREAM		DMA1_Stream2
#define I2C_HELPER_I2C3_DMA_RX_IRQn			DMA1_Stream2_IRQn
#define I2C_HELPER_I2C3_DMA_RX_IRQHandler	DMA1_Stream2_IRQHandler
#define I2C_HELPER_I2C3_DMA_RX_PRIORITY		0x0F
#define I2C_HELPER_I2C3_DMA_RX_SUBPRIORITY	0x00

/* GPIO Configuration ---------------------------------------------------------*/
/* Pin&Port */
#define I2C_HELPER_I2C1_SCL_GPIO_PORT				GPIOB
#define I2C_HELPER_I2C1_SCL_GPIO_PIN				GPIO_PIN_6
#define I2C_HELPER_I2C1_SDA_GPIO_PORT				GPIOB
#define I2C_HELPER_I2C1_SDA_GPIO_PIN				GPIO_PIN_9

#define I2C_HELPER_I2C2_SCL_GPIO_PORT				GPIOB
#define I2C_HELPER_I2C2_SCL_GPIO_PIN				GPIO_PIN_10
#define I2C_HELPER_I2C2_SDA_GPIO_PORT				GPIOB
#define I2C_HELPER_I2C2_SDA_GPIO_PIN				GPIO_PIN_11

#define I2C_HELPER_I2C3_SCL_GPIO_PORT				GPIOA
#define I2C_HELPER_I2C3_SCL_GPIO_PIN				GPIO_PIN_8
#define I2C_HELPER_I2C3_SDA_GPIO_PORT				GPIOC
#define I2C_HELPER_I2C3_SDA_GPIO_PIN				GPIO_PIN_9

/* Alternate function */
#define I2C_HELPER_I2C1_SCL_GPIO_AF					GPIO_AF4_I2C1
#define I2C_HELPER_I2C1_SDA_GPIO_AF					GPIO_AF4_I2C1

#define I2C_HELPER_I2C2_SCL_GPIO_AF					GPIO_AF4_I2C2
#define I2C_HELPER_I2C2_SDA_GPIO_AF					GPIO_AF4_I2C2

#define I2C_HELPER_I2C3_SCL_GPIO_AF					GPIO_AF4_I2C3
#define I2C_HELPER_I2C3_SDA_GPIO_AF					GPIO_AF4_I2C3

/* Exported macro ------------------------------------------------------------*/
/* Peripheral Clock */
#define I2C_HELPER_I2C1_CLK_ENABLE()				__I2C1_CLK_ENABLE()
#define I2C_HELPER_I2C1_CLK_DISABLE()				__I2C1_CLK_DISABLE()
#define I2C_HELPER_I2C1_FORCE_RESET() 				__I2C1_FORCE_RESET()
#define I2C_HELPER_I2C1_RELEASE_RESET() 			__I2C1_RELEASE_RESET()

#define I2C_HELPER_I2C2_CLK_ENABLE()				__I2C2_CLK_ENABLE()
#define I2C_HELPER_I2C2_CLK_DISABLE()				__I2C2_CLK_DISABLE()
#define I2C_HELPER_I2C2_FORCE_RESET() 				__I2C2_FORCE_RESET()
#define I2C_HELPER_I2C2_RELEASE_RESET() 			__I2C2_RELEASE_RESET()

#define I2C_HELPER_I2C3_CLK_ENABLE()				__I2C3_CLK_ENABLE()
#define I2C_HELPER_I2C3_CLK_DISABLE()				__I2C3_CLK_DISABLE()
#define I2C_HELPER_I2C3_FORCE_RESET() 				__I2C3_FORCE_RESET()
#define I2C_HELPER_I2C3_RELEASE_RESET() 			__I2C3_RELEASE_RESET()

/* GPIO Macros */
/* GPIO Clock */
#define I2C_HELPER_I2C1_SCL_GPIO_CLK_ENABLE()		__GPIOB_CLK_ENABLE()
#define I2C_HELPER_I2C1_SDA_GPIO_CLK_ENABLE()		__GPIOB_CLK_ENABLE()
#define I2C_HELPER_I2C1_SCL_GPIO_CLK_DISABLE()		__GPIOB_CLK_DISABLE()
#define I2C_HELPER_I2C1_SDA_GPIO_CLK_DISABLE()		__GPIOB_CLK_DISABLE()

#define I2C_HELPER_I2C2_SCL_GPIO_CLK_ENABLE()		__GPIOB_CLK_ENABLE()
#define I2C_HELPER_I2C2_SDA_GPIO_CLK_ENABLE()		__GPIOB_CLK_ENABLE()
#define I2C_HELPER_I2C2_SCL_GPIO_CLK_DISABLE()		__GPIOB_CLK_DISABLE()
#define I2C_HELPER_I2C2_SDA_GPIO_CLK_DISABLE()		__GPIOB_CLK_DISABLE()

#define I2C_HELPER_I2C3_SCL_GPIO_CLK_ENABLE()		__GPIOA_CLK_ENABLE()
#define I2C_HELPER_I2C3_SDA_GPIO_CLK_ENABLE()		__GPIOC_CLK_ENABLE()
#define I2C_HELPER_I2C3_SCL_GPIO_CLK_DISABLE()		__GPIOA_CLK_DISABLE()
#define I2C_HELPER_I2C3_SDA_GPIO_CLK_DISABLE()		__GPIOC_CLK_DISABLE()

/* Exported functions ------------------------------------------------------- */
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
