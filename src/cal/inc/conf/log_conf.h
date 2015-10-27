/**
  ******************************************************************************
  * @file    log_conf.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    11/lug/2015
  * @brief   TODO: brief for log_conf.h
  ******************************************************************************
  */
#ifndef CAL_INC_CONF_LOG_CONF_H_
#define CAL_INC_CONF_LOG_CONF_H_

/* Includes ********************************************************************/
#include "cal_conf.h"

/**
 * @addtogroup CAL_Module CAL Module
 * @{
 */

/**
 * @addtogroup CAL_CONF Configuration files
 * @{
 * @brief File di configurazione
 */

/**
 * @defgroup CAL_LOG_CONF LOG COnfiguration file
 * @brief File di configurazione del log.
 * @{
 */

#if (CAL_USE_EVENTLOGGER_LOG == 1)
#include "EventLogger.h" // Include the LOG utility to be used
#endif

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_LOG_CONF_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#if (CAL_USE_EVENTLOGGER_LOG == 1)
#define CAL_LOG_NAMESPACE_CONF	DATALINK //!< This is defined into "EventLogger.h"
#else
#define CAL_LOG_NAMESPACE_CONF	0 //!< Simple integer namespace for the CAL level
#endif
#define CAL_LOG_NODEID_CONF		1 //!< 1 ?
#define CAL_LOG_LVL_CONF		5 //!< 0: ALERT, 1: CRITICAL, 2: ERROR, 3: WARNING, 4: NOTICE, 5: INFORMATIONAL, 6: DEBUG

/**
 * @}
 */

/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif /* CAL_INC_CONF_LOG_CONF_H_ */
