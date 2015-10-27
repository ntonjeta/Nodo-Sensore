/**
  ******************************************************************************
  * @file    queue.c
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    29/giu/2015
  * @brief   TODO: brief for queue.c
  ******************************************************************************
  */

/* Includes ********************************************************************/
#include "utils/chunk_queue.h"

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
 * @defgroup CAL_UTILS_CHUNK_QUEUE Chunk Queue Module
 * @brief Modulo per la gestione della coda di chunks
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
 * @defgroup CAL_UTILS_CHUNK_QUEUE_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

PLCP_ChunkQueue* initChunkQueue()
{
	// Logging
	calLogString(CAL_LOG_DEBUG, "initChunkQueue", "FUN-CALLED", "Chunks queue initialized");

	// allocate malloc
	PLCP_ChunkQueue* queue = queueMalloc(sizeof(PLCP_ChunkQueue));

	// Logging
	calLogInt(CAL_LOG_DEBUG, "initChunkQueue", "QUEUE-ALLOCATED-B", sizeof(PLCP_ChunkQueue));

	// the queue is empty, so the head and tail pointer are 0
	queue->head = NULL;
	queue->tail = NULL;

	// lenght is 0 at init
	queue->length = 0;

	return queue;
}

void enqueueChunk(PLCP_ChunkQueue* queue, PMD_Chunk* const element)
{
	// Logging
	calLogString(CAL_LOG_DEBUG, "enqueueChunk", "FUN-CALLED", "Chunk enqueued");

	// this is a FIFO queue, so we have to enqueue using the tail pointer
	PLCP_ChunkQueueNode* node = queueMalloc(sizeof(PLCP_ChunkQueueNode));

	// Logging
	calLogInt(CAL_LOG_DEBUG, "enqueueChunk", "QUEUE-NODE-ALLOCATED-B", sizeof(PLCP_ChunkQueueNode));

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

PMD_Chunk* dequeueChunk(PLCP_ChunkQueue* queue)
{
	// Logging
	calLogString(CAL_LOG_DEBUG, "dequeueChunk", "FUN-CALLED", "Attempt to dequeue a chunk");

	// return if the queue is empty
	if (chunkQueueLength(queue) == 0)
	{
		// Logging
		calLogString(CAL_LOG_DEBUG, "dequeueChunk", "CHUNK-DEQUEUE", "Chunk queue is empty");
		return NULL;
	}

	// temp node (needed for the free)
	PLCP_ChunkQueueNode* temp = queue->head;

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
	PMD_Chunk* element = temp->data;

	// substract the length
	queue->length--;

	// free the node
	queueFree(temp);

	// Logging
	calLogInt(CAL_LOG_DEBUG, "dequeueChunk", "QUEUE-NODE-DEALLOCATED-B", sizeof(PLCP_ChunkQueueNode));

	// return the needed element
	return element;
}

PMD_Chunk* queueGetHeadChunk(PLCP_ChunkQueue* queue)
{
	// return if the queue is empty
	if (chunkQueueLength(queue) == 0)
	{
		return NULL;
	}
	return queue->head->data;
}

void deInitChunkQueue(PLCP_ChunkQueue* queue)
{
	// we can't deInit a non-empty queue
	if (queue->length > 0)
	{
		return;
	}

	queueFree(queue);

	// Logging
	calLogInt(CAL_LOG_DEBUG, "deInitChunkQueue", "QUEUE-DEALLOCATED-B", sizeof(PLCP_ChunkQueue));
}

uint16_t chunkQueueLength(const PLCP_ChunkQueue* queue)
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
