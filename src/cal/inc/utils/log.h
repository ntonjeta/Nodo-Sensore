/**
 ******************************************************************************
 * @file    log.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    11/lug/2015
 * @brief   TODO: brief for log.h
 ******************************************************************************
 */
#ifndef CAL_INC_UTILS_LOG_H_
#define CAL_INC_UTILS_LOG_H_

/* Includes ********************************************************************/
#include <stdint.h>
#include "conf/log_conf.h"

/**
 * @addtogroup CAL_Module CAL Module
 * @{
 */

/**
 * @defgroup CAL_LOG CAL Log Module
 * @brief Modulo per il logging in CAL
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_LOG_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define CAL_LOG_NAMESPACE	CAL_LOG_NAMESPACE_CONF
#define CAL_LOG_NODEID		CAL_LOG_NODEID_CONF
#define CAL_LOG_LEVEL		CAL_LOG_LVL_CONF

/**
 * @}
 */

/* Exported Macros *************************************************************/

/* Exported Types **************************************************************/

/**
 * @defgroup CAL_LOG_Exported_Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Livelli di severità del log
 */
typedef enum
{
	CAL_LOG_ALERT = 0,		//!< CAL_LOG_ALERT
	CAL_LOG_CRITICAL,		//!< CAL_LOG_CRITICAL
	CAL_LOG_ERROR,			//!< CAL_LOG_ERROR
	CAL_LOG_WARNING,		//!< CAL_LOG_WARNING
	CAL_LOG_NOTICE,			//!< CAL_LOG_NOTICE
	CAL_LOG_INFORMATIONAL,	//!< CAL_LOG_INFORMATIONAL
	CAL_LOG_DEBUG			//!< CAL_LOG_DEBUG
} CAL_LogSeverity;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_LOG_Exported_Functions Exported Functions
 * @brief Funzioni esportate.
 * @{
 */


void calLogInt(CAL_LogSeverity severity, char* functionName, char* name, uint16_t value);
void calLogString(CAL_LogSeverity severity, char* functionName, char* name, char* value);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif /* CAL_INC_UTILS_LOG_H_ */
