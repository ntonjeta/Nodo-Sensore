/* @file    stm32f4xx_i2c_helper_ex.c
 * @author  Giovanni Di Fiore - SE4
 * @version V0.1
 * @date    28-May-2015
 * @brief   SPI Extension Helper Implementation
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

// include the spi_helper.h file (this will include the _hal.h file for SPI peripheral)
#include "include/stm32f4xx_spi_helper.h"
#include "include/stm32f4xx_spi_helper_ex.h"

/** @addtogroup STM32F4xx_Helper_Library Helper Library
 * @{
 */

/** @addtogroup SPI_Helper SPI Helper
 * @{
 */

/* Private define ------------------------------------------------------------*/
#define SPI_TIMEOUT_VALUE  10

/* Private prototypes -------------------------------------- */
static HAL_StatusTypeDef HELPER_SPI_WaitOnFlagUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
static void SPI_TxISR(SPI_HandleTypeDef *hspi);
static void SPI_2LinesRxISR(SPI_HandleTypeDef *hspi);
static void SPI_TxCloseIRQHandler(SPI_HandleTypeDef *hspi);
static void SPI_RxCloseIRQHandler(SPI_HandleTypeDef *hspi);

/** @addtogroup SPI_Helper_Exported_Functions_Extended
 * @{
 */


/**
 * @brief This transmit function can be used for the transmission in Half-Duplex (1 line, bidirectional) mode and the TX/RX SPI peripherals are on the same board.
 *
 * @param hspi
 * @param pData
 * @param Size
 * @param Timeout
 * @return HAL_StatusTypeDef HAL status. HAL_OK if the transmission completes
 */
HAL_StatusTypeDef HELPER_SPI_HalfDuplex_OnBoard_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  if(hspi->State == HAL_SPI_STATE_READY)
  {
    if((pData == NULL ) || (Size == 0))
    {
      return  HAL_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));

    /* Process Locked */
    __HAL_LOCK(hspi);

    /* Configure communication */
    hspi->State = HAL_SPI_STATE_BUSY_TX;
    hspi->ErrorCode   = HAL_SPI_ERROR_NONE;

    hspi->pTxBuffPtr = pData;
    hspi->TxXferSize = Size;
    hspi->TxXferCount = Size;

    /*Init field not used in handle to zero */
    hspi->TxISR = 0;
    hspi->RxISR = 0;
    hspi->RxXferSize   = 0;
    hspi->RxXferCount  = 0;

    /* Reset CRC Calculation */
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
      SPI_RESET_CRC(hspi);
    }

    if(hspi->Init.Direction == SPI_DIRECTION_1LINE)
    {
      /* Configure communication direction : 1Line */
      SPI_1LINE_TX(hspi);
    }

    /* Check if the SPI is already enabled */
    if((hspi->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Enable SPI peripheral */
      __HAL_SPI_ENABLE(hspi);
    }

    /* Transmit data in 8 Bit mode */
    if(hspi->Init.DataSize == SPI_DATASIZE_8BIT)
    {
      if((hspi->Init.Mode == SPI_MODE_SLAVE)|| (hspi->TxXferCount == 0x01))
      {
        hspi->Instance->DR = (*hspi->pTxBuffPtr++);
        hspi->TxXferCount--;
      }
      while(hspi->TxXferCount > 0)
      {
        /* Wait until TXE flag is set to send data */

        if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_TXE, RESET, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        hspi->Instance->DR = (*hspi->pTxBuffPtr++);
        hspi->TxXferCount--;
      }
      /* Enable CRC Transmission */
      if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
      {
        hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
      }
    }
    /* Transmit data in 16 Bit mode */
    else
    {
      if((hspi->Init.Mode == SPI_MODE_SLAVE) || (hspi->TxXferCount == 0x01))
      {
        hspi->Instance->DR = *((uint16_t*)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr+=2;
        hspi->TxXferCount--;
      }
      while(hspi->TxXferCount > 0)
      {
        /* Wait until TXE flag is set to send data */
        if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_TXE, RESET, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        hspi->Instance->DR = *((uint16_t*)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr+=2;
        hspi->TxXferCount--;
      }
      /* Enable CRC Transmission */
      if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
      {
        hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
      }
    }

    // The wait cannot be done because the transmission won't begin until the master initialize a new transmission procedure
    // For the master mode, the wait cannot be done because the Rx interrupt arrives before this function ends

    /* Wait until TXE flag is set to send data
	if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_TXE, RESET, Timeout) != HAL_OK)
	{
	  hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
	  return HAL_TIMEOUT;
	}

	Wait until Busy flag is reset before disabling SPI
	if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_BSY, SET, Timeout) != HAL_OK)
	{
	  hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
	  return HAL_TIMEOUT;
	}
	*/

    if (hspi->Init.Mode == SPI_MODE_MASTER)
    {
		// Clear OVERRUN flag because the received data is not read in master mode
		__HAL_SPI_CLEAR_OVRFLAG(hspi);
    }

    hspi->State = HAL_SPI_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hspi);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HELPER_SPI_MasterReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pRxData, uint16_t Size)
{
 uint32_t tmpstate = 0;

 tmpstate = hspi->State;
  if((tmpstate == HAL_SPI_STATE_READY) && (hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
  {
    if((pRxData == NULL ) || (Size == 0))
    {
      return  HAL_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

    /* Process locked */
    __HAL_LOCK(hspi);

    /* Set the BUSY_RX state */
    hspi->State = HAL_SPI_STATE_BUSY_RX;

    /* Configure communication */
    hspi->ErrorCode    = HAL_SPI_ERROR_NONE;

    /* Transmit a dummyData buffer */
    uint8_t dummyData[Size];
    hspi->TxISR = &SPI_TxISR;
    hspi->pTxBuffPtr   = dummyData;
    hspi->TxXferSize   = Size;
    hspi->TxXferCount  = Size;

    hspi->RxISR = &SPI_2LinesRxISR;
    hspi->pRxBuffPtr   = pRxData;
    hspi->RxXferSize   = Size;

    /* ------------------------------------------------------------------------------------------------------------------------------------ */
    /* EDIT: for some reason, the last byte is not received... so the RxCpltCallback MUST be called when the RxXferCount == 1 */
    /* ------------------------------------------------------------------------------------------------------------------------------------ */
    hspi->RxXferCount  = Size-1;

    /* Reset CRC Calculation */
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
      SPI_RESET_CRC(hspi);
    }

    /* Enable TXE, RXNE and ERR interrupt */
    __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

    /* Process Unlocked */
    __HAL_UNLOCK(hspi);

    /* Check if the SPI is already enabled */
    if((hspi->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Enable SPI peripheral */
      __HAL_SPI_ENABLE(hspi);
    }

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


/* Private implementations -------------------------------------- */

/**
  * @brief This function handles SPI Communication Timeout.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  Flag: SPI flag to check
  * @param  Status: Flag status to check: RESET or set
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef HELPER_SPI_WaitOnFlagUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus Status, uint32_t Timeout)
{
  uint32_t tickstart = 0;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until flag is set */
  if(Status == RESET)
  {
    while(__HAL_SPI_GET_FLAG(hspi, Flag) == RESET)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable the SPI and reset the CRC: the CRC value should be cleared
             on both master and slave sides in order to resynchronize the master
             and slave for their respective CRC calculation */

          /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
          __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);

          /* Reset CRC Calculation */
          if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
          {
            SPI_RESET_CRC(hspi);
          }

          hspi->State= HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while(__HAL_SPI_GET_FLAG(hspi, Flag) != RESET)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable the SPI and reset the CRC: the CRC value should be cleared
             on both master and slave sides in order to resynchronize the master
             and slave for their respective CRC calculation */

          /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
          __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);

          /* Reset CRC Calculation */
          if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
          {
            SPI_RESET_CRC(hspi);
          }

          hspi->State= HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Handler to transmit amount of data in no-blocking mode
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval void
  */
static void SPI_TxISR(SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 8 Bit mode */
  if(hspi->Init.DataSize == SPI_DATASIZE_8BIT)
  {
    hspi->Instance->DR = (*hspi->pTxBuffPtr++);
  }
  /* Transmit data in 16 Bit mode */
  else
  {
    hspi->Instance->DR = *((uint16_t*)hspi->pTxBuffPtr);
    hspi->pTxBuffPtr+=2;
  }
  hspi->TxXferCount--;

  if(hspi->TxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
      /* calculate and transfer CRC on Tx line */
      hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
    }
    SPI_TxCloseIRQHandler(hspi);
  }
}

/**
  * @brief  Interrupt Handler to receive amount of data in 2Lines mode
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval void
  */
static void SPI_2LinesRxISR(SPI_HandleTypeDef *hspi)
{
  /* Receive data in 8 Bit mode */
  if(hspi->Init.DataSize == SPI_DATASIZE_8BIT)
  {
    (*hspi->pRxBuffPtr++) = hspi->Instance->DR;
  }
  /* Receive data in 16 Bit mode */
  else
  {
    *((uint16_t*)hspi->pRxBuffPtr) = hspi->Instance->DR;
    hspi->pRxBuffPtr+=2;
  }
  hspi->RxXferCount--;

  if(hspi->RxXferCount==0)
  {
    SPI_RxCloseIRQHandler(hspi);
  }
}

/**
* @brief  Interrupt Handler to close Tx transfer
* @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
*                the configuration information for SPI module.
* @retval void
*/
static void SPI_TxCloseIRQHandler(SPI_HandleTypeDef *hspi)
{
	/* Wait until TXE flag is set to send data */
	if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_TXE, RESET, SPI_TIMEOUT_VALUE) != HAL_OK)
	{
	  hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
	}

	/* Disable TXE interrupt */
	__HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE ));

	/* Disable ERR interrupt if Receive process is finished */
	if(__HAL_SPI_GET_IT_SOURCE(hspi, SPI_IT_RXNE) == RESET)
	{
	  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_ERR));

	  /* Wait until Busy flag is reset before disabling SPI */
	  if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_BSY, SET, SPI_TIMEOUT_VALUE) != HAL_OK)
	  {
		hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
	  }

	  /* Clear OVERRUN flag in 2 Lines communication mode because received is not read */
	  if(hspi->Init.Direction == SPI_DIRECTION_2LINES)
	  {
		__HAL_SPI_CLEAR_OVRFLAG(hspi);
	  }

	  /* Check if Errors has been detected during transfer */
	  if(hspi->ErrorCode ==  HAL_SPI_ERROR_NONE)
	  {
		/* Check if we are in Tx or in Rx/Tx Mode */
		if(hspi->State == HAL_SPI_STATE_BUSY_TX_RX)
		{
		  /* Set state to READY before run the Callback Complete */
		  hspi->State = HAL_SPI_STATE_READY;
		  HAL_SPI_TxRxCpltCallback(hspi);
		}
		else
		{
		  /* Set state to READY before run the Callback Complete */
		  hspi->State = HAL_SPI_STATE_READY;
		  HAL_SPI_TxCpltCallback(hspi);
		}
	  }
	  else
	  {
		/* Set state to READY before run the Callback Complete */
		hspi->State = HAL_SPI_STATE_READY;
		/* Call Error call back in case of Error */
		HAL_SPI_ErrorCallback(hspi);
	  }
	}
}

/**
  * @brief  Interrupt Handler to close Rx transfer
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval void
  */
static void SPI_RxCloseIRQHandler(SPI_HandleTypeDef *hspi)
{
  __IO uint16_t tmpreg;

  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    /* Wait until RXNE flag is set to send data */
    if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_RXNE, RESET, SPI_TIMEOUT_VALUE) != HAL_OK)
    {
      hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
    }

    /* Read CRC to reset RXNE flag */
    tmpreg = hspi->Instance->DR;
    UNUSED(tmpreg);

    /* Wait until RXNE flag is set to send data */
    if(HELPER_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_RXNE, SET, SPI_TIMEOUT_VALUE) != HAL_OK)
    {
      hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
    }

    /* Check if CRC error occurred */
    if(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
    {
      hspi->ErrorCode |= HAL_SPI_ERROR_CRC;

      /* Reset CRC Calculation */
      SPI_RESET_CRC(hspi);
    }
  }

  /* Disable RXNE and ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE));

  /* if Transmit process is finished */
  if(__HAL_SPI_GET_IT_SOURCE(hspi, SPI_IT_TXE) == RESET)
  {
    /* Disable ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_ERR));

    if((hspi->Init.Mode == SPI_MODE_MASTER)&&((hspi->Init.Direction == SPI_DIRECTION_1LINE)||(hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
    {
      /* Disable SPI peripheral */
      __HAL_SPI_DISABLE(hspi);
    }

    /* Check if Errors has been detected during transfer */
    if(hspi->ErrorCode ==  HAL_SPI_ERROR_NONE)
    {
      /* Check if we are in Rx or in Rx/Tx Mode */
      if(hspi->State == HAL_SPI_STATE_BUSY_TX_RX)
      {
        /* Set state to READY before run the Callback Complete */
        hspi->State = HAL_SPI_STATE_READY;
        HAL_SPI_TxRxCpltCallback(hspi);
      }
      else
      {
        /* Set state to READY before run the Callback Complete */
        hspi->State = HAL_SPI_STATE_READY;
        HAL_SPI_RxCpltCallback(hspi);
      }
    }
    else
    {
      /* Set state to READY before run the Callback Complete */
      hspi->State = HAL_SPI_STATE_READY;
      /* Call Error call back in case of Error */
      HAL_SPI_ErrorCallback(hspi);
    }
  }
}

/**
 * @}
 */

/**
 * @}
 */
