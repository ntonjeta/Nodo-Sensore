/**
 ******************************************************************************
 * @file    pmd.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    02/lug/2015
 * @brief   TODO: brief for pmd.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "pmd.h"

#if (CAL_USE_OS == 1)
#include "freertos_tasks.h"

/* Private Constants ***********************************************************/
#define PMD_MIN_STACK_SIZE			312
#define PMD_TASK_PRIORITY			tskIDLE_PRIORITY

/* Private Macros **************************************************************/
/* Private Types ***************************************************************/

/**
 * @{
 */

typedef struct
{
	PMD_Status (*fun)(PMD_Chunk*);
	QueueHandle_t* queue;
} FREERTOS_PMD_PeriphConf;

/**
 * @}
 */

/* Private Variables ***********************************************************/

/**
 * @addtogroup
 * @brief
 * @{
 */

/* PMD Specific Tasks */
static TaskHandle_t vPmdPeriphTask_handle[IFX_TYPES_COUNT * 2];

/* PMD Specific Queues */
static TaskHandle_t vPmdPeriphQueue_handle[IFX_TYPES_COUNT * 2];

/**
 * @}
 */

/* Private Functions ***********************************************************/

/**
 * @addtogroup
 * @brief
 * @{
 */
/* PMD Specific  */
void vPmdPeriphFunCal(void*);

/**
 * @}
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup
 * @brief PMD Tasks
 * @{
 */

/* PMD  */

///**
// * @brief Upstream task of the pmd sub-layer
// * @param in p Parameter passed from the task creator
// * @retval none
// */
//void vPmdUpstreamTask(void* p)
//{
//	// The input parameter of the task is not used
//	calUnused(p);
//
//	// Init the input-communication queue
//	vPmdUpstreamQueue_handle = xQueueCreate(1, sizeof(FREERTOS_CAL_Message));
//
//	FREERTOS_CAL_Message message;
//
//	for (;;)
//	{
//		if (vPmdUpstreamQueue_handle != NULL)
//		{
//			// Wait for a message in blocking-mode.
//			if (xQueueReceive(vPmdUpstreamQueue_handle, &message,
//					portMAX_DELAY))
//			{
//				xQueueSend(vPlcpUpstreamQueue_handle, &message, portMAX_DELAY);
//			}
//		}
//	}
//
//	vTaskDelete(NULL);
//}
/**
 * @brief Downstrean task of the pmd sub-layer
 * @param in p Parameter passed from the task creator
 * @retval none
 */
void vPmdDownstreamTask(void* p)
{
	// The input parameter of the task is not used
	calUnused(p);

	extern PMD_Status pmdSendI2c(PMD_Chunk*);
	extern PMD_Status pmdReceiveI2c(PMD_Chunk*);
	extern PMD_Status pmdSendSpi(PMD_Chunk*);
	extern PMD_Status pmdReceiveSpi(PMD_Chunk*);
	extern PMD_Status pmdSendUart(PMD_Chunk*);
	extern PMD_Status pmdReceiveUart(PMD_Chunk*);

	// Init the input-communication queue
	vPmdDownstreamQueue_handle = xQueueCreate(IFX_TYPES_COUNT*2, sizeof(FREERTOS_CAL_Message));

	FREERTOS_PMD_PeriphConf conf[IFX_TYPES_COUNT * 2];
	PMD_Status (*pmdFun[IFX_TYPES_COUNT * 2])(PMD_Chunk*) =
	{	pmdSendI2c,pmdReceiveI2c, //I2C
			pmdSendSpi,pmdReceiveSpi,// SPI
			pmdSendUart,pmdReceiveUart// UART
	};
	// Create sending and receiving task
//	for (uint8_t i = 0; i < IFX_TYPES_COUNT * 2; i += 2)
//	{
//		// Create queue
//		conf[i].fun = pmdFun[i];
//		conf[i].queue = &(vPmdPeriphQueue_handle[i]);
//		xTaskCreate(vPmdPeriphFunCal, "PMD Send Task", PMD_MIN_STACK_SIZE,
//				&(conf[i]), PMD_TASK_PRIORITY+4, &(vPmdPeriphTask_handle[i])); //TODO
//		conf[i + 1].fun = pmdFun[i + 1];
//		conf[i + 1].queue = &(vPmdPeriphQueue_handle[i + 1]);
//		xTaskCreate(vPmdPeriphFunCal, "PMD Receive Task", PMD_MIN_STACK_SIZE,
//				&(conf[i + 1]), PMD_TASK_PRIORITY+4,
//				&(vPmdPeriphTask_handle[i + 1])); //TODO
//	}

	FREERTOS_CAL_Message message;
	PMD_Chunk* chunk;
	for (;;)
	{
		if (vPmdDownstreamQueue_handle != NULL)
		{
			// Wait for a message in blocking-mode.
			if (xQueueReceive(vPmdDownstreamQueue_handle, &message,
					portMAX_DELAY))
			{
				// There should be only one parameter of PMD_Chunk type
				chunk = (PMD_Chunk*) message.parameters;

//				// Message received, check the type
				switch (message.type)
				{
				case CAL_SEND:
				{
					/* Call the type-specific function */
					switch (chunk->pmdIfx->type)
					{
					case PMD_I2C:
//						xQueueSend(vPmdPeriphQueue_handle[0], &message,
//								portMAX_DELAY);
						pmdSendI2c(chunk);
						break;
					case PMD_SPI:
//						xQueueSend(vPmdPeriphQueue_handle[2], &message,
//								portMAX_DELAY);
						pmdSendSpi(chunk);
						break;
					case PMD_UART:
//						xQueueSend(vPmdPeriphQueue_handle[4], &message,
//								portMAX_DELAY);
						pmdSendUart(chunk);
						break;
					default:
						break;
					}
				}
					break;
				case CAL_RECEIVE:
				{
					/* Call the type-specific function */
					switch (chunk->pmdIfx->type)
					{
					case PMD_I2C:
//						xQueueSend(vPmdPeriphQueue_handle[1], &message,
//								portMAX_DELAY);
						pmdReceiveI2c(chunk);
						break;
					case PMD_SPI:
//						xQueueSend(vPmdPeriphQueue_handle[3], &message,
//								portMAX_DELAY);
						pmdReceiveSpi(chunk);
						break;
					case PMD_UART:
//						xQueueSend(vPmdPeriphQueue_handle[5], &message,
//								portMAX_DELAY);
						pmdReceiveUart(chunk);
						break;
					default:
						break;
					}
				}
					break;
				default:
					break;
				}
			}
		}
	}

	vTaskDelete(NULL);
}

/* PMD Specific  */

void vPmdPeriphFunCal(void* p)
{
	FREERTOS_PMD_PeriphConf* conf = (FREERTOS_PMD_PeriphConf*) p;

	// Init the input-communication queue
	*(conf->queue) = xQueueCreate(1, sizeof(FREERTOS_CAL_Message));

	QueueHandle_t queue = *(conf->queue);

	FREERTOS_CAL_Message message;
	for (;;)
	{
		if (queue != NULL)
		{
			// Wait for a message in blocking-mode.
			if (xQueueReceive(queue, &message, portMAX_DELAY))
			{
				conf->fun((PMD_Chunk*)message.parameters);
			}
		}
	}
	vTaskDelete(NULL);
}

/**
 * @}
 */
#endif
