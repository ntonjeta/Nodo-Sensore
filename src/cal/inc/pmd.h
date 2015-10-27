/**
 ******************************************************************************
 * @file    pmd.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   Physical Medium Dependent layer. Provides hardware-dependant function
 * 		 to configure, initialize, send and receive data on different types
 * 		 of communication peripheral.
 ******************************************************************************
 */
#ifndef CAL_PMD_H_
#define CAL_PMD_H_

/* Includes ********************************************************************/
#include "conf/pmd_conf.h"
#include "cal_def.h"

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
 * @defgroup CAL_PHY_PMD_Module CAL Physical Medium Dependant Sub-Layer
 * @brief Sottolivello dipendente dall' hardware sottostante
 * @{
 */

/* Exported Constants **********************************************************/

/* Exported Macros *************************************************************/
/**
 * @defgroup CAL_PHY_PMD_Exported_Macros Exported Macros
 * @brief Macro esportate
 * @{
 */

#define PMD_isType(ptr,pmd_type)			((ptr)->type == (pmd_type)) /**< Controllo sul tipo di interfaccia */
#define PMD_isInterfaceConfigured(ifx)		(ifx->status == PMD_IF_STATUS_CONFIGURED || ifx->status == PMD_IF_STATUS_INITIALIZED)
#define PMD_isInterfaceInitialized(ifx)		(ifx->status == PMD_IF_STATUS_INITIALIZED)

/**
 * @}
 */

/* Exported Types **************************************************************/
/**
 * @defgroup CAL_PHY_PMD_Exported_Type Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief PMD Status
 */
typedef enum
{
	PMD_OK = 0x00, /**< OK */
	PMD_ERROR = 0x01, /**< ERROR */
	PMD_BUSY = 0x02, /**< BUSY */
	PMD_TIMEOUT = 0x03, /**< TIMEOUT */
	PMD_ALREADY_CONFIGURED = 0x04, /**< Interface already configure */
	PMD_ALREADY_INITIALIZED = 0x05 /**< Interface already initialized */
} PMD_Status;

typedef uint16_t PMD_InterfaceId;

/**
 * @brief PMD Interface Status
 */
typedef enum
{
	PMD_IF_STATUS_NOT_CONFIGURED, /**< Not configured, the default state */
	PMD_IF_STATUS_CONFIGURED, /**< Configured, after the pmdConfig */
	PMD_IF_STATUS_INITIALIZED /**< Initialized, after the pmdInit */
} PMD_InterfaceStatus;

/**
 * @brief PMD Interface Struct
 */
typedef struct
{
	// ------ to ppp_pmd.c -------
	PMD_InterfaceId id; /**< Interface identifier */
	PMD_InterfaceType type; /**< Specifies the type of the interface */
	PMD_InterfaceStatus status; /**< Specifies the status of the interface */

	// ------ from network level -------
	CAL_InterfaceNumber ifxNumber; /**< The mapped CAL_Interface number */
} PMD_Interface;

/**
 * @brief PMD Chunk Struct
 */
typedef struct
{
	uint8_t* data; /**< Data pointer */
	PMD_Interface* pmdIfx; /**< PMD Interface reference */
	CAL_Option_Type isLastChunk; /**< If the chunk is the last of a series */
} PMD_Chunk;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/
/**
 * @defgroup CAL_PHY_PMD_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

PMD_Status pmdConfig(PMD_Interface* pmd_ifx);
PMD_Status pmdInit(PMD_Interface* pmd_ifx);
PMD_Status pmdDeInit(PMD_Interface* pmd_ifx);
PMD_Status pmdSend(PMD_Chunk* chunk);
PMD_Status pmdReceive(PMD_Chunk* pmd_ifx);

/**
 * @}
 */

/**
 * @defgroup CAL_PHY_PMD_Callback Exported Callback
 * @brief Callback
 * @{
 */
void pmdChunkSentCallback(PMD_Chunk* chunk);
void pmdChunkSendErrorCallback(PMD_Chunk* chunk);
void pmdChunkReceivedCallback(PMD_Chunk* chunk);
void pmdChunkReceiveErrorCallback(PMD_Chunk* chunk);

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

#endif /* CAL_PMD_H_ */
