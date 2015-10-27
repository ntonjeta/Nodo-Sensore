/**
  ******************************************************************************
  * @file    plcp_utils.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    03/lug/2015
  * @brief   TODO: brief for plcp_utils.h
  ******************************************************************************
  */
#ifndef CAL_SRC_PHY_PLCP_PLCP_UTILS_H_
#define CAL_SRC_PHY_PLCP_PLCP_UTILS_H_

/* Includes ********************************************************************/
#include "frame.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @addtogroup CAL_PHY CAL Physical Layer
 * @brief Livello fisico di CAL
 * @{
 */

/**
 * @addtogroup CAL_PHY_PLCP_Module CAL Physical Layer Convergence Procedure Sub-Layer
 * @brief Sottolivello fisico di convergenza
 * @{
 */

/**
 * @defgroup CAL_PHY_PLCP_UTILS CAL PLCP Utils
 * @brief Funzioni di utilità per il livello plcp
 * @{
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_PHY_PLCP_UTILS_Exported_Functions Utility Exported Functions
 * @brief Funzioni di utilità esportate
 * @{
 */

// Queue management and tx/rx processes
PMD_Chunk* _getNextEnqueuedChunkOnIfx(CAL_InterfaceNumber ifx);
PMD_Chunk* _getNextEnqueuedChunkOnQueue(PLCP_ChunkQueue* queue);
void _cleanSendChunksOnIfx(CAL_InterfaceNumber ifx);
void _cleanReceivedChunksOnIfx(CAL_InterfaceNumber ifx);
void _cleanChunksOnQueue(PLCP_ChunkQueue* queue);
void _enqueueFrameChunks(DL_Frame* frame, DL_NumChunks_Type numChunks);
void _enqueueReceivedChunk(PMD_Chunk* chunk);

// Chunk allocation / deallocation
PMD_Chunk* _allocateReceiveChunkForIfx(CAL_InterfaceNumber ifx);
PMD_Chunk* _allocateChunk();
void _deAllocateChunk(PMD_Chunk* chunk);

// Init and deInit of the PMD interfaces
CAL_Option_Type _getEnableStatusOnIfx(CAL_InterfaceNumber ifx);

// Frame building
DL_Frame* _buildReceivedFrameOnIfx(CAL_InterfaceNumber ifx);
DL_Frame* _buildReceivedFrameOnQueue(PLCP_ChunkQueue* queue);

// Receipt process status management
PLCP_ReceiveStatus _getReceiveStatusOnIfx(CAL_InterfaceNumber ifx);
PLCP_ReceiveStatus _getReceiveStatusOnPlcpIfx(PLCP_Interface* plcpIfx);
void _setReceiveStatusOnIfx(CAL_InterfaceNumber ifx, PLCP_ReceiveStatus rxStatus);
void _setReceiveStatusOnPlcpIfx(PLCP_Interface* plcpIfx, PLCP_ReceiveStatus rxStatus);

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

/**
 * @}
 */
#endif /* CAL_SRC_PHY_PLCP_PLCP_UTILS_H_ */
