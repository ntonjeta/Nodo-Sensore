/**
 ******************************************************************************
 * @file    cal_def.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    04/lug/2015
 * @brief   CAL Definitions
 ******************************************************************************
 */
#ifndef CAL_INC_CAL_DEF_H_
#define CAL_INC_CAL_DEF_H_

/* Includes ********************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "conf/cal_conf.h"
#include "utils/memory_utils.h"
#include "utils/log.h"

/**
 * @addtogroup CAL_Module CAL Module
 * @{
 */

/**
 * @addtogroup CAL_CAL_DEF CAL Definitions
 * @{
 */

/* Exported Constants **********************************************************/
/**
 * @defgroup CAL_CAL_DEF_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define CHUNK_LENGTH 	16 /**< Lunghezza dei chunk */

/**
 * @}
 */
/* Exported Macros *************************************************************/

/**
 * @defgroup CAL_CAL_DEF_Exported_Macros Exported Macros
 * @brief Macro esportate
 * @{
 */

#if (CAL_USE_OS == 0)
#define calMalloc				malloc 	/**< Ridenominazione malloc */
#define calFree					free	/**< Ridenominazione free */
#else
#define calMalloc				pvPortMalloc
#define calFree					vPortFree
#endif

#define calAssertTrue(x)		if (x == 0) for(;;) 	/**< Assert */
#define calUnused(x)			(void)x 				/**< To avoid -Wunused warnings */
#define CAL_UNUSED_FUNCTION		__attribute__((unused))	/**< Per evitare unused sulle funzioni e variabili */
#define CAL_WEAK				__attribute__((weak)) 	//!< Weak Definition

#ifndef NULL
#define NULL					0
#endif


/**
 * @}
 */

/* Exported Types **************************************************************/

/**
 * @addtogroup CAL_CAL_DEF_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */
typedef uint8_t CAL_InterfaceNumber; /**< Tipo numero dell'interfacce */
#define IF0 0
#define IF1 1
#define IF2 2
#define IF3 3
#define IF4 4
#define IF5 5
#define IF_ALL 6

/**
 * @brief Stato
 */
typedef enum
{
	CAL_OK = 0x0,		/**< Stato OK */
	CAL_ERROR = 0x01	/**< Stato di Errore */
} CAL_Status;

/**
 * @brief Opzione SI o NO
 */
typedef enum
{
	CAL_NO = 0x00, 	/**< NO */
	CAL_YES = 0x01	/**< YES */
} CAL_Option_Type;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @}
 */

/**
 * @}
 */

#endif /* CAL_INC_CAL_DEF_H_ */
