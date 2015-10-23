#include "libUART.h"
#include "string.h"
#include "utils.h"
#include "stm32f4_discovery.h"

unsigned char received_string[MAX_STRLEN];
static unsigned char buffer_ricezione[MAX_STRLEN];
UART_HandleTypeDef huart5;

void setup(){
	initUART();
	cleanVector(buffer_ricezione,sizeof(buffer_ricezione));
}

void initUART(){

	//Handle della periferica UART4.

	huart5.Instance = UART5;
	huart5.Init.Mode = UART_MODE_TX_RX;		/* Modalita' Tx ed Rx attive */
	huart5.Init.WordLength = UART_WORDLENGTH_8B;
	huart5.Init.StopBits = UART_STOPBITS_1;
	huart5.Init.Parity = UART_PARITY_NONE;
	huart5.Init.BaudRate = BAUDRATE;
	huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart5.Init.OverSampling= UART_OVERSAMPLING_16;

	HAL_UART_Init(&huart5);

}

void UART5_IRQHandler(){
	HAL_UART_IRQHandler(&huart5);
	__HAL_UART_CLEAR_OREFLAG(&huart5);
	__HAL_UART_CLEAR_FLAG(&huart5,UART_FLAG_RXNE);
}


/**
  * @brief  Rx Transfer completed callbacks.
  * @param  husart: pointer to a USART_HandleTypeDef structure that contains
  *                the configuration information for the specified USART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	getFrame();
	netLevelCallback(received_string);
	while(HAL_UART_Receive_IT(huart,buffer_ricezione,MAX_STRLEN) != HAL_OK){};

}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  husart: pointer to a USART_HandleTypeDef structure that contains
  *                the configuration information for the specified USART module.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	int i =0;
	BSP_LED_Toggle(LED5);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	BSP_LED_On(LED6);
}
// Funzione get
void getFrame()
{
	cleanVector(received_string,sizeof(received_string));
	memcpy(received_string,buffer_ricezione,MAX_BUFFER);
	cleanVector(buffer_ricezione,sizeof(buffer_ricezione));
}

// Funzione che genera un certo ritardo
void Delay( uint32_t nTime)
{
	uint32_t i;
	for (i=0; i<nTime; i++);
}
// Funzione che invia una stringa di caratteri
HAL_StatusTypeDef usart_send(void* frame/*,uint16_t size*/)
{
	while(HAL_UART_Transmit_IT(&huart5, (uint8_t*)frame, MAX_STRLEN) != HAL_OK);
	return HAL_OK;
}

HAL_StatusTypeDef usart_receive()
{
	while(HAL_UART_Receive_IT(&huart5,buffer_ricezione,MAX_STRLEN) != HAL_OK){};
	return HAL_OK;
}


