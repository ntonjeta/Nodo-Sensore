/**
 ******************************************************************************
 * @file    stm32f4xx_uart_helper.c
 * @author  Salvatore Miranda - SE4
 * @version V2.0
 * @date    16-June-2015
 * @brief   UART Helper Module
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_uart_helper.h"


/** @addtogroup STM32F4xx_Helper_Library
 * @{
 */

/** @defgroup UART_HELPER
 * @brief UART Helper Module
 * @{
 */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static UART_HandleTypeDef    UartHandle1;
static UART_HandleTypeDef    UartHandle2;
static UART_HandleTypeDef    UartHandle3;
static UART_HandleTypeDef    UartHandle4;
static UART_HandleTypeDef    UartHandle5;
static UART_HandleTypeDef    UartHandle6;

/* Private functions ---------------------------------------------------------*/
/** @defgroup UART_HELPER_Private_Functions
 * @{
 */
/* IRQ Handlers -------------------------------------------------------------*/

#if (UART1_INTERRUPT==HELPER_UART_USE_INT)
void USART1_IRQHandler(){
	HAL_UART_IRQHandler(&UartHandle1);
}
#endif

#if (UART2_INTERRUPT==HELPER_UART_USE_INT)
void USART2_IRQHandler(){
	HAL_UART_IRQHandler(&UartHandle2);
}
#endif

#if (UART3_INTERRUPT==HELPER_UART_USE_INT)
void USART3_IRQHandler(){
	HAL_UART_IRQHandler(&UartHandle3);
}
#endif

#if (UART4_INTERRUPT==HELPER_UART_USE_INT)
void UART4_IRQHandler(){
	HAL_UART_IRQHandler(&UartHandle4);
}
#endif

#if (UART5_INTERRUPT==HELPER_UART_USE_INT)
void UART5_IRQHandler(){
	HAL_UART_IRQHandler(&UartHandle5);
}
#endif

#if (UART6_INTERRUPT==HELPER_UART_USE_INT)
void USART6_IRQHandler(){
	HAL_UART_IRQHandler(&UartHandle6);
}
#endif


/**
 * @}
 */


/* Public functions *************************************************************/

/**
 * @brief	Uart Initialization Function.
 * @param	numUart: numero della periferica UART da inizializzare.
 * 			numUart può assumere uno dei seguenti valori:
 * 			@arg HELPER_UART1: periferica UART 1;
 * 			@arg HELPER_UART2: periferica UART 2.
 * 			@arg HELPER_UART3: periferica UART 3;
 * 			@arg HELPER_UART4: periferica UART 4.
 * 			@arg HELPER_UART5: periferica UART 5;
 * 			@arg HELPER_UART6: periferica UART 6.
 *
 * @retval	Stato, che può assumere uno dei seguenti valori:
 * 			@arg	HELPER_UART_OK:	inizializzazione avvenuta con successo;
 * 			@arg	HELPER_UART_ERROR:	Errore qualsiasi avvenuto durante l'Inizializzazione.
 */
HELPER_UART_Status_TypeDef HELPER_UART_Init(HELPER_UART_TypeDef numUart){

		//A seconda della periferica mi riferisco ad un Handle Specifico
		UART_HandleTypeDef  *UartHandle_x=HELPER_UART_GetHandle(numUart);

		if(HAL_UART_GetState(UartHandle_x) == HAL_UART_STATE_RESET)
		  {
		    /* UART configuration -----------------------------------------------------*/

		    UartHandle_x->Instance = HELPER_UART(numUart);

		    UartHandle_x->Init.Mode = HELPER_UART_MODE(numUart);
		    UartHandle_x->Init.WordLength = HELPER_UART_LENGHT(numUart);
		    UartHandle_x->Init.StopBits = HELPER_UART_STOP_B(numUart);
		    UartHandle_x->Init.Parity = HELPER_UART_PARITY(numUart);
		    UartHandle_x->Init.BaudRate = HELPER_UART_BAUDRATE(numUart);
		    UartHandle_x->Init.HwFlowCtl = HELPER_UART_HWCONTROL(numUart);
		    UartHandle_x->Init.OverSampling= HELPER_UART_OVERSAMPLING(numUart);

			//La HAL_UART_MspInit(UartHandle_x) sarà chiamata internamente dalla HAL_XYZ_Init(..)
		    HAL_StatusTypeDef status = 0;
		    switch(HELPER_UART_FUNCTIONAL_MODE(numUart))
		    {
		    	case HELPER_UART_HALF_DUPLEX_MODE: status = HAL_HalfDuplex_Init(UartHandle_x);break;

		    	case HELPER_UART_LIN_MODE: status = HAL_LIN_Init(UartHandle_x,UART_LINBREAKDETECTLENGTH_11B);break;

		    	case HELPER_UART_MULTIPROCESSOR_MODE:
		    		status = HAL_MultiProcessor_Init(UartHandle_x,
		    				HELPER_UART_MULTIPROCESSOR_ADDRESS(numUart),
							HELPER_UART_MULTIPROCESSOR_WAKEUP_METHOD(numUart)
		    		);
		    		break;

		    	default: status = HAL_UART_Init(UartHandle_x);
		    }

		    if(status!=HAL_OK)
		    	return HELPER_UART_ERROR;
		    else
		    	return HELPER_UART_OK;
		  }
		else
			return HELPER_UART_ERROR;
}

/**
 * @brief	Uart De-Initialization Function.
 * @param	numUart: numero della periferica UART da de-inizializzare.
 * 			numUart può assumere uno dei seguenti valori:
 * 			@arg HELPER_UART1: periferica UART 1;
 * 			@arg HELPER_UART2: periferica UART 2.
 * 			@arg HELPER_UART3: periferica UART 3;
 * 			@arg HELPER_UART4: periferica UART 4.
 * 			@arg HELPER_UART5: periferica UART 5;
 * 			@arg HELPER_UART6: periferica UART 6.
 *
 * @retval	None
 */
HAL_StatusTypeDef HELPER_UART_DeInit(HELPER_UART_TypeDef numUart){
	return HAL_UART_DeInit(HELPER_UART_GetHandle(numUart));
}

/**
 * @brief	Funzione di utilità che consente di ottenere il numero di periferica dall'Handle fornito in ingresso.
 *
 * @param	huart: handle della periferica huart.
 *
 * @retval	Il numero della periferica Uart associata all'handle huart.
 *
 */
HELPER_UART_TypeDef HELPER_UART_GetNumUart(UART_HandleTypeDef* huart){

		  if(huart->Instance==USART1) return HELPER_UART1;
		  else
			  if(huart->Instance==USART2) return HELPER_UART2;
			  else
				  if(huart->Instance==USART3) return HELPER_UART3;
				  else
					  if(huart->Instance==UART4) return HELPER_UART4;
					  else
						  if(huart->Instance==UART5) return HELPER_UART5;
						  else return HELPER_UART6;
}

/**
 * @brief	Funzione di utilità che consente di selezionare l'Handle specifico per la periferica Uart indicata.
 *
 * @param	numUart: numero della periferica UART da inizializzare.
 * 			numUart può assumere uno dei seguenti valori:
 * 			@arg HELPER_UART1: periferica UART 1;
 * 			@arg HELPER_UART2: periferica UART 2.
 * 			@arg HELPER_UART3: periferica UART 3;
 * 			@arg HELPER_UART4: periferica UART 4.
 * 			@arg HELPER_UART5: periferica UART 5;
 * 			@arg HELPER_UART6: periferica UART 6.
 *
 * @retval	L'Handler della periferica Uart indicata.
 *
 */
UART_HandleTypeDef* HELPER_UART_GetHandle(HELPER_UART_TypeDef numUart){
	UART_HandleTypeDef  *UartHandle_x=0;
	switch(numUart){
		case HELPER_UART1:UartHandle_x=&UartHandle1;break;
		case HELPER_UART2:UartHandle_x=&UartHandle2;break;
		case HELPER_UART3:UartHandle_x=&UartHandle3;break;
		case HELPER_UART4:UartHandle_x=&UartHandle4;break;
		case HELPER_UART5:UartHandle_x=&UartHandle5;break;
		case HELPER_UART6:UartHandle_x=&UartHandle6;break;
	}
	return UartHandle_x;
}

/**
 * @brief	Funzione che inizializza GPIO e NVIC per l'UART che si sta inizializzando.
 * 			Viene richiamata dalla funzione @ref HAL_UART_Init.
 *
 * @param	huart: Handle specifico della perifericha che si sta inizializzando.
 *
 * @retval  None.
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	  GPIO_InitTypeDef   GPIO_InitStructure;
	  
	  //Seleziono la periferica in base all'istanza
	  HELPER_UART_TypeDef N=HELPER_UART_GetNumUart(huart);
	  
	  /* Enable the UART peripheral */
	  HELPER_UART_CLK_ENABLE(N);

	  /* Enable GPIO clocks
	   * Per l'UART5 abilita SOLO il clock per il porto GPIOC di trasmissione
	   *  */
	  HELPER_UART_GPIO_CLK_ENABLE(N);

	  //Uart General Pin Configurations
	  GPIO_InitStructure.Pull  = GPIO_NOPULL;//GPIO_PULLUP;//
	  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	  GPIO_InitStructure.Alternate = HELPER_UART_AF(N);
	  GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;


//	  switch(huart->Init.Mode){
//	  	  /* UART TX pin configuration */
//		  case UART_MODE_TX: GPIO_InitStructure.Pin = HELPER_UART_TX_PIN(N) ;break;
//		  /* UART RX pin configuration */
//		  case UART_MODE_RX: GPIO_InitStructure.Pin = HELPER_UART_RX_PIN(N); break;
//		  /* UART TX and RX pin configuration */
//		  default:  GPIO_InitStructure.Pin = HELPER_UART_TX_PIN(N)|HELPER_UART_RX_PIN(N);
//	  }
//	  if(N!=HELPER_UART5)
//			  HAL_GPIO_Init(HELPER_UART_GPIO_PORT(N), &GPIO_InitStructure);
//	  else
//		  //Per UART5 con ricezione abilitata cambia il porto del pin di RX, quindi va abilitato opportunamente
//		  if(huart->Init.Mode!=UART_MODE_TX)
//		  {
//			  //Abilito il clock per la ricezione sul porto D (UART5)
//			  HELPER_UART5_GPIO_CLK_ENABLE_RX();
//
//			  //Inizializzo il porto GPIO specializzato per la ricezione (Port D)
//			  HAL_GPIO_Init(HELPER_UART5_GPIO_PORT_RX , &GPIO_InitStructure);
//		  }

	  if(huart->Init.Mode==UART_MODE_TX || huart->Init.Mode==UART_MODE_TX_RX ){

		  GPIO_InitStructure.Pin = HELPER_UART_TX_PIN(N) ;

		  HAL_GPIO_Init(HELPER_UART_GPIO_PORT(N), &GPIO_InitStructure);
	  }

	  // UART RX pin configuration
	  if(huart->Init.Mode==UART_MODE_RX || huart->Init.Mode==UART_MODE_TX_RX ){

		  GPIO_InitStructure.Pin = HELPER_UART_RX_PIN(N);

		  if(N!=HELPER_UART5)
			  HAL_GPIO_Init(HELPER_UART_GPIO_PORT(N), &GPIO_InitStructure);
		  else{
			  //Abilito il clock per la ricezione sul porto D (UART5)
			  HELPER_UART5_GPIO_CLK_ENABLE_RX();

			  //Inizializzo il porto GPIO specializzato per la ricezione (Port D)
			  HAL_GPIO_Init(HELPER_UART5_GPIO_PORT_RX , &GPIO_InitStructure);
		  }
	  }

	  //GESTIONE RTS/CTS (SE HWControl Abilitato)
	  if(N!=HELPER_UART4 && N!=HELPER_UART5 ){
		  switch(huart->Init.HwFlowCtl){
			  case UART_HWCONTROL_RTS:GPIO_InitStructure.Pin = HELPER_UART_RTS_PIN(N);break;
			  case UART_HWCONTROL_CTS:GPIO_InitStructure.Pin = HELPER_UART_CTS_PIN(N);break;
			  case UART_HWCONTROL_RTS_CTS:GPIO_InitStructure.Pin = HELPER_UART_RTS_PIN(N)|HELPER_UART_CTS_PIN(N);break;
		  }
		  if(huart->Init.HwFlowCtl!=UART_HWCONTROL_NONE)
			  HAL_GPIO_Init(HELPER_UART_GPIO_PORT(N), &GPIO_InitStructure);
	  }
	  if(HELPER_UART_INTERRUPT(N)!=HELPER_UART_NO_INT){
		  HAL_NVIC_SetPriority(HELPER_UART_IRQ(N), HELPER_UART_INT_PRIORITY(N), HELPER_UART_INT_SUB_PRIORITY(N));
		  HAL_NVIC_EnableIRQ(HELPER_UART_IRQ(N));
	  }
}

/**
 * @brief	Funzione che deinizializza GPIO e NVIC per l'UART precedentemente inizializzata.
 * 			Viene richiamata dalla funzione @ref HAL_UART_DeInit.
 *
 * @param	huart: Handle specifico della perifericha che si sta inizializzando.
 *
 * @retval	None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart){

	//Seleziono la periferica in base all'istanza
	HELPER_UART_TypeDef N = HELPER_UART_GetNumUart(huart);
	HELPER_UART_FORCE_RESET(N);
	HELPER_UART_RELEASE_RESET(N);

	/* UART TX pin deinit */
	if(huart->Init.Mode==UART_MODE_TX || huart->Init.Mode==UART_MODE_TX_RX )
		HAL_GPIO_DeInit(HELPER_UART_GPIO_PORT(N),HELPER_UART_TX_PIN(N));

	/* UART RX pin deinit */
	if(huart->Init.Mode==UART_MODE_RX || huart->Init.Mode==UART_MODE_TX_RX ){
		//Selezione necessaria per gestire il diverso porto in ricezione dell'Uart5
		if(N!=HELPER_UART5)
			HAL_GPIO_DeInit(HELPER_UART_GPIO_PORT(N),HELPER_UART_RX_PIN(N));
		else
			HAL_GPIO_DeInit(HELPER_UART5_GPIO_PORT_RX ,HELPER_UART_RX_PIN(N));
	}

	 //GESTIONE RTS/CTS (SE HWControl Abilitato e se la periferica UART supporta tale modalità)
	if(N!=HELPER_UART4 && N!=HELPER_UART5 ){
		switch(huart->Init.HwFlowCtl){
			case UART_HWCONTROL_RTS:HAL_GPIO_DeInit(HELPER_UART_GPIO_PORT(N),HELPER_UART_RTS_PIN(N));break;
			case UART_HWCONTROL_CTS:HAL_GPIO_DeInit(HELPER_UART_GPIO_PORT(N),HELPER_UART_CTS_PIN(N));break;
			case UART_HWCONTROL_RTS_CTS:{
				HAL_GPIO_DeInit(HELPER_UART_GPIO_PORT(N),HELPER_UART_RTS_PIN(N));
				HAL_GPIO_DeInit(HELPER_UART_GPIO_PORT(N),HELPER_UART_CTS_PIN(N));
			}break;
		}
	}


	//Disabilito le interruzioni, se erano state abilitate
	if(HELPER_UART_INTERRUPT(N)!=HELPER_UART_NO_INT)
		HAL_NVIC_DisableIRQ(HELPER_UART_IRQ(N));

}


/**
 * @brief	Funzione di trasmissione BLOCCANTE per UART.
 * @param	numUart: numero della periferica UART da cui trasmettere.
 * 			numUart deve essere precedentemente abilitata per la trasmissione previa inizializzazione
 * 			e può assumere uno dei seguenti valori:
 * 			@arg HELPER_UART1: periferica UART 1;
 * 			@arg HELPER_UART2: periferica UART 2.
 * 			@arg HELPER_UART3: periferica UART 3;
 * 			@arg HELPER_UART4: periferica UART 4.
 * 			@arg HELPER_UART5: periferica UART 5;
 * 			@arg HELPER_UART6: periferica UART 6.
 *
 * @param	pData:	puntatore all'area di memoria da cui leggere il valore da trasferire.
 *
 * @param	Size: dimensione del trasferimento.
 * @retval	Stato, che può assumere uno dei seguenti valori:
 * 			@arg	HELPER_UART_OK:	trasmissione avvenuta con successo;
 * 			@arg	HELPER_UART_ERROR:	Errore qualsiasi avvenuto durante la trasmissione.
 */
HELPER_UART_Status_TypeDef HELPER_UART_Transmit(HELPER_UART_TypeDef numUart,uint8_t *pData,uint16_t Size){
	UART_HandleTypeDef  *UartHandle_x=HELPER_UART_GetHandle(numUart);

	while(HAL_UART_Transmit(UartHandle_x, pData, Size, 10000)!=HAL_OK){
	if (HAL_UART_GetError(UartHandle_x) != HAL_UART_ERROR_NONE)
		return  HELPER_UART_ERROR;
	}
	return HELPER_UART_OK;
}


/**
 * @brief	Funzione di ricezione BLOCCANTE per UART.
 * @param	numUart: numero della periferica UART da cui ricevere.
 * 			numUart deve essere precedentemente abilitata per la ricezione previa inizializzazione
 * 			e può assumere uno dei seguenti valori:
 * 			@arg HELPER_UART1: periferica UART 1;
 * 			@arg HELPER_UART2: periferica UART 2.
 * 			@arg HELPER_UART3: periferica UART 3;
 * 			@arg HELPER_UART4: periferica UART 4.
 * 			@arg HELPER_UART5: periferica UART 5;
 * 			@arg HELPER_UART6: periferica UART 6.
 *
 * @param	pData:	puntatore all'area di memoria su cui scrivere i dati trasferiti.
 *
 * @param	Size: dimensione del trasferimento.
 * @retval	Stato, che può assumere uno dei seguenti valori:
 * 			@arg	HELPER_UART_OK:	trasmissione avvenuta con successo;
 * 			@arg	HELPER_UART_ERROR:	Errore qualsiasi avvenuto durante la trasmissione.
 */
HELPER_UART_Status_TypeDef HELPER_UART_Receive(HELPER_UART_TypeDef numUart,uint8_t *pData,uint16_t Size){
	UART_HandleTypeDef  *UartHandle_x=HELPER_UART_GetHandle(numUart);
	while(HAL_UART_Receive(UartHandle_x, pData, Size, 10000)!=HAL_OK){
		 if (HAL_UART_GetError(UartHandle_x) != HAL_UART_ERROR_NONE)
			return HELPER_UART_ERROR;
	}
	return HELPER_UART_OK;
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
