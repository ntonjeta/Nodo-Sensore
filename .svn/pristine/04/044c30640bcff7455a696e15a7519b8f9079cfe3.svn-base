/*
 * gsi.c
 *
 *  Created on: 04/lug/2015
 *      Author: ntonjeta
 */

//#include "gsi_config.h"
#include "gsi.h"

/* Private variables ---------------------------------------------------------*/
GSI_Sensor sensorlist[GSI_SENSOR_NUMBER];

/* Peripheral Handle varibles ------------------------------------------------*/
I2C_HandleTypeDef hi2c3;
SPI_HandleTypeDef hspi2;
ADC_HandleTypeDef hadc1;

#ifdef FIP_SENSOR_ENABLED
USBD_HandleTypeDef USBD_Device;
#endif

// DA FARE ALLOCCAZIONE DEALLOCAZIONE DEI BUFFER
// RX Buffer I2C SPI ---------------------------------------------------------*/
int16_t 	*i2c_rx_buffer,*spi_rx_buffer;
// I2C/SPI variable ----------------------------------------------------------*/
int16_t 	spi_dato,i2c_dato;
uint16_t	i2c_addres;
// Analog sensor variable ----------------------------------------------------*/
uint32_t 	analog_data = 0;
// RX Buffer FIP -------------------------------------------------------------*/
uint8_t* receivingBuffer;
uint8_t* sendingBuffer;

#ifdef FIP_SENSOR_ENABLED
// FIP message variable ------------------------------------------------------*/
FIPMessage* requestSensor, *response, *printTerminal;
#endif

int stop = 0;

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
static void MX_I2C3_Init(void);
static void MX_SPI2_Init(void);
static void MX_ADC1_Init(void);
/* Logical private function --------------------------------------------------*/
Bool 	 isValidID (uint8_t ID,uint16_t *index);
float 	 fipRead   (Class_Type);

//Prevedere delle funzioni che fanno il controllo iniziale della lista


/*###############################################################################*/
/* ------------- Private logical function implementation ------------------------*/
/*###############################################################################*/

/* Check if ID is valid ---------------------------------------------------------*/
Bool isValidID (uint8_t ID,uint16_t *index)
{
	uint16_t i = 0;

	for(i=0;i<GSI_SENSOR_NUMBER;i++)
		if(ID == sensorlist[i].id){
			*index = i;
			return TRUE;
		}
	return FALSE;
}

#ifdef FIP_SENSOR_ENABLED
/* Read Data from CATA -----------------------------------------------------------*/
float fipRead(Class_Type class)
{
	//Variable Declaration
	uint8_t disp_res = 0;
	int receivedBytes,packetSize;
	float readData = 0;

	SensorMessageParameters fipParamsSensor;
	TerminalMessageParameters fipParamsTerminal;

	fipParamsSensor.operation = sensor_one_read ;
	switch(class){
	case Position:
		fipParamsSensor.sensorMask = SENSOR_MASK_PROXIMITY ;
		break;
	case Optical:
		fipParamsSensor.sensorMask = SENSOR_MASK_LIGHT ;
		break;
	case Mechanical:
		fipParamsSensor.sensorMask = SENSOR_MASK_ACCELERATOR_X ;
		break;
	case Electromagnetic:
		fipParamsSensor.sensorMask = SENSOR_MASK_MAGNETIC_X;
		break;
	case Pressure:
		fipParamsSensor.sensorMask = SENSOR_MASK_PRESSURE;
		break;
	case Humidity:
		fipParamsSensor.sensorMask = SENSOR_HUMIDITY;
		break;

	}
	createFIPSensorMessage(fipParamsSensor, &requestSensor);

	fipParamsTerminal.operation = terminal_print;
	fipParamsTerminal.text_buffer = (uint8_t*) malloc(256 * sizeof(uint8_t));

	receivingBuffer = (uint8_t*) malloc(sizeof(uint8_t) * 64);
	sendingBuffer   = (uint8_t*) malloc(sizeof(uint8_t) * 64);

	packetSize 		= serializeFIPMessage(requestSensor, sendingBuffer);
	VCP_write(sendingBuffer, packetSize);

	while (disp_res != 1) {
		receivedBytes = VCP_read(receivingBuffer, 64);
		disp_res = dispatch(receivingBuffer, receivedBytes);
	}

	dequeueMessage(&response);

	switch(class){
	case Position:
		readData = getProximity(response);
		break;
	case Optical:
		readData = getLight(response);
		break;
	case Mechanical:
		readData = getAcceleratorX(response);
		break;
	case Electromagnetic:
		readData = getMagneticX(response);
		break;
	case Pressure:
		readData = getPressure(response);
		break;
	case Humidity:
		readData = getHumidity(response);
		break;

	}

	fipParamsTerminal.text_lenght = sprintf(fipParamsTerminal.text_buffer,"Light Value: %f", getLight(response));

	createFIPTerminalMessage(fipParamsTerminal, &printTerminal);
	packetSize = serializeFIPMessage(printTerminal, sendingBuffer);
	VCP_write(sendingBuffer, packetSize);


	//dealocation
	free(receivingBuffer);
	free(sendingBuffer);
	destroyFIPMessage(response);
	destroyFIPMessage(printTerminal);

	return readData;
}
#endif

/*###############################################################################*/
/*###############################################################################*/


/*###############################################################################*/
/* ---------------------------- Method implementation ---------------------------*/
/*###############################################################################*/

OP_STATE initSensors (void)
{
	/* Initialize hardware --------------------------------------------------------- */

#ifdef I2C_SENSOR_ENABLED
	MX_GPIO_Init();
	MX_I2C3_Init();
	i2c_rx_buffer = malloc(sizeof(uint16_t)*2);

#endif

#ifdef SPI_SENSOR_ENABLED
	MX_GPIO_Init();
	MX_SPI2_Init();
	spi_rx_buffer = malloc(sizeof(uint16_t));


#endif

#ifdef ADC_SENSOR_ENABLED
	MX_GPIO_Init();
	MX_ADC1_Init();
#endif

#ifdef FIP_SENSOR_ENABLED
	USBD_Init(&USBD_Device, &VCP_Desc, 0);
	USBD_RegisterClass(&USBD_Device, &USBD_CDC);
	USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_Template_fops);
	USBD_Start(&USBD_Device);
	HAL_Delay(4000);

	enableDispatching(); //Non ho capito bene a cosa serva sta funzione
#endif

	//	uint16_t i = 0;
	//	for(i=0;i<SENSOR_NUMBER;i++){
	////		sensorlist[i].ID 			= conf_ID[i];
	////		sensorlist[i].sensor_class  = conf_sensor_class[i];
	////		sensorlist[i].link 			= conf_link[i];
	////		sensorlist[i].address 		= conf_addres[i];
	////		sensorlist[i].dataread		= FALSE;

	//QUESTO PEZZO LO DEVO CAMBIARE ASSOLUTAMETNE
	sensorlist[0].id 			= ID_1;
	sensorlist[0].sensor_class 	= CLASS_1;
	sensorlist[0].link			= LINK_1;
	sensorlist[0].address		= ADDRESS_1;
	sensorlist[0].dataread		= FALSE;

	sensorlist[1].id 			= ID_2;
	sensorlist[1].sensor_class 	= CLASS_2;
	sensorlist[1].link			= LINK_2;
	sensorlist[1].address		= ADDRESS_2;
	sensorlist[1].dataread		= FALSE;

	//
	//	sensorlist[2].ID 			= ID_3;
	//	sensorlist[2].sensor_class 	= CLASS_3;
	//	sensorlist[2].link			= LINK_3;
	//	sensorlist[2].address		= ADDRESS_3;
	//	sensorlist[2].dataread		= FALSE;
	//PEZZOTTO DA TOGLIERE

#ifdef I2C_SENSOR_ENABLED
	if(HAL_I2C_Slave_Receive_IT(&hi2c3,i2c_rx_buffer,sizeof(uint16_t)*2) != HAL_OK)
	{
		errorHandler();
	}
#endif

#ifdef SPI_SENSOR_ENABLED
	if(HAL_SPI_Receive_IT(&hspi2,(uint16_t *)spi_rx_buffer,sizeof(uint16_t)) != HAL_OK)
	{
		errorHandler();
	}

#endif

#ifdef ADC_SENSOR_ENABLED
	if(HAL_ADC_Start_IT(&hadc1) != HAL_OK)
	{
		errorHandler();
	}
#endif


	return OP_OK;
}

OP_STATE readData (uint8_t ID,Data *data)
{
	uint16_t i = 0;
	uint16_t sensorID;

	if(isValidID(ID,&sensorID) != TRUE){
		return OP_ERR_ID;
	}

	//In tutto questo io ho ancora il problema di CATE da risolverema vedro di integrarlo con questo codice
	if(sensorlist[sensorID].link == I2C || sensorlist[sensorID].link == SPI){//SE si tratta di sensori digitali sincroni
		if(sensorlist[sensorID].dataread == FALSE){
			return OP_ERR_OVERUN;
		}else{
			data->value = sensorlist[sensorID].lastData.value;
		}
	}else if(sensorlist[sensorID].link == Analog){

		if(sensorlist[sensorID].dataread == FALSE){
			return OP_ERR_OVERUN;
		}else{
			data->value = sensorlist[sensorID].lastData.value;
			sensorlist[sensorID].dataread = FALSE;
		}


	}else if(sensorlist[sensorID].link == CATE){
#ifdef FIP_SENSOR_ENABLED
		sensorlist[sensorID].lastData.value = (int16_t) fipRead(sensorlist[sensorID].sensor_class);
#endif
	}

	return OP_OK;

}

/*###############################################################################*/
/*------------------------------- GET Method ------------------------------------*/
/*###############################################################################*/


void getIDSensorList(uint8_t *ID_array)
{
	uint16_t i = 0;
	for(i=0;i<GSI_SENSOR_NUMBER;i++)
	{
		ID_array[i]= sensorlist[i].id;
	}
}

uint16_t getSensorNumber ()
{
	return (uint16_t)GSI_SENSOR_NUMBER;
}





/*###############################################################################*/
/*###############################################################################*/

/*###############################################################################*/
/* -------------------- CallBack Implementation ---------------------------------*/
/*###############################################################################*/

#ifdef SPI_SENSOR_ENABLED


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	int16_t i = 0;

	spi_dato = *spi_rx_buffer;

	for(i=0;i<GSI_SENSOR_NUMBER;i++)
	{
		if(sensorlist[i].link == SPI){
			sensorlist[i].lastData.value = spi_dato;
			sensorlist[i].dataread = TRUE;
			break;
		}
	}

	//BSP_LED_Toggle(LED4);
	if(HAL_SPI_Receive_IT(&hspi2,(uint16_t *)spi_rx_buffer,sizeof(uint16_t)) != HAL_OK)
	{
		//qui va la logica applicattiva di gestione degli
		errorHandler();
	}
}

#endif

#ifdef I2C_SENSOR_ENABLED

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	int16_t i = 0;
#ifdef TESTING
	BSP_LED_Toggle(LED3);
#endif
	i2c_addres	= i2c_rx_buffer[0];
	i2c_dato	= i2c_rx_buffer[1];
	for(i=0;i<GSI_SENSOR_NUMBER;i++)
	{
		if(sensorlist[i].link == I2C && sensorlist[i].address == i2c_addres){
			sensorlist[i].lastData.value = i2c_dato;
			sensorlist[i].dataread = TRUE;
			break;
		}
	}

	if(HAL_I2C_Slave_Receive_IT(&hi2c3,i2c_rx_buffer,sizeof(uint16_t)*2) != HAL_OK)
	{
		errorHandler();
	}
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
}

#endif

#ifdef ADC_SENSOR_ENABLED

//Per ora la inseriamo ma forse questa callback si deve togliere
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	int16_t i = 0;

	analog_data=HAL_ADC_GetValue(hadc);
	analog_data-= Calibration_Value;
#ifdef TESTING
	BSP_LED_Toggle(LED4);
#endif
	for(i=0;i<GSI_SENSOR_NUMBER;i++)
	{
		if(sensorlist[i].link == Analog){
			sensorlist[i].lastData.value = (uint16_t) analog_data;
			sensorlist[i].dataread = TRUE;
			break;
		}
	}

	if(HAL_ADC_Start_IT(&hadc1) != HAL_OK)
	{
		errorHandler();
	}
}

#endif

/*###############################################################################*/
/*###############################################################################*/

/*###############################################################################*/
/*------------------  Initialization function implementation --------------------*/
/*###############################################################################*/

#ifdef I2C_SENSOR_ENABLED

/* I2C3 init function */
void MX_I2C3_Init(void)
{

	hi2c3.Instance 				= I2C3;
	hi2c3.Init.ClockSpeed 		= 100000;
	hi2c3.Init.DutyCycle 			= I2C_DUTYCYCLE_2;
	hi2c3.Init.OwnAddress1 		= 0;
	hi2c3.Init.AddressingMode 	= I2C_ADDRESSINGMODE_7BIT;
	hi2c3.Init.DualAddressMode	= I2C_DUALADDRESS_DISABLED;
	hi2c3.Init.OwnAddress2 		= 0;
	hi2c3.Init.GeneralCallMode	= I2C_GENERALCALL_DISABLED;
	hi2c3.Init.NoStretchMode 		= I2C_NOSTRETCH_DISABLED;
	HAL_I2C_Init(&hi2c3);

}



#endif

#ifdef SPI_SENSOR_ENABLED

/* SPI1 init function */
void MX_SPI2_Init(void)
{

	hspi2.Instance 				= SPI2;
	hspi2.Init.Mode 			= SPI_MODE_SLAVE;
	hspi2.Init.Direction 		= SPI_DIRECTION_1LINE;
	hspi2.Init.DataSize 		= SPI_DATASIZE_16BIT;
	hspi2.Init.CLKPolarity 		= SPI_POLARITY_HIGH;
	hspi2.Init.CLKPhase 		= SPI_PHASE_1EDGE;
	hspi2.Init.NSS 				= SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler= SPI_BAUDRATEPRESCALER_2;
	hspi2.Init.FirstBit 		= SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode 			= SPI_TIMODE_DISABLED;
	hspi2.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLED;
	hspi2.Init.CRCPolynomial	= 0;
	HAL_SPI_Init(&hspi2);

}

#endif

#ifdef ADC_SENSOR_ENABLED

/*ADC Initialization */
void MX_ADC1_Init(void)
{
	ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc1.Instance 						= ADC1;
	hadc1.Init.ClockPrescaler 			= ADC_CLOCKPRESCALER_PCLK_DIV8;
	hadc1.Init.Resolution 				= ADC_RESOLUTION12b;
	hadc1.Init.ScanConvMode 			= DISABLE;
	hadc1.Init.ContinuousConvMode 		= DISABLE;
	hadc1.Init.DiscontinuousConvMode 	= DISABLE;
	hadc1.Init.ExternalTrigConvEdge 	= ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.DataAlign 				= ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion 			= 1;
	hadc1.Init.DMAContinuousRequests 	= DISABLE;
	hadc1.Init.EOCSelection 			= EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}


#endif


void MX_GPIO_Init()
{
	/* GPIO Ports Clock Enable */
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
}



/*###############################################################################*/
/*###############################################################################*/





//RICORDARSI DI REGISTRARE LE CALLBACK forse �� logica applicativa mo vediamo


void 		destroyGSI	()
{
	//DA FARE
}


//FUNZIONI DI COMODO DA ANDARE A CAMBIARE DOPO


void errorHandler(void)
{
	//BSP_LED_Toggle(LED5);
	while(1) {__NOP();}
}

