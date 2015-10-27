/**
 ******************************************************************************
 * @file    timer.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    05/lug/2015
 * @brief   TODO: brief for timer.c
 ******************************************************************************
 */

#include "utils/timer.h"

#if (CAL_USE_OS == 0)

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
 * @addtogroup CAL_TIMER Timer Module
 * @brief Modulo per la gestione del timer
 * @{
 */

/* Private Constants ***********************************************************/

/**
 * @defgroup CAL_UTILS_TIMER_Private_Constants Private Constants
 * @brief Costanti private
 * @{
 */

static TIM_HandleTypeDef timerHandler;

/**
 * @}
 */

/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/

/**
 * @defgroup CAL_UTILS_TIMER_Private_Functions Private Functions
 * @brief Funzioni private
 * @{
 */

/**
 * @brief Timer Msp Init CAL-specifica
 * @param htim Handle del timer
 */
static void CAL_TIM_MspInit(TIM_HandleTypeDef* htim)
{
	(void)htim;

	/* TIMx Peripheral clock enable */
	CAL_TIM_CLK_ENABLE();

	/*##-2- Configure the NVIC for TIMx ########################################*/
	/* Set Interrupt Group Priority */
	HAL_NVIC_SetPriority(CAL_TIM_IRQn, CAL_TIM_INT_PRIORITY, CAL_TIM_INT_SUBPRIORITY);

	/* Enable the TIMx global Interrupt */
	HAL_NVIC_EnableIRQ(CAL_TIM_IRQn);
}

/**
 * @brief Callback chiamata quando il timer è scaduto
 * @param htim Handle del timer
 */
static void CAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	(void)htim;
	// Call all attached callbacks for CAL levels

	// 1) Callback for DATALINK layer
	dlTimerPeriodElapsedCallback();

	// n) All other callbacks
	// ...

}

/**
 * @}
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @addtogroup CAL_UTILS_TIMER_Exported_Functions Exported Functions
 * @brief Funzioni esportate.
 * @{
 */

/**
 * @brief Init the timer specified into the helper file
 * @param period: the period in ms
 * @retval none
 */
void CAL_TIM_Init(int msPeriod)
{
	/* Compute the prescaler value to have the counter clock equal to 10 KHz */
	uint32_t uwPrescalerValue = (uint32_t) ((SystemCoreClock / 2) / 10000) - 1;

	/* Set TIMx instance */
	timerHandler.Instance = CAL_TIM;

	timerHandler.Init.Period = 10 * msPeriod - 1;
	timerHandler.Init.Prescaler = uwPrescalerValue;
	timerHandler.Init.ClockDivision = 0;
	timerHandler.Init.CounterMode = TIM_COUNTERMODE_UP;

	// inner init
	if (HAL_TIM_Base_Init(&timerHandler) != HAL_OK)
	{
		/* Initialization Error */
	}
}

/**
 * @brief Avvia il timer
 * @retval none
 */
void CAL_TIM_Start(void)
{
	// init the timer
	if (HAL_TIM_Base_Start_IT(&timerHandler) != HAL_OK)
	{
		// Starting Error
	}
}


// Weak callback
__attribute__((weak)) void dlTimerPeriodElapsedCallback()
{
	// This function should by implemented by the DATALINK layer
}

// The following two functions may conflict with other definitions into the whole project
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == timerHandler.Instance)
	{
		CAL_TIM_MspInit(htim);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim->Instance == timerHandler.Instance)
	{
		CAL_TIM_PeriodElapsedCallback(htim);
	}
}

void CAL_TIM_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&timerHandler);
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
#endif // CAL_USE_OS
