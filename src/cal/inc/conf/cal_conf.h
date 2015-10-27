/**
  ******************************************************************************
  * @file    cal_conf.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    04/lug/2015
  * @brief   CAL Configuration File
  ******************************************************************************
  */
#ifndef CAL_INC_CONF_CAL_CONF_H_
#define CAL_INC_CONF_CAL_CONF_H_

/* Includes ********************************************************************/

/**
 * @addtogroup CAL_Module CAL Module
 * @{
 */

/**
 * @defgroup CAL_CONF Configuration files
 * @{
 * @brief File di configurazione
 */

/**
 * @defgroup CAL_CAL_CONF CAL Configuration file
 * @brief File di configurazione di CAL
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_CAL_CONF_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define CAL_USE_OS					0 			/**< Se è utilizzato un Embedded OS */
#define CAL_USE_OS_FREERTOS			CAL_USE_OS	/**< Se è utilizzato FREERTOS */

#define CAL_USE_LOG					0			/**< Se abilitare il logging */
#define CAL_USE_EVENTLOGGER_LOG		0			/**< Se abilitare il logging con l'utility EventLogger */

#define CAL_RX_TIMER_PERIOD_MS		5		   /**< Periodo timer/task di che scandisce la Rx Queue, Notification queue e verifica timeout frame */
#define CAL_NUM_TICK_MAX			10		/**< Numero di tick per il retry di una frame (periodo: tick*CAL_RX_TIMER_PERIOD_MS) */

#define CAL_WELCOME_NUM_RETRY		0		/**< Numero ritentativi del welcome packet */

#if (CAL_USE_OS == 0)
	// Configure a timer when the OS is not enabled
	#define CAL_TIMx					TIM3 						/**< Timer da utilizzare */
	#define	CAL_TIMx_IRQn				TIM3_IRQn
	#define CAL_TIMx_IRQHandler			TIM3_IRQHandler
	#define CAL_TIMx_CLK_ENABLE()		__HAL_RCC_TIM3_CLK_ENABLE()
	#define CAL_TIMx_INT_PRIORITY		5
	#define CAL_TIMx_INT_SUBPRIORITY	1
#endif

#if (CAL_USE_OS == 1 && CAL_USE_OS_FREERTOS == 1)
	#include "FreeRTOS.h"
	#include "task.h"
	#include "queue.h"
	#include "semphr.h"
#endif

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
#endif /* CAL_INC_CONF_CAL_CONF_H_ */
