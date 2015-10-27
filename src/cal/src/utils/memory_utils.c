/**
  ******************************************************************************
  * @file    memory_utils.c
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    07/lug/2015
  * @brief   TODO: brief for memory_utils.c
  ******************************************************************************
  */

/* Includes ********************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/
/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

extern uint32_t mallocCounter;
extern uint32_t freeCounter;

/**
 * @defgroup CAL_UTILS_MEMORY_UTILS_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/**
 * @brief Wrapper della malloc
 * @param size
 */
void* calDebugMalloc(size_t size)
{
	mallocCounter++;
	return malloc(size);
}

/**
 * @brief Wrapper della free
 * @param ptr
 */
void calDebugFree(void* ptr)
{
	freeCounter++;
	return free(ptr);
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
