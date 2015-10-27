/* @file    stm32f4xx_i2c_helper.c
 * @author  Giovanni Di Fiore - SE4
 * @version V0.1
 * @date    17-April-2015
 * @brief   SPI Helper Implementation
 * 			This is the main file that implements the prototypes defined in stm32f4xx_spi_helper.h
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
#include "include/stm32f4xx_spi_helper.h"

/** @addtogroup STM32F4xx_Helper_Library Helper Library
 * @{
 */

/** @addtogroup SPI_Helper SPI Helper
 * @{
 */


/* private variables ---------------------------------------------------------*/
static SPI_HandleTypeDef HELPER_SPI1_Handle; /*!< Handler for the SPI1 peripheral */
static SPI_HandleTypeDef HELPER_SPI2_Handle; /*!< Handler for the SPI2 peripheral */
static SPI_HandleTypeDef HELPER_SPI3_Handle; /*!< Handler for the SPI3 peripheral */

/** @defgroup SPI_Helper_IRQHandlers HAL Interrupt handlers
 * @{
 */
#if (SPI_HELPER_SPI1_INT == SPI_HELPER_INT_ON)
void SPI1_IRQHandler(void)
{
	HAL_SPI_IRQHandler(HELPER_SPI_GetHandle(HELPER_SPI1));
}
#endif

#if (SPI_HELPER_SPI2_INT == SPI_HELPER_INT_ON)
void SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(HELPER_SPI_GetHandle(HELPER_SPI2));
}
#endif

#if (SPI_HELPER_SPI3_INT == SPI_HELPER_INT_ON)
void SPI3_IRQHandler(void)
{
	HAL_SPI_IRQHandler(HELPER_SPI_GetHandle(HELPER_SPI3));
}
#endif
/**
 * @}
 */


/** @addtogroup SPI_Helper_Exported_Functions
 * @{
 */ 

/**
 * @brief	This function returns the internal managed handler for the SPI peripheral specified by the input parameter
 * @param	HELPER_SPIx The internal handler's peripheral number
 * @return	The internal managed handler to the peripheral
 */
SPI_HandleTypeDef * HELPER_SPI_GetHandle(HELPER_SPI_TypeDef HELPER_SPIx)
{
	switch(HELPER_SPIx)
	{
		case HELPER_SPI1:
			return &HELPER_SPI1_Handle;
			break;
		case HELPER_SPI2:
			return &HELPER_SPI2_Handle;
			break;
		case HELPER_SPI3:
			return &HELPER_SPI3_Handle;
			break;
		default:
			return 0;
	}
}

/**
 * @brief	This function initialize the peripheral according the configuration
 *			macros/defines specified into the stm32f4xx_spi_helper_conf.h header file
 * @param	HELPER_SPIx The internal handler's peripheral number
 * @return	A status specified by the HAL_StatusTypeDef
 */
HAL_StatusTypeDef HELPER_SPI_Init(HELPER_SPI_TypeDef HELPER_SPIx)
{
	SPI_HandleTypeDef* handle = HELPER_SPI_GetHandle(HELPER_SPIx);

	switch(HELPER_SPIx)
	{
		case HELPER_SPI1:
			handle->Instance				= SPI1;
			handle->Init.Mode				= SPI_HELPER_SPI1_MODE; // this configures the mode (SLAVE or MASTER)
			handle->Init.BaudRatePrescaler	= SPI_HELPER_SPI1_BAUDRATEPRESCALER;
			handle->Init.Direction			= SPI_HELPER_SPI1_DIRECTION;
			handle->Init.CLKPhase			= SPI_HELPER_SPI1_CLKPHASE;
			handle->Init.CLKPolarity		= SPI_HELPER_SPI1_CLKPOLARITY;
			handle->Init.CRCCalculation		= SPI_HELPER_SPI1_CRCCALCULATION;
			handle->Init.CRCPolynomial		= SPI_HELPER_SPI1_CRCPOLYNOMIAL;
			handle->Init.DataSize			= SPI_HELPER_SPI1_DATASIZE;
			handle->Init.FirstBit			= SPI_HELPER_SPI1_FIRSTBIT;
			handle->Init.NSS				= SPI_HELPER_SPI1_NSS;
			handle->Init.TIMode				= SPI_HELPER_SPI1_TIMODE;
			break;
		case HELPER_SPI2:
			handle->Instance				= SPI2;
			handle->Init.Mode 				= SPI_HELPER_SPI2_MODE; // this configures the mode (SLAVE or MASTER)
			handle->Init.BaudRatePrescaler	= SPI_HELPER_SPI2_BAUDRATEPRESCALER;
			handle->Init.Direction			= SPI_HELPER_SPI2_DIRECTION;
			handle->Init.CLKPhase			= SPI_HELPER_SPI2_CLKPHASE;
			handle->Init.CLKPolarity		= SPI_HELPER_SPI2_CLKPOLARITY;
			handle->Init.CRCCalculation		= SPI_HELPER_SPI2_CRCCALCULATION;
			handle->Init.CRCPolynomial		= SPI_HELPER_SPI2_CRCPOLYNOMIAL;
			handle->Init.DataSize			= SPI_HELPER_SPI2_DATASIZE;
			handle->Init.FirstBit			= SPI_HELPER_SPI2_FIRSTBIT;
			handle->Init.NSS				= SPI_HELPER_SPI2_NSS;
			handle->Init.TIMode				= SPI_HELPER_SPI2_TIMODE;
			break;
		case HELPER_SPI3:
			handle->Instance				= SPI3;
			handle->Init.Mode				= SPI_HELPER_SPI3_MODE; // this configures the mode (SLAVE or MASTER)
			handle->Init.BaudRatePrescaler	= SPI_HELPER_SPI3_BAUDRATEPRESCALER;
			handle->Init.Direction			= SPI_HELPER_SPI3_DIRECTION;
			handle->Init.CLKPhase			= SPI_HELPER_SPI3_CLKPHASE;
			handle->Init.CLKPolarity		= SPI_HELPER_SPI3_CLKPOLARITY;
			handle->Init.CRCCalculation		= SPI_HELPER_SPI3_CRCCALCULATION;
			handle->Init.CRCPolynomial		= SPI_HELPER_SPI3_CRCPOLYNOMIAL;
			handle->Init.DataSize			= SPI_HELPER_SPI3_DATASIZE;
			handle->Init.FirstBit			= SPI_HELPER_SPI3_FIRSTBIT;
			handle->Init.NSS				= SPI_HELPER_SPI3_NSS;
			handle->Init.TIMode				= SPI_HELPER_SPI3_TIMODE;
			break;
	}

	// reset and init
	handle->State = HAL_SPI_STATE_RESET;

	return HAL_SPI_Init(handle);
}

/**
 * @brief 	This function de-initialize the peripheral referenced by the parameter
 * @param 	HELPER_SPIx The internal handler's peripheral number to de-initialize
 * @return 	A status specified by the HAL_StatusTypeDef
 */
HAL_StatusTypeDef	HELPER_SPI_DeInit(HELPER_SPI_TypeDef HELPER_SPIx)
{
	switch(HELPER_SPIx)
	{
		case HELPER_SPI1:
			return HAL_SPI_DeInit(&HELPER_SPI1_Handle);
			break;
		case HELPER_SPI2:
			return HAL_SPI_DeInit(&HELPER_SPI2_Handle);
			break;
		case HELPER_SPI3:
			return HAL_SPI_DeInit(&HELPER_SPI3_Handle);
			break;
		default:
			return 0;
	}
}



/**
 * @}
 */


/** @defgroup SPI_Helper_HAL_Weak_Implementation Weak implementations of HAL functions
 * @brief These implementations are required by the HAL to initialize the low level hardware for the SPI peripherals.
 * @{
 */
 
/**
 * @brief	This function initialize the low level hardware for each peripheral specified into the SPI handle pointer as input.
 * 			- Clock initialization;
 * 			- GPIO initialization for SCK, MISO and MOSI pins;
 * 			- Enables interrupts if configured;
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	// if we are configuring SPI1
	if (hspi->Instance == SPI1)
	{
		SPI_HELPER_SPI1_SCK_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI1_MISO_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI1_MOSI_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI1_CLK_ENABLE();

		/*##-1- Configure peripheral GPIO ##########################################*/
		/* SPI SCK GPIO pin configuration  */
		GPIO_InitStruct.Pin       = SPI_HELPER_SPI1_SCK_GPIO_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI1_SCK_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPI_HELPER_SPI1_MISO_GPIO_PIN;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI1_MISO_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPI_HELPER_SPI1_MOSI_GPIO_PIN;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI1_MOSI_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI1_MOSI_GPIO_PORT, &GPIO_InitStruct);

		/* Enable Interrupt if configured. See stm32f4xx_helper_conf.h file. */
		if (SPI_HELPER_SPI1_INT==SPI_HELPER_INT_ON)
		{
			HAL_NVIC_SetPriority(SPI1_IRQn, SPI_HELPER_SPI1_INT_PRIORITY, SPI_HELPER_SPI1_INT_SUBPRIORITY);
			HAL_NVIC_EnableIRQ(SPI1_IRQn);
		}

	}
	else if (hspi->Instance == SPI2) // now configure SPI2
	{
		SPI_HELPER_SPI2_SCK_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI2_MISO_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI2_MOSI_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI2_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* SPI SCK GPIO pin configuration  */
		GPIO_InitStruct.Pin       = SPI_HELPER_SPI2_SCK_GPIO_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI2_SCK_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPI_HELPER_SPI2_MISO_GPIO_PIN;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI2_MISO_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI2_MISO_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPI_HELPER_SPI2_MOSI_GPIO_PIN;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI2_MOSI_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI2_MOSI_GPIO_PORT, &GPIO_InitStruct);

		/* Enable Interrupt if configured. See stm32f4xx_helper_conf.h file. */
		if (SPI_HELPER_SPI2_INT==SPI_HELPER_INT_ON)
		{
			HAL_NVIC_SetPriority(SPI2_IRQn, SPI_HELPER_SPI2_INT_PRIORITY, SPI_HELPER_SPI2_INT_SUBPRIORITY);
			HAL_NVIC_EnableIRQ(SPI2_IRQn);
		}

	}
	else if (hspi->Instance == SPI3) // now configure SPI2
	{
		SPI_HELPER_SPI3_SCK_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI3_MISO_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI3_MOSI_GPIO_CLK_ENABLE();
		SPI_HELPER_SPI3_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* SPI SCK GPIO pin configuration  */
		GPIO_InitStruct.Pin       = SPI_HELPER_SPI3_SCK_GPIO_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI3_SCK_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI3_SCK_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPI_HELPER_SPI3_MISO_GPIO_PIN;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI3_MISO_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI3_MISO_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPI_HELPER_SPI3_MOSI_GPIO_PIN;
		GPIO_InitStruct.Alternate = SPI_HELPER_SPI3_MOSI_GPIO_AF;
		HAL_GPIO_Init(SPI_HELPER_SPI3_MOSI_GPIO_PORT, &GPIO_InitStruct);

		/* Enable Interrupt if configured. See stm32f4xx_helper_conf.h file. */
		if (SPI_HELPER_SPI3_INT==SPI_HELPER_INT_ON)
		{
			HAL_NVIC_SetPriority(SPI3_IRQn, SPI_HELPER_SPI3_INT_PRIORITY, SPI_HELPER_SPI3_INT_SUBPRIORITY);
			HAL_NVIC_EnableIRQ(SPI3_IRQn);
		}
	}

}

/**
 * @brief	This function de-initialize the low level hardware for each peripheral specified into the SPI handle pointer as input.
 * 			- Clock reset;
 * 			- GPIO reset for SCK, MISO and MOSI pins;
 * 			- Disables interrupts if configured;
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
	// deInit SP1
	if (hspi->Instance == SPI1)
	{
		SPI_HELPER_SPI1_FORCE_RESET();
		SPI_HELPER_SPI1_RELEASE_RESET();

		/* DeInit SPI1 SCK */
		HAL_GPIO_DeInit(SPI_HELPER_SPI1_SCK_GPIO_PORT, SPI_HELPER_SPI1_SCK_GPIO_PIN);
		/* DeInit SPI1 MISO */
		HAL_GPIO_DeInit(SPI_HELPER_SPI1_MISO_GPIO_PORT, SPI_HELPER_SPI1_MISO_GPIO_PIN);
		/* DeInit SPI1 MOSI */
		HAL_GPIO_DeInit(SPI_HELPER_SPI1_MOSI_GPIO_PORT, SPI_HELPER_SPI1_MOSI_GPIO_PIN);

		if (SPI_HELPER_SPI1_INT==SPI_HELPER_INT_ON)
		{
			HAL_NVIC_DisableIRQ(SPI1_IRQn);
		}
	}
	else if (hspi->Instance == SPI2) // now deInit SPI2
	{
		SPI_HELPER_SPI2_FORCE_RESET();
		SPI_HELPER_SPI2_RELEASE_RESET();

		/* DeInit SPI2 SCK */
		HAL_GPIO_DeInit(SPI_HELPER_SPI2_SCK_GPIO_PORT, SPI_HELPER_SPI2_SCK_GPIO_PIN);
		/* DeInit SPI2 MISO */
		HAL_GPIO_DeInit(SPI_HELPER_SPI2_MISO_GPIO_PORT, SPI_HELPER_SPI2_MISO_GPIO_PIN);
		/* DeInit SPI2 MOSI */
		HAL_GPIO_DeInit(SPI_HELPER_SPI2_MOSI_GPIO_PORT, SPI_HELPER_SPI2_MOSI_GPIO_PIN);

		if (SPI_HELPER_SPI2_INT==SPI_HELPER_INT_ON)
		{
			HAL_NVIC_DisableIRQ(SPI2_IRQn);
		}

	}
	else if (hspi->Instance == SPI3) // now deInit SPI2
	{
		SPI_HELPER_SPI3_FORCE_RESET();
		SPI_HELPER_SPI3_RELEASE_RESET();

		/* DeInit SPI3 SCK */
		HAL_GPIO_DeInit(SPI_HELPER_SPI3_SCK_GPIO_PORT, SPI_HELPER_SPI3_SCK_GPIO_PIN);
		/* DeInit SPI3 MISO */
		HAL_GPIO_DeInit(SPI_HELPER_SPI3_MISO_GPIO_PORT, SPI_HELPER_SPI3_MISO_GPIO_PIN);
		/* DeInit SPI3 MOSI */
		HAL_GPIO_DeInit(SPI_HELPER_SPI3_MOSI_GPIO_PORT, SPI_HELPER_SPI3_MOSI_GPIO_PIN);

		if (SPI_HELPER_SPI3_INT==SPI_HELPER_INT_ON)
		{
			HAL_NVIC_DisableIRQ(SPI3_IRQn);
		}
	}
}

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

