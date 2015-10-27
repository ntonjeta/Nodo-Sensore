/**
 ******************************************************************************
 * @file    crc.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    05/lug/2015
 * @brief   TODO: brief for crc.h
 ******************************************************************************
 */
#ifndef CAL_INC_UTILS_CRC_H_
#define CAL_INC_UTILS_CRC_H_

/* Includes ********************************************************************/
#include <stdint.h>

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
 * @defgroup CAL_UTILS_CRC CRC Module
 * @brief Fornisce le funzione per l'accesso all'hardware per il calcolo di un CRC-32.
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_UTILS_CRC_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define CRC_LENGTH			4 	/**< Lunghezza CRC */

/**
 * @}
 */

/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_UTILS_CRC_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

uint8_t crcInit();
uint8_t crcDeInit();
uint8_t crcCheckState();
uint32_t crcCalculate(uint32_t* data, uint32_t length);

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

#endif /* CAL_INC_UTILS_CRC_H_ */
