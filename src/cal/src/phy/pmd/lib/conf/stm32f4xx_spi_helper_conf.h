/**
 ******************************************************************************
 * @file    stm32f4xx_SPI_helper_conf.h
 * @author  Giovanni Di Fiore - SE4
 * @version V0.1
 * @date    17-April-2015
 * @brief   SPI Configuration file
 *          This file should be modified by the user when it's necessary. The
 *          file contains peripheral's configuration defines and interrupt enablers
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
#ifndef __STM32F4xx_SPI_HELPER_CONF_H
#define __STM32F4xx_SPI_HELPER_CONF_H

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief	This enumeration is used to define the state of the interrupt inside this configuration file
*/
typedef enum {
	SPI_HELPER_INT_OFF = 0,
	SPI_HELPER_INT_ON = 1
} SPI_HELPER_Interrupt_Typedef;


/* Exported constants --------------------------------------------------------*/


/* SPI1 ----------------------------------------------------------------------*/

/* GPIO configuration --------------------------------------------------------*/
#define SPI_HELPER_SPI1_CLK_ENABLE()				__HAL_RCC_SPI1_CLK_ENABLE()
#define SPI_HELPER_SPI1_SCK_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI_HELPER_SPI1_MISO_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI_HELPER_SPI1_MOSI_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI_HELPER_SPI1_FORCE_RESET()				__HAL_RCC_SPI1_FORCE_RESET()
#define SPI_HELPER_SPI1_RELEASE_RESET()				__HAL_RCC_SPI1_RELEASE_RESET()

// configure SPI1 CLK
#define SPI_HELPER_SPI1_SCK_GPIO_PIN				GPIO_PIN_3
#define SPI_HELPER_SPI1_SCK_GPIO_AF					GPIO_AF5_SPI1
#define SPI_HELPER_SPI1_SCK_GPIO_PORT				GPIOB

// configure SPI1 MISO
#define SPI_HELPER_SPI1_MISO_GPIO_PIN				GPIO_PIN_4
#define SPI_HELPER_SPI1_MISO_GPIO_AF				GPIO_AF5_SPI1
#define SPI_HELPER_SPI1_MISO_GPIO_PORT				GPIOB

// configure SPI1 MOSI
#define SPI_HELPER_SPI1_MOSI_GPIO_PIN				GPIO_PIN_5
#define SPI_HELPER_SPI1_MOSI_GPIO_AF				GPIO_AF5_SPI1
#define SPI_HELPER_SPI1_MOSI_GPIO_PORT				GPIOB

/* SPI configuration --------------------------------------------------------*/
#define SPI_HELPER_SPI1_MODE						SPI_MODE_MASTER
#define SPI_HELPER_SPI1_BAUDRATEPRESCALER			SPI_BAUDRATEPRESCALER_8
#define SPI_HELPER_SPI1_DIRECTION					SPI_DIRECTION_1LINE
#define SPI_HELPER_SPI1_CLKPHASE					SPI_PHASE_1EDGE
#define SPI_HELPER_SPI1_CLKPOLARITY					SPI_POLARITY_HIGH
#define SPI_HELPER_SPI1_CRCCALCULATION				SPI_CRCCALCULATION_DISABLE
#define SPI_HELPER_SPI1_CRCPOLYNOMIAL				7
#define SPI_HELPER_SPI1_DATASIZE					SPI_DATASIZE_8BIT
#define SPI_HELPER_SPI1_FIRSTBIT					SPI_FIRSTBIT_MSB
#define SPI_HELPER_SPI1_NSS							SPI_NSS_SOFT
#define SPI_HELPER_SPI1_TIMODE						SPI_TIMODE_DISABLE

// configurations for interrupts
#define SPI_HELPER_SPI1_INT							SPI_HELPER_INT_OFF
#define SPI_HELPER_SPI1_INT_PRIORITY				0x0F
#define SPI_HELPER_SPI1_INT_SUBPRIORITY				0x00




/* GPIO configuration --------------------------------------------------------*/
// SPI2
#define SPI_HELPER_SPI2_CLK_ENABLE()				__HAL_RCC_SPI2_CLK_ENABLE()
#define SPI_HELPER_SPI2_SCK_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI_HELPER_SPI2_MISO_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI_HELPER_SPI2_MOSI_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI_HELPER_SPI2_FORCE_RESET()				__HAL_RCC_SPI2_FORCE_RESET()
#define SPI_HELPER_SPI2_RELEASE_RESET()				__HAL_RCC_SPI2_RELEASE_RESET()

// configure SPI2 CLK
#define SPI_HELPER_SPI2_SCK_GPIO_PIN				GPIO_PIN_13
#define SPI_HELPER_SPI2_SCK_GPIO_AF					GPIO_AF5_SPI2
#define SPI_HELPER_SPI2_SCK_GPIO_PORT				GPIOB

// configure SPI2 MISO
#define SPI_HELPER_SPI2_MISO_GPIO_PIN				GPIO_PIN_14
#define SPI_HELPER_SPI2_MISO_GPIO_AF				GPIO_AF5_SPI2
#define SPI_HELPER_SPI2_MISO_GPIO_PORT				GPIOB

// configure SPI2 MOSI
#define SPI_HELPER_SPI2_MOSI_GPIO_PIN				GPIO_PIN_15
#define SPI_HELPER_SPI2_MOSI_GPIO_AF				GPIO_AF5_SPI2
#define SPI_HELPER_SPI2_MOSI_GPIO_PORT				GPIOB

// configurations for handle
#define SPI_HELPER_SPI2_MODE						SPI_MODE_MASTER
#define SPI_HELPER_SPI2_BAUDRATEPRESCALER			SPI_BAUDRATEPRESCALER_256
#define SPI_HELPER_SPI2_DIRECTION					SPI_DIRECTION_2LINES
#define SPI_HELPER_SPI2_CLKPHASE					SPI_PHASE_1EDGE
#define SPI_HELPER_SPI2_CLKPOLARITY					SPI_POLARITY_HIGH
#define SPI_HELPER_SPI2_CRCCALCULATION				SPI_CRCCALCULATION_DISABLE
#define SPI_HELPER_SPI2_CRCPOLYNOMIAL				7
#define SPI_HELPER_SPI2_DATASIZE					SPI_DATASIZE_8BIT
#define SPI_HELPER_SPI2_FIRSTBIT					SPI_FIRSTBIT_MSB
#define SPI_HELPER_SPI2_NSS							SPI_NSS_SOFT
#define SPI_HELPER_SPI2_TIMODE						SPI_TIMODE_DISABLE

// configurations for interrupts
#define SPI_HELPER_SPI2_INT							SPI_HELPER_INT_ON
#define SPI_HELPER_SPI2_INT_PRIORITY				0x02
#define SPI_HELPER_SPI2_INT_SUBPRIORITY				0


/* GPIO configuration --------------------------------------------------------*/
// SPI3
#define SPI_HELPER_SPI3_CLK_ENABLE()				__HAL_RCC_SPI3_CLK_ENABLE()
#define SPI_HELPER_SPI3_SCK_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define SPI_HELPER_SPI3_MISO_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define SPI_HELPER_SPI3_MOSI_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define SPI_HELPER_SPI3_FORCE_RESET()				__HAL_RCC_SPI3_FORCE_RESET()
#define SPI_HELPER_SPI3_RELEASE_RESET()				__HAL_RCC_SPI3_RELEASE_RESET()

// configure SPI3 CLK
#define SPI_HELPER_SPI3_SCK_GPIO_PIN				GPIO_PIN_10
#define SPI_HELPER_SPI3_SCK_GPIO_AF					GPIO_AF6_SPI3
#define SPI_HELPER_SPI3_SCK_GPIO_PORT				GPIOC

// configure SPI3 MISO
#define SPI_HELPER_SPI3_MISO_GPIO_PIN				GPIO_PIN_11
#define SPI_HELPER_SPI3_MISO_GPIO_AF				GPIO_AF6_SPI3
#define SPI_HELPER_SPI3_MISO_GPIO_PORT				GPIOC

// configure SPI3 MOSI
#define SPI_HELPER_SPI3_MOSI_GPIO_PIN				GPIO_PIN_12
#define SPI_HELPER_SPI3_MOSI_GPIO_AF				GPIO_AF6_SPI3
#define SPI_HELPER_SPI3_MOSI_GPIO_PORT				GPIOC

// configurations for handle
#define SPI_HELPER_SPI3_MODE						SPI_MODE_SLAVE
#define SPI_HELPER_SPI3_BAUDRATEPRESCALER			SPI_BAUDRATEPRESCALER_256
#define SPI_HELPER_SPI3_DIRECTION					SPI_DIRECTION_2LINES
#define SPI_HELPER_SPI3_CLKPHASE					SPI_PHASE_1EDGE
#define SPI_HELPER_SPI3_CLKPOLARITY					SPI_POLARITY_HIGH
#define SPI_HELPER_SPI3_CRCCALCULATION				SPI_CRCCALCULATION_DISABLE
#define SPI_HELPER_SPI3_CRCPOLYNOMIAL				7
#define SPI_HELPER_SPI3_DATASIZE					SPI_DATASIZE_8BIT
#define SPI_HELPER_SPI3_FIRSTBIT					SPI_FIRSTBIT_MSB
#define SPI_HELPER_SPI3_NSS							SPI_NSS_SOFT
#define SPI_HELPER_SPI3_TIMODE						SPI_TIMODE_DISABLE

// configurations for interrupts
#define SPI_HELPER_SPI3_INT							SPI_HELPER_INT_ON
#define SPI_HELPER_SPI3_INT_PRIORITY				0x02
#define SPI_HELPER_SPI3_INT_SUBPRIORITY				0


/* Exported functions ------------------------------------------------------- */
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_SPI_HELPER_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
