/*
 * gsi_msp.c

 *
 *  Created on: 06/lug/2015
 *      Author: ntonjeta
 */


#include "gsi_config.h"

/*###############################################################################*/
/*----.------------------- MSP Initialization Function --------------------------*/
/*###############################################################################*/

#ifdef I2C_SENSOR_ENABLED

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hi2c->Instance==I2C3)
  {

    /**I2C3 GPIO Configuration
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL
    */
    GPIO_InitStruct.Pin 		= GPIO_PIN_9;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull 		= GPIO_PULLUP;
    GPIO_InitStruct.Speed 		= GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate 	= GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin 		= GPIO_PIN_8;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull 		= GPIO_PULLUP;
    GPIO_InitStruct.Speed 		= GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate 	= GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __I2C3_CLK_ENABLE();
   /* System interrupt init*/
    HAL_NVIC_SetPriority(I2C3_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
    HAL_NVIC_SetPriority(I2C3_ER_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
  }

}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{

  if(hi2c->Instance==I2C3)
  {
    /* Peripheral clock disable */
    __I2C3_CLK_DISABLE();

    /**I2C3 GPIO Configuration
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);

    HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
  }

}

#endif

#ifdef SPI_SENSOR_ENABLED

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hspi->Instance==SPI2)
  {
     /* Peripheral clock enable */
    __SPI2_CLK_ENABLE();

    /**SPI2 GPIO Configuration
    PB13     ------> SPI1_SCK
    PB14     ------> SPI1_MISO
    PB15     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* System interrupt init*/
    HAL_NVIC_SetPriority(SPI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SPI2_IRQn);
    }

}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{

  if(hspi->Instance==SPI2)
  {
	/* Peripheral clock disable */
    __SPI2_CLK_DISABLE();

    /**SPI2 GPIO Configuration
    PB13     ------> SPI1_SCK
    PB14     ------> SPI1_MISO
    PB15     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(SPI2_IRQn);
  }

}

#endif

#ifdef ADC_SENSOR_ENABLED

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hadc->Instance==ADC1)
  {
      /* Peripheral clock enable */
    __ADC1_CLK_ENABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* System interrupt init*/
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  }

}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

  if(hadc->Instance==ADC1)
  {
     /* Peripheral clock disable */
    __ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  }

}

#endif

/*###############################################################################*/
/*###############################################################################*/




