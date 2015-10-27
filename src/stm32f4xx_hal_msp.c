/**
 ******************************************************************************
 * @file    stm32f4xx_hal_msp.c
 * @author  MCD Application Team
 * @version V1.2.1
 * @date    13-March-2015
 * @brief   HAL MSP module.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */
#include "stm32f4xx_hal.h"
/** @defgroup HAL_MSP
 * @brief HAL MSP module.
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
 * @{
 */

///**
// * @brief UART MSP Initialization
// *        This function configures the hardware resources used in this example:
// * @retval None
// */
//void HAL_UART_MspInit(UART_HandleTypeDef *huart){
//
//	// Configurazione porti GPIO per UART4
//	__UART5_CLK_ENABLE();	/* Abilita la periferica locata sul bus APB1 */
//	__GPIOD_CLK_ENABLE();	/* Abilito il clock per il porto GPIOD */
//	__GPIOC_CLK_ENABLE();	/* Abilito il clock per il porto GPIOC */
//
//	GPIO_InitTypeDef  GPIO_InitStructure;	/* Handle che conterr������������������ le informazioni di configurazione del porto GPIO scelto */
//
//	GPIO_InitStructure.Pull  = GPIO_NOPULL;
//	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
//	GPIO_InitStructure.Alternate = GPIO_AF8_UART5; /* Ad UART4 ������������������ associata la AF8 */
//	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
//
//	GPIO_InitStructure.Pin = GPIO_PIN_12; /* OR Pin da abilitare (Pc12 = Tx) */
//	HAL_GPIO_Init(
//			GPIOC,		/* Inizializza GPIO A ...*/
//			&GPIO_InitStructure	/* ... secondo la configurazione prima eseguita */
//	);
//	GPIO_InitStructure.Pin = GPIO_PIN_2; /* OR Pin da abilitare (PD2 = Rx) */
//	HAL_GPIO_Init(
//			GPIOD,		/* Inizializza GPIO A ...*/
//			&GPIO_InitStructure	/* ... secondo la configurazione prima eseguita */
//	);
//
//	/* Da questo momento in poi i PIN PA0 e PA1 saranno utilizzati per la Tx e Rx di UART4. */
//	HAL_NVIC_SetPriority(
//			UART5_IRQn, 	/*!< UART4 global Interrupt - STM32 specific Interrupt Number - Unico vettore interruzioni per UART4*/
//			PRIORITY,		/* Valore di prorit������ */
//			SUBPRIORITY	/* Valore di Sub-Priority */
//	);
//
//	HAL_NVIC_EnableIRQ(UART5_IRQn);
//	__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
//	__HAL_UART_DISABLE_IT(huart, UART_IT_LBD);
//	__HAL_UART_DISABLE_IT(huart, UART_IT_TXE);
//	__HAL_UART_DISABLE_IT(huart, UART_IT_TC);
//
//}
//
///**
//  * @brief CRC MSP Initialization
//  *        This function configures the hardware resources used in this example:
//  *           - Peripheral's clock enable
//  * @param hcrc: CRC handle pointer
//  * @retval None
//  */
//void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
//{
//   /* CRC Peripheral clock enable */
//  __HAL_RCC_CRC_CLK_ENABLE();
//}
//
///**
//  * @brief CRC MSP De-Initialization
//  *        This function freeze the hardware resources used in this example:
//  *          - Disable the Peripheral's clock
//  * @param hcrc: CRC handle pointer
//  * @retval None
//  */
//void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
//{
//  /* Enable CRC reset state */
//  __HAL_RCC_CRC_FORCE_RESET();
//
//  /* Release CRC from reset state */
//  __HAL_RCC_CRC_RELEASE_RESET();
//}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
