/**
  ******************************************************************************
  * @file    queue.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    29/giu/2015
  * @brief   TODO: brief for queue.h
  ******************************************************************************
  */
#ifndef CAL_SRC_PHY_PLCP_QUEUE_H_
#define CAL_SRC_PHY_PLCP_QUEUE_H_

/* Includes ********************************************************************/
#include "pmd.h"

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

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/

/**
 * @defgroup CAL_UTILS_CHUNK_QUEUE_Exported_Macros Exported Macros
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
 * @defgroup CAL_UTILS_CHUNK_QUEUE_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Nodo coda
 */
typedef struct PLCP_ChunkQueueNode {
	PMD_Chunk* data;
	struct PLCP_ChunkQueueNode* next;
} PLCP_ChunkQueueNode;

/**
 * @brief Coda
 */
typedef struct {
	PLCP_ChunkQueueNode* head;
	PLCP_ChunkQueueNode* tail;
	uint16_t length;
} PLCP_ChunkQueue;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_UTILS_CHUNK_QUEUE_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

PLCP_ChunkQueue* initChunkQueue();
void enqueueChunk(PLCP_ChunkQueue* queue, PMD_Chunk* const element);
PMD_Chunk* dequeueChunk(PLCP_ChunkQueue* queue);
PMD_Chunk* queueGetHeadChunk(PLCP_ChunkQueue* queue);
uint16_t chunkQueueLength(const PLCP_ChunkQueue* queue);
void deInitChunkQueue(PLCP_ChunkQueue* queue);

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

#endif /* CAL_SRC_PHY_PLCP_QUEUE_H_ */
