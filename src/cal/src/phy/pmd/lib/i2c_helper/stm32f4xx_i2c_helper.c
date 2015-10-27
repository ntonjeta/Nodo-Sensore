/**
 ******************************************************************************
 * @file    stm32f4xx_i2c_helper.c
 * @author  Federico Iannucci - SE4
 * @version V0.3
 * @date    17-April-2015
 * @brief   I2C Helper Module
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
#include "stm32f4xx_i2c_helper.h"

/** @addtogroup STM32F4xx_Helper_Library
 * @{
 */

/** @addtogroup I2C_Helper
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup I2C_Helper_Private_Defines Private Defines
 * @{
 */

/** @addtogroup I2C_Helper_Private_Defines_Group1 Interrupt Flags
 * @brief Interrupt flags.
 * @{
 */
#ifndef I2C_HELPER_I2C1_EV_IT_ENABLE
#define I2C_HELPER_I2C1_EV_IT_ENABLE 0
#endif
#ifndef I2C_HELPER_I2C1_ER_IT_ENABLE
#define I2C_HELPER_I2C1_ER_IT_ENABLE 0
#endif

#ifndef I2C_HELPER_I2C2_EV_IT_ENABLE
#define I2C_HELPER_I2C2_EV_IT_ENABLE 0
#endif
#ifndef I2C_HELPER_I2C2_ER_IT_ENABLE
#define I2C_HELPER_I2C2_ER_IT_ENABLE 0
#endif

#ifndef I2C_HELPER_I2C3_EV_IT_ENABLE
#define I2C_HELPER_I2C3_EV_IT_ENABLE 0
#endif
#ifndef I2C_HELPER_I2C3_ER_IT_ENABLE
#define I2C_HELPER_I2C3_ER_IT_ENABLE 0
#endif

/**
 * @}
 */

/** @addtogroup I2C_Helper_Private_Defines_Group2 DMA Flags
 * @brief Interrupt flags.
 * @{
 */
#ifndef I2C_HELPER_I2C1_DMA_ENABLE
#define I2C_HELPER_I2C1_DMA_ENABLE 0
#endif

#ifndef I2C_HELPER_I2C2_DMA_ENABLE
#define I2C_HELPER_I2C2_DMA_ENABLE 0
#endif

#ifndef I2C_HELPER_I2C3_DMA_ENABLE
#define I2C_HELPER_I2C3_DMA_ENABLE 0
#endif

/**
 * @}
 */

/**
 * @}
 */

/* Private macro -------------------------------------------------------------*/

/** @addtogroup I2C_Helper_Private_Macros Private Macros
 * @{
 */
#define HELPER_I2C_UNUSED  __attribute__((unused))

/**
 * @}
 */

/* Private variables ---------------------------------------------------------*/
/** @addtogroup I2C_Helper_Private_Variables Private Variables
 * @{
 */

/** @addtogroup I2C_Helper_Private_Variables_Group1 I2C Handlers
 * @brief Peripheral handlers.
 * @{
 */
static I2C_HandleTypeDef HELPER_I2C1_Handle; /*!< Handler for the I2C1 peripheral */
static I2C_HandleTypeDef HELPER_I2C2_Handle; /*!< Handler for the I2C2 peripheral */
static I2C_HandleTypeDef HELPER_I2C3_Handle; /*!< Handler for the I2C3 peripheral */

/**
 * @}
 */

/** @addtogroup I2C_Helper_Private_Variables_Group2 DMA Handlers
 * @brief DMA handlers.
 * @{
 */
static DMA_HandleTypeDef  HELPER_I2C1_hdma_tx HELPER_I2C_UNUSED; /* Transmission */
static DMA_HandleTypeDef HELPER_I2C1_hdma_rx HELPER_I2C_UNUSED; /* Reception */
static DMA_HandleTypeDef HELPER_I2C2_hdma_tx HELPER_I2C_UNUSED; /* Transmission */
static DMA_HandleTypeDef HELPER_I2C2_hdma_rx HELPER_I2C_UNUSED; /* Reception */
static DMA_HandleTypeDef HELPER_I2C3_hdma_tx HELPER_I2C_UNUSED; /* Transmission */
static DMA_HandleTypeDef HELPER_I2C3_hdma_rx HELPER_I2C_UNUSED; /* Reception */

/**
 * @}
 */

/**
 * @}
 */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Helper_Private_Functions Weak Implemented Functions
 * @ IRQ Handlers, MspInit and MspDeInit.
 * @{
 */

/** @defgroup I2C_Helper_IRQ_Handler IRQ Handlers
 * @{
 */

/* IRQ Handlers -------------------------------------------------------------*/
#if (I2C_HELPER_I2C1_EV_IT_ENABLE == 1)
/**
 * @brief Event Handler for the I2C1 component.
 */
void I2C1_EV_IRQHandler()
{
	//HAL_I2C_EV_IRQHandler(&HELPER_I2C1_Handle);
	I2C_HELPER_EV_IRQHandler(&HELPER_I2C1_Handle);
}
#endif

#if (I2C_HELPER_I2C1_ER_IT_ENABLE == 1)
/**
 * @brief Error Handler for the I2C1 component.
 */
void I2C1_ER_IRQHandler()
{
	//HAL_I2C_ER_IRQHandler(&HELPER_I2C1_Handle);
	I2C_HELPER_ER_IRQHandler(&HELPER_I2C1_Handle);
}
#endif

#if (I2C_HELPER_I2C2_EV_IT_ENABLE == 1)
/**
 * @brief Event Handler for the I2C2 component.
 */
void I2C2_EV_IRQHandler()
{
	//HAL_I2C_EV_IRQHandler(&HELPER_I2C2_Handle);
	I2C_HELPER_EV_IRQHandler(&HELPER_I2C2_Handle);
}
#endif

#if (I2C_HELPER_I2C2_ER_IT_ENABLE == 1)
/**
 * @brief Error Handler for the I2C2 component.
 */
void I2C2_ER_IRQHandler()
{
	//HAL_I2C_ER_IRQHandler(&HELPER_I2C2_Handle);
	I2C_HELPER_ER_IRQHandler(&HELPER_I2C2_Handle);
}
#endif

#if (I2C_HELPER_I2C3_EV_IT_ENABLE == 1)
/**
 * @brief Event Handler for the I2C3 component.
 */
void I2C3_EV_IRQHandler()
{
	//HAL_I2C_EV_IRQHandler(&HELPER_I2C3_Handle);
	I2C_HELPER_EV_IRQHandler(&HELPER_I2C3_Handle);
}
#endif

#if (I2C_HELPER_I2C3_ER_IT_ENABLE == 1)
/**
 * @brief Error Handler for the I2C3 component.
 */
void I2C3_ER_IRQHandler()
{
	//HAL_I2C_ER_IRQHandler(&HELPER_I2C3_Handle);
	I2C_HELPER_ER_IRQHandler(&HELPER_I2C3_Handle);
}
#endif

/**
 * @}
 */

/** @defgroup I2C_Helper_IRQ_Handler DMA IRQ Handlers
 * @{
 */

#if (I2C_HELPER_I2C1_DMA_TX_ENABLE == 1)
/**
 * @brief This function handle DMA Interrupt
 */
void I2C_HELPER_I2C1_DMA_TX_IRQHandler()
{
	HAL_DMA_IRQHandler(HELPER_I2C1_Handle.hdmatx);
}
#endif

#if (I2C_HELPER_I2C1_DMA_RX_ENABLE == 1)
/**
 * @brief This function handle DMA Interrupt
 */
void I2C_HELPER_I2C1_DMA_RX_IRQHandler()
{
	HAL_DMA_IRQHandler(HELPER_I2C1_Handle.hdmarx);
}
#endif

#if (I2C_HELPER_I2C2_DMA_TX_ENABLE == 1)
/**
 * @brief This function handle DMA Interrupt
 */
void I2C_HELPER_I2C2_DMA_TX_IRQHandler()
{
	HAL_DMA_IRQHandler(HELPER_I2C2_Handle.hdmatx);
}
#endif

#if (I2C_HELPER_I2C2_DMA_RX_ENABLE == 1)
/**
 * @brief This function handle DMA Interrupt
 */
void I2C_HELPER_I2C2_DMA_RX_IRQHandler()
{
	HAL_DMA_IRQHandler(HELPER_I2C2_Handle.hdmarx);
}
#endif

#if (I2C_HELPER_I2C3_DMA_TX_ENABLE == 1)
/**
 * @brief This function handle DMA Interrupt
 */
void I2C_HELPER_I2C3_DMA_TX_IRQHandler()
{
	HAL_DMA_IRQHandler(HELPER_I2C3_Handle.hdmatx);
}
#endif

#if (I2C_HELPER_I2C3_DMA_RX_ENABLE == 1)
/**
 * @brief This function handle DMA Interrupt
 */
void I2C_HELPER_I2C3_DMA_RX_IRQHandler()
{
	HAL_DMA_IRQHandler(HELPER_I2C3_Handle.hdmarx);
}
#endif

/**
 * @}
 */

/**@addtogroup I2C_Helper_Init_Functions Initialization Functions
 * @{
 */

/**
 * @brief I2C MSP Initialization
 *        This function configures the hardware resources used:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - DMA configuration for transmission request by peripheral
 *           - NVIC configuration for DMA interrupt request enable
 *        This function is called by HAL_i2C_Init.
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (hi2c->Instance == I2C1)
	{
		/*##-1- Enable GPIO Clocks #################################################*/
		/* Enable GPIO SDA/SCL clock */
		I2C_HELPER_I2C1_SDA_GPIO_CLK_ENABLE();
		I2C_HELPER_I2C1_SCL_GPIO_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* I2C SCL GPIO pin configuration  */
		GPIO_InitStruct.Pin = I2C_HELPER_I2C1_SCL_GPIO_PIN; /* Which pin */
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; /* The Mode MUST BE OpenDrain */
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = I2C_HELPER_I2C1_SCL_GPIO_AF;
		HAL_GPIO_Init(I2C_HELPER_I2C1_SCL_GPIO_PORT, &GPIO_InitStruct);

		/* I2C SDA GPIO pin configuration  */
		GPIO_InitStruct.Pin = I2C_HELPER_I2C1_SDA_GPIO_PIN;
		GPIO_InitStruct.Alternate = I2C_HELPER_I2C1_SDA_GPIO_AF;
		HAL_GPIO_Init(I2C_HELPER_I2C1_SDA_GPIO_PORT, &GPIO_InitStruct);

		/*##-3- Configure the DMA streams ##########################################*/
#if (I2C_HELPER_I2C1_DMA_TX_ENABLE == 1)
		/* Enable DMA1 clock */
		I2C_HELPER_I2Cx_DMA_CLK_ENABLE();

		/* Configure the DMA handler for Transmission process */
		HELPER_I2C1_hdma_tx.Instance = I2C_HELPER_I2C1_DMA_TX_STREAM;

		HELPER_I2C1_hdma_tx.Init.Channel = I2C_HELPER_I2C1_DMA_TX_CHANNEL;
		HELPER_I2C1_hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		HELPER_I2C1_hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		HELPER_I2C1_hdma_tx.Init.MemInc = DMA_MINC_ENABLE;
		HELPER_I2C1_hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HELPER_I2C1_hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		HELPER_I2C1_hdma_tx.Init.Mode = DMA_NORMAL;
		HELPER_I2C1_hdma_tx.Init.Priority = DMA_PRIORITY_LOW;
		HELPER_I2C1_hdma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HELPER_I2C1_hdma_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		HELPER_I2C1_hdma_tx.Init.MemBurst = DMA_MBURST_INC4;
		HELPER_I2C1_hdma_tx.Init.PeriphBurst = DMA_PBURST_INC4;

		HAL_DMA_Init(&HELPER_I2C1_hdma_tx);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hi2c, hdmatx, HELPER_I2C1_hdma_tx);

		/*##-3.1- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for DMA transfer complete interrupt (I2C1_TX) */
		HAL_NVIC_SetPriority(I2C_HELPER_I2C1_DMA_TX_IRQn,
		I2C_HELPER_I2C1_DMA_TX_PRIORITY,
		I2C_HELPER_I2C1_DMA_TX_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C_HELPER_I2C1_DMA_TX_IRQn);
#endif
#if (I2C_HELPER_I2C1_DMA_RX_ENABLE == 1)
		/* Enable DMA1 clock */
		I2C_HELPER_I2Cx_DMA_CLK_ENABLE();

		/* Configure the DMA handler for Transmission process */
		HELPER_I2C1_hdma_rx.Instance = I2C_HELPER_I2C1_DMA_RX_STREAM;

		HELPER_I2C1_hdma_rx.Init.Channel = I2C_HELPER_I2C1_DMA_RX_CHANNEL;
		HELPER_I2C1_hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		HELPER_I2C1_hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		HELPER_I2C1_hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
		HELPER_I2C1_hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HELPER_I2C1_hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		HELPER_I2C1_hdma_rx.Init.Mode = DMA_NORMAL;
		HELPER_I2C1_hdma_rx.Init.Priority = DMA_PRIORITY_HIGH;
		HELPER_I2C1_hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HELPER_I2C1_hdma_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		HELPER_I2C1_hdma_rx.Init.MemBurst = DMA_MBURST_INC4;
		HELPER_I2C1_hdma_rx.Init.PeriphBurst = DMA_PBURST_INC4;

		HAL_DMA_Init(&HELPER_I2C1_hdma_rx);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hi2c, hdmarx, HELPER_I2C1_hdma_rx);

		/*##-3.1- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for DMA transfer complete interrupt (I2C1_RX) */
		HAL_NVIC_SetPriority(I2C_HELPER_I2C1_DMA_RX_IRQn,
				I2C_HELPER_I2C1_DMA_RX_PRIORITY,
				I2C_HELPER_I2C1_DMA_RX_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C_HELPER_I2C1_DMA_RX_IRQn);
#endif
		/*##-4- Enable I2C peripheral Clock ########################################*/
		/* Enable I2C1 clock */
		I2C_HELPER_I2C1_CLK_ENABLE();

		/*##-5- Enable interrupt #######################################*/
#if (I2C_HELPER_I2C1_EV_IT_ENABLE == 1)
		HAL_NVIC_SetPriority(I2C1_EV_IRQn, I2C_HELPER_I2C1_EV_IT_PRIORITY,
				I2C_HELPER_I2C1_EV_IT_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
#endif
#if (I2C_HELPER_I2C1_ER_IT_ENABLE == 1)
		HAL_NVIC_SetPriority(I2C1_ER_IRQn, I2C_HELPER_I2C1_ER_IT_PRIORITY,
				I2C_HELPER_I2C1_ER_IT_PRIORITY);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
#endif

	}
	else if (hi2c->Instance == I2C2)
	{
		/*##-1- Enable GPIO Clocks #################################################*/
		/* Enable GPIO SDA/SCL clock */
		I2C_HELPER_I2C2_SDA_GPIO_CLK_ENABLE();
		I2C_HELPER_I2C2_SCL_GPIO_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* I2C SCL GPIO pin configuration  */
		GPIO_InitStruct.Pin = I2C_HELPER_I2C2_SCL_GPIO_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = I2C_HELPER_I2C2_SCL_GPIO_AF;
		HAL_GPIO_Init(I2C_HELPER_I2C2_SCL_GPIO_PORT, &GPIO_InitStruct);

		/* I2C SDA GPIO pin configuration  */
		GPIO_InitStruct.Pin = I2C_HELPER_I2C2_SDA_GPIO_PIN;
		GPIO_InitStruct.Alternate = I2C_HELPER_I2C2_SDA_GPIO_AF;
		HAL_GPIO_Init(I2C_HELPER_I2C2_SDA_GPIO_PORT, &GPIO_InitStruct);

		/*##-3- Configure the DMA streams ##########################################*/
#if (I2C_HELPER_I2C2_DMA_TX_ENABLE == 1)
		/* Enable DMA1 clock */
		I2C_HELPER_I2Cx_DMA_CLK_ENABLE();

		/* Configure the DMA handler for Transmission process */
		HELPER_I2C2_hdma_tx.Instance = I2C_HELPER_I2C2_DMA_TX_STREAM;

		HELPER_I2C2_hdma_tx.Init.Channel = I2C_HELPER_I2C2_DMA_TX_CHANNEL;
		HELPER_I2C2_hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		HELPER_I2C2_hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		HELPER_I2C2_hdma_tx.Init.MemInc = DMA_MINC_ENABLE;
		HELPER_I2C2_hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HELPER_I2C2_hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		HELPER_I2C2_hdma_tx.Init.Mode = DMA_NORMAL;
		HELPER_I2C2_hdma_tx.Init.Priority = DMA_PRIORITY_LOW;
		HELPER_I2C2_hdma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HELPER_I2C2_hdma_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		HELPER_I2C2_hdma_tx.Init.MemBurst = DMA_MBURST_INC4;
		HELPER_I2C2_hdma_tx.Init.PeriphBurst = DMA_PBURST_INC4;

		HAL_DMA_Init(&HELPER_I2C2_hdma_tx);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hi2c, hdmatx, HELPER_I2C2_hdma_tx);

		/*##-3.1- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for DMA transfer complete interrupt (I2C1_TX) */
		HAL_NVIC_SetPriority(I2C_HELPER_I2C2_DMA_TX_IRQn, I2C_HELPER_I2C2_DMA_TX_PRIORITY, I2C_HELPER_I2C2_DMA_TX_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C_HELPER_I2C2_DMA_TX_IRQn);
#endif
#if (I2C_HELPER_I2C2_DMA_RX_ENABLE == 1)
		/* Configure the DMA handler for Transmission process */
		HELPER_I2C2_hdma_rx.Instance = I2C_HELPER_I2C2_DMA_RX_STREAM;

		HELPER_I2C2_hdma_rx.Init.Channel = I2C_HELPER_I2C2_DMA_RX_CHANNEL;
		HELPER_I2C2_hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		HELPER_I2C2_hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		HELPER_I2C2_hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
		HELPER_I2C2_hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HELPER_I2C2_hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		HELPER_I2C2_hdma_rx.Init.Mode = DMA_NORMAL;
		HELPER_I2C2_hdma_rx.Init.Priority = DMA_PRIORITY_HIGH;
		HELPER_I2C2_hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HELPER_I2C2_hdma_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		HELPER_I2C2_hdma_rx.Init.MemBurst = DMA_MBURST_INC4;
		HELPER_I2C2_hdma_rx.Init.PeriphBurst = DMA_PBURST_INC4;

		HAL_DMA_Init(&HELPER_I2C2_hdma_rx);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hi2c, hdmarx, HELPER_I2C2_hdma_rx);

		/*##-3.1- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for DMA transfer complete interrupt (I2C1_RX) */
		HAL_NVIC_SetPriority(I2C_HELPER_I2C2_DMA_RX_IRQn,
		I2C_HELPER_I2C2_DMA_RX_PRIORITY, I2C_HELPER_I2C2_DMA_RX_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C_HELPER_I2C2_DMA_RX_IRQn);
#endif
		/*##-4- Enable I2C peripheral Clock ########################################*/
		/* Enable I2C2 clock */
		I2C_HELPER_I2C2_CLK_ENABLE();

		/*##-5- Enable interrupt #######################################*/
#if (I2C_HELPER_I2C2_EV_IT_ENABLE == 1)
		HAL_NVIC_SetPriority(I2C2_EV_IRQn, I2C_HELPER_I2C2_EV_IT_PRIORITY,
		I2C_HELPER_I2C2_EV_IT_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
#endif
#if (I2C_HELPER_I2C2_ER_IT_ENABLE == 1)
		HAL_NVIC_SetPriority(I2C2_ER_IRQn, I2C_HELPER_I2C2_ER_IT_PRIORITY,
		I2C_HELPER_I2C2_ER_IT_PRIORITY);
		HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
#endif

	}
	else if (hi2c->Instance == I2C3)
	{
		/*##-1- Enable GPIO Clocks #################################################*/
		/* Enable GPIO SDA/SCL clock */
		I2C_HELPER_I2C3_SDA_GPIO_CLK_ENABLE();
		I2C_HELPER_I2C3_SCL_GPIO_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* I2C SCL GPIO pin configuration  */
		GPIO_InitStruct.Pin = I2C_HELPER_I2C3_SCL_GPIO_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = I2C_HELPER_I2C3_SCL_GPIO_AF;
		HAL_GPIO_Init(I2C_HELPER_I2C3_SCL_GPIO_PORT, &GPIO_InitStruct);

		/* I2C SDA GPIO pin configuration  */
		GPIO_InitStruct.Pin = I2C_HELPER_I2C3_SDA_GPIO_PIN;
		GPIO_InitStruct.Alternate = I2C_HELPER_I2C3_SDA_GPIO_AF;
		HAL_GPIO_Init(I2C_HELPER_I2C3_SDA_GPIO_PORT, &GPIO_InitStruct);

		/*##-3- Configure the DMA streams ##########################################*/
#if (I2C_HELPER_I2C3_DMA_TX_ENABLE == 1)
		/* Enable DMA1 clock */
		I2C_HELPER_I2Cx_DMA_CLK_ENABLE();

		/* Configure the DMA handler for Transmission process */
		HELPER_I2C3_hdma_tx.Instance = I2C_HELPER_I2C3_DMA_TX_STREAM;

		HELPER_I2C3_hdma_tx.Init.Channel = I2C_HELPER_I2C3_DMA_TX_CHANNEL;
		HELPER_I2C3_hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		HELPER_I2C3_hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		HELPER_I2C3_hdma_tx.Init.MemInc = DMA_MINC_ENABLE;
		HELPER_I2C3_hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HELPER_I2C3_hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		HELPER_I2C3_hdma_tx.Init.Mode = DMA_NORMAL;
		HELPER_I2C3_hdma_tx.Init.Priority = DMA_PRIORITY_LOW;
		HELPER_I2C3_hdma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HELPER_I2C3_hdma_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		HELPER_I2C3_hdma_tx.Init.MemBurst = DMA_MBURST_INC4;
		HELPER_I2C3_hdma_tx.Init.PeriphBurst = DMA_PBURST_INC4;

		HAL_DMA_Init(&HELPER_I2C3_hdma_tx);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hi2c, hdmatx, HELPER_I2C3_hdma_tx);

		/*##-3.1- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for DMA transfer complete interrupt (I2C1_TX) */
		HAL_NVIC_SetPriority(I2C_HELPER_I2C3_DMA_TX_IRQn,
				I2C_HELPER_I2C3_DMA_TX_PRIORITY,
				I2C_HELPER_I2C3_DMA_TX_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C_HELPER_I2C3_DMA_TX_IRQn);
#endif
#if (I2C_HELPER_I2C3_DMA_RX_ENABLE == 1)
		/* Configure the DMA handler for Transmission process */
		HELPER_I2C3_hdma_rx.Instance = I2C_HELPER_I2C3_DMA_RX_STREAM;

		HELPER_I2C3_hdma_rx.Init.Channel = I2C_HELPER_I2C3_DMA_RX_CHANNEL;
		HELPER_I2C3_hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		HELPER_I2C3_hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		HELPER_I2C3_hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
		HELPER_I2C3_hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HELPER_I2C3_hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		HELPER_I2C3_hdma_rx.Init.Mode = DMA_NORMAL;
		HELPER_I2C3_hdma_rx.Init.Priority = DMA_PRIORITY_HIGH;
		HELPER_I2C3_hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HELPER_I2C3_hdma_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		HELPER_I2C3_hdma_rx.Init.MemBurst = DMA_MBURST_INC4;
		HELPER_I2C3_hdma_rx.Init.PeriphBurst = DMA_PBURST_INC4;

		HAL_DMA_Init(&HELPER_I2C3_hdma_rx);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hi2c, hdmarx, HELPER_I2C3_hdma_rx);

		/*##-3.1- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for DMA transfer complete interrupt (I2C1_RX) */
		HAL_NVIC_SetPriority(I2C_HELPER_I2C3_DMA_RX_IRQn, I2C_HELPER_I2C3_DMA_RX_PRIORITY, I2C_HELPER_I2C3_DMA_RX_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C_HELPER_I2C3_DMA_RX_IRQn);
#endif
		/*##-4- Enable I2C peripheral Clock ########################################*/
		/* Enable I2C3 clock */
		I2C_HELPER_I2C3_CLK_ENABLE();

		/*##-5- Enable interrupt #######################################*/
#if (I2C_HELPER_I2C3_EV_IT_ENABLE == 1)
		HAL_NVIC_SetPriority(I2C3_EV_IRQn, I2C_HELPER_I2C3_EV_IT_PRIORITY,
				I2C_HELPER_I2C3_EV_IT_PRIORITY);
		HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
#endif
#if (I2C_HELPER_I2C3_ER_IT_ENABLE == 1)
		HAL_NVIC_SetPriority(I2C3_ER_IRQn, I2C_HELPER_I2C3_ER_IT_PRIORITY,
				I2C_HELPER_I2C3_ER_IT_PRIORITY);
		HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
#endif
	}
}

/**
 * @brief I2C MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO, DMA and NVIC configuration to their default state
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == I2C1)
	{
		/*##-1- Reset peripherals ##################################################*/
		I2C_HELPER_I2C1_FORCE_RESET();
		I2C_HELPER_I2C1_RELEASE_RESET();

		/*##-2- Disable peripherals and GPIO Clocks ################################*/
		/* Configure I2C Tx as alternate function  */
		HAL_GPIO_DeInit(I2C_HELPER_I2C1_SCL_GPIO_PORT,
		I2C_HELPER_I2C1_SCL_GPIO_PIN);
		/* Configure I2C Rx as alternate function  */
		HAL_GPIO_DeInit(I2C_HELPER_I2C1_SDA_GPIO_PORT,
		I2C_HELPER_I2C1_SDA_GPIO_PIN);

		/*##-3- Disable the NVIC for DMA ###########################################*/
		HAL_NVIC_DisableIRQ(I2C_HELPER_I2C1_DMA_TX_IRQn);
		HAL_NVIC_DisableIRQ(I2C_HELPER_I2C1_DMA_RX_IRQn);

		/*##-4- Disable interrupts ################################*/
#if (I2C_HELPER_I2C1_EV_IT_ENABLE == 1)
		HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
#endif
#if (I2C_HELPER_I2C1_ER_IT_ENABLE == 1)
		HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
#endif

	}
	else if (hi2c->Instance == I2C2)
	{
		/*##-1- Reset peripherals ##################################################*/
		I2C_HELPER_I2C2_FORCE_RESET();
		I2C_HELPER_I2C2_RELEASE_RESET();

		/*##-2- Disable peripherals and GPIO Clocks ################################*/
		/* Configure I2C Tx as alternate function  */
		HAL_GPIO_DeInit(I2C_HELPER_I2C2_SCL_GPIO_PORT,
		I2C_HELPER_I2C2_SCL_GPIO_PIN);
		/* Configure I2C Rx as alternate function  */
		HAL_GPIO_DeInit(I2C_HELPER_I2C2_SDA_GPIO_PORT,
		I2C_HELPER_I2C2_SDA_GPIO_PIN);

		/*##-3- Disable the NVIC for DMA ###########################################*/
		HAL_NVIC_DisableIRQ(I2C_HELPER_I2C2_DMA_TX_IRQn);
		HAL_NVIC_DisableIRQ(I2C_HELPER_I2C2_DMA_RX_IRQn);

		/*##-4- Disable interrupts ################################*/
#if (I2C_HELPER_I2C2_EV_IT_ENABLE == 1)
		HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
#endif
#if (I2C_HELPER_I2C2_ER_IT_ENABLE == 1)
		HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
#endif

	}
	else if (hi2c->Instance == I2C3)
	{
		/*##-1- Reset peripherals ##################################################*/
		I2C_HELPER_I2C3_FORCE_RESET();
		I2C_HELPER_I2C3_RELEASE_RESET();

		/*##-2- Disable peripherals and GPIO Clocks ################################*/
		/* Configure I2C Tx as alternate function  */
		HAL_GPIO_DeInit(I2C_HELPER_I2C3_SCL_GPIO_PORT,
		I2C_HELPER_I2C3_SCL_GPIO_PIN);
		/* Configure I2C Rx as alternate function  */
		HAL_GPIO_DeInit(I2C_HELPER_I2C3_SDA_GPIO_PORT,
		I2C_HELPER_I2C3_SDA_GPIO_PIN);

		/*##-3- Disable the NVIC for DMA ###########################################*/
		HAL_NVIC_DisableIRQ(I2C_HELPER_I2C3_DMA_TX_IRQn);
		HAL_NVIC_DisableIRQ(I2C_HELPER_I2C3_DMA_RX_IRQn);

		/*##-4- Disable interrupts ################################*/
#if (I2C_HELPER_I2C3_EV_IT_ENABLE == 1)
		HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);
#endif
#if (I2C_HELPER_I2C3_ER_IT_ENABLE == 1)
		HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
#endif
	}

	/*##-5- Disable the DMA Streams ############################################*/
	/* De-Initialize the DMA Stream associate to transmission process */
	HAL_DMA_DeInit(hi2c->hdmatx);
	/* De-Initialize the DMA Stream associate to reception process */
	HAL_DMA_DeInit(hi2c->hdmatx);
}

/**
 * @}
 */

/* Public functions *************************************************************/
/** @addtogroup SPI_Helper_Exported_Functions Public Functions
 * @{
 */

/**
 * @brief	This function returns the internal managed handler for the I2C peripheral specified by the input parameter
 * @param	HELPER_I2Cx The internal handler's peripheral number
 * @return	The internal managed handler to the peripheral
 */
I2C_HandleTypeDef * HELPER_I2C_GetHandle(HELPER_I2C_TypeDef HELPER_I2Cx)
{
	switch (HELPER_I2Cx)
	{
	case HELPER_I2C1:
		return &HELPER_I2C1_Handle;
		break;
	case HELPER_I2C2:
		return &HELPER_I2C2_Handle;
		break;
	case HELPER_I2C3:
		return &HELPER_I2C3_Handle;
		break;
	default:
		return NULL;
	}
}

/**
 * @brief	This function returns the HELPER_I2C_TypeDef from an I2C_HandlerTypeDef
 * @param	hi2c The internal handler's peripheral number
 * @return	The internal managed handler to the peripheral
 */
HELPER_I2C_TypeDef HELPER_I2C_GetNum(I2C_HandleTypeDef* hi2c)
{

	if (hi2c->Instance == I2C1)
	{
		return HELPER_I2C1;
	}
	else if (hi2c->Instance == I2C2)
	{
		return HELPER_I2C2;
	}
	else if (hi2c->Instance == I2C3)
	{
		return HELPER_I2C3;
	}
	return NULL;
}

/**
 * @brief	This function initialize the peripheral according the configuration
 *			macros/defines specified into the stm32f4xx_i2c_helper_conf.h header file
 * @param	HELPER_I2Cx The internal handler's peripheral number
 * @return	A status specified by the HAL_StatusTypeDef
 */
HAL_StatusTypeDef HELPER_I2C_Init(HELPER_I2C_TypeDef HELPER_I2Cx)
{
	I2C_HandleTypeDef* handle = HELPER_I2C_GetHandle(HELPER_I2Cx);
	HAL_StatusTypeDef status;
	uint8_t enPEC = 0;

	switch (HELPER_I2Cx)
	{
	case HELPER_I2C1:
		handle->Instance = I2C1;
		handle->Init.ClockSpeed = I2C_HELPER_I2C1_CLOCK_SPEED;
		handle->Init.DutyCycle = I2C_HELPER_I2C1_DUTY_CYCLE;
		handle->Init.AddressingMode = I2C_HELPER_I2C1_ADDRESSING_MODE;
		handle->Init.OwnAddress1 = I2C_HELPER_I2C1_OWN_ADDRESS_1;
		handle->Init.DualAddressMode = I2C_HELPER_I2C1_DUAL_ADDRESSING;
		handle->Init.OwnAddress2 = I2C_HELPER_I2C1_OWN_ADDRESS_2;
		handle->Init.GeneralCallMode = I2C_HELPER_I2C1_GENERAL_CALL_MODE;
		handle->Init.NoStretchMode = I2C_HELPER_I2C1_NO_STRETCH_MODE;
		if (I2C_HELPER_I2C1_PEC_MODE == I2C_PECMODE_ENABLE)
		{
			enPEC = 1;
		}
		break;
	case HELPER_I2C2:
		handle->Instance = I2C2;
		handle->Init.ClockSpeed = I2C_HELPER_I2C2_CLOCK_SPEED;
		handle->Init.DutyCycle = I2C_HELPER_I2C2_DUTY_CYCLE;
		handle->Init.AddressingMode = I2C_HELPER_I2C2_ADDRESSING_MODE;
		handle->Init.OwnAddress1 = I2C_HELPER_I2C2_OWN_ADDRESS_1;
		handle->Init.DualAddressMode = I2C_HELPER_I2C2_DUAL_ADDRESSING;
		handle->Init.OwnAddress2 = I2C_HELPER_I2C2_OWN_ADDRESS_2;
		handle->Init.GeneralCallMode = I2C_HELPER_I2C2_GENERAL_CALL_MODE;
		handle->Init.NoStretchMode = I2C_HELPER_I2C1_NO_STRETCH_MODE;
		if (I2C_HELPER_I2C2_PEC_MODE == I2C_PECMODE_ENABLE)
		{
			enPEC = 1;
		}
		break;
	case HELPER_I2C3:
		handle->Instance = I2C3;
		handle->Init.ClockSpeed = I2C_HELPER_I2C3_CLOCK_SPEED;
		handle->Init.DutyCycle = I2C_HELPER_I2C3_DUTY_CYCLE;
		handle->Init.AddressingMode = I2C_HELPER_I2C3_ADDRESSING_MODE;
		handle->Init.OwnAddress1 = I2C_HELPER_I2C3_OWN_ADDRESS_1;
		handle->Init.DualAddressMode = I2C_HELPER_I2C3_DUAL_ADDRESSING;
		handle->Init.OwnAddress2 = I2C_HELPER_I2C3_OWN_ADDRESS_2;
		handle->Init.GeneralCallMode = I2C_HELPER_I2C3_GENERAL_CALL_MODE;
		handle->Init.NoStretchMode = I2C_HELPER_I2C3_NO_STRETCH_MODE;
		if (I2C_HELPER_I2C3_PEC_MODE == I2C_PECMODE_ENABLE)
		{
			enPEC = 1;
		}
		break;
	}

	status = HAL_I2C_Init(handle);
	/* MUST BE after the Init */
	if (status == HAL_OK && enPEC == 1)
	{
		/*Enable PEC on the handle*/
		handle->Instance->CR1 |= I2C_PECMODE_ENABLE;
	}

	return status;
}

/**
 * @brief 	This function de-initialize the peripheral referenced by the parameter
 * @param 	HELPER_I2Cx The internal handler's peripheral number to de-initialize
 * @return 	A status specified by the HAL_StatusTypeDef
 */
HAL_StatusTypeDef HELPER_I2C_DeInit(HELPER_I2C_TypeDef HELPER_I2Cx)
{
	switch (HELPER_I2Cx)
	{
	case HELPER_I2C1:
		return HAL_I2C_DeInit(&HELPER_I2C1_Handle);
		break;
	case HELPER_I2C2:
		return HAL_I2C_DeInit(&HELPER_I2C2_Handle);
		break;
	case HELPER_I2C3:
		return HAL_I2C_DeInit(&HELPER_I2C3_Handle);
		break;
	default:
		return 0;
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

/* HAL PORTING ********************************************************************/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
