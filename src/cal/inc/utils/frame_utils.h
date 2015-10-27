/**
 ******************************************************************************
 * @file    frame_utils.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    05/lug/2015
 * @brief   TODO: brief for frame_utils.h
 ******************************************************************************
 */
#ifndef CAL_INC_UTILS_FRAME_UTILS_H_
#define CAL_INC_UTILS_FRAME_UTILS_H_

/* Includes ********************************************************************/
#include "frame.h"
#include "crc.h"

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
 * @defgroup CAL_UTILS_FRAME_UTILS Frame Utils
 * @brief Funzioni di utilità per la gestione delle frame, CRC, checksum etc...
 * @{
 */

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

uint8_t frameHeaderChecksumCalculate(DL_Frame*);
void frameHeaderChecksumCreate(DL_Frame_Header*);
CAL_Option_Type frameHeaderChecksumCheck(DL_Frame*);

CAL_Option_Type isHeader(uint8_t*);

CAL_Option_Type frameCRCCreate(uint8_t*,uint32_t length);
CAL_Option_Type frameCRCCheck(uint8_t*,uint32_t length);

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

#endif /* CAL_INC_UTILS_FRAME_UTILS_H_ */
