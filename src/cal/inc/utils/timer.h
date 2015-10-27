/**
  ******************************************************************************
  * @file    timer.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    05/lug/2015
  * @brief   TODO: brief for timer.h
  ******************************************************************************
  */
#ifndef CAL_INC_UTILS_TIMER_H_
#define CAL_INC_UTILS_TIMER_H_

#include "conf/cal_conf.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @defgroup CAL_UTILS CAL Utils
 * @brief Moduli di utilità utilizzati da CAL
 * @{
 */

/**
 * @defgroup CAL_TIMER Timer Module
 * @brief Modulo per la gestione del timer
 * @{
 */

#if (CAL_USE_OS == 0)

	/* Includes ********************************************************************/
	#include "stm32f4xx_hal.h"

	/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_UTILS_TIMER_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

	#define CAL_TIM					CAL_TIMx
	#define CAL_TIM_IRQn			CAL_TIMx_IRQn
	#define CAL_TIM_IRQHandler		CAL_TIMx_IRQHandler
	#define CAL_TIM_CLK_ENABLE()	CAL_TIMx_CLK_ENABLE();
	#define CAL_TIM_INT_PRIORITY	CAL_TIMx_INT_PRIORITY
	#define CAL_TIM_INT_SUBPRIORITY	CAL_TIMx_INT_SUBPRIORITY

/**
 * @}
 */

	/* Exported Macros *************************************************************/
	/* Exported Types **************************************************************/
	/* Exported Variables **********************************************************/
	/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_UTILS_TIMER_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

	void CAL_TIM_Init(int msPeriod);
	void CAL_TIM_Start();

	// Callbacks to be implemented in every CAL level that needs the timer
	void dlTimerPeriodElapsedCallback();

	/**
	 * @}
	 */

#endif

	/**
	 * @}
	 */

	/**
	 * @}
	 */

	/**
	 * @}
	 */

#endif /* CAL_INC_UTILS_TIMER_H_ */
