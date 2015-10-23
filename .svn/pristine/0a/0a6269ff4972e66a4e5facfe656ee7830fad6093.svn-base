/*
 * gsi_it.c
 *
 *  Created on: 06/lug/2015
 *      Author: ntonjeta
 */


#include "gsi_config.h"

extern I2C_HandleTypeDef hi2c3;
extern SPI_HandleTypeDef hspi2;
extern ADC_HandleTypeDef hadc1;

#ifdef FIP_SENSOR_ENABLED
extern USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;
#endif


/*###############################################################################*/
/*------------------------- CallBack Registration -------------------------------*/
/*###############################################################################*/
#ifdef I2C_SENSOR_ENABLED

void I2C3_ER_IRQHandler(void)
{
  HAL_I2C_ER_IRQHandler(&hi2c3);
}

/**
* @brief This function handles I2C1 event interrupt.
*/
void I2C3_EV_IRQHandler(void)
{
   HAL_I2C_EV_IRQHandler(&hi2c3);
}

#endif

#ifdef SPI_SENSOR_ENABLED

void SPI2_IRQHandler	(void)
{
	HAL_SPI_IRQHandler(&hspi2);

}

#endif

#ifdef ADC_SENSOR_ENABLED

void ADC_IRQHandler(void)
{
  HAL_ADC_IRQHandler(&hadc1);
}

#endif

#ifdef FIP_SENSOR_ENABLED
/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}

/**
  * @brief  OTG_FS_IRQHandler
  *          This function handles USB-On-The-Go FS global interrupt request.
  *          requests.
  * @param  None
  * @retval None
  */
void OTG_FS_IRQHandler(void)
{
   HAL_PCD_IRQHandler(&hpcd);
}

#endif
/*###############################################################################*/
/*###############################################################################*/



