/**
 ******************************************************************************
 * @file    crc.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    05/lug/2015
 * @brief   TODO: brief for crc.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "utils/crc.h"
#include "stm32f4xx_hal.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @addtogroup CAL_UTILS CAL Utils
 * @brief Moduli di utilità utilizzati da CAL
 * @{
 */

/**
 * @addtogroup CAL_UTILS_CRC CRC Module
 * @brief Fornisce le funzione per l'accesso all'hardware per il calcolo di un CRC-32.
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/

/**
 * @defgroup CAL_UTILS_CRC_Private_Types Private Types
 * @brief Tipi privati
 * @{
 */

CRC_HandleTypeDef CrcHandle; /**< Handle della periferica CRC */

/**
 * @}
 */

/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/
/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @addtogroup CAL_UTILS_CRC_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/**
 * @brief Inizializza il CRC-Calculator
 * @retval none
 */
uint8_t crcInit()
{
	CrcHandle.Instance = CRC;

	if (HAL_CRC_Init(&CrcHandle) == HAL_OK)
	{
		return 1;
	}

	return 0;
}

/**
 * @brief De-inizializza il CRC-Calculator
 * @retval none
 */
uint8_t crcDeInit()
{
	if (HAL_CRC_DeInit(&CrcHandle) == HAL_OK)
	{
		return 1;
	}

	return 0;
}

uint8_t crcCheckState()
{
	return HAL_CRC_GetState(&CrcHandle) == HAL_CRC_STATE_READY;
}

/**
 * @brief Calcola un CRC-32 bit
 * @param in data Dati su cui calcolarlo
 * @param in length Lunghezza dei dati
 * @retval CRC-32
 */
uint32_t crcCalculate(uint32_t* data, uint32_t length)
{
	return HAL_CRC_Calculate(&CrcHandle, data, length);
}

/**
 * @}
 */

/* HAL Dependant ****************************************************************/

/**
 * @defgroup CAL_UTILS_CRC_HAL_Dependant Hardware Dependant Functions
 * @brief Funzioni per la configurazione dell'hardware sottostante.
 * @{
 */

/**
 * @brief CRC MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
	(void)hcrc;

	/* CRC Peripheral clock enable */
	__HAL_RCC_CRC_CLK_ENABLE();
}

/**
 * @brief CRC MSP De-Initialization
 *        This function freeze the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
{
	(void)hcrc;

	/* Enable CRC reset state */
	__HAL_RCC_CRC_FORCE_RESET();

	/* Release CRC from reset state */
	__HAL_RCC_CRC_RELEASE_RESET();
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

/**
 * @}
 */

/**
 * @}
 */
