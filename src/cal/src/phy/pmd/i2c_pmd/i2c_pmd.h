/**
 ******************************************************************************
 * @file    i2c_pmd.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   Physical Medium Dependant I2C Peripheral module
 ******************************************************************************
 */
#ifndef CAL_PMD_I2C_PMD_H_
#define CAL_PMD_I2C_PMD_H_

/* Includes ********************************************************************/
#include "pmd.h"
#include "../lib/i2c_helper/stm32f4xx_i2c_helper.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @addtogroup CAL_PHY Livello Fisico
 * @brief Livello fisico di CAL
 * @{
 */

/**
 * @addtogroup CAL_PHY_PMD_Module Sottolivello PMD
 * @{
 */

/**
 * @defgroup CAL_PHY_PMD_I2C Livello I2C del PMD
 * @brief Livello che gestisce periferiche di tipo I2C
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_PHY_PMD_I2C_Exported_Constants Exported Constants
 * @brief PMD I2C Costanti Esportate
 * @{
 */

#define USE_DMA						1	/**< If the DMA has to be used */

/**
 * @}
 */

/* Exported Macros *************************************************************/
/**
 * @defgroup CAL_PHY_PMD_I2C_Exported_Macros Exported Macros
 * @brief PMD I2C Macro esportate
 * @{
 */

#define PMD_isTypeI2c(ptr)				PMD_isType(ptr,PMD_I2C) /**< Controllo sul tipo di interfaccia -> I2C */

/**
 * @}
 */

/* Exported Types **************************************************************/

/**
 * @defgroup CAL_PHY_PMD_I2C_Exported_Types Exported Types
 * @brief PMD I2C Tipi esportati
 * @{
 */

/**
 * @brief I2C_PMD_Interface used for the mapping with physical peripheral.
 */
typedef struct
{
	PMD_Interface* pmd_ifx; /**< PMD_Interface reference */
	HELPER_I2C_TypeDef i2c_tx; /**< I2C Master */
	HELPER_I2C_TypeDef i2c_rx; /**< I2C Slave */
	PMD_Chunk* chunkToSend; /**< Local ptr chunk to send */
	PMD_Chunk* chunkToReceive; /**< Local ptr chunk to receive */
} I2C_PMD_Interface;

/**
 * @}
 */

/* Exported Variables **********************************************************/
/**
 * @defgroup CAL_PHY_PMD_I2C_Exported_Variables Exported Variables
 * @brief PMD I2C Exported Variables
 * @{
 */

/**
 * @brief Local i2c interfaces vector. Change here if other I2C interfaces are added,
 * 	  	  All I2C_TX (I2C_RX) have the same address
 */
static I2C_PMD_Interface i2c_pmd_interfaces[I2C_NUM_INTERFACES] =
{
{ NULL, HELPER_I2C1, HELPER_I2C2, NULL, NULL } };

/**
 * @}
 */

/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_PHY_PMD_I2C_Exported_Functions Exported Functions
 * @brief PMD I2C Exported Functions
 * @{
 */

PMD_Status pmdConfigI2c(PMD_Interface* pmd_ifx);
PMD_Status pmdInitI2c(PMD_Interface* pmd_ifx);
PMD_Status pmdDeInitI2c(PMD_Interface* pmd_ifx);
PMD_Status pmdSendI2c(PMD_Chunk* chunk);
PMD_Status pmdReceiveI2c(PMD_Chunk* chunk);

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

#endif /* CAL_PMD_I2C_PMD_H_ */
