/**
  ******************************************************************************
  * @file    frame_queue.c
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    30/giu/2015
  * @brief   TODO: brief for frame_queue.c
  ******************************************************************************
  */


/* Includes ********************************************************************/
#include "utils/frame_queue.h"

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

/**
 * @defgroup CAL_UTILS_FRAME_QUEUE_Exported_Macros Exported Macros
 * @brief Macro esportate
 * @{
 */

DL_FrameQueue* initFrameQueue()
{
	// Logging
	calLogString(CAL_LOG_DEBUG, "initFrameQueue", "FUN-CALLED", "Frame queue initialized");

	// allocate malloc
	DL_FrameQueue* queue = queueMalloc(sizeof(DL_FrameQueue));

	// Logging
	calLogInt(CAL_LOG_DEBUG, "initFrameQueue", "QUEUE-ALLOCATED-B", sizeof(DL_FrameQueue));

	// the queue is empty, so the head and tail pointer are 0
	queue->head = NULL;
	queue->tail = NULL;

	// lenght is 0 at init
	queue->length = 0;

	return queue;
}

void enqueueFrame(DL_FrameQueue* queue, DL_Frame* const element)
{
	// Logging
	calLogString(CAL_LOG_DEBUG, "enqueueFrame", "FUN-CALLED", "Frame enqueued");

	// this is a FIFO queue, so we have to enqueue using the tail pointer
	DL_FrameQueueNode* node = queueMalloc(sizeof(DL_FrameQueueNode));

	// Logging
	calLogInt(CAL_LOG_DEBUG, "enqueueFrame", "QUEUE-NODE-ALLOCATED-B", sizeof(DL_FrameQueueNode));

	// assign the data element
	node->data = element;

	// no next element (this will be the last one)
	node->next = NULL;

	// if this is the first node, the head and tail pointers point to this node
	if (queue->length == 0)
	{
		// assign to tail and head this node
		queue->tail = node;
		queue->head = node;
		queue->length++;
		return;
	}

	// set this node as the next of the current tail node
	queue->tail->next = node;

	// finally update the tail node
	queue->tail = node;

	// increment the length
	queue->length++;
}

DL_Frame* dequeueFrame(DL_FrameQueue* queue)
{
	// Logging
	calLogString(CAL_LOG_DEBUG, "dequeueFrame", "FUN-CALLED", "Attempt to dequeue a frame");

	// return if the queue is empty
	if (frameQueueLength(queue) == 0)
	{
		// Logging
		calLogString(CAL_LOG_DEBUG, "dequeueFrame", "FRAME-DEQUEUE", "Frame queue is empty");
		return NULL;
	}

	// temp node (needed for the free)
	DL_FrameQueueNode* temp = queue->head;

	// if there is only one element, the tail and head pointers point to the same node (to be extracted)
	if (queue->length == 1)
	{
		// so set them to NULL
		queue->tail = queue->head = NULL;
	}
	else
	{
		// otherwise, we have other nodes, the new head must be updated to the next one
		queue->head = temp->next;
	}

	// give the element pointer back to the user
	DL_Frame* element = temp->data;

	// substract the length
	queue->length--;

	// free the node
	queueFree(temp);

	// Logging
	calLogInt(CAL_LOG_DEBUG, "dequeueFrame", "QUEUE-NODE-DEALLOCATED-B", sizeof(DL_FrameQueueNode));

	// return the needed element
	return element;
}

DL_Frame* queueGetHeadFrame(DL_FrameQueue* queue)
{
	// return if the queue is empty
	if (frameQueueLength(queue) == 0)
	{
		return NULL;
	}
	return queue->head->data;
}

void deInitFrameQueue(DL_FrameQueue* queue)
{
	// we can't deInit a non-empty queue
	if (queue->length > 0)
	{
		return;
	}

	queueFree(queue);

	// Logging
	calLogInt(CAL_LOG_DEBUG, "deInitFrameQueue", "QUEUE-DEALLOCATED-B", sizeof(DL_FrameQueue));
}

uint16_t frameQueueLength(const DL_FrameQueue* queue)
{
	return queue->length;
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
