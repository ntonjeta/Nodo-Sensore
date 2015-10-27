/**
  ******************************************************************************
  * @file    frame_queue.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    30/giu/2015
  * @brief   TODO: brief for frame_queue.h
  ******************************************************************************
  */

#ifndef CAL_INC_UTILS_FRAME_QUEUE_H_
#define CAL_INC_UTILS_FRAME_QUEUE_H_

/* Includes ********************************************************************/
#include "frame.h"

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
 * @defgroup CAL_UTILS_FRAME_QUEUE Frame Queue Module
 * @brief Modulo per la gestione della coda di frame
 * @{
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/

/**
 * @defgroup CAL_UTILS_FRAME_QUEUE_Exported_Macros Exported Macros
 * @brief Macro esportate
 * @{
 */

#define queueMalloc calMalloc
#define queueFree	calFree

/**
 * @}
 */

/* Exported Types **************************************************************/

/**
 * @defgroup CAL_UTILS_FRAME_QUEUE_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Nodo coda
 */
typedef struct DL_FrameQueueNode {
	DL_Frame* data;
	struct DL_FrameQueueNode* next;
} DL_FrameQueueNode;

/**
 * @brief Code
 */
typedef struct {
	DL_FrameQueueNode* head;
	DL_FrameQueueNode* tail;
	uint16_t length;
} DL_FrameQueue;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_UTILS_FRAME_QUEUE_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

DL_FrameQueue* initFrameQueue();
void enqueueFrame(DL_FrameQueue* queue, DL_Frame* const element);
DL_Frame* dequeueFrame(DL_FrameQueue* queue);
DL_Frame* queueGetHeadFrame(DL_FrameQueue* queue);
uint16_t frameQueueLength(const DL_FrameQueue* queue);
void deInitFrameQueue(DL_FrameQueue* queue);

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

#endif /* CAL_INC_UTILS_FRAME_QUEUE_H_ */
