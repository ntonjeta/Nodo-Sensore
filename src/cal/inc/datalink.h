/**
 ******************************************************************************
 * @file    datalink.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   TODO: brief for datalink.h
 ******************************************************************************
 */

#ifndef CAL_DATALINK_DATALINK_H_
#define CAL_DATALINK_DATALINK_H_

/* Includes ********************************************************************/
#include "cal_def.h"
#include "plcp.h"
#include "frame.h"
#include "utils/frame_queue.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @defgroup CAL_DATALINK_Module CAL Datalink Layer
 * @brief Livello datalink
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_DATALINK_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define DL_SEQ_NUMBER_MAP_SIZE		256 	/**< Massimo sequence number */
#define DL_NUM_TICK_MAX				CAL_NUM_TICK_MAX		/**< Numero di tick per il retry */
#define DL_TIMEOUT_PERIOD_MS		CAL_RX_TIMER_PERIOD_MS		/**< Periodo del timeout */
#define DL_WELCOME_NUM_RETRY		CAL_WELCOME_NUM_RETRY		/**< Numero tentativi del welcome packet */

/**
 * @}
 */

/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/

/**
 * @defgroup CAL_DATALINK_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Stato datalink
 */

typedef enum
{
	DL_OK = CAL_OK, 		/**< Stato OK */       //!< DL_OK
	DL_ERROR = CAL_ERROR	/**< Stato ERRORE *///!< DL_ERROR
} DL_Status;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @addtogroup CAL_DATALINK_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

DL_Status dlInit();
void dlSendFrame(CAL_InterfaceNumber ifx, uint8_t* packet,
		uint16_t packetLength, uint8_t numRetry);
void dlFrameSentCallback(CAL_InterfaceNumber ifx);
void dlReceivedFrame(DL_Frame *frame);
void dlEnableInterface(CAL_InterfaceNumber ifx);
void dlDisableInterface(CAL_InterfaceNumber ifx);
CAL_Option_Type* dlGetInterfaceStatusMap();
CAL_Option_Type dlGetInterfaceAttachStatus(CAL_InterfaceNumber ifx);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif /* CAL_DATALINK_DATALINK_H_ */
