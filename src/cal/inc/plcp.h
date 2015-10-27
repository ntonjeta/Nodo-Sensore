/**
  ******************************************************************************
  * @file    plcp.h
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    28/giu/2015
  * @brief   TODO: brief for plcp.h
  ******************************************************************************
  */
#ifndef CAL_PLCP_PLCP_H_
#define CAL_PLCP_PLCP_H_

/* Includes ********************************************************************/
#include "cal_def.h"
#include "frame.h"
#include "pmd.h"
#include "utils/chunk_queue.h"

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
 * @defgroup CAL_PHY_PLCP_Module CAL Physical Layer Convergence Procedure Sub-Layer
 * @brief Sottolivello fisico di convergenza
 * @{
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/

/**
 * @defgroup CAL_PLCP_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Stato in ricezione
 */
typedef enum
{
	PLCP_RX_HEADER_EXPECTED,//!< Atteso un chunk con header in testa
	PLCP_RX_DATA_EXPECTED   //!< Atteso un chunk dato
} PLCP_ReceiveStatus;

/**
 * @brief Astrazione dell'interfaccia al livello PLCP
 */
typedef struct
{
	// --- PMD area ---
	// This is the interface available to the pmd level
	PMD_Interface* pmdIfx; /**< Interfaccia livello PMD */

	// --- PLCP area ---
	// These queues store all the chunks received and to be send
	PLCP_ChunkQueue* txQueue; /**< Coda in invio */
	PLCP_ChunkQueue* rxQueue; /**< Coda in ricezione */

	// Temp chunks that are into the PMD area waiting for both TX process and RX process
	// The txQueue and rxQueue have heads that point to the next chunk to be transmitted (not the temp chunk given to the PMD)
	PMD_Chunk* tmpTxChunk; /**< Chunk in invio */
	PMD_Chunk* tmpRxChunk; /**< Chunk in ricezione */

	// Store the status of the interface
	CAL_Option_Type enabled; /**< Interfaccia abilitata */

	// Store the status of the receipt process like a finite state machine
	PLCP_ReceiveStatus rxStatus; /**< Stato della ricezione */

	// --- CAL area ---
	// mapping di PMD_Interface su un numero interfaccia (IF0, IF1...)
	CAL_InterfaceNumber ifxNumber; /**< The mapped CAL_Interface number */
} PLCP_Interface;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_PLCP_Exported_Functions Exported Functions
 * @{
 */

void plcpInit();
void plcpConfigPmdInterfaces();

CAL_Status plcpEnableInterface(CAL_InterfaceNumber ifx);
CAL_Status plcpDisableInterface(CAL_InterfaceNumber ifx);

CAL_Option_Type plcpGetInterfaceStatus(CAL_InterfaceNumber ifx);
CAL_Option_Type* plcpGetInterfaceStatusMap();

void plcpSendFrame(DL_Frame* frame, DL_NumChunks_Type numChunks);

void plcpChunkSentCallback(PMD_Chunk* chunk);
void plcpChunkSendErrorCallback(PMD_Chunk *chunk);

void plcpChunkReceivedCallback(PMD_Chunk* chunk);
void plcpChunkReceiveErrorCallback(PMD_Chunk* chunk);

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

#endif /* CAL_PLCP_PLCP_H_ */
