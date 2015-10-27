/**
 ******************************************************************************
 * @file    stm32f4xx_uart_helper_config.h
 * @author  Salvatore Miranda - SE4
 * @version V2.0
 * @date    16-June-2015
 * @brief   UART Helper Configuration file
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

 */
 /**

 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_UART_CONFIG_H
#define __STM32F4xx_UART_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/*=============================== INIZIO PARTE MODIFICABILE =======================================

  Configurazioni per UART1,2,3,4,5,6.
  E' possibile modificare il PinMapping ed i parametri di configurazione.

*/

//############################### UART1 #######################################
// -------------------------------- UART1 Pin Mapping---------------------------------------------------

/*
 * NOTA BENE: Per la sola modalit� UART si consiglia di usare il porto B usando solo TX (PB6) e RX (PB7) senza HW Control.
 */
#define HELPER_UART1_GPIO_CLK_ENABLE()            	__GPIOA_CLK_ENABLE()
#define HELPER_UART1_GPIO_CLK_DISABLE()           	__GPIOA_CLK_DISABLE()
#define HELPER_UART1_GPIO_PORT                    	GPIOB                      /* GPIOB */
#define HELPER_UART1_AF                           	GPIO_AF7_USART1
#define HELPER_UART1_CK_PIN                      	GPIO_PIN_8                 /* PA.8 */
#define HELPER_UART1_TX_PIN                      	GPIO_PIN_6                 /* PB.6 */
#define HELPER_UART1_RX_PIN                      	GPIO_PIN_7                 /* PB.7 */
#define HELPER_UART1_CTS_PIN                      	GPIO_PIN_11                 /* PA.11 */
#define HELPER_UART1_RTS_PIN                      	GPIO_PIN_12                 /* PA.12 */

// -------------------------------- UART1 Config. Parameters ---------------------------------------------------

#define UART1_LENGHT					UART_WORDLENGTH_8B //UART_WORDLENGTH_9B,UART_WORDLENGTH_8B
#define UART1_STOP_B					UART_STOPBITS_1   // UART_STOPBITS_0_5, UART_STOPBITS_1_5, UART_STOPBITS_2,UART_STOPBITS_1,
#define UART1_PARITY					UART_PARITY_NONE  // UART_PARITY_EVEN, UART_PARITY_ODD, UART_PARITY_NONE
#define UART1_MODE						UART_MODE_TX_RX   // UART_MODE_TX, UART_MODE_RX,UART_MODE_TX_RX
#define  UART1_OVERSAMPLING 			UART_OVERSAMPLING_16 //UART_OVERSAMPLING_8, UART_OVERSAMPLING_16

#define UART1_HWCONTROL 		UART_HWCONTROL_NONE //UART_HWCONTROL_RTS, UART_HWCONTROL_CTS, UART_HWCONTROL_RTS_CTS
#define UART1_BAUDRATE			9600

#define UART1_FUNCTIONAL_MODE				HELPER_UART_NORMAL_MODE //HELPER_UART_HALF_DUPLEX_MODE
#define UART1_MULTIPROCESSOR_ADDRESS		0x0 //VALIDO SOLO PER MULTIPROCESSOR MODE con WAKEUP_ADDRESSMARK!!
#define UART1_MULTIPROCESSOR_WAKEUP_METHOD 	UART_WAKEUPMETHOD_ADDRESSMARK //UART_WAKEUPMETHOD_IDLELINE ,UART_WAKEUPMETHOD_ADDRESSMARK

// ---------------- Parametri custom definiti ( Uart_Interrupt_TypeDef) -------------------//
#define UART1_INTERRUPT		    HELPER_UART_USE_INT //HELPER_UART_USE_INT, HELPER_UART_NO_INT
#define UART1_INT_PRIORITY		0x02
#define UART1_INT_SUB_PRIORITY  0

/*############################### UART2 #######################################*/
// -------------------------------- UART2 Pin Mapping---------------------------------------------------

#define HELPER_UART2_GPIO_CLK_ENABLE()        	    __GPIOD_CLK_ENABLE()
#define HELPER_UART2_GPIO_CLK_DISABLE()      	    __GPIOD_CLK_DISABLE()
#define HELPER_UART2_GPIO_PORT            	        GPIOD                      /* GPIOD */
#define HELPER_UART2_AF                   	  	    GPIO_AF7_USART2
#define HELPER_UART2_CK_PIN                      	GPIO_PIN_7                 /* PD.7 */
#define HELPER_UART2_TX_PIN                      	GPIO_PIN_5                  /* PD.5 */
#define HELPER_UART2_RX_PIN                      	GPIO_PIN_6                  /* PD.6 */
#define HELPER_UART2_CTS_PIN                      	GPIO_PIN_3                  /* PD.3 */
#define HELPER_UART2_RTS_PIN                      	GPIO_PIN_4                  /* PD.4 */


// -------------------------------- UART2 Config. Parameters ---------------------------------------------------
#define UART2_LENGHT			UART_WORDLENGTH_8B //UART_WORDLENGTH_9B,UART_WORDLENGTH_8B
#define UART2_STOP_B			UART_STOPBITS_1   // UART_STOPBITS_0_5, UART_STOPBITS_1_5, UART_STOPBITS_2,UART_STOPBITS_1,
#define UART2_PARITY			UART_PARITY_NONE  // UART_PARITY_EVEN, UART_PARITY_ODD, UART_PARITY_NONE
#define UART2_MODE				UART_MODE_TX_RX   // UART_MODE_TX, UART_MODE_RX, UART_MODE_TX_RX
#define  UART2_OVERSAMPLING 	UART_OVERSAMPLING_16 //UART_OVERSAMPLING_8, UART_OVERSAMPLING_16

#define UART2_HWCONTROL 		UART_HWCONTROL_NONE //UART_HWCONTROL_RTS, UART_HWCONTROL_CTS, UART_HWCONTROL_RTS_CTS
#define UART2_BAUDRATE			9600


#define UART2_FUNCTIONAL_MODE				HELPER_UART_NORMAL_MODE //HELPER_UART_HALF_DUPLEX_MODE,HELPER_UART_MULTIPROCESSOR_MODE ,NORMAL
#define UART2_MULTIPROCESSOR_ADDRESS		0x0 					//VALIDO SOLO PER MULTIPROCESSOR MODE con WAKEUP_ADDRESSMARK!!
#define UART2_MULTIPROCESSOR_WAKEUP_METHOD 	UART_WAKEUPMETHOD_ADDRESSMARK //UART_WAKEUPMETHOD_IDLELINE ,UART_WAKEUPMETHOD_ADDRESSMARK

// ---------------- Parametri custom definiti ( Uart_Interrupt_TypeDef) -------------------//

#define UART2_INTERRUPT		   	HELPER_UART_USE_INT //HELPER_UART_USE_INT, HELPER_UART_NO_INT
#define UART2_INT_PRIORITY		0x02
#define UART2_INT_SUB_PRIORITY  0

/*############################### UART3 #######################################*/

// -------------------------------- UART3 Pin Mapping---------------------------------------------------

#define HELPER_UART3_GPIO_CLK_ENABLE()          	  __GPIOD_CLK_ENABLE()
#define HELPER_UART3_GPIO_CLK_DISABLE()         	  __GPIOD_CLK_DISABLE()
#define HELPER_UART3_GPIO_PORT                  	GPIOD                      /* GPIOD */
#define HELPER_UART3_AF                        		GPIO_AF7_USART3
#define HELPER_UART3_CK_PIN                      	GPIO_PIN_10                 /* PD.10 */
#define HELPER_UART3_TX_PIN                      	GPIO_PIN_8                  /* PD.8 */
#define HELPER_UART3_RX_PIN                      	GPIO_PIN_9                  /* PD.9 */
#define HELPER_UART3_CTS_PIN                      	GPIO_PIN_11                  /* PD.11 */
#define HELPER_UART3_RTS_PIN                      	GPIO_PIN_12                  /* PD.12 */


// -------------------------------- UART3 Config. Parameters ---------------------------------------------------
#define UART3_LENGHT						UART_WORDLENGTH_8B //UART_WORDLENGTH_9B,UART_WORDLENGTH_8B
#define UART3_STOP_B						UART_STOPBITS_1   // UART_STOPBITS_0_5, UART_STOPBITS_1_5, UART_STOPBITS_2,UART_STOPBITS_1,
#define UART3_PARITY						UART_PARITY_NONE  // UART_PARITY_EVEN, UART_PARITY_ODD, UART_PARITY_NONE
#define UART3_MODE							UART_MODE_TX_RX   // UART_MODE_TX, UART_MODE_RX, UART_MODE_TX_RX
#define  UART3_OVERSAMPLING 				UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16
#define UART3_HWCONTROL 					UART_HWCONTROL_NONE //UART_HWCONTROL_RTS, UART_HWCONTROL_CTS, UART_HWCONTROL_RTS_CTS
#define UART3_BAUDRATE						9600

#define UART3_FUNCTIONAL_MODE				HELPER_UART_NORMAL_MODE //HELPER_UART_HALF_DUPLEX_MODE, Normal, Multiprocessor
#define UART3_MULTIPROCESSOR_ADDRESS		0x5 //VALIDO SOLO PER MULTIPROCESSOR MODE con WAKEUP_ADDRESSMARK!!
#define UART3_MULTIPROCESSOR_WAKEUP_METHOD 	UART_WAKEUPMETHOD_IDLELINE //UART_WAKEUPMETHOD_IDLELINE ,UART_WAKEUPMETHOD_ADDRESSMARK

// ---------------- Parametri custom definiti ( Uart_Interrupt_TypeDef) -------------------//

#define UART3_INTERRUPT		    HELPER_UART_USE_INT //HELPER_UART_USE_INT, HELPER_UART_NO_INT
#define UART3_INT_PRIORITY		0x02
#define UART3_INT_SUB_PRIORITY  0


/* ############################### UART4 #######################################*/

// -------------------------------- UART4 Pin Mapping---------------------------------------------------

#define HELPER_UART4_GPIO_CLK_ENABLE()            	__GPIOC_CLK_ENABLE()
#define HELPER_UART4_GPIO_CLK_DISABLE()           	__GPIOC_CLK_DISABLE()
#define HELPER_UART4_GPIO_PORT                    	GPIOC                      /* GPIOC */
#define HELPER_UART4_AF                           	GPIO_AF8_UART4
#define HELPER_UART4_TX_PIN                      	GPIO_PIN_10                 /* PC.10 */
#define HELPER_UART4_RX_PIN                      	GPIO_PIN_11                 /* PC.11 */


// -------------------------------- UART4 Config. Parameters ---------------------------------------------------
#define UART4_LENGHT			UART_WORDLENGTH_8B //UART_WORDLENGTH_9B,UART_WORDLENGTH_8B
#define UART4_STOP_B			UART_STOPBITS_1   //UART_STOPBITS_2
#define UART4_PARITY			UART_PARITY_NONE // UART_PARITY_EVEN, UART_PARITY_ODD, UART_PARITY_NONE
#define UART4_MODE				UART_MODE_TX_RX // UART_MODE_TX, UART_MODE_RX, UART_MODE_TX_RX
#define UART4_HWCONTROL 		UART_HWCONTROL_NONE //UART4 NON HA HWCONTROL!
#define  UART4_OVERSAMPLING 	UART_OVERSAMPLING_16 //UART_OVERSAMPLING_8, UART_OVERSAMPLING_16
#define UART4_BAUDRATE			9600

#define UART4_FUNCTIONAL_MODE				HELPER_UART_NORMAL_MODE //HELPER_UART_HALF_DUPLEX_MODE
#define UART4_MULTIPROCESSOR_ADDRESS		0x5 //VALIDO SOLO PER MULTIPROCESSOR MODE con WAKEUP_ADDRESSMARK!!
#define UART4_MULTIPROCESSOR_WAKEUP_METHOD 	UART_WAKEUPMETHOD_ADDRESSMARK //UART_WAKEUPMETHOD_IDLELINE ,UART_WAKEUPMETHOD_ADDRESSMARK
// ---------------- Parametri custom definiti( Uart_Interrupt_TypeDef) -------------------//

#define UART4_INTERRUPT		    HELPER_UART_USE_INT // HELPER_UART_USE_INT, HELPER_UART_NO_INT
#define UART4_INT_PRIORITY		0x02
#define UART4_INT_SUB_PRIORITY  0

/*############################### UART5 #######################################
 *
 * NOTA: UART5 usa 2 porti diversi per la ricezione e trasmissione (rispettivamente PortC e PortD) e sono unici
 * (quindi non possono essere cambiati). Per tale motivo ci sar� una gestione particolare per la configurazione di tali porti.
 * Inoltre si consiglia di non modificare nessuno di questi valori per la board STM32F4_DISCOVERY.
 */

// -------------------------------- UART5 Pin Mapping---------------------------------------------------
#define HELPER_UART5_GPIO_PORT                    	GPIOC                      /* GPIOC */
#define HELPER_UART5_GPIO_CLK_ENABLE()            	__GPIOC_CLK_ENABLE()
#define HELPER_UART5_GPIO_CLK_DISABLE()           	__GPIOC_CLK_DISABLE()
#define HELPER_UART5_GPIO_CLK_ENABLE_RX()           __GPIOD_CLK_ENABLE()	/* Clock enable/disable aggiunti per gestire la Rx su porto diverso (PORTD) */
#define HELPER_UART5_GPIO_CLK_DISABLE_RX()          __GPIOD_CLK_DISABLE()

#define HELPER_UART5_GPIO_PORT_RX                   GPIOD                      /* GPIOD AGGIUNTO SOLO PER LA RICEZIONE! */
#define HELPER_UART5_AF                           	GPIO_AF8_UART5
#define HELPER_UART5_TX_PIN                      	GPIO_PIN_12                 /* PC.12 */
#define HELPER_UART5_RX_PIN                      	GPIO_PIN_2                 /* PD.2 */

// -------------------------------- UART5 Config. Parameters ---------------------------------------------------
#define UART5_LENGHT			UART_WORDLENGTH_8B //UART_WORDLENGTH_9B,UART_WORDLENGTH_8B
#define UART5_STOP_B			UART_STOPBITS_1   //UART_STOPBITS_2
#define UART5_PARITY			UART_PARITY_NONE // UART_PARITY_EVEN, UART_PARITY_ODD, UART_PARITY_NONE
#define UART5_MODE				UART_MODE_TX_RX // UART_MODE_TX, UART_MODE_RX, UART_MODE_TX_RX

#define  UART5_OVERSAMPLING 	UART_OVERSAMPLING_16 //UART_OVERSAMPLING_8, UART_OVERSAMPLING_16
#define UART5_BAUDRATE			9600
#define UART5_HWCONTROL 		UART_HWCONTROL_NONE //UART5 NON HA HWCONTROL!


#define UART5_FUNCTIONAL_MODE					HELPER_UART_NORMAL_MODE //HELPER_UART_HALF_DUPLEX_MODE
#define UART5_MULTIPROCESSOR_ADDRESS			0x0 //VALIDO SOLO PER MULTIPROCESSOR MODE con WAKEUP_ADDRESSMARK!!
#define UART5_MULTIPROCESSOR_WAKEUP_METHOD 		UART_WAKEUPMETHOD_IDLELINE //UART_WAKEUPMETHOD_IDLELINE ,UART_WAKEUPMETHOD_ADDRESSMARK
// ---------------- Parametri custom definiti ( Uart_Interrupt_TypeDef) -------------------//

#define UART5_INTERRUPT		    HELPER_UART_USE_INT // HELPER_UART_USE_INT, HELPER_UART_NO_INT
#define UART5_INT_PRIORITY		0x02
#define UART5_INT_SUB_PRIORITY  0


/*############################### UART6 #######################################*/

// -------------------------------- UART6 Pin Mapping---------------------------------------------------

#define HELPER_UART6_GPIO_CLK_ENABLE()           __GPIOC_CLK_ENABLE()
#define HELPER_UART6_GPIO_CLK_DISABLE()          __GPIOC_CLK_DISABLE()
#define HELPER_UART6_GPIO_PORT                   GPIOC                      /* GPIOC */
#define HELPER_UART6_AF                          GPIO_AF8_USART6
#define HELPER_UART6_CK_PIN                      GPIO_PIN_8                 /* PC.8 */
#define HELPER_UART6_TX_PIN                      GPIO_PIN_6                  /* PC.6 */
#define HELPER_UART6_RX_PIN                      GPIO_PIN_7                  /* PC.7 */

// UART6 permette di usare CTS e RTS solo se si usa il PortoG
#define HELPER_UART6_CTS_PIN                      GPIO_PIN_15                  /* PG.15 */
#define HELPER_UART6_RTS_PIN                      GPIO_PIN_12                  /* PG.12 */


// -------------------------------- UART6 Config. Parameters ---------------------------------------------------
#define UART6_LENGHT			UART_WORDLENGTH_8B //UART_WORDLENGTH_9B,UART_WORDLENGTH_8B
#define UART6_STOP_B			UART_STOPBITS_1   // UART_STOPBITS_0_5, UART_STOPBITS_1_5, UART_STOPBITS_2,UART_STOPBITS_1,
#define UART6_PARITY			UART_PARITY_NONE  // UART_PARITY_EVEN, UART_PARITY_ODD, UART_PARITY_NONE
#define UART6_MODE				UART_MODE_TX_RX   // UART_MODE_TX, UART_MODE_RX, UART_MODE_TX_RX
#define  UART6_OVERSAMPLING 	UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16

//NOTA: Poich� RTS/CTS sono disponibili solo sul PortoG, HWControl deve essere posto a NONE quando si usano altri porti.

#define UART6_HWCONTROL 		UART_HWCONTROL_NONE //UART_HWCONTROL_RTS, UART_HWCONTROL_CTS, UART_HWCONTROL_RTS_CTS
#define UART6_BAUDRATE			9600

#define UART6_FUNCTIONAL_MODE					HELPER_UART_NORMAL_MODE //HELPER_UART_HALF_DUPLEX_MODE
#define UART6_MULTIPROCESSOR_ADDRESS			0x3 //VALIDO SOLO PER MULTIPROCESSOR MODE con WAKEUP_ADDRESSMARK!!
#define UART6_MULTIPROCESSOR_WAKEUP_METHOD 		UART_WAKEUPMETHOD_ADDRESSMARK //UART_WAKEUPMETHOD_IDLELINE ,UART_WAKEUPMETHOD_ADDRESSMARK

// ---------------- Parametri custom definiti ( Uart_Interrupt_TypeDef) -------------------//

#define UART6_INTERRUPT		    HELPER_UART_USE_INT // HELPER_UART_USE_INT, HELPER_UART_NO_INT
#define UART6_INT_PRIORITY		0x02
#define UART6_INT_SUB_PRIORITY  0

/*
 * =============================================================================================================
 * =============================================================================================================
 * ############################################ FINE PARTE MODIFICABILE ###########################################
 * =============================================================================================================
 * =============================================================================================================
 * =============================================================================================================
 * =============================================================================================================
 */

 //############################### UART1 #######################################
  #define HELPER_UART_1                              USART1
  #define HELPER_UART1_CLK_ENABLE()                 __USART1_CLK_ENABLE()
  #define HELPER_UART1_CLK_DISABLE()                 __USART1_CLK_DISABLE()
  #define HELPER_UART1_IRQN						USART1_IRQn
 /*############################### UART2 #######################################*/
 #define HELPER_UART_2                              USART2
 #define HELPER_UART2_CLK_ENABLE()                 __USART2_CLK_ENABLE()
 #define HELPER_UART2_CLK_DISABLE()                 __USART2_CLK_DISABLE()
 #define HELPER_UART2_IRQN						USART2_IRQn
 /*############################### UART3 #######################################*/
 #define HELPER_UART_3                              USART3
 #define HELPER_UART3_CLK_ENABLE()                 __USART3_CLK_ENABLE()
 #define HELPER_UART3_CLK_DISABLE()                 __USART3_CLK_DISABLE()
 #define HELPER_UART3_IRQN						USART3_IRQn
 /* ############################### UART4 #######################################*/
 #define HELPER_UART_4                              UART4
 #define HELPER_UART4_CLK_ENABLE()                 __UART4_CLK_ENABLE()
 #define HELPER_UART4_CLK_DISABLE()                 __UART4_CLK_DISABLE()
 #define HELPER_UART4_IRQN						UART4_IRQn
 /*############################### UART5 ####################################### */
 #define HELPER_UART_5                              UART5
 #define HELPER_UART5_CLK_ENABLE()                 __UART5_CLK_ENABLE()
 #define HELPER_UART5_CLK_DISABLE()                 __UART5_CLK_DISABLE()
 #define HELPER_UART5_IRQN						UART5_IRQn
 /*############################### UART6 #######################################*/
 #define HELPER_UART_6                              USART6
 #define HELPER_UART6_CLK_ENABLE()                 __USART6_CLK_ENABLE()
 #define HELPER_UART6_CLK_DISABLE()                 __USART6_CLK_DISABLE()
 #define HELPER_UART6_IRQN						USART6_IRQn

/*
 * Macro per generalizzare le funzioni
 */
// ############################### UART(N), N 1,2,3,4,5,6 ####################################### //

#define HELPER_UART(N)                            	((N==HELPER_UART1)? HELPER_UART_1 :((N==HELPER_UART2)? HELPER_UART_2 : ((N==HELPER_UART3)? HELPER_UART_3 : ((N==HELPER_UART4)? HELPER_UART_4 : ((N==HELPER_UART5)? HELPER_UART_5 : HELPER_UART_6)))))

#define HELPER_UART_CLK_ENABLE(N)                 	((N==HELPER_UART1)? __USART1_CLK_ENABLE() :((N==HELPER_UART2)? __USART2_CLK_ENABLE() : ((N==HELPER_UART3)? __USART3_CLK_ENABLE() : ((N==HELPER_UART4)? __UART4_CLK_ENABLE() : ((N==HELPER_UART5)? __UART5_CLK_ENABLE() : __USART6_CLK_ENABLE())))))

#define HELPER_UART_CLK_DISABLE(N)                 	((N==HELPER_UART1)? __USART1_CLK_DISABLE() :((N==HELPER_UART2)? __USART2_CLK_DISABLE() : ((N==HELPER_UART3)? __USART3_CLK_DISABLE() : ((N==HELPER_UART4)? __UART4_CLK_DISABLE() : ((N==HELPER_UART5)? __UART5_CLK_DISABLE() : __USART6_CLK_DISABLE())))))




#define HELPER_UART_FORCE_RESET(N)						((N==HELPER_UART1)? __HAL_RCC_USART1_FORCE_RESET() :((N==HELPER_UART2)? __HAL_RCC_USART2_FORCE_RESET() : ((N==HELPER_UART3)? __HAL_RCC_USART3_FORCE_RESET() : ((N==HELPER_UART4)? __HAL_RCC_UART4_FORCE_RESET() : ((N==HELPER_UART5)? __HAL_RCC_UART5_FORCE_RESET() : __HAL_RCC_USART6_FORCE_RESET() )))))

#define HELPER_UART_RELEASE_RESET(N)						((N==HELPER_UART1)? __HAL_RCC_USART1_RELEASE_RESET() :((N==HELPER_UART2)? __HAL_RCC_USART2_RELEASE_RESET() : ((N==HELPER_UART3)? __HAL_RCC_USART3_RELEASE_RESET() : ((N==HELPER_UART4)? __HAL_RCC_UART4_RELEASE_RESET() : ((N==HELPER_UART5)? __HAL_RCC_UART5_RELEASE_RESET() : __HAL_RCC_USART6_RELEASE_RESET() )))))


#define HELPER_UART_GPIO_PORT(N)                  	((N==HELPER_UART1)? HELPER_UART1_GPIO_PORT :((N==HELPER_UART2)? HELPER_UART2_GPIO_PORT : ((N==HELPER_UART3)? HELPER_UART3_GPIO_PORT : ((N==HELPER_UART4)? HELPER_UART4_GPIO_PORT : ((N==HELPER_UART5)? HELPER_UART5_GPIO_PORT : HELPER_UART6_GPIO_PORT)))))

#define HELPER_UART_AF(N)                           ((N==HELPER_UART1)? HELPER_UART1_AF :((N==HELPER_UART2)? HELPER_UART2_AF : ((N==HELPER_UART3)? HELPER_UART3_AF : ((N==HELPER_UART4)? HELPER_UART4_AF : ((N==HELPER_UART5)? HELPER_UART5_AF : HELPER_UART6_AF)))))

#define HELPER_UART_GPIO_CLK_ENABLE(N)            	((N==HELPER_UART1)? HELPER_UART1_GPIO_CLK_ENABLE() :((N==HELPER_UART2)? HELPER_UART2_GPIO_CLK_ENABLE() : ((N==HELPER_UART3)? HELPER_UART3_GPIO_CLK_ENABLE() : ((N==HELPER_UART4)? HELPER_UART4_GPIO_CLK_ENABLE() : ((N==HELPER_UART5)? HELPER_UART5_GPIO_CLK_ENABLE() : HELPER_UART6_GPIO_CLK_ENABLE())))))

#define HELPER_UART_GPIO_CLK_DISABLE(N)           	((N==HELPER_UART1)? HELPER_UART1_GPIO_CLK_DISABLE() :((N==HELPER_UART2)? HELPER_UART2_GPIO_CLK_DISABLE() : ((N==HELPER_UART3)? HELPER_UART3_GPIO_CLK_DISABLE() : ((N==HELPER_UART4)? HELPER_UART4_GPIO_CLK_DISABLE() : ((N==HELPER_UART5)? HELPER_UART5_GPIO_CLK_DISABLE() : HELPER_UART6_GPIO_CLK_DISABLE())))))

#define HELPER_UART_TX_PIN(N)                     	((N==HELPER_UART1)? HELPER_UART1_TX_PIN :((N==HELPER_UART2)? HELPER_UART2_TX_PIN : ((N==HELPER_UART3)? HELPER_UART3_TX_PIN : ((N==HELPER_UART4)? HELPER_UART4_TX_PIN : ((N==HELPER_UART5)? HELPER_UART5_TX_PIN : HELPER_UART6_TX_PIN)))))

#define HELPER_UART_RX_PIN(N)                    	((N==HELPER_UART1)? HELPER_UART1_RX_PIN :((N==HELPER_UART2)? HELPER_UART2_RX_PIN : ((N==HELPER_UART3)? HELPER_UART3_RX_PIN : ((N==HELPER_UART4)? HELPER_UART4_RX_PIN : ((N==HELPER_UART5)? HELPER_UART5_RX_PIN : HELPER_UART6_RX_PIN)))))

// TALI PIN SONO POSSEDUTI SOLO DALLE PERIFERICHE UART/USART (UART1,2,3 E 6[Su portoG] ) CHE POSSEGGONO L'HWCONTRL

#define HELPER_UART_CTS_PIN(N)							((N==HELPER_UART1)?  HELPER_UART1_CTS_PIN :((N==HELPER_UART2)?  HELPER_UART2_CTS_PIN :((N==HELPER_UART3)?  HELPER_UART3_CTS_PIN :  HELPER_UART6_CTS_PIN)))

#define HELPER_UART_RTS_PIN(N)							((N==HELPER_UART1)?  HELPER_UART1_RTS_PIN :((N==HELPER_UART2)?  HELPER_UART2_RTS_PIN :((N==HELPER_UART3)?  HELPER_UART3_RTS_PIN :  HELPER_UART6_RTS_PIN)))


#define HELPER_UART_IRQ(N)                    		((N==HELPER_UART1)? HELPER_UART1_IRQN :((N==HELPER_UART2)? HELPER_UART2_IRQN : ((N==HELPER_UART3)? HELPER_UART3_IRQN : ((N==HELPER_UART4)? HELPER_UART4_IRQN : ((N==HELPER_UART5)? HELPER_UART5_IRQN : HELPER_UART6_IRQN)))))

#define HELPER_UART_LENGHT(N)						((N==HELPER_UART1)? UART1_LENGHT :((N==HELPER_UART2)? UART2_LENGHT : ((N==HELPER_UART3)? UART3_LENGHT : ((N==HELPER_UART4)? UART4_LENGHT : ((N==HELPER_UART5)? UART5_LENGHT : UART6_LENGHT)))))


#define HELPER_UART_STOP_B(N)						((N==HELPER_UART1)? UART1_STOP_B :((N==HELPER_UART2)? UART2_STOP_B : ((N==HELPER_UART3)? UART3_STOP_B : ((N==HELPER_UART4)? UART4_STOP_B : ((N==HELPER_UART5)? UART5_STOP_B : UART6_STOP_B)))))

#define HELPER_UART_PARITY(N)						((N==HELPER_UART1)? UART1_PARITY :((N==HELPER_UART2)? UART2_PARITY : ((N==HELPER_UART3)? UART3_PARITY : ((N==HELPER_UART4)? UART4_PARITY : ((N==HELPER_UART5)? UART5_PARITY : UART6_PARITY)))))

#define HELPER_UART_HWCONTROL(N)					((N==HELPER_UART1)? UART1_HWCONTROL :((N==HELPER_UART2)? UART2_HWCONTROL : ((N==HELPER_UART3)? UART3_HWCONTROL : ((N==HELPER_UART4)? UART4_HWCONTROL : ((N==HELPER_UART5)? UART5_HWCONTROL : UART6_HWCONTROL)))))

#define HELPER_UART_MODE(N)							((N==HELPER_UART1)? UART1_MODE :((N==HELPER_UART2)? UART2_MODE : ((N==HELPER_UART3)? UART3_MODE : ((N==HELPER_UART4)? UART4_MODE : ((N==HELPER_UART5)? UART5_MODE : UART6_MODE)))))

#define HELPER_UART_BAUDRATE(N)						((N==HELPER_UART1)? UART1_BAUDRATE :((N==HELPER_UART2)? UART2_BAUDRATE : ((N==HELPER_UART3)? UART3_BAUDRATE : ((N==HELPER_UART4)? UART4_BAUDRATE : ((N==HELPER_UART5)? UART5_BAUDRATE : UART6_BAUDRATE)))))

#define HELPER_UART_OVERSAMPLING(N) 				((N==HELPER_UART1)? UART1_OVERSAMPLING :((N==HELPER_UART2)? UART2_OVERSAMPLING : ((N==HELPER_UART3)? UART3_OVERSAMPLING : ((N==HELPER_UART4)? UART4_OVERSAMPLING : ((N==HELPER_UART5)? UART5_OVERSAMPLING : UART6_OVERSAMPLING)))))

#define HELPER_UART_FUNCTIONAL_MODE(N)				((N==HELPER_UART1)? UART1_FUNCTIONAL_MODE :((N==HELPER_UART2)? UART2_FUNCTIONAL_MODE : ((N==HELPER_UART3)? UART3_FUNCTIONAL_MODE : ((N==HELPER_UART4)? UART4_FUNCTIONAL_MODE : ((N==HELPER_UART5)? UART5_FUNCTIONAL_MODE : UART6_FUNCTIONAL_MODE)))))

#define HELPER_UART_MULTIPROCESSOR_ADDRESS(N)		((N==HELPER_UART1)? UART1_MULTIPROCESSOR_ADDRESS :((N==HELPER_UART2)? UART2_MULTIPROCESSOR_ADDRESS : ((N==HELPER_UART3)? UART3_MULTIPROCESSOR_ADDRESS : ((N==HELPER_UART4)? UART4_MULTIPROCESSOR_ADDRESS : ((N==HELPER_UART5)? UART5_MULTIPROCESSOR_ADDRESS : UART6_MULTIPROCESSOR_ADDRESS)))))

#define HELPER_UART_MULTIPROCESSOR_WAKEUP_METHOD(N)	((N==HELPER_UART1)? UART1_MULTIPROCESSOR_WAKEUP_METHOD :((N==HELPER_UART2)? UART2_MULTIPROCESSOR_WAKEUP_METHOD : ((N==HELPER_UART3)? UART3_MULTIPROCESSOR_WAKEUP_METHOD : ((N==HELPER_UART4)? UART4_MULTIPROCESSOR_WAKEUP_METHOD : ((N==HELPER_UART5)? UART5_MULTIPROCESSOR_WAKEUP_METHOD : UART6_MULTIPROCESSOR_WAKEUP_METHOD)))))


#define HELPER_UART_INT_PRIORITY(N)		    		((N==HELPER_UART1)? UART1_INT_PRIORITY :((N==HELPER_UART2)? UART2_INT_PRIORITY : ((N==HELPER_UART3)? UART3_INT_PRIORITY : ((N==HELPER_UART4)? UART4_INT_PRIORITY : ((N==HELPER_UART5)? UART5_INT_PRIORITY : UART6_INT_PRIORITY)))))

#define HELPER_UART_INT_SUB_PRIORITY(N)		    	((N==HELPER_UART1)? UART1_INT_SUB_PRIORITY :((N==HELPER_UART2)? UART2_INT_SUB_PRIORITY : ((N==HELPER_UART3)? UART3_INT_SUB_PRIORITY : ((N==HELPER_UART4)? UART4_INT_SUB_PRIORITY : ((N==HELPER_UART5)? UART5_INT_SUB_PRIORITY : UART6_INT_SUB_PRIORITY)))))

#define HELPER_UART_INTERRUPT(N)		    		((N==HELPER_UART1)? UART1_INTERRUPT :((N==HELPER_UART2)? UART2_INTERRUPT : ((N==HELPER_UART3)? UART3_INTERRUPT : ((N==HELPER_UART4)? UART4_INTERRUPT : ((N==HELPER_UART5)? UART5_INTERRUPT : UART6_INTERRUPT)))))


#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_UART_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
