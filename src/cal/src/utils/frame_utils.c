/**
 ******************************************************************************
 * @file    frame_utils.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    05/lug/2015
 * @brief   TODO: brief for frame_utils.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "utils/frame_utils.h"

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
 * @addtogroup CAL_UTILS_FRAME_UTILS Frame Utils
 * @brief Funzioni di utilità per la gestione delle frame, CRC, checksum etc...
 * @{
 */

/* Check to see if CHUNK_LENGTH is multiple of CRC_LENGTH */
#if (CHUNK_LENGTH%CRC_LENGTH != 0)
#error "CHUNK_LENGTH MUST BE multiple of CRC_LENGTH"
#endif

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/

/* Declarations */
uint8_t checksumCalculate(uint8_t*, uint8_t);
uint8_t checksumCheck(const uint8_t const*, uint8_t, uint8_t);

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_UTILS_FRAME_UTILS_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/**
 * @brief Calcola la checksum sull'header di una frame
 * @param in frame La frame sul cui header calcolare la checksum
 * @retval La checksum
 */
uint8_t frameHeaderChecksumCalculate(DL_Frame* frame)
{
	return checksumCalculate(frame->data, HEADER_LENGTH - 1);
}

/**
 * @brief Crea la checksum nell'header della frame
 * @param in frame La frame
 * @retval none
 */
void frameHeaderChecksumCreate(DL_Frame_Header* header)
{
	uint8_t data[HEADER_LENGTH - 1];

	data[DL_FTYPE_FIELD] = header->fType;
	data[DL_SEQNUMBER_FIELD] = header->seqNumber;
	data[DL_PADDING_FIELD] = header->padding;
	data[DL_RESERVED_FIELD] = header->reserved;
	data[DL_NUMCHUNKS_FIELD] = header->numChunks;

	header->checksum = checksumCalculate(data, HEADER_LENGTH - 1);
}

/**
 * @brief Controlla la checksum sull'header
 * @param in frame La frame su cui fare il controllo
 * @retval L'esito del confronto
 * 		   @arg 0 Fallito
 * 		   @arg 1 Successo
 */
CAL_Option_Type frameHeaderChecksumCheck(DL_Frame* frame)
{
	return checksumCheck(frame->data, HEADER_LENGTH - 1,
			frame->data[DL_CHECKSUM_FIELD]) == 1;
}

/**
 * @brief Controlla che data contiene un header in testa
 * @param in data Il puntatore ai dati
 * @retval L'esito :
 * 		   @arg 0 Fallito
 * 		   @arg 1 Successo
 */
CAL_Option_Type isHeader(uint8_t*data)
{

	uint8_t retval = CAL_NO;
	/* Check type field */
	if (data[DL_FTYPE_FIELD] >= 0x01 && data[DL_FTYPE_FIELD] <= 0x04)
	{
		if (data[DL_RESERVED_FIELD] == CAL_FIELD_RESERVED)
		{
			if (checksumCheck(data, HEADER_LENGTH - 1, data[DL_CHECKSUM_FIELD])
					== 1)
			{
				retval = CAL_YES;
			}
		}
	}

	return retval;
}

/**
 * @brief Crea il CRC della frame e lo appende
 * @param in frame
 * @retval L'esito :
 * 		   @arg 0 Fallito
 * 		   @arg 1 Successo
 */
CAL_Option_Type frameCRCCreate(uint8_t* data, uint32_t length)
{
	if (crcCheckState() != 1)
	{
		return CAL_NO;
	}

	uint32_t* data32 = (uint32_t*) data;
	uint32_t data32Length = (length - CRC_LENGTH) / 4;

	uint32_t crcValue = crcCalculate(data32, data32Length);

	data32[data32Length] = crcValue;

	return CAL_YES;
}

/**
 * @brief Controlla il CRC della frame e lo appende
 * @param in frame
 * @retval L'esito :
 * 		   @arg 0 Fallito
 * 		   @arg 1 Successo
 */
CAL_Option_Type frameCRCCheck(uint8_t* data, uint32_t length)
{
	if (crcCheckState() != 1)
	{
		return CAL_NO;
	}

	uint32_t* data32 = (uint32_t*) data;
	uint32_t data32Length = (length - CRC_LENGTH) / 4;

	uint32_t crcValue = crcCalculate(data32, data32Length);

	uint32_t crcValueToCheck = data32[data32Length];

	if (crcValue == crcValueToCheck)
		return CAL_YES;
	else
		return CAL_NO;
}

/**
 * @}
 */

/* Private Functions Implementations ********************************************/

/**
 * @defgroup CAL_UTILS_FRAME_UTILS_Private_Functions Private Functions
 * @brief Funzioni private
 * @{
 */

/**
 * @brief Calcola una checksum.
 * @param in data Puntatore ai dati su cui calcolarla
 * @param in length Lunghezza dei dati
 * @retval La checksum
 */
uint8_t checksumCalculate(uint8_t* data, uint8_t length)
{

	uint8_t checksum = 0;

	for (uint8_t i = 0; i < length; i++)
	{
		checksum += data[i]; // Eventualmente mettere degli shift aritmetici
	}

	return ~checksum; // two's complement.
}

/**
 * @brief Controlla una checksum.
 * @param in data Puntatore ai dati su cui calcolarla
 * @param in length Lunghezza dei dati
 * @retval La checksum
 */
uint8_t checksumCheck(const uint8_t const *data, uint8_t length,
		uint8_t checksumToCheck)
{
	uint8_t checksum = 1;

	for (uint8_t i = 0; i < length; i++)
	{
		checksum += data[i]; // Eventualmente mettere degli shift aritmetici
	}

	return (uint8_t) (checksum + checksumToCheck) == 0;
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
