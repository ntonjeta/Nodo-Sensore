/**
 ******************************************************************************
 * @file    stm32f4xx_hal_i2c.c
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    26-December-2014
 * @brief   I2C HAL module driver.
 *          This file provides firmware functions to manage the following
 *          functionalities of the Inter Integrated Circuit (I2C) peripheral:
 *           + Initialization and de-initialization functions
 *           + IO operation functions
 *           + Peripheral Control functions
 *           + Peripheral State functions
 *
 @verbatim
 ==============================================================================
 ##### How to use this driver #####
 ==============================================================================
 [..]
 The I2C HAL driver can be used as follows:

 (#) Declare a I2C_HandleTypeDef handle structure, for example:
 I2C_HandleTypeDef  hi2c;

 (#)Initialize the I2C low level resources by implement the HAL_I2C_MspInit() API:
 (##) Enable the I2Cx interface clock
 (##) I2C pins configuration
 (+++) Enable the clock for the I2C GPIOs
 (+++) Configure I2C pins as alternate function open-drain
 (##) NVIC configuration if you need to use interrupt process
 (+++) Configure the I2Cx interrupt priority
 (+++) Enable the NVIC I2C IRQ Channel
 (##) DMA Configuration if you need to use DMA process
 (+++) Declare a DMA_HandleTypeDef handle structure for the transmit or receive stream
 (+++) Enable the DMAx interface clock using
 (+++) Configure the DMA handle parameters
 (+++) Configure the DMA Tx or Rx Stream
 (+++) Associate the initialized DMA handle to the hi2c DMA Tx or Rx handle
 (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on
 the DMA Tx or Rx Stream

 (#) Configure the Communication Speed, Duty cycle, Addressing mode, Own Address1,
 Dual Addressing mode, Own Address2, General call and Nostretch mode in the hi2c Init structure.

 (#) Initialize the I2C registers by calling the HAL_I2C_Init(), configures also the low level Hardware
 (GPIO, CLOCK, NVIC...etc) by calling the customized HAL_I2C_MspInit(&hi2c) API.

 (#) To check if target device is ready for communication, use the function HAL_I2C_IsDeviceReady()

 (#) For I2C IO and IO MEM operations, three operation modes are available within this driver :

 *** Polling mode IO operation ***
 =================================
 [..]
 (+) Transmit in master mode an amount of data in blocking mode using HAL_I2C_Master_Transmit()
 (+) Receive in master mode an amount of data in blocking mode using HAL_I2C_Master_Receive()
 (+) Transmit in slave mode an amount of data in blocking mode using HAL_I2C_Slave_Transmit()
 (+) Receive in slave mode an amount of data in blocking mode using HAL_I2C_Slave_Receive()

 *** Polling mode IO MEM operation ***
 =====================================
 [..]
 (+) Write an amount of data in blocking mode to a specific memory address using HAL_I2C_Mem_Write()
 (+) Read an amount of data in blocking mode from a specific memory address using HAL_I2C_Mem_Read()


 *** Interrupt mode IO operation ***
 ===================================
 [..]
 (+) Transmit in master mode an amount of data in non blocking mode using HAL_I2C_Master_Transmit_IT()
 (+) At transmission end of transfer HAL_I2C_MasterTxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MasterTxCpltCallback
 (+) Receive in master mode an amount of data in non blocking mode using HAL_I2C_Master_Receive_IT()
 (+) At reception end of transfer HAL_I2C_MasterRxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MasterRxCpltCallback
 (+) Transmit in slave mode an amount of data in non blocking mode using HAL_I2C_Slave_Transmit_IT()
 (+) At transmission end of transfer HAL_I2C_SlaveTxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_SlaveTxCpltCallback
 (+) Receive in slave mode an amount of data in non blocking mode using HAL_I2C_Slave_Receive_IT()
 (+) At reception end of transfer HAL_I2C_SlaveRxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_SlaveRxCpltCallback
 (+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
 add his own code by customization of function pointer HAL_I2C_ErrorCallback

 *** Interrupt mode IO MEM operation ***
 =======================================
 [..]
 (+) Write an amount of data in no-blocking mode with Interrupt to a specific memory address using
 HAL_I2C_Mem_Write_IT()
 (+) At MEM end of write transfer HAL_I2C_MemTxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MemTxCpltCallback
 (+) Read an amount of data in no-blocking mode with Interrupt from a specific memory address using
 HAL_I2C_Mem_Read_IT()
 (+) At MEM end of read transfer HAL_I2C_MemRxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MemRxCpltCallback
 (+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
 add his own code by customization of function pointer HAL_I2C_ErrorCallback

 *** DMA mode IO operation ***
 ==============================
 [..]
 (+) Transmit in master mode an amount of data in non blocking mode (DMA) using
 HAL_I2C_Master_Transmit_DMA()
 (+) At transmission end of transfer HAL_I2C_MasterTxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MasterTxCpltCallback
 (+) Receive in master mode an amount of data in non blocking mode (DMA) using
 HAL_I2C_Master_Receive_DMA()
 (+) At reception end of transfer HAL_I2C_MasterRxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MasterRxCpltCallback
 (+) Transmit in slave mode an amount of data in non blocking mode (DMA) using
 HAL_I2C_Slave_Transmit_DMA()
 (+) At transmission end of transfer HAL_I2C_SlaveTxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_SlaveTxCpltCallback
 (+) Receive in slave mode an amount of data in non blocking mode (DMA) using
 HAL_I2C_Slave_Receive_DMA()
 (+) At reception end of transfer HAL_I2C_SlaveRxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_SlaveRxCpltCallback
 (+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
 add his own code by customization of function pointer HAL_I2C_ErrorCallback

 *** DMA mode IO MEM operation ***
 =================================
 [..]
 (+) Write an amount of data in no-blocking mode with DMA to a specific memory address using
 HAL_I2C_Mem_Write_DMA()
 (+) At MEM end of write transfer HAL_I2C_MemTxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MemTxCpltCallback
 (+) Read an amount of data in no-blocking mode with DMA from a specific memory address using
 HAL_I2C_Mem_Read_DMA()
 (+) At MEM end of read transfer HAL_I2C_MemRxCpltCallback is executed and user can
 add his own code by customization of function pointer HAL_I2C_MemRxCpltCallback
 (+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
 add his own code by customization of function pointer HAL_I2C_ErrorCallback


 *** I2C HAL driver macros list ***
 ==================================
 [..]
 Below the list of most used macros in I2C HAL driver.

 (+) __HAL_I2C_ENABLE: Enable the I2C peripheral
 (+) __HAL_I2C_DISABLE: Disable the I2C peripheral
 (+) __HAL_I2C_GET_FLAG : Checks whether the specified I2C flag is set or not
 (+) __HAL_I2C_CLEAR_FLAG : Clear the specified I2C pending flag
 (+) __HAL_I2C_ENABLE_IT: Enable the specified I2C interrupt
 (+) __HAL_I2C_DISABLE_IT: Disable the specified I2C interrupt

 [..]
 (@) You can refer to the I2C HAL driver header file for more useful macros


 @endverbatim
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
#include "stm32f4xx_i2c_helper_hal.h"

/** @addtogroup I2C_Helper
 * @{
 */

/** @defgroup I2C_Helper_HAL
 * @{
 */

#ifdef HAL_I2C_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup I2C_Private_Constants
 * @{
 */
#define I2C_TIMEOUT_FLAG          ((uint32_t)35)     /* 35 ms */
#define I2C_TIMEOUT_ADDR_SLAVE    ((uint32_t)10000)  /* 10 s  */
/**
 * @}
 */

/* Private macro -------------------------------------------------------------*/

/** @addtogroup I2C_Private_Macros
 * @{
 */
#define I2C_CHECK_PEC(hi2c)			(((hi2c)->Instance->CR1 & I2C_PECMODE_ENABLE) == I2C_PECMODE_ENABLE)
/**
 * @}
 */

/* Private variables ---------------------------------------------------------*/

/** @addtogroup I2C_Helper_Private_Variables_Group3 DMA Variables
 * @brief DmaUsed variables for internal purpose.
 * @{
 */
static uint8_t HELPER_I2C1_dmaUsed; /*!< dmaUsed for the I2C1 peripheral */
static uint8_t HELPER_I2C2_dmaUsed; /*!< dmaUsed for the I2C2 peripheral */
static uint8_t HELPER_I2C3_dmaUsed; /*!< dmaUsed for the I2C3 peripheral */

/**
 * @}
 */
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup I2C_Private_Functions
 * @{
 */

static void setDmaUsed(I2C_HandleTypeDef* hi2c, uint8_t newVal);
static uint8_t getDmaUsed(I2C_HandleTypeDef* hi2c);

/* New Callback *****************************************************************/
static void I2C_DMA_ITSlaveReceiveCplt(DMA_HandleTypeDef *hdma);
/********************************************************************************/
static void I2C_DMAError(DMA_HandleTypeDef *hdma);

static HAL_StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_MasterRequestRead(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c,
		uint32_t Flag, FlagStatus Status, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(
		I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout);

static HAL_StatusTypeDef I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_MasterTransmit_BTF(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_MasterReceive_BTF(I2C_HandleTypeDef *hi2c);

static HAL_StatusTypeDef I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_SlaveTransmit_BTF(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_SlaveReceive_BTF(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_Slave_ADDR(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_Slave_STOPF(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_Slave_AF(I2C_HandleTypeDef *hi2c);
/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
/** @defgroup I2C_Exported_Functions I2C Exported Functions
 * @{
 */

/** @defgroup I2C_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
 * @{
 */

/**
 * @brief  Transmits in master mode an amount of data in blocking mode.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_withPEC(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_TX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		/* Send Slave Address */
		if (I2C_MasterRequestWrite(hi2c, DevAddress, Timeout) != HAL_OK)
		{
			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_ERROR;
			}
			else
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_TIMEOUT;
			}
		}

		/* Clear ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

		while (Size > 0)
		{
			/* Wait until TXE flag is set */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
					!= HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Write data to DR */
			hi2c->Instance->DR = (*pData++);
			Size--;

			if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (Size != 0))
			{
				/* Write data to DR */
				hi2c->Instance->DR = (*pData++);
				Size--;
			}
		}

		/* Wait until TXE flag is set */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/********************* PEC CODE ********************************/
		/* Check if the PecMode is enabled */
		if (I2C_CHECK_PEC(hi2c) && Size == 0)
		{
			/* The master enables PEC Byte transmission, */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/***************************************************************/

		/* Generate Stop */
		hi2c->Instance->CR1 |= I2C_CR1_STOP;

		/* Wait until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		hi2c->State = HAL_I2C_STATE_READY;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

// [ILG]
#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

/**
 * @brief  Receives in master mode an amount of data in blocking mode.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Receive_withPEC(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_RX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		/* Send Slave Address */
		if (I2C_MasterRequestRead(hi2c, DevAddress, Timeout) != HAL_OK)
		{
			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_ERROR;
			}
			else
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_TIMEOUT;
			}
		}

		if (Size == 1 && !I2C_CHECK_PEC(hi2c))
		{
			/* Disable Acknowledge */
			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

			/* Generate Stop */
			hi2c->Instance->CR1 |= I2C_CR1_STOP;
		}
		else if (Size == 2 || (Size == 1 && I2C_CHECK_PEC(hi2c)))
		{
			/* Disable Acknowledge */
			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Enable Pos */
			hi2c->Instance->CR1 |= I2C_CR1_POS;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
		}
		else
		{
			/* Enable Acknowledge */
			hi2c->Instance->CR1 |= I2C_CR1_ACK;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
		}

		while (Size > 0)
		{
			if (Size <= 3)
			{
				/* One byte */
				if (Size == 1)
				{
					/* Wait until RXNE flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET,
							Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Read data from DR */
					(*pData++) = hi2c->Instance->DR;
					Size--;
				}
				/* Two bytes */
				else if (Size == 2)
				{
					/* Wait until BTF flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET,
							Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Generate Stop, only if there isn't PECMODE */
					hi2c->Instance->CR1 |=
							!I2C_CHECK_PEC(hi2c) ?
							I2C_CR1_STOP :
													(uint32_t) 0x00000000;

					/* Read data from DR */
					(*pData++) = hi2c->Instance->DR;
					Size--;

					/* Read data from DR */
					(*pData++) = hi2c->Instance->DR;
					Size--;
				}
				/* 3 Last bytes */
				else
				{
					/* Wait until BTF flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET,
							Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Disable Acknowledge, only if there isn't PECMODE */
					hi2c->Instance->CR1 &=
							!I2C_CHECK_PEC(hi2c) ?
									~I2C_CR1_ACK : (uint32_t) 0xFFFFFFFF;

					/* Read data from DR */
					(*pData++) = hi2c->Instance->DR;
					Size--;

					/* Wait until BTF flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET,
							Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Generate Stop, only if there isn't PECMODE */
					hi2c->Instance->CR1 |=
							!I2C_CHECK_PEC(hi2c) ?
							I2C_CR1_STOP :
													(uint32_t) 0x00000000;

					/* Read data from DR */
					(*pData++) = hi2c->Instance->DR;
					Size--;

					/* Read data from DR */
					(*pData++) = hi2c->Instance->DR;
					Size--;
				}
			}
			else
			{
				/* Wait until RXNE flag is set */
				if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET,
						Timeout) != HAL_OK)
				{
					return HAL_TIMEOUT;
				}

				/* Read data from DR */
				(*pData++) = hi2c->Instance->DR;
				Size--;

				if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET)
				{
					/* Read data from DR */
					(*pData++) = hi2c->Instance->DR;
					Size--;
				}
			}
		}
		/********************* PEC CODE ********************************/
		/* Check if the PecMode is enabled */
		if (I2C_CHECK_PEC(hi2c) && Size == 0)
		{
			/* Master disables Acknowledge, in order to sends the final NACK */
			/* MUST BE DONE HERE! */
			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Master enables PEC Byte reception */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;

			/* The master waits until RXNE flag is set, it means data register is NOT empty. */
			/* RxNE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET, Timeout)
					!= HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Master generates Stop */
			hi2c->Instance->CR1 |= I2C_CR1_STOP;

			/* Master should check for PEC Error */
			/* PER Error Event */
			if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_PECERR) == SET)
			{
				/* PEC Error, set the error code */
				hi2c->ErrorCode = HAL_I2C_ERROR_PEC;
				/* If there's a PEC Error, it's the application logic that decides what to do */
			}

			/* The slave reads the data, cleaning the RxNE */
			(*pData++) = hi2c->Instance->DR;
		}
		/***************************************************************/

		/* Disable Pos */
		hi2c->Instance->CR1 &= ~I2C_CR1_POS;

		/* Wait until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		hi2c->State = HAL_I2C_STATE_READY;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

/**
 * @brief  Transmits in slave mode an amount of data in blocking mode.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_withPEC(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_TX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		/* Enable Address Acknowledge */
		hi2c->Instance->CR1 |= I2C_CR1_ACK;

		/* Wait until ADDR flag is set */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Clear ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

		/* If 10bit addressing mode is selected */
		if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_10BIT)
		{
			/* Wait until ADDR flag is set */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout)
					!= HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
		}

		while (Size > 0)
		{
			/* Wait until TXE flag is set */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
					!= HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Write data to DR */
			hi2c->Instance->DR = (*pData++);
			Size--;

			if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (Size != 0))
			{
				/* Write data to DR */
				hi2c->Instance->DR = (*pData++);
				Size--;
			}
		}
		/********************* PEC CODE ********************************/
		/* Check if the PecMode is enabled */
		if (I2C_CHECK_PEC(hi2c) && Size == 0)
		{
			/* Slave waits until TXE flag is set */
			/* TxE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
					!= HAL_OK)
			{
				return HAL_TIMEOUT;
			}
			/* Slave sends the PEC Byte after the last one */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/***************************************************************/

		/* Wait until AF flag is set */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_AF, RESET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Clear AF flag */
		__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

		/* Disable Address Acknowledge */
		hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

		/* Wait until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		hi2c->State = HAL_I2C_STATE_READY;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

/**
 * @brief  Receive in slave mode an amount of data in blocking mode
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Receive_withPEC(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_RX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		/* Enable Address Acknowledge */
		hi2c->Instance->CR1 |= I2C_CR1_ACK;

		/* Wait until ADDR flag is set */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Clear ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

		while (Size > 0)
		{
			/* Wait until RXNE flag is set */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET, Timeout)
					!= HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Read data from DR */
			(*pData++) = hi2c->Instance->DR;
			Size--;

			if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (Size != 0))
			{
				/* Read data from DR */
				(*pData++) = hi2c->Instance->DR;
				Size--;
			}
		}

		/********************* PEC CODE ********************************/
		/* Check if the PecMode is enabled */
		if (I2C_CHECK_PEC(hi2c) && Size == 0)
		{
			/* Slave enables PEC Byte reception */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/***************************************************************/

		/* Wait until STOP flag is set */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_STOPF, RESET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/********************* PEC CODE - Cont *************************/
		/* Check if the PecMode is enabled */
		if (I2C_CHECK_PEC(hi2c) && Size == 0)
		{
			/* Slave should check for PEC Error */
			/* PER Error Event */
			if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_PECERR) == SET)
			{
				/* PEC Error, set the error code */
				hi2c->ErrorCode = HAL_I2C_ERROR_PEC;
				/* If there's a PEC Error, it's the application logic that
				 * decides what to do */
			}

			/* The slave reads the PEC Byte, cleaning the RxNE */
			(*pData) = hi2c->Instance->DR;
		}
		/***************************************************************/

		/* Clear STOP flag */
		__HAL_I2C_CLEAR_STOPFLAG(hi2c);

		/* Disable Address Acknowledge */
		hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

		/* Wait until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		hi2c->State = HAL_I2C_STATE_READY;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

/** @defgroup Self_I2C_Exported_Functions Exported Functions
 * @ Utility functions for master/slave transmitting and receiving.
 * @{
 */

/**
 * @brief Master 'hi2c_master' transmits in polling mode 'Size' data pointed
 * 		  by 'txData' to 'hi2c_slave' that save it in 'rxData' with 'Timeout' as timeout.
 * @param hi2c_master: I2C Master Handle.
 * @param hi2c_slave : I2C Slave Handle.
 * @param txData	 : Pointer to the data transfered by the master.
 * @param rxData	 : Pointer to the data received by the slave.
 * @param Size		 : The size of the data.
 * @param Timeout	 : Timeout of polling waiting.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_onBoard(
		I2C_HandleTypeDef *hi2c_master, I2C_HandleTypeDef *hi2c_slave,
		uint8_t *txData, uint8_t *rxData, uint16_t Size, uint32_t Timeout)
{

	uint16_t masterSize = Size;

	/* Check if the master and the slave periph are ready */
	if (hi2c_master->State == HAL_I2C_STATE_READY
			&& hi2c_slave->State == HAL_I2C_STATE_READY)
	{
		/* Check if not-NULL data pointers and not-Zero Size has been provided */
		if ((txData == NULL) || (txData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		/* Check, in both handles, if the flag BUSY (in SR2) is SET , it would mean that there is
		 * a communication on the bus, id est SCL or SDA are low.
		 */
		if (__HAL_I2C_GET_FLAG(hi2c_master, I2C_FLAG_BUSY) == SET
				|| __HAL_I2C_GET_FLAG(hi2c_slave, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked, lock the handle to avoid concurrent access */
		__HAL_LOCK(hi2c_master);
		__HAL_LOCK(hi2c_slave);

		/* Change the state of the master */
		hi2c_master->State = HAL_I2C_STATE_BUSY_TX;
		hi2c_master->ErrorCode = HAL_I2C_ERROR_NONE;

		/* Change the state of the slave */
		hi2c_slave->State = HAL_I2C_STATE_BUSY_RX;
		hi2c_slave->ErrorCode = HAL_I2C_ERROR_NONE;

		/*
		 * This is the problem on the same board, the ACK it has to be enabled via software.
		 */
		/* The slave enables the Address Acknowledge */
		hi2c_slave->Instance->CR1 |= I2C_CR1_ACK;

		/* The master sends the Slave Address */
		if (I2C_MasterRequestWrite(hi2c_master, hi2c_slave->Init.OwnAddress1,
				Timeout) != HAL_OK)
		{
			if (hi2c_master->ErrorCode == HAL_I2C_ERROR_AF)
			{ /* Acknowledge failure */
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c_master);
				return HAL_ERROR;
			}
			else
			{ /* The retry time is over */
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c_master);
				return HAL_TIMEOUT;
			}
		}

		/* The slave has responded so the ADDR flag has been set now
		 * The master clears the ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c_master);

		/* The Slave waits until ADDR flag is set (wait if ADDR is RESET) */
		/* The ADDR event for the slave */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_ADDR, RESET,
				Timeout) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Slave clears ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c_slave);

		/* The master is in transmitter mode, the slave in receive mode
		 * Begin the transmission
		 */
		while (Size > 0)
		{
			/* The master wait until TXE flag is set, it means that DSR is empty,
			 * if it isn't the first transmission it also means that an ACK for the
			 * previous data has been received, in case of a NACK TxE is not set */
			/* TxE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c_master, I2C_FLAG_TXE, RESET,
					Timeout) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* The master can write data to DR (that will be copied in the DSR to start the transfer)
			 * clearing the TxE */
			hi2c_master->Instance->DR = (*txData++);
			masterSize--;

			/* The master checks if the data has already been transferred, and so if there's another
			 * to transfer it can do it (as expected DSR is like a buffer) */
			/* BTF Event */
			if ((__HAL_I2C_GET_FLAG(hi2c_master, I2C_FLAG_BTF) == SET)
					&& (masterSize > 0))
			{
				/* The master writes the other data to DR, clearing the BTF */
				hi2c_master->Instance->DR = (*txData++);
				masterSize--;
			}

			/* The master waits until TxE flag is set, it's waiting for the end of the serial transmission */
			/* TxE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c_master, I2C_FLAG_TXE, RESET,
					Timeout) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}
			/* At this point the master is already ready for another transmission */

			/* The slave waits until RxNE flag is set, it means DSR (and so the DR) is NOT empty id est
			 * something has been received */
			/* RxNE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_RXNE, RESET,
					Timeout) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* The slave reads data from DR, clearing the RxNE */
			(*rxData++) = hi2c_slave->Instance->DR;
			Size--;

			/* The slave checks if another data has been received in DSR */
			/* BTF Event */
			if ((__HAL_I2C_GET_FLAG(hi2c_slave, I2C_FLAG_BTF) == SET)
					&& (Size != 0))
			{
				/* The slave reads data from DR, clearing the BTF */
				(*rxData++) = hi2c_slave->Instance->DR;
				Size--;
			}

			/********************* PEC CODE *****************************************/
			/* Check if the PecMode is enabled for both and it's the last byte transferred/received */
			if (I2C_CHECK_PEC(hi2c_master) && I2C_CHECK_PEC(hi2c_slave)
					&& Size == 0)
			{
				/* The master enables PEC Byte transmission, */
				hi2c_master->Instance->CR1 |= I2C_CR1_PEC;

				/* The master MUST NOT wait until TXE flag is set, because the pec transmission
				 * doens't fire the TxE Event */
//				if (I2C_WaitOnFlagUntilTimeout(hi2c_master, I2C_FLAG_TXE, RESET,
//						Timeout) != HAL_OK) {
//					return HAL_TIMEOUT;
//				}
				/* The slave enables PEC Byte reception */
				hi2c_slave->Instance->CR1 |= I2C_CR1_PEC;

				/* The slave waits until RXNE flag is set, it means data register is NOT empty. */
				/* RxNE Event */
				if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_RXNE, RESET,
						Timeout) != HAL_OK)
				{
					return HAL_TIMEOUT;
				}

				/* The slave should check for PEC Error */
				/* PER Error Event */
				if (__HAL_I2C_GET_FLAG(hi2c_slave, I2C_FLAG_PECERR) == SET)
				{
					/* PEC Error, set the error code */
					hi2c_slave->ErrorCode = HAL_I2C_ERROR_PEC;
					/* If there's a PEC Error, it's the application logic that decides what to do */
				}

				/* The slave reads the data, cleaning the RxNE */
				(*rxData++) = hi2c_slave->Instance->DR;
			}
			/************************************************************************/
		}

		/* The master generates Stop condition */
		hi2c_master->Instance->CR1 |= I2C_CR1_STOP;

		/* The Slave waits until STOP flag is set */
		/* STOPF Event */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_STOPF, RESET,
				Timeout) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* The master clears STOP flag */
		__HAL_I2C_CLEAR_STOPFLAG(hi2c_slave);

		/* The slave disables Address Acknowledge */
		hi2c_slave->Instance->CR1 &= ~I2C_CR1_ACK;

		/* The slave wait until BUSY flag is reset,
		 * the slave has released the lines so it should see the lines high -> no communications */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* The master waits until BUSY flag is reset
		 * the master has released the lines so it should see the lines high -> no communications */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_master, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Update the periph state */
		hi2c_slave->State = HAL_I2C_STATE_READY;
		hi2c_master->State = HAL_I2C_STATE_READY;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c_master);
		__HAL_UNLOCK(hi2c_slave);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

/**
 * @brief Slave 'hi2c_slave' transmits in polling mode 'Size' datas pointed
 * 		  by 'txData' to 'hi2c_master' that save it in 'rxData' with 'Timeout' as a timeout.
 * @param hi2c_master: I2C Master Handler.
 * @param hi2c_slave : I2C Slave Handler
 * @param txData	 : Pointer to the data transfered by the master.
 * @param rxData	 : Pointer to the data received by the slave.
 * @param Size		 : The size of the data.
 * @param Timeout	 : Timeout of polling waiting.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_onBoard(I2C_HandleTypeDef *hi2c_master,
		I2C_HandleTypeDef *hi2c_slave, uint8_t *txData, uint8_t *rxData,
		uint16_t Size, uint32_t Timeout)
{

	/*************************************************************************
	 * This function is partially commented, read masterTransmitSlaveReceive *
	 * first to properly understand all the events flow.					 *
	 *************************************************************************/

	uint16_t slaveSize = Size;

	if (hi2c_master->State == HAL_I2C_STATE_READY
			&& hi2c_slave->State == HAL_I2C_STATE_READY)
	{
		if ((txData == NULL) || (rxData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c_master, I2C_FLAG_BUSY) == SET
				|| __HAL_I2C_GET_FLAG(hi2c_slave, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c_master);
		__HAL_LOCK(hi2c_slave);

		hi2c_master->State = HAL_I2C_STATE_BUSY_RX;
		hi2c_master->ErrorCode = HAL_I2C_ERROR_NONE;

		hi2c_slave->State = HAL_I2C_STATE_BUSY_TX;
		hi2c_slave->ErrorCode = HAL_I2C_ERROR_NONE;

		/* Slave enables Address Acknowledge */
		hi2c_slave->Instance->CR1 |= I2C_CR1_ACK;

		/* Master sends Slave Address */
		if (I2C_MasterRequestRead(hi2c_master, hi2c_slave->Init.OwnAddress1,
				Timeout) != HAL_OK)
		{
			if (hi2c_master->ErrorCode == HAL_I2C_ERROR_AF)
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c_master);
				return HAL_ERROR;
			}
			else
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c_master);
				return HAL_TIMEOUT;
			}
		}

		/* Slave waits until ADDR flag is set */
		/* ADDR Event */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_ADDR, RESET,
				Timeout) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Slave clears ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c_slave);

		/* If 10bit addressing mode is selected */
		if (hi2c_slave->Init.AddressingMode == I2C_ADDRESSINGMODE_10BIT)
		{
			/* Wait until ADDR flag is set */
			/* ADDR Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_ADDR, RESET,
					Timeout) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c_slave);
		}

		/* Master receive-mode configuration,
		 * it's necessary because the ADDR clearing has to be done in a certain order */
		if (Size == 1 && !I2C_CHECK_PEC(hi2c_master))
		{
			/* Only one byte */
			/* Master disables Acknowledge, in order to sends the final NACK */
			hi2c_master->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Master clears ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c_master);

			/* Master generates Stop condition */
			hi2c_master->Instance->CR1 |= I2C_CR1_STOP;
		}
		else if (Size == 2 || (Size == 1 && I2C_CHECK_PEC(hi2c_master)))
		{
			/* Two byte, after the first one the second one will immediately
			 * saved in the DSR */
			/* Master disables Acknowledge, in order to sends the final NACK */
			hi2c_master->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Master enable Pos, ACK Position bit
			 * it'used only if the master has to receive 2 bytes */
			hi2c_master->Instance->CR1 |= I2C_CR1_POS;

			/* Master clears ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c_master);
		}
		else
		{
			/* Master enables Acknowledge, because it has to responde
			 * to the byte-transmission of the slave */
			hi2c_master->Instance->CR1 |= I2C_CR1_ACK;

			/* Master clears ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c_master);
		}

		/* The master is in receive mode, the slave in transmit mode
		 * Begin the transmission */
		while (Size > 0)
		{
			/* Slave waits until TXE flag is set */
			/* TxE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_TXE, RESET,
					Timeout) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Slave writes data to DR */
			hi2c_slave->Instance->DR = (*txData++);
			slaveSize--;

			/* I don't know why but this delay it's needed */
			HAL_Delay(1);

			/* If there's another byte to send */
			/* BTF Event */
			if ((__HAL_I2C_GET_FLAG(hi2c_slave, I2C_FLAG_BTF) == SET)
					&& (slaveSize > 0))
			{
				/* Slave writes another data to DR */
				hi2c_slave->Instance->DR = (*txData++);
				slaveSize--;
			}

			/***************************************************************************
			 * The master receive is implemented in a recursive way, the master reads
			 * at most 2 byte at time, and it differentiates if it has to receive <=3 o >3
			 * bytes.
			 ***************************************************************************/
			if (Size <= 3)
			{
				/* One byte */
				if (Size == 1)
				{
					/* Master waits until RXNE flag is set */
					/* RxNE Event */
					if (I2C_WaitOnFlagUntilTimeout(hi2c_master,
					I2C_FLAG_RXNE, RESET, Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Master reads data from DR */
					(*rxData++) = hi2c_master->Instance->DR;
					Size--;

				}
				/* Two bytes */
				else if (Size == 2)
				{
					/* Master waits until BTF flag is set */
					/* BTF Event */
					if (I2C_WaitOnFlagUntilTimeout(hi2c_master,
					I2C_FLAG_BTF, RESET, Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

//					/* Master generates Stop */
//					hi2c_master->Instance->CR1 |= I2C_CR1_STOP;

					/* Two consecutive read */
					/* Master reads data from DR */
					(*rxData++) = hi2c_master->Instance->DR;
					Size--;

					/* Master reads data from DR */
					(*rxData++) = hi2c_master->Instance->DR;
					Size--;

				}
				/* 3 Last bytes */
				else
				{
					/* Master waits until BTF flag is set */
					/* BTF Event */
					if (I2C_WaitOnFlagUntilTimeout(hi2c_master,
					I2C_FLAG_BTF, RESET, Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Master disables Acknowledge, in order to sends the final NACK */
//					hi2c_master->Instance->CR1 &= ~I2C_CR1_ACK;
					/* Master reads data from DR */
					(*rxData++) = hi2c_master->Instance->DR;
					Size--;

					/* Master waits until BTF flag is set */
					/* BTF Event */
					if (I2C_WaitOnFlagUntilTimeout(hi2c_master,
					I2C_FLAG_BTF, RESET, Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* The rest is the same as 2 byte */

					/* Master generates Stop */
//					hi2c_master->Instance->CR1 |= I2C_CR1_STOP;
					/* Two consecutive read */
					/* Master reads data from DR */
					(*rxData++) = hi2c_master->Instance->DR;
					Size--;

					/* Master reads data from DR */
					(*rxData++) = hi2c_master->Instance->DR;
					Size--;

				}
			}
			else
			{
				/* More than 3 bytes */
				/* Master waits until RXNE flag is set */
				/* RxNE Event */
				if (I2C_WaitOnFlagUntilTimeout(hi2c_master, I2C_FLAG_RXNE,
						RESET, Timeout) != HAL_OK)
				{
					return HAL_TIMEOUT;
				}

				/* Master reads data from DR */
				(*rxData++) = hi2c_master->Instance->DR;
				Size--;

				/* Master checks if BTF flag is set, maybe another data is arrived */
				/* BTF Event */
				if (__HAL_I2C_GET_FLAG(hi2c_master, I2C_FLAG_BTF) == SET)
				{
					/* Master reads data from DR */
					(*rxData++) = hi2c_master->Instance->DR;
					Size--;
				}
			}
			/* Last byte */
			if (Size == 0)
			{
				/********************* PEC CODE *****************************************/
				/* Check if the PecMode is enabled for both */
				if (I2C_CHECK_PEC(hi2c_master) && I2C_CHECK_PEC(hi2c_slave))
				{

					/* Slave waits until TXE flag is set */
					/* TxE Event */
					if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_TXE,
							RESET, Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Slave sends the PEC Byte after the last */
					hi2c_slave->Instance->CR1 |= I2C_CR1_PEC;
					/* This code take the PEC Byte from the SR2 */
//					uint32_t PecByte = (hi2c_slave->Instance->SR2 & 0xFF00)
//							>> 8;
					/* Master disables Acknowledge, in order to sends the final NACK */
					/* MUST BE DONE HERE! */
					hi2c_master->Instance->CR1 &= ~I2C_CR1_ACK;

					/* Master enables PEC Byte reception */
					hi2c_master->Instance->CR1 |= I2C_CR1_PEC;

					/* The master waits until RXNE flag is set, it means data register is NOT empty. */
					/* RxNE Event */
					if (I2C_WaitOnFlagUntilTimeout(hi2c_master,
					I2C_FLAG_RXNE, RESET, Timeout) != HAL_OK)
					{
						return HAL_TIMEOUT;
					}

					/* Master should check for PEC Error */
					/* PER Error Event */
					if (__HAL_I2C_GET_FLAG(hi2c_master, I2C_FLAG_PECERR) == SET)
					{
						/* PEC Error, set the error code */
						hi2c_master->ErrorCode = HAL_I2C_ERROR_PEC;
						/* If there's a PEC Error, it's the application logic that decides what to do */
					}

					/* The slave reads the data, cleaning the RxNE */
					(*rxData++) = hi2c_master->Instance->DR;

				}
				else
				{
					hi2c_master->Instance->CR1 &= ~I2C_CR1_ACK;
				}
				/************************************************************************/
				/* Master generates Stop */
				hi2c_master->Instance->CR1 |= I2C_CR1_STOP;
			}
		}

		/* Master Disables Pos */
		hi2c_master->Instance->CR1 &= ~I2C_CR1_POS;

		/* Slave waits until AF flag is set */
		/* AF Event */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_AF, RESET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Slave clears AF flag */
		__HAL_I2C_CLEAR_FLAG(hi2c_slave, I2C_FLAG_AF);

		/* Slave disables Address Acknowledge */
		hi2c_slave->Instance->CR1 &= ~I2C_CR1_ACK;

		/* Slave waits until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_slave, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Master waits until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c_master, I2C_FLAG_BUSY, SET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Put the state to READY */
		hi2c_master->State = HAL_I2C_STATE_READY;
		hi2c_slave->State = HAL_I2C_STATE_READY;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c_master);
		__HAL_UNLOCK(hi2c_slave);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}
/**
 * @}
 */

/**
 * @brief  Transmit in master mode an amount of data in no-blocking mode with Interrupt
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT_withPEC(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_TX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		hi2c->pBuffPtr = pData;
		hi2c->XferSize = Size;
		hi2c->XferCount = Size;

		/* Send Slave Address */
		if (I2C_MasterRequestWrite(hi2c, DevAddress, I2C_TIMEOUT_FLAG)
				!= HAL_OK)
		{
			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_ERROR;
			}
			else
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_TIMEOUT;
			}
		}

		/* Clear ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		/* Note : The I2C interrupts must be enabled after unlocking current process
		 to avoid the risk of I2C interrupt handle execution before current
		 process unlock */

		/* Enable EVT, BUF and ERR interrupt */
		__HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

/**
 * @brief  Receive in master mode an amount of data in no-blocking mode with Interrupt
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT_withPEC(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_RX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		hi2c->pBuffPtr = pData;
		hi2c->XferSize = Size;
		hi2c->XferCount = Size;

		/* Send Slave Address */
		if (I2C_MasterRequestRead(hi2c, DevAddress, I2C_TIMEOUT_FLAG) != HAL_OK)
		{
			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_ERROR;
			}
			else
			{
				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);
				return HAL_TIMEOUT;
			}
		}

		if (hi2c->XferCount == 1 && !I2C_CHECK_PEC(hi2c))
		{
			/* Disable Acknowledge */
			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

			if (!I2C_CHECK_PEC(hi2c))
			{
				/* Generate Stop */
				hi2c->Instance->CR1 |= I2C_CR1_STOP;
			}
		}
		else if (hi2c->XferCount == 2 || (Size == 1 && I2C_CHECK_PEC(hi2c)))
		{
			/* Disable Acknowledge */
			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Enable Pos */
			hi2c->Instance->CR1 |= I2C_CR1_POS;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
		}
		else
		{
			/* Enable Acknowledge */
			hi2c->Instance->CR1 |= I2C_CR1_ACK;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
		}

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		/* Note : The I2C interrupts must be enabled after unlocking current process
		 to avoid the risk of I2C interrupt handle execution before current
		 process unlock */

		/* Enable EVT, BUF and ERR interrupt */
		__HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

/**
 * @brief  Transmit in slave mode an amount of data in no-blocking mode with Interrupt
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT_withPEC(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_TX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		hi2c->pBuffPtr = pData;
		hi2c->XferSize = Size;
		hi2c->XferCount = Size;

		/* Enable Address Acknowledge */
		hi2c->Instance->CR1 |= I2C_CR1_ACK;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		/* Note : The I2C interrupts must be enabled after unlocking current process
		 to avoid the risk of I2C interrupt handle execution before current
		 process unlock */

		/* Enable EVT, BUF and ERR interrupt */
		__HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

/**
 * @brief  Receive in slave mode an amount of data in no-blocking mode with Interrupt
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT_withPEC(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_RX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		hi2c->pBuffPtr = pData;
		hi2c->XferSize = Size;
		hi2c->XferCount = Size;

		/* Enable Address Acknowledge */
		hi2c->Instance->CR1 |= I2C_CR1_ACK;

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		/* Note : The I2C interrupts must be enabled after unlocking current process
		 to avoid the risk of I2C interrupt handle execution before current
		 process unlock */

		/* Enable EVT, BUF and ERR interrupt */
		__HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

///**
// * @brief  Transmit in master mode an amount of data in no-blocking mode with DMA
// * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
// *         the configuration information for I2C module
// * @param  DevAddress: Target device address
// * @param  pData: Pointer to data buffer
// * @param  Size: Amount of data to be sent
// * @retval HAL status
// */
//HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c,
//		uint16_t DevAddress, uint8_t *pData, uint16_t Size)
//{
//	if (hi2c->State == HAL_I2C_STATE_READY)
//	{
//		if ((pData == NULL) || (Size == 0))
//		{
//			return HAL_ERROR;
//		}
//
//		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
//		{
//			return HAL_BUSY;
//		}
//
//		/* Process Locked */
//		__HAL_LOCK(hi2c);
//
//		hi2c->State = HAL_I2C_STATE_BUSY_TX;
//		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
//
//		hi2c->pBuffPtr = pData;
//		hi2c->XferSize = Size;
//		hi2c->XferCount = Size;
//
//		/* Set the I2C DMA transfer complete callback */
//		hi2c->hdmatx->XferCpltCallback = I2C_DMAMasterTransmitCplt;
//
//		/* Set the DMA error callback */
//		hi2c->hdmatx->XferErrorCallback = I2C_DMAError;
//
//		/* Enable the DMA Stream */
//		HAL_DMA_Start_IT(hi2c->hdmatx, (uint32_t) pData,
//				(uint32_t) &hi2c->Instance->DR, Size);
//
//		/* Send Slave Address */
//		if (I2C_MasterRequestWrite(hi2c, DevAddress, I2C_TIMEOUT_FLAG)
//				!= HAL_OK)
//		{
//			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
//			{
//				/* Process Unlocked */
//				__HAL_UNLOCK(hi2c);
//				return HAL_ERROR;
//			}
//			else
//			{
//				/* Process Unlocked */
//				__HAL_UNLOCK(hi2c);
//				return HAL_TIMEOUT;
//			}
//		}
//
//		/* Enable DMA Request */
//		hi2c->Instance->CR2 |= I2C_CR2_DMAEN;
//
//		/* Clear ADDR flag */
//		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//		/* Process Unlocked */
//		__HAL_UNLOCK(hi2c);
//
//		return HAL_OK;
//	}
//	else
//	{
//		return HAL_BUSY;
//	}
//}

///**
// * @brief  Receive in master mode an amount of data in no-blocking mode with DMA
// * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
// *         the configuration information for I2C module
// * @param  DevAddress: Target device address
// * @param  pData: Pointer to data buffer
// * @param  Size: Amount of data to be sent
// * @retval HAL status
// */
//HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c,
//		uint16_t DevAddress, uint8_t *pData, uint16_t Size)
//{
//	if (hi2c->State == HAL_I2C_STATE_READY)
//	{
//		if ((pData == NULL) || (Size == 0))
//		{
//			return HAL_ERROR;
//		}
//
//		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
//		{
//			return HAL_BUSY;
//		}
//
//		/* Process Locked */
//		__HAL_LOCK(hi2c);
//
//		hi2c->State = HAL_I2C_STATE_BUSY_RX;
//		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
//
//		hi2c->pBuffPtr = pData;
//		hi2c->XferSize = Size;
//		hi2c->XferCount = Size;
//
//		/* Set the I2C DMA transfer complete callback */
//		hi2c->hdmarx->XferCpltCallback = I2C_DMAMasterReceiveCplt;
//
//		/* Set the DMA error callback */
//		hi2c->hdmarx->XferErrorCallback = I2C_DMAError;
//
//		/* Enable the DMA Stream */
//		HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t) &hi2c->Instance->DR,
//				(uint32_t) pData, Size);
//
//		/* Send Slave Address */
//		if (I2C_MasterRequestRead(hi2c, DevAddress, I2C_TIMEOUT_FLAG) != HAL_OK)
//		{
//			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
//			{
//				/* Process Unlocked */
//				__HAL_UNLOCK(hi2c);
//				return HAL_ERROR;
//			}
//			else
//			{
//				/* Process Unlocked */
//				__HAL_UNLOCK(hi2c);
//				return HAL_TIMEOUT;
//			}
//		}
//
//		if (Size == 1)
//		{
//			/* Disable Acknowledge */
//			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//		}
//		else
//		{
//			/* Enable Last DMA bit */
//			hi2c->Instance->CR2 |= I2C_CR2_LAST;
//		}
//
//		/* Enable DMA Request */
//		hi2c->Instance->CR2 |= I2C_CR2_DMAEN;
//
//		/* Clear ADDR flag */
//		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//		/* Process Unlocked */
//		__HAL_UNLOCK(hi2c);
//
//		return HAL_OK;
//	}
//	else
//	{
//		return HAL_BUSY;
//	}
//}
//
///**
// * @brief  Transmit in slave mode an amount of data in no-blocking mode with DMA
// * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
// *         the configuration information for I2C module
// * @param  pData: Pointer to data buffer
// * @param  Size: Amount of data to be sent
// * @retval HAL status
// */
//HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c,
//		uint8_t *pData, uint16_t Size)
//{
//	if (hi2c->State == HAL_I2C_STATE_READY)
//	{
//		if ((pData == NULL) || (Size == 0))
//		{
//			return HAL_ERROR;
//		}
//
//		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
//		{
//			return HAL_BUSY;
//		}
//
//		/* Process Locked */
//		__HAL_LOCK(hi2c);
//
//		hi2c->State = HAL_I2C_STATE_BUSY_TX;
//		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
//
//		hi2c->pBuffPtr = pData;
//		hi2c->XferSize = Size;
//		hi2c->XferCount = Size;
//
//		/* Set the I2C DMA transfer complete callback */
//		hi2c->hdmatx->XferCpltCallback = I2C_DMASlaveTransmitCplt;
//
//		/* Set the DMA error callback */
//		hi2c->hdmatx->XferErrorCallback = I2C_DMAError;
//
//		/* Enable the DMA Stream */
//		HAL_DMA_Start_IT(hi2c->hdmatx, (uint32_t) pData,
//				(uint32_t) &hi2c->Instance->DR, Size);
//
//		/* Enable DMA Request */
//		hi2c->Instance->CR2 |= I2C_CR2_DMAEN;
//
//		/* Enable Address Acknowledge */
//		hi2c->Instance->CR1 |= I2C_CR1_ACK;
//
//		/* Wait until ADDR flag is set */
//		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET,
//		I2C_TIMEOUT_ADDR_SLAVE) != HAL_OK)
//		{
//			return HAL_TIMEOUT;
//		}
//
//		/* If 7bit addressing mode is selected */
//		if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
//		{
//			/* Clear ADDR flag */
//			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//		}
//		else
//		{
//			/* Clear ADDR flag */
//			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//			/* Wait until ADDR flag is set */
//			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET,
//			I2C_TIMEOUT_ADDR_SLAVE) != HAL_OK)
//			{
//				return HAL_TIMEOUT;
//			}
//
//			/* Clear ADDR flag */
//			__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//		}
//
//		/* Process Unlocked */
//		__HAL_UNLOCK(hi2c);
//
//		return HAL_OK;
//	}
//	else
//	{
//		return HAL_BUSY;
//	}
//}
//
///**
// * @brief  Receive in slave mode an amount of data in no-blocking mode with DMA
// * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
// *         the configuration information for I2C module
// * @param  pData: Pointer to data buffer
// * @param  Size: Amount of data to be sent
// * @retval HAL status
// */
//HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c,
//		uint8_t *pData, uint16_t Size)
//{
//	if (hi2c->State == HAL_I2C_STATE_READY)
//	{
//		if ((pData == NULL) || (Size == 0))
//		{
//			return HAL_ERROR;
//		}
//
//		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
//		{
//			return HAL_BUSY;
//		}
//
//		/* Process Locked */
//		__HAL_LOCK(hi2c);
//
//		hi2c->State = HAL_I2C_STATE_BUSY_RX;
//		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
//
//		hi2c->pBuffPtr = pData;
//		hi2c->XferSize = Size;
//		hi2c->XferCount = Size;
//
//		/* Set the I2C DMA transfer complete callback */
//		hi2c->hdmarx->XferCpltCallback = I2C_DMASlaveReceiveCplt;
//
//		/* Set the DMA error callback */
//		hi2c->hdmarx->XferErrorCallback = I2C_DMAError;
//
//		/* Enable the DMA Stream */
//		HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t) &hi2c->Instance->DR,
//				(uint32_t) pData, Size);
//
//		/* Enable DMA Request */
//		hi2c->Instance->CR2 |= I2C_CR2_DMAEN;
//
//		/* Enable Address Acknowledge */
//		hi2c->Instance->CR1 |= I2C_CR1_ACK;
//
//		/* Wait until ADDR flag is set */
//		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET,
//		I2C_TIMEOUT_ADDR_SLAVE) != HAL_OK)
//		{
//			return HAL_TIMEOUT;
//		}
//
//		/* Clear ADDR flag */
//		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//		/* Process Unlocked */
//		__HAL_UNLOCK(hi2c);
//
//		return HAL_OK;
//	}
//	else
//	{
//		return HAL_BUSY;
//	}
//}

/* New Functions *********************************************************************/
/**
 * @brief  Receive in slave mode an amount of data in no-blocking mode with DMA, avoiding
 * 		   the reception of the address in polled mode.
 * 		   REQUIRE enabled interrupt.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA_IT(I2C_HandleTypeDef *hi2c,
		uint8_t *pData, uint16_t Size)
{
	if (hi2c->State == HAL_I2C_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2c);

		hi2c->State = HAL_I2C_STATE_BUSY_RX;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

		hi2c->pBuffPtr = pData;
		hi2c->XferSize = Size;
		hi2c->XferCount = Size;

//		/* Set the I2C DMA transfer complete callback */
//		hi2c->hdmarx->XferCpltCallback = I2C_DMASlaveReceiveCplt;
//
//		/* Set the DMA error callback */
//		hi2c->hdmarx->XferErrorCallback = I2C_DMAError;
//
//		/* Enable the DMA Stream */
//		HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t) &hi2c->Instance->DR,
//				(uint32_t) pData, Size);
//
//		/* Enable DMA Request */
//		hi2c->Instance->CR2 |= I2C_CR2_DMAEN;

		/* Enable Address Acknowledge */
		hi2c->Instance->CR1 |= I2C_CR1_ACK;

//		/* Wait until ADDR flag is set */
//		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET,
//		I2C_TIMEOUT_ADDR_SLAVE) != HAL_OK) {
//			return HAL_TIMEOUT;
//		}
//
//		/* Clear ADDR flag */
//		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

		/* Set the dmaUsed flag */
		setDmaUsed(hi2c, 0x01);

		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		/* Note : The I2C interrupts must be enabled after unlocking current process
		 to avoid the risk of I2C interrupt handle execution before current
		 process unlock */

		/* Enable EVT, BUF and ERR interrupt */
		__HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}
/*************************************************************************************/
/**
 * @brief  This function handles I2C event interrupt request.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
void I2C_HELPER_EV_IRQHandler(I2C_HandleTypeDef *hi2c)
{
	uint32_t tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
	/* Master mode selected */
	if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_MSL) == SET)
	{
		/* I2C in mode Transmitter -----------------------------------------------*/
		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TRA) == SET)
		{
			tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE);
			tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_BUF);
			tmp3 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF);
			tmp4 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_EVT);
			/* TXE set and BTF reset -----------------------------------------------*/
			if ((tmp1 == SET) && (tmp2 == SET) && (tmp3 == RESET))
			{
				I2C_MasterTransmit_TXE(hi2c);
			}
			/* BTF set -------------------------------------------------------------*/
			else if ((tmp3 == SET) && (tmp4 == SET))
			{
				I2C_MasterTransmit_BTF(hi2c);
			}
		}
		/* I2C in mode Receiver --------------------------------------------------*/
		else
		{
			tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE);
			tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_BUF);
			tmp3 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF);
			tmp4 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_EVT);
			/* RXNE set and BTF reset -----------------------------------------------*/
			if ((tmp1 == SET) && (tmp2 == SET) && (tmp3 == RESET))
			{
				I2C_MasterReceive_RXNE(hi2c);
			}
			/* BTF set -------------------------------------------------------------*/
			else if ((tmp3 == SET) && (tmp4 == SET))
			{
				I2C_MasterReceive_BTF(hi2c);
			}
		}
	}
	/* Slave mode selected */
	else
	{
		tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR);
		tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, (I2C_IT_EVT));
		tmp3 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_STOPF);
		tmp4 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TRA);
		/* ADDR set --------------------------------------------------------------*/
		if ((tmp1 == SET) && (tmp2 == SET))
		{
			I2C_Slave_ADDR(hi2c);
		}
		/* STOPF set --------------------------------------------------------------*/
		else if ((tmp3 == SET) && (tmp2 == SET))
		{
			I2C_Slave_STOPF(hi2c);
		}
		/* I2C in mode Transmitter -----------------------------------------------*/
		else if (tmp4 == SET)
		{
			tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE);
			tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_BUF);
			tmp3 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF);
			tmp4 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_EVT);
			/* TXE set and BTF reset -----------------------------------------------*/
			if ((tmp1 == SET) && (tmp2 == SET) && (tmp3 == RESET))
			{
				I2C_SlaveTransmit_TXE(hi2c);
			}
			/* BTF set -------------------------------------------------------------*/
			else if ((tmp3 == SET) && (tmp4 == SET))
			{
				I2C_SlaveTransmit_BTF(hi2c);
			}
		}
		/* I2C in mode Receiver --------------------------------------------------*/
		else
		{
			tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE);
			tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_BUF);
			tmp3 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF);
			tmp4 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_EVT);
			/* RXNE set and BTF reset ----------------------------------------------*/
			if ((tmp1 == SET) && (tmp2 == SET) && (tmp3 == RESET))
			{
				I2C_SlaveReceive_RXNE(hi2c);
			}
			/* BTF set -------------------------------------------------------------*/
			else if ((tmp3 == SET) && (tmp4 == SET))
			{
				I2C_SlaveReceive_BTF(hi2c);
			}
		}
	}
}

/**
 * @brief  This function handles I2C error interrupt request.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
void I2C_HELPER_ER_IRQHandler(I2C_HandleTypeDef *hi2c)
{
	uint32_t tmp1 = 0, tmp2 = 0, tmp3 = 0;

	tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BERR);
	tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_ERR);
	/* I2C Bus error interrupt occurred ----------------------------------------*/
	if ((tmp1 == SET) && (tmp2 == SET))
	{
		hi2c->ErrorCode |= HAL_I2C_ERROR_BERR;

		/* Clear BERR flag */
		__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_BERR);
	}

	tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ARLO);
	tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_ERR);
	/* I2C Arbitration Loss error interrupt occurred ---------------------------*/
	if ((tmp1 == SET) && (tmp2 == SET))
	{
		hi2c->ErrorCode |= HAL_I2C_ERROR_ARLO;

		/* Clear ARLO flag */
		__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ARLO);
	}

	tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF);
	tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_ERR);
	/* I2C Acknowledge failure error interrupt occurred ------------------------*/
	if ((tmp1 == SET) && (tmp2 == SET))
	{
		tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_MSL);
		tmp2 = hi2c->XferCount;
		tmp3 = hi2c->State;
		if ((tmp1 == RESET) && (tmp2 == 0) && (tmp3 == HAL_I2C_STATE_BUSY_TX))
		{
			I2C_Slave_AF(hi2c);
		}
		else
		{
			hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
			/* Clear AF flag */
			__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
		}
	}

	tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_OVR);
	tmp2 = __HAL_I2C_GET_IT_SOURCE(hi2c, I2C_IT_ERR);
	/* I2C Over-Run/Under-Run interrupt occurred -------------------------------*/
	if ((tmp1 == SET) && (tmp2 == SET))
	{
		hi2c->ErrorCode |= HAL_I2C_ERROR_OVR;
		/* Clear OVR flag */
		__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_OVR);
	}

	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
	{
		hi2c->State = HAL_I2C_STATE_READY;

		/* Disable Pos bit in I2C CR1 when error occurred in Master/Mem Receive IT Process */
		hi2c->Instance->CR1 &= ~I2C_CR1_POS;

		HAL_I2C_ErrorCallback(hi2c);
	}
}

/** @defgroup I2C_Exported_Functions_Group3 Peripheral State and Errors functions
 *  @brief   Peripheral State and Errors functions
 *
 @verbatim
 ===============================================================================
 ##### Peripheral State and Errors functions #####
 ===============================================================================
 [..]
 This subsection permits to get in run-time the status of the peripheral
 and the data flow.

 @endverbatim
*/

 /**
 * @brief  Handle TXE flag for Master
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c)
{
	/* Write data to DR */
	hi2c->Instance->DR = (*hi2c->pBuffPtr++);
	hi2c->XferCount--;

	if (hi2c->XferCount == 0)
	{
		/* Disable BUF interrupt */
		__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);
	}

	return HAL_OK;
}

/**
 * @brief  Handle BTF flag for Master transmitter
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_MasterTransmit_BTF(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->XferCount != 0)
	{
		/* Write data to DR */
		hi2c->Instance->DR = (*hi2c->pBuffPtr++);
		hi2c->XferCount--;
	}
	else
	{

		/************ PEC CODE **********************/
		if (I2C_CHECK_PEC(hi2c))
		{
			/* Write PEC bit and send PEC Byte */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/*******************************************/

		/* Disable EVT, BUF and ERR interrupt */
		__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

		/* Generate Stop */
		hi2c->Instance->CR1 |= I2C_CR1_STOP;

		/* Wait until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET,
		I2C_TIMEOUT_FLAG) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		if (hi2c->State == HAL_I2C_STATE_MEM_BUSY_TX)
		{
			hi2c->State = HAL_I2C_STATE_READY;

			HAL_I2C_MemTxCpltCallback(hi2c);
		}
		else
		{
			hi2c->State = HAL_I2C_STATE_READY;

			HAL_I2C_MasterTxCpltCallback(hi2c);
		}
	}
	return HAL_OK;
}

// [ILG]
#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

/**
 * @brief  Handle RXNE flag for Master
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c)
{
	uint32_t tmp = 0;

	tmp = hi2c->XferCount;
	if (tmp > 3)
	{
		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;
	}
	else if ((tmp == 2) || (tmp == 3))
	{
		/* Disable BUF interrupt */
		__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);
	}
	else
	{
		/* Disable EVT, BUF and ERR interrupt */
		__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;

		/********************* PEC CODE *****************************************/
		if (I2C_CHECK_PEC(hi2c) && hi2c->XferCount == 0)
		{
			/* Disable Acknowledge */
			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Write PEC bit and receive PEC Byte */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;

			/* The master waits until RXNE flag is set, it means data register is NOT empty. */
			/* RxNE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET,
			I2C_TIMEOUT_FLAG) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}

			/* Generate Stop */
			hi2c->Instance->CR1 |= I2C_CR1_STOP;

			/* Read PEC Byte */
			*hi2c->pBuffPtr = hi2c->Instance->DR;
		}
		/***********************************************************************/

		/* Wait until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET,
		I2C_TIMEOUT_FLAG) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Disable Pos */
		hi2c->Instance->CR1 &= ~I2C_CR1_POS;

		if (hi2c->State == HAL_I2C_STATE_MEM_BUSY_RX)
		{
			hi2c->State = HAL_I2C_STATE_READY;

			HAL_I2C_MemRxCpltCallback(hi2c);
		}
		else
		{
			hi2c->State = HAL_I2C_STATE_READY;

			HAL_I2C_MasterRxCpltCallback(hi2c);
		}
	}
	return HAL_OK;
}

/**
 * @brief  Handle BTF flag for Master receiver
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_MasterReceive_BTF(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->XferCount == 3)
	{
		/* Disable Acknowledge, only if there isn't PECMODE */
		hi2c->Instance->CR1 &=
				!I2C_CHECK_PEC(hi2c) ? ~I2C_CR1_ACK : (uint32_t) 0xFFFFFFFF;

		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;
	}
	else if (hi2c->XferCount == 2)
	{
		/* Generate Stop, only if there isn't PECMODE */
		hi2c->Instance->CR1 |= !I2C_CHECK_PEC(hi2c) ?
		I2C_CR1_STOP :
														(uint32_t) 0x00000000;

		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;

		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;

		/* Disable EVT and ERR interrupt */
		__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

		/********************* PEC CODE *****************************************/
		if (I2C_CHECK_PEC(hi2c) && hi2c->XferCount == 0)
		{
			/* Disable Acknowledge */
			hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Write PEC bit and receive PEC Byte */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;

			/* The master waits until RXNE flag is set, it means data register is NOT empty. */
			/* RxNE Event */
			if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET,
			I2C_TIMEOUT_FLAG) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}
			/* Generate Stop */
			hi2c->Instance->CR1 |= I2C_CR1_STOP;

			/* Read PEC Byte */
			*hi2c->pBuffPtr = hi2c->Instance->DR;

		}
		/***********************************************************************/

		/* Wait until BUSY flag is reset */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET,
		I2C_TIMEOUT_FLAG) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Disable Pos */
		hi2c->Instance->CR1 &= ~I2C_CR1_POS;

		if (hi2c->State == HAL_I2C_STATE_MEM_BUSY_RX)
		{
			hi2c->State = HAL_I2C_STATE_READY;

			HAL_I2C_MemRxCpltCallback(hi2c);
		}
		else
		{
			hi2c->State = HAL_I2C_STATE_READY;

			HAL_I2C_MasterRxCpltCallback(hi2c);
		}
	}
	else
	{
		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;
	}
	return HAL_OK;
}

/**
 * @brief  Handle TXE flag for Slave
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->XferCount != 0)
	{
		/* Write data to DR */
		hi2c->Instance->DR = (*hi2c->pBuffPtr++);
		hi2c->XferCount--;
	}
	else
	{
		/************ PEC CODE **********************/
		/* Last byte transmitted */
		if (I2C_CHECK_PEC(hi2c))
		{
			/* Write PEC bit, transmit the PEC Byte */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/*******************************************/
	}
	return HAL_OK;
}

/**
 * @brief  Handle BTF flag for Slave transmitter
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_SlaveTransmit_BTF(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->XferCount != 0)
	{
		/* Write data to DR */
		hi2c->Instance->DR = (*hi2c->pBuffPtr++);
		hi2c->XferCount--;
	}
	else
	{
		/************ PEC CODE **********************/
		/* Last byte transmitted */
		if (I2C_CHECK_PEC(hi2c))
		{
			/* Write PEC bit, transmit the PEC Byte */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/*******************************************/
	}
	return HAL_OK;
}

/**
 * @brief  Handle RXNE flag for Slave
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->XferCount != 0)
	{
		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;

		/************ PEC CODE **********************/
		/* Last byte received */
		if (I2C_CHECK_PEC(hi2c) && hi2c->XferCount == 0)
		{
			/* Write PEC bit, receive and check the PEC Byte */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/*******************************************/
	}
	return HAL_OK;
}

/**
 * @brief  Handle BTF flag for Slave receiver
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_SlaveReceive_BTF(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->XferCount != 0)
	{
		/* Read data from DR */
		(*hi2c->pBuffPtr++) = hi2c->Instance->DR;
		hi2c->XferCount--;

		/************ PEC CODE **********************/
		/* Last byte received */
		if (I2C_CHECK_PEC(hi2c) && hi2c->XferCount == 0)
		{
			/* Write PEC bit, receive and check the PEC Byte */
			hi2c->Instance->CR1 |= I2C_CR1_PEC;
		}
		/*******************************************/
	}
	return HAL_OK;
}

// [ILG]
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/**
 * @brief  Handle ADD flag for Slave
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_Slave_ADDR(I2C_HandleTypeDef *hi2c)
{
	/* DMA_IT Code ***********************************************/
	/* Configure the DMA */
	if (getDmaUsed(hi2c) == 0x01)
	{
		/* Disable EVT, BUF and ERR interrupt */
		__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

		/* Set the I2C DMA transfer complete callback */
		hi2c->hdmarx->XferCpltCallback = I2C_DMA_ITSlaveReceiveCplt;

		/* Set the DMA error callback */
		hi2c->hdmarx->XferErrorCallback = I2C_DMAError;

		/* Enable the DMA Stream */
		HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t) &hi2c->Instance->DR,
				(uint32_t) hi2c->pBuffPtr, hi2c->XferSize);

		/* Enable DMA Request */
		hi2c->Instance->CR2 |= I2C_CR2_DMAEN;

		/* Clear dmaUsed Flag */
		setDmaUsed(hi2c, 0x00);
	}
	/*************************************************************/
	/* Clear ADDR flag */
	__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

	return HAL_OK;
}

/**
 * @brief  Handle STOPF flag for Slave
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_Slave_STOPF(I2C_HandleTypeDef *hi2c)
{
	/* DMA_IT Code ***********************************************/
	if (getDmaUsed(hi2c) == 0x01)
	{
		setDmaUsed(hi2c, 0x00);
	}
	else
	{
		/************ PEC CODE **********************/
		if (I2C_CHECK_PEC(hi2c))
		{
			/* Read PEC Byte */
			*hi2c->pBuffPtr = hi2c->Instance->DR;
		}
		/*******************************************/
	}
	/*************************************************************/

	/* Disable EVT, BUF and ERR interrupt */
	__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

	/* Clear STOPF flag */
	__HAL_I2C_CLEAR_STOPFLAG(hi2c);

	/* Disable Acknowledge */
	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

	/* Wait until BUSY flag is reset */
	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
			!= HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	hi2c->State = HAL_I2C_STATE_READY;

	HAL_I2C_SlaveRxCpltCallback(hi2c);

	return HAL_OK;
}

/**
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_Slave_AF(I2C_HandleTypeDef *hi2c)
{
	/* Disable EVT, BUF and ERR interrupt */
	__HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

	/* Clear AF flag */
	__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

	/* Disable Acknowledge */
	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

	/* Wait until BUSY flag is reset */
	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
			!= HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	hi2c->State = HAL_I2C_STATE_READY;

	HAL_I2C_SlaveTxCpltCallback(hi2c);

	return HAL_OK;
}

/**
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  DevAddress: Target device address
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint32_t Timeout)
{
	/* Generate Start */
	hi2c->Instance->CR1 |= I2C_CR1_START;

	/* Wait until SB flag is set */
	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
	{
		/* Send slave address */
		hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);
	}
	else
	{
		/* Send header of slave address */
		hi2c->Instance->DR = I2C_10BIT_HEADER_WRITE(DevAddress);

		/* Wait until ADD10 flag is set */
		if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADD10,
				Timeout) != HAL_OK)
		{
			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
			{
				return HAL_ERROR;
			}
			else
			{
				return HAL_TIMEOUT;
			}
		}

		/* Send slave address */
		hi2c->Instance->DR = I2C_10BIT_ADDRESS(DevAddress);
	}

	/* Wait until ADDR flag is set */
	if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout)
			!= HAL_OK)
	{
		if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
		{
			return HAL_ERROR;
		}
		else
		{
			return HAL_TIMEOUT;
		}
	}

	return HAL_OK;
}

/**
 * @brief  Master sends target device address for read request.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  DevAddress: Target device address
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_MasterRequestRead(I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint32_t Timeout)
{
	/* Enable Acknowledge */
	hi2c->Instance->CR1 |= I2C_CR1_ACK;

	/* Generate Start */
	hi2c->Instance->CR1 |= I2C_CR1_START;

	/* Wait until SB flag is set */
	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
	{
		/* Send slave address */
		hi2c->Instance->DR = I2C_7BIT_ADD_READ(DevAddress);
	}
	else
	{
		/* Send header of slave address */
		hi2c->Instance->DR = I2C_10BIT_HEADER_WRITE(DevAddress);

		/* Wait until ADD10 flag is set */
		if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADD10,
				Timeout) != HAL_OK)
		{
			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
			{
				return HAL_ERROR;
			}
			else
			{
				return HAL_TIMEOUT;
			}
		}

		/* Send slave address */
		hi2c->Instance->DR = I2C_10BIT_ADDRESS(DevAddress);

		/* Wait until ADDR flag is set */
		if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR,
				Timeout) != HAL_OK)
		{
			if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
			{
				return HAL_ERROR;
			}
			else
			{
				return HAL_TIMEOUT;
			}
		}

		/* Clear ADDR flag */
		__HAL_I2C_CLEAR_ADDRFLAG(hi2c);

		/* Generate Restart */
		hi2c->Instance->CR1 |= I2C_CR1_START;

		/* Wait until SB flag is set */
		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout)
				!= HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		/* Send header of slave address */
		hi2c->Instance->DR = I2C_10BIT_HEADER_READ(DevAddress);
	}

	/* Wait until ADDR flag is set */
	if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout)
			!= HAL_OK)
	{
		if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
		{
			return HAL_ERROR;
		}
		else
		{
			return HAL_TIMEOUT;
		}
	}

	return HAL_OK;
}

///**
// * @brief  Master sends target device address followed by internal memory address for write request.
// * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
// *         the configuration information for I2C module
// * @param  DevAddress: Target device address
// * @param  MemAddress: Internal memory address
// * @param  MemAddSize: Size of internal memory address
// * @param  Timeout: Timeout duration
// * @retval HAL status
// */
//static HAL_StatusTypeDef I2C_RequestMemoryWrite(I2C_HandleTypeDef *hi2c,
//		uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize,
//		uint32_t Timeout)
//{
//	/* Generate Start */
//	hi2c->Instance->CR1 |= I2C_CR1_START;
//
//	/* Wait until SB flag is set */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout) != HAL_OK)
//	{
//		return HAL_TIMEOUT;
//	}
//
//	/* Send slave address */
//	hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);
//
//	/* Wait until ADDR flag is set */
//	if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout)
//			!= HAL_OK)
//	{
//		if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
//		{
//			return HAL_ERROR;
//		}
//		else
//		{
//			return HAL_TIMEOUT;
//		}
//	}
//
//	/* Clear ADDR flag */
//	__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//	/* Wait until TXE flag is set */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
//			!= HAL_OK)
//	{
//		return HAL_TIMEOUT;
//	}
//
//	/* If Memory address size is 8Bit */
//	if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
//	{
//		/* Send Memory Address */
//		hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
//	}
//	/* If Memory address size is 16Bit */
//	else
//	{
//		/* Send MSB of Memory Address */
//		hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);
//
//		/* Wait until TXE flag is set */
//		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
//				!= HAL_OK)
//		{
//			return HAL_TIMEOUT;
//		}
//
//		/* Send LSB of Memory Address */
//		hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
//	}
//
//	return HAL_OK;
//}
//
///**
// * @brief  Master sends target device address followed by internal memory address for read request.
// * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
// *         the configuration information for I2C module
// * @param  DevAddress: Target device address
// * @param  MemAddress: Internal memory address
// * @param  MemAddSize: Size of internal memory address
// * @param  Timeout: Timeout duration
// * @retval HAL status
// */
//static HAL_StatusTypeDef I2C_RequestMemoryRead(I2C_HandleTypeDef *hi2c,
//		uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize,
//		uint32_t Timeout)
//{
//	/* Enable Acknowledge */
//	hi2c->Instance->CR1 |= I2C_CR1_ACK;
//
//	/* Generate Start */
//	hi2c->Instance->CR1 |= I2C_CR1_START;
//
//	/* Wait until SB flag is set */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout) != HAL_OK)
//	{
//		return HAL_TIMEOUT;
//	}
//
//	/* Send slave address */
//	hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);
//
//	/* Wait until ADDR flag is set */
//	if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout)
//			!= HAL_OK)
//	{
//		if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
//		{
//			return HAL_ERROR;
//		}
//		else
//		{
//			return HAL_TIMEOUT;
//		}
//	}
//
//	/* Clear ADDR flag */
//	__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//	/* Wait until TXE flag is set */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
//			!= HAL_OK)
//	{
//		return HAL_TIMEOUT;
//	}
//
//	/* If Memory address size is 8Bit */
//	if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
//	{
//		/* Send Memory Address */
//		hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
//	}
//	/* If Memory address size is 16Bit */
//	else
//	{
//		/* Send MSB of Memory Address */
//		hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);
//
//		/* Wait until TXE flag is set */
//		if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
//				!= HAL_OK)
//		{
//			return HAL_TIMEOUT;
//		}
//
//		/* Send LSB of Memory Address */
//		hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
//	}
//
//	/* Wait until TXE flag is set */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout)
//			!= HAL_OK)
//	{
//		return HAL_TIMEOUT;
//	}
//
//	/* Generate Restart */
//	hi2c->Instance->CR1 |= I2C_CR1_START;
//
//	/* Wait until SB flag is set */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout) != HAL_OK)
//	{
//		return HAL_TIMEOUT;
//	}
//
//	/* Send slave address */
//	hi2c->Instance->DR = I2C_7BIT_ADD_READ(DevAddress);
//
//	/* Wait until ADDR flag is set */
//	if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout)
//			!= HAL_OK)
//	{
//		if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
//		{
//			return HAL_ERROR;
//		}
//		else
//		{
//			return HAL_TIMEOUT;
//		}
//	}
//
//	return HAL_OK;
//}
//
///**
// * @brief  DMA I2C master transmit process complete callback.
// * @param  hdma: DMA handle
// * @retval None
// */
//static void I2C_DMAMasterTransmitCplt(DMA_HandleTypeDef *hdma)
//{
//	I2C_HandleTypeDef* hi2c =
//			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;
//
//	/* Wait until BTF flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	/* Generate Stop */
//	hi2c->Instance->CR1 |= I2C_CR1_STOP;
//
//	/* Disable DMA Request */
//	hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;
//
//	hi2c->XferCount = 0;
//
//	/* Wait until BUSY flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	hi2c->State = HAL_I2C_STATE_READY;
//
//	/* Check if Errors has been detected during transfer */
//	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
//	{
//		HAL_I2C_ErrorCallback(hi2c);
//	}
//	else
//	{
//		HAL_I2C_MasterTxCpltCallback(hi2c);
//	}
//}
//
///**
// * @brief  DMA I2C slave transmit process complete callback.
// * @param  hdma: DMA handle
// * @retval None
// */
//static void I2C_DMASlaveTransmitCplt(DMA_HandleTypeDef *hdma)
//{
//	I2C_HandleTypeDef* hi2c =
//			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;
//
//	/* Wait until AF flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_AF, RESET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	/* Clear AF flag */
//	__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
//
//	/* Disable Address Acknowledge */
//	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//	/* Disable DMA Request */
//	hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;
//
//	hi2c->XferCount = 0;
//
//	/* Wait until BUSY flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	hi2c->State = HAL_I2C_STATE_READY;
//
//	/* Check if Errors has been detected during transfer */
//	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
//	{
//		HAL_I2C_ErrorCallback(hi2c);
//	}
//	else
//	{
//		HAL_I2C_SlaveTxCpltCallback(hi2c);
//	}
//}
//
///**
// * @brief  DMA I2C master receive process complete callback
// * @param  hdma: DMA handle
// * @retval None
// */
//static void I2C_DMAMasterReceiveCplt(DMA_HandleTypeDef *hdma)
//{
//	I2C_HandleTypeDef* hi2c =
//			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;
//
//	/* Generate Stop */
//	hi2c->Instance->CR1 |= I2C_CR1_STOP;
//
//	/* Disable Last DMA */
//	hi2c->Instance->CR2 &= ~I2C_CR2_LAST;
//
//	/* Disable Acknowledge */
//	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//	/* Disable DMA Request */
//	hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;
//
//	hi2c->XferCount = 0;
//
//	/* Wait until BUSY flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	hi2c->State = HAL_I2C_STATE_READY;
//
//	/* Check if Errors has been detected during transfer */
//	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
//	{
//		HAL_I2C_ErrorCallback(hi2c);
//	}
//	else
//	{
//		HAL_I2C_MasterRxCpltCallback(hi2c);
//	}
//}
//
///**
// * @brief  DMA I2C slave receive process complete callback.
// * @param  hdma: DMA handle
// * @retval None
// */
//static void I2C_DMASlaveReceiveCplt(DMA_HandleTypeDef *hdma)
//{
//	I2C_HandleTypeDef* hi2c =
//			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;
//
//	/* Wait until STOPF flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_STOPF, RESET,
//	I2C_TIMEOUT_FLAG) != HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	/* Clear STOPF flag */
//	__HAL_I2C_CLEAR_STOPFLAG(hi2c);
//
//	/* Disable Address Acknowledge */
//	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//	/* Disable DMA Request */
//	hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;
//
//	hi2c->XferCount = 0;
//
//	/* Wait until BUSY flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	hi2c->State = HAL_I2C_STATE_READY;
//
//	/* Check if Errors has been detected during transfer */
//	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
//	{
//		HAL_I2C_ErrorCallback(hi2c);
//	}
//	else
//	{
//		HAL_I2C_SlaveRxCpltCallback(hi2c);
//	}
//}

/* New Functions *********************************************************************/
/**
 * @brief  DMA I2C slave receive process complete callback, without STOPF polled wait.
 * @param  hdma: DMA handle
 * @retval None
 */
static void I2C_DMA_ITSlaveReceiveCplt(DMA_HandleTypeDef *hdma)
{
	I2C_HandleTypeDef* hi2c =
			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;

	/* Set DMAUsed */
	setDmaUsed(hi2c, 0x01);

	/* Enable EVT, BUF and ERR interrupt */
	__HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

//	/* Wait until STOPF flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_STOPF, RESET,
//	I2C_TIMEOUT_FLAG) != HAL_OK) {
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	/* Clear STOPF flag */
//	__HAL_I2C_CLEAR_STOPFLAG(hi2c);

//	/* Disable Address Acknowledge */
//	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//	/* Disable DMA Request */
//	hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;
//
//	hi2c->XferCount = 0;
//
//	/* Wait until BUSY flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK) {
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	hi2c->State = HAL_I2C_STATE_READY;
//
//	/* Check if Errors has been detected during transfer */
//	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE) {
//		HAL_I2C_ErrorCallback(hi2c);
//	} else {
//		HAL_I2C_SlaveRxCpltCallback(hi2c);
//	}
}
/*************************************************************************************/

///**
// * @brief  DMA I2C Memory Write process complete callback
// * @param  hdma: DMA handle
// * @retval None
// */
//static void I2C_DMAMemTransmitCplt(DMA_HandleTypeDef *hdma)
//{
//	I2C_HandleTypeDef* hi2c =
//			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;
//
//	/* Wait until BTF flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	/* Generate Stop */
//	hi2c->Instance->CR1 |= I2C_CR1_STOP;
//
//	/* Disable DMA Request */
//	hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;
//
//	hi2c->XferCount = 0;
//
//	/* Wait until BUSY flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	hi2c->State = HAL_I2C_STATE_READY;
//
//	/* Check if Errors has been detected during transfer */
//	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
//	{
//		HAL_I2C_ErrorCallback(hi2c);
//	}
//	else
//	{
//		HAL_I2C_MemTxCpltCallback(hi2c);
//	}
//}
//
///**
// * @brief  DMA I2C Memory Read process complete callback
// * @param  hdma: DMA handle
// * @retval None
// */
//static void I2C_DMAMemReceiveCplt(DMA_HandleTypeDef *hdma)
//{
//	I2C_HandleTypeDef* hi2c =
//			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;
//
//	/* Generate Stop */
//	hi2c->Instance->CR1 |= I2C_CR1_STOP;
//
//	/* Disable Last DMA */
//	hi2c->Instance->CR2 &= ~I2C_CR2_LAST;
//
//	/* Disable Acknowledge */
//	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//	/* Disable DMA Request */
//	hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;
//
//	hi2c->XferCount = 0;
//
//	/* Wait until BUSY flag is reset */
//	if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_FLAG)
//			!= HAL_OK)
//	{
//		hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
//	}
//
//	hi2c->State = HAL_I2C_STATE_READY;
//
//	/* Check if Errors has been detected during transfer */
//	if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
//	{
//		HAL_I2C_ErrorCallback(hi2c);
//	}
//	else
//	{
//		HAL_I2C_MemRxCpltCallback(hi2c);
//	}
//}

/**
 * @brief  DMA I2C communication error callback.
 * @param  hdma: DMA handle
 * @retval None
 */
static void I2C_DMAError(DMA_HandleTypeDef *hdma)
{
	I2C_HandleTypeDef* hi2c =
			(I2C_HandleTypeDef*) ((DMA_HandleTypeDef*) hdma)->Parent;

	/* Disable Acknowledge */
	hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

	hi2c->XferCount = 0;

	hi2c->State = HAL_I2C_STATE_READY;

	hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

	HAL_I2C_ErrorCallback(hi2c);
}

/**
 * @brief  This function handles I2C Communication Timeout.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  Flag: specifies the I2C flag to check.
 * @param  Status: The new Flag status (SET or RESET).
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c,
		uint32_t Flag, FlagStatus Status, uint32_t Timeout)
{
	uint32_t tickstart = 0;

	/* Get tick */
	tickstart = HAL_GetTick();

	/* Wait until flag is set */
	if (Status == RESET)
	{
		while (__HAL_I2C_GET_FLAG(hi2c, Flag) == RESET)
		{
			/* Check for the Timeout */
			if (Timeout != HAL_MAX_DELAY)
			{
				if ((Timeout == 0) || ((HAL_GetTick() - tickstart) > Timeout))
				{
					hi2c->State = HAL_I2C_STATE_READY;

					/* Process Unlocked */
					__HAL_UNLOCK(hi2c);

					return HAL_TIMEOUT;
				}
			}
		}
	}
	else
	{
		while (__HAL_I2C_GET_FLAG(hi2c, Flag) != RESET)
		{
			/* Check for the Timeout */
			if (Timeout != HAL_MAX_DELAY)
			{
				if ((Timeout == 0) || ((HAL_GetTick() - tickstart) > Timeout))
				{
					hi2c->State = HAL_I2C_STATE_READY;

					/* Process Unlocked */
					__HAL_UNLOCK(hi2c);

					return HAL_TIMEOUT;
				}
			}
		}
	}
	return HAL_OK;
}

/**
 * @brief  This function handles I2C Communication Timeout for Master addressing phase.
 * @param  hi2c: pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @param  Flag: specifies the I2C flag to check.
 * @param  Timeout: Timeout duration
 * @retval HAL status
 */
static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(
		I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout)
{
	uint32_t tickstart = 0;

	/* Get tick */
	tickstart = HAL_GetTick();

	while (__HAL_I2C_GET_FLAG(hi2c, Flag) == RESET)
	{
		if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF) == SET)
		{
			/* Generate Stop */
			hi2c->Instance->CR1 |= I2C_CR1_STOP;

			/* Clear AF Flag */
			__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

			hi2c->ErrorCode = HAL_I2C_ERROR_AF;
			hi2c->State = HAL_I2C_STATE_READY;

			/* Process Unlocked */
			__HAL_UNLOCK(hi2c);

			return HAL_ERROR;
		}

		/* Check for the Timeout */
		if (Timeout != HAL_MAX_DELAY)
		{
			if ((Timeout == 0) || ((HAL_GetTick() - tickstart) > Timeout))
			{
				hi2c->State = HAL_I2C_STATE_READY;

				/* Process Unlocked */
				__HAL_UNLOCK(hi2c);

				return HAL_TIMEOUT;
			}
		}
	}
	return HAL_OK;
}

/**
 * @}
 */

/**
 * @brief Set dmaUsed variable for the correct i2c periph
 * @param in hi2c I2c Handler
 * @retval none
 */
static void setDmaUsed(I2C_HandleTypeDef* hi2c, uint8_t newVal)
{
	if (hi2c->Instance == I2C1)
	{
		HELPER_I2C1_dmaUsed = newVal;
	}
	else if (hi2c->Instance == I2C2)
	{
		HELPER_I2C2_dmaUsed = newVal;
	}
	else if (hi2c->Instance == I2C3)
	{
		HELPER_I2C3_dmaUsed = newVal;
	}
}

/**
 * @brief Get dmaUsed variable for the correct i2c periph
 * @param in hi2c I2c Handler
 * @retval none
 */
static uint8_t getDmaUsed(I2C_HandleTypeDef* hi2c)
{
	if (hi2c->Instance == I2C1)
	{
		return HELPER_I2C1_dmaUsed;
	}
	else if (hi2c->Instance == I2C2)
	{
		return HELPER_I2C2_dmaUsed;
	}
	else if (hi2c->Instance == I2C3)
	{
		return HELPER_I2C3_dmaUsed;
	}
	return 0;
}

#endif /* HAL_I2C_MODULE_ENABLED */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
