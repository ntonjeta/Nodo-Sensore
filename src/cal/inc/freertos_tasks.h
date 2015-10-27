/**
 ******************************************************************************
 * @file    tasks.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    02/lug/2015
 * @brief   TODO: brief for tasks.h
 ******************************************************************************
 */
#ifndef CAL_INC_FREERTOS_TASKS_H_
#define CAL_INC_FREERTOS_TASKS_H_

#include "conf/cal_conf.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

#if (CAL_USE_OS == 1 && CAL_USE_OS_FREERTOS == 1)

/* Includes ********************************************************************/
/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_FREERTOS_TASK_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define CAL_TASKS_STACK_SIZE		512

/**
 * @}
 */

/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/

/**
 * @defgroup CAL_FREERTOS_TASK_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Message type
 */
typedef enum
{
	CAL_SEND,
	CAL_RECEIVE,
	CAL_SENT,	//callback
	CAL_RECEIVED, //callback
	CAL_ENABLE_IF,
	CAL_DISABLE_IF,
	CAL_INIT_IF,
	CAL_DEINIT_IF,
	CAL_ATTACHED_IF, //callback
	CAL_DETACHED_IF, //callback
	CAL_SEND_ERROR,
	CAL_RECEIVE_ERROR
	//CAL_NEW_MESSAGE_TYPE
} FREERTOS_CAL_MessageType;

typedef void* FREERTOS_CAL_MessageElement; /**< Tipo dell'elemento dei messaggi */

/**
 * @brief Tipo di messaggio spedito nelle code di FREERTOS
 */
typedef struct FREERTOS_CAL_Message
{
	FREERTOS_CAL_MessageType type;
	uint8_t paramLength;
	FREERTOS_CAL_MessageElement parameters;
} FREERTOS_CAL_Message;

/**
 * @}
 */

/* Exported Variables **********************************************************/

/**
 * @defgroup CAL_FREERTOS_TASK_Exported_Variables Exported Variables
 * @brief Handle di code
 * @{
 */

/**
 * @defgroup CAL_FREERTOS_TASK_Exported_Variables_Group1 Task Handles
 * @brief Task handle
 * @{
 */

/* CAL Tasks */
TaskHandle_t vCalUpstreamTask_handle;

/* Datalink Tasks */
TaskHandle_t vDlUpstreamTask_handle;
TaskHandle_t vDlDownstreamTask_handle;
TaskHandle_t vDlCheckTimeoutTask_handle;

/* PLCP Tasks */
TaskHandle_t vPlcpUpstreamTask_handle;
TaskHandle_t vPlcpDownstreamTask_handle;

/* PMD Tasks */
TaskHandle_t vPmdUpstreamTask_handle;
TaskHandle_t vPmdDownstreamTask_handle;

/**
 * @}
 */

/**
 * @defgroup CAL_FREERTOS_TASK_Exported_Variables_Group2 Queue Handles
 * @brief Queue Handles
 * @{
 */

/* Datalink Queues */
QueueHandle_t vDlUpstreamQueue_handle;
QueueHandle_t vDlDownstreamQueue_handle;

/* PLCP Queues */
QueueHandle_t vPlcpUpstreamQueue_handle;
QueueHandle_t vPlcpDownstreamQueue_handle;

/* PMD Queues */
QueueHandle_t vPmdUpstreamQueue_handle;
QueueHandle_t vPmdDownstreamQueue_handle;

/**
 * @}
 */

/**
 * @defgroup CAL_FREERTOS_TASK_Exported_Variables_Group3 Semaphore Handles
 * @brief Semaphores Handlers
 * @{
 */

/* Datalink Semaphores */
SemaphoreHandle_t xDlSequenceNumberSemaphore_handle;
SemaphoreHandle_t xDlQueueTxSemaphore_handle;
SemaphoreHandle_t xDlWaitingStageSemaphore_handle;
SemaphoreHandle_t xDlInterfaceStatusSemaphore_handle;

/**
 * @}
 */

/**
 * @}
 */

/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_FREERTOS_TASK_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/* Cal */
void vCalUpstreamTask(void*);

/* Datalink  */
void vDlUpstreamTask(void*);
void vDlDownstreamTask(void*);
void vDlCheckTimeoutTask(void*);

/* PLCP  */
void vPlcpUpstreamTask(void*);
void vPlcpDownstreamTask(void*);

/* PMD  */
//void vPmdUpstreamTask(void*);
void vPmdDownstreamTask(void*);

/**
 * @}
 */

/**
 * @}
 */

#endif

/**
 * @}
 */
#endif /* CAL_INC_FREERTOS_TASKS_H_ */
