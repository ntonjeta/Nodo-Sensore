/**
 ******************************************************************************
 * @file    stm32f4xx_uart_helper.h
 * @author  Salvatore Miranda - SE4
 * @version V2.0
 * @date    16-June-2015
 * @brief   UART Helper Header File
 *          This file contains all default definition.
 *          Only this has to be included.
 ******************************************************************************
@verbatim

 ===============================================================================
 	 	 	 	 	 ##### UART Helper Configuration #####
 ===============================================================================
 [..] In order to use an UARTx peripheral you need to:
 (+) Configure parameters related to UARTx in Helper Uart Config file:
  (++) Pin Mapping
  (++) Mode
  (++) Parity
  (++) Word Length
  (++) # Stop Bits
  (++) Hardware Control (CTS/RTS)
  (++) OverSampling
  (++) Baud Rate
  (++) Functional Mode (Normal,Half-Duplex,LIN,Multiprocessor)
  	  (+++) Wakeup Method, if Functional Mode is Multiprocessor
  	  	  (++++) Address if Wakeup Method is ADDRESSMARK
  (++) Enable Interrupt
  	  (+++) Priority
  	  (+++) Sub Priority

 (+) Call the @ref HELPER_UART_Init passing the reference (@ref HELPER_UART_TypeDef) to the peripheral desired.
 (+) Call other functions of the UART Helper Library which you need.

 In addition you can in every moment avoid this Uart Helper Library by calling the function HELPER_UART_GetHandle
 which returns the Handle of the selected UARTx peripheral, then call the specific HAL Uart function which you need.

 Please note that you must enable the stm32f4xx_hal_uart.c (UART4 and UART5) and stm32f4xx_hal_usart.c (UART1,UART2,UART3,UART6).

 Example - UART (Normal Mode):

 @endverbatim
 @code {.c}
	 //Initialize UART5 using UART_Helper Library
	 HELPER_UART_Init(HELPER_UART5);

	 //Getting the UART2 Handle
	 UART_HandleTypeDef* UartHandle2 = HELPER_UART_GetHandle(HELPER_UART2);

	 //Initialize UART2 without Helper
	 UartHandle2->Instance = UART2;
	 UartHandle2->Init.BaudRate = 9600;
	  ....
	  //Other settings
	  ....

	  //Call HAL_UART_Init (It calls the HAL_UART_MspInit defined into UART_HELPER Library).
	  HAL_UART_Init(UartHandle2);

  @endcode
  @verbatim
  In addition you can use your GPIO_Configuration by calling your custom function.
  Example:
  	  myGPIOConfiguration();
  @endverbatim

@verbatim
===============================================================================
 ##### UART Helper I/O Operations #####
 ===============================================================================
 [..] Use the UART custom functions.
 @see stm32f4xx_uart_helper.h
 @see stm32f4xx_hal_uart.h

 Polling Examples :

 @endverbatim
 @code {.c}
	 //Use the HAL_UART_TRANSMIT passing the UartHandle retrieved using the function HELPER_UART_GetHandle
	 while(HAL_UART_Transmit(UartHandle2, &toSend,SIZE,TIMEOUT)!=HAL_OK){
		if (HAL_UART_GetError(UartHandle2) != HAL_UART_ERROR_NONE){
			//Some error occured
		}
	 }

	 // UART5 Receive using the Helper Function
	 if(HELPER_UART_Receive(HELPER_UART5,&toReceive,1)==HELPER_UART_ERROR){
		//Some Error Occured (not timeout error)
	 }

 @endcode

@verbatim
 Interrupt Examples:
 In order to use the interrupts the value UARTx_INTERRUPT must be UART_INT_USE_INT,
 then define one of these function in your application :
 	 void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
 	 void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
 	 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
 	 void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
 	 void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);

 	 Please note that the non-blocking functions of UART are not been implemented in this Helper Library,
 	 so you must refer to the HAL_UART using the UART_Handle.

 Usage :

 @endverbatim
 @code {.c}
	  UART_HandleTypeDef* UartHandle2 = HELPER_UART_GetHandle(HELPER_UART2);

	 //Use the HAL_UART_Receive_IT to Receive data in non-blocking mode
	 // (you must define the function HAL_UART_RxCpltCallback(..) to manage the end of reception)
	 while(HAL_UART_Receive_IT(UartHandle2,  uint8_t *pData,SIZE)!=HAL_OK){
		if (HAL_UART_GetError(UartHandle2) != HAL_UART_ERROR_NONE){
			//Some error occured
		}
	 }

	 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		 //Rx is completed
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
#ifndef __STM32F4xx_UART_HELPER_H
#define __STM32F4xx_UART_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "../conf/stm32f4xx_uart_helper_conf.h"

 /** @defgroup STM32F4xx_Helper_Library Helper Library
  * @brief STM32F4xx Peripheral Helper library
  * @{
  */

 /** @defgroup UART_Helper UART Helper
  * @brief UART Helper Module
  * @{
  */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	  HELPER_UART1 = 1,
	  HELPER_UART2 = 2,
	  HELPER_UART3 = 3,
	  HELPER_UART4 = 4,
	  HELPER_UART5 = 5,
	  HELPER_UART6 = 6
} HELPER_UART_TypeDef;

//MODALITA' DI INTERRUZIONE
typedef enum
{
  HELPER_UART_NO_INT = 0,
  HELPER_UART_USE_INT = 1
} HELPER_UART_Interrupt_TypeDef;

//MODALITA' DI FUNZIONAMENTO
typedef enum
{
  HELPER_UART_NORMAL_MODE = 0,
  HELPER_UART_HALF_DUPLEX_MODE = 1,
  HELPER_UART_LIN_MODE = 2,
  HELPER_UART_MULTIPROCESSOR_MODE = 3

} HELPER_UART_Functional_Modes_TypeDef;

typedef enum
{
  HELPER_UART_OK = 0,
  HELPER_UART_ERROR = 1,
} HELPER_UART_Status_TypeDef;


/* Exported functions ------------------------------------------------------- */

HELPER_UART_Status_TypeDef HELPER_UART_Init(HELPER_UART_TypeDef numUart);
HAL_StatusTypeDef HELPER_UART_DeInit(HELPER_UART_TypeDef numUart);
HELPER_UART_TypeDef HELPER_UART_GetNumUart(UART_HandleTypeDef* huart);
UART_HandleTypeDef* HELPER_UART_GetHandle(HELPER_UART_TypeDef numUart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
HELPER_UART_Status_TypeDef HELPER_UART_Transmit(HELPER_UART_TypeDef numUart,uint8_t *pData,uint16_t Size);
HELPER_UART_Status_TypeDef HELPER_UART_Receive(HELPER_UART_TypeDef numUart,uint8_t *pData,uint16_t Size);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_UART_HELPER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

