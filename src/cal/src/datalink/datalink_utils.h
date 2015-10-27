/**
 ******************************************************************************
 * @file    datalink_utils.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    03/lug/2015
 * @brief   TODO: brief for datalink_utils.h
 ******************************************************************************
 */

#ifndef CAL_SRC_DATALINK_DATALINK_UTILS_H_
#define CAL_SRC_DATALINK_DATALINK_UTILS_H_

/* Includes ********************************************************************/

#if CAL_USE_OS == 1
#include "semphr.h"
#endif

#include "frame.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @defgroup CAL_DATALINK_Module CAL Datalink Layer
 * @brief Livello datalink
 * @{
 */

/**
 * @defgroup CAL_DATALINK_UTILS CAL Datalinks Utils
 * @brief Funzioni di utilità per il livello datalink
 * @{
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/

/**
 * @defgroup CAL_DATALINK_UTILS_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Stato sequence number
 */
typedef enum
{
	AVAILABLE = 0x00,	/**< Disponibile */ //!< AVAILABLE
	NOT_AVAILABLE		/**< Non disponibile *///!< NOT_AVAILABLE
} DL_SeqNumber_Status;

/**
 * @brief Stato di interfaccia
 */
typedef enum
{
	DL_READY, DL_NOT_READY
} DL_InterfaceReady_Status;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_DATALINK_UTILS_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/* Utils implemented into OS Files dependent */
#if CAL_USE_OS == 1
SemaphoreHandle_t _dlTaskEnqueueAndTryToSend(CAL_InterfaceNumber ifx, DL_Frame *frame);
void _dlTaskSendAckFrame(DL_InterfaceReady_Status ifx,DL_SeqNumber_Type seqNumber);
void _dlTaskNotifySendingFailure(DL_Frame *frame);
void _dlTaskNotifySentFrame(DL_Frame *frame);
#endif

/* Utils implemented into datalink.c (OS independent) */

void _dlScanWaitingStagingArea();
void _dlEvaluateNumRetry(DL_Frame* frame, DL_SeqNumber_Type seqNumber);

void _dlSwitchReceivedFrame(DL_Frame *frame);

void _dlReceivedAckFrame(DL_Frame *frame);
void _dlReceivedByeFrame(DL_Frame *frame);
void _dlReceivedDataFrame(DL_Frame *frame);
void _dlReceivedWelcomeFrame(DL_Frame *frame);

void _dlSendAckFrame(CAL_InterfaceNumber ifx, DL_SeqNumber_Type seqNumber);
void _dlSendWelcomeFrame(CAL_InterfaceNumber ifx);
void _dlSendByeFrame(CAL_InterfaceNumber ifx);

void _dlFrameSent(CAL_InterfaceNumber ifx);

DL_SeqNumber_Type _dlGetSequenceNumber(CAL_InterfaceNumber ifx);

DL_Frame_Header *_dlGetHeaderFromFrame(DL_Frame *frame);
uint8_t* _dlGetPacketFromFrame(DL_Frame *frame);

DL_Frame* _dlPrepareFrame(CAL_InterfaceNumber ifx,uint16_t length);
void _dlPrepareFrameData(uint8_t *frameOut, DL_Frame_Header *header,
		uint8_t headerLength, uint8_t* packet, uint16_t packetLength,uint8_t paddingLength,CAL_Option_Type calculateCRC);

DL_Frame* _dlPrepareToSendFrameOverInterface(CAL_InterfaceNumber ifxIn);

DL_InterfaceReady_Status _dlGetInterfaceReadyStatus(CAL_InterfaceNumber ifx);
void _dlSetInterfaceReadyStatus(CAL_InterfaceNumber ifx,DL_InterfaceReady_Status newStatus);

DL_Frame* _dlGetFrameFromTxStage(uint8_t seqNumber);
void _dlEnqueueTxFrameQueue(CAL_InterfaceNumber ifx, DL_Frame *frame);


void _dlFreeResources(int16_t seqNumber,DL_Frame_Header *header,DL_Frame *frame);

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

#endif /* CAL_SRC_DATALINK_DATALINK_UTILS_H_ */
