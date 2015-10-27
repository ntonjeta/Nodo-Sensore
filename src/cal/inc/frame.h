/**
 ******************************************************************************
 * @file    frame.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    30/giu/2015
 * @brief   TODO: brief for frame.h
 ******************************************************************************
 */

#ifndef CAL_INC_FRAME_H_
#define CAL_INC_FRAME_H_

/* Includes ********************************************************************/
#include "cal_def.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @defgroup CAL_FRAME CAL Frame Module
 * @brief Modulo per la gestione delle frame
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_FRAME_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define HEADER_LENGTH					6		/**< Lunghezza dello header */

#if (CHUNK_LENGTH < HEADER_LENGTH)
#error "CHUNK_LENGHT MUST BE >= HEADER_LENGHT"
#endif

#define CAL_FIELD_RESERVED				0x00	/**< Valore del campo riservato */

/**
 * @}
 */

/* Exported Macros *************************************************************/

/**
 * @defgroup CAL_FRAME_Exported_Macros Exported Macros
 * @brief Macro esportate
 * @{
 */
#define dlGetFieldValue(ptr,offset)		ptr[offset] /**< */

/**
 * @}
 */

/* Exported Types **************************************************************/

/**
 * @defgroup CAL_FRAME_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

typedef uint8_t DL_SeqNumber_Type;
typedef uint8_t DL_Padding_Type;
typedef uint8_t DL_Reserved_Type;
typedef uint8_t DL_NumChunks_Type;
typedef uint8_t DL_Checksum_Type;

/**
 * @brief Struttura della frame
 */
typedef struct
{
	CAL_InterfaceNumber ifx;
	uint8_t* data;
} DL_Frame;

/**
 * @brief Campi dello header
 */
typedef enum
{
	DL_FTYPE_FIELD = 0x00,    //!< DL_FTYPE_FIELD
	DL_SEQNUMBER_FIELD = 0x01,//!< DL_SEQNUMBER_FIELD
	DL_NUMCHUNKS_FIELD = 0x02,//!< DL_NUMCHUNKS_FIELD
	DL_PADDING_FIELD = 0x03,  //!< DL_PADDING_FIELD
	DL_RESERVED_FIELD = 0x04, //!< DL_RESERVED_FIELD
	DL_CHECKSUM_FIELD = 0x05  //!< DL_CHECKSUM_FIELD
} DL_Header_Field;

/**
 * @brief Tipi di frame
 */
typedef enum
{
	DL_DATA = 0x01,       //!< DL_DATA
	DL_ACK = 0x02,        //!< DL_ACK
	DL_WELCOME = 0x03,    //!< DL_WELCOME
	DL_BYE = 0x04,        //!< DL_BYE
	DL_SENT_FAILED = 0x05,//!< DL_SENT_FAILED
	DL_SENT = 0x06        //!< DL_SENT
//NEW_TYPE = (The previous one incremented by 1)
} DL_Frame_Type;

/**
 * @brief Struttura dello header della frame
 */
typedef struct
{
	DL_Frame_Type fType;
	DL_SeqNumber_Type seqNumber;
	DL_NumChunks_Type numChunks;
	DL_Padding_Type padding;
	DL_Reserved_Type reserved;
	DL_Checksum_Type checksum;
} DL_Frame_Header;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @}
 */

/**
 * @}
 */

#endif /* CAL_INC_FRAME_H_ */
