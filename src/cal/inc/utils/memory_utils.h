/**
  ******************************************************************************
  * @file    memory_utils.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    07/lug/2015
  * @brief   TODO: brief for memory_utils.h
  ******************************************************************************
  */
#ifndef CAL_INC_UTILS_MEMORY_UTILS_H_
#define CAL_INC_UTILS_MEMORY_UTILS_H_

/* Includes ********************************************************************/

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
 * @defgroup CAL_UTILS_MEMORY_UTILS Memory Utils
 * @brief Utilità per il debug della memoria utilizzata
 * @{
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_UTILS_MEMORY_UTILS_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

void* calDebugMalloc(size_t size);
void calDebugFree(void* ptr);

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

#endif /* CAL_INC_UTILS_MEMORY_UTILS_H_ */
