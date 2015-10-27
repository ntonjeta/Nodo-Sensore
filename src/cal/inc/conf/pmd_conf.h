/**
 ******************************************************************************
 * @file    pmd_conf.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   CAL PMD Configuration file
 ******************************************************************************
 */
#ifndef CAL_PMD_CONF_H_
#define CAL_PMD_CONF_H_

/* Includes ********************************************************************/
#include <stdint.h>

/**
 * @addtogroup CAL_Module CAL Module
 * @{
 */

/**
 * @addtogroup CAL_CONF Configuration files
 * @{
 * @brief File di configurazione
 */

/**
 * @defgroup CAL_PMD_CONF PMD Configuration file
 * @brief File di configurazione del livello PMD
 * @{
 */

/* Exported Constants **********************************************************/

/**
 * @defgroup CAL_PMD_CONF_Exported_Constants Exported Constants
 * @brief Costanti esportate
 * @{
 */

#define IFX_TYPES_COUNT			3 /**< This MUST be equal to the number of element into the PMD_InterfaceType enum */
#define GET_MAX_INTERFACES()	(SPI_NUM_INTERFACES+UART_NUM_INTERFACES+I2C_NUM_INTERFACES)

/**
 * @defgroup CAL_PMD_CONF_Exported_Constants_Group1 Peripheral Interface Numbers
 * @brief An interface is a bi-directional communication channel. The way to achieve this
 * 	      is peripheral-type dependent. It's masked by the PMD level.
 * @{
 */
#define UART_NUM_INTERFACES		3
#define SPI_NUM_INTERFACES		1
#define I2C_NUM_INTERFACES		0

/**
 * @}
 */

/**
 * @}
 */

/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/

/**
 * @defgroup CAL_PMD_CONF_Exported_Types Exported Types
 * @brief Tipi esportati
 * @{
 */

/**
 * @brief Tipo di interfaccia
 */
typedef enum
{
	PMD_I2C, 	/**< I2C */
	PMD_SPI, 	/**< SPI */
	PMD_UART, 	/**< UART */
} PMD_InterfaceType;


/**
 * @brief Tipo configurazione di interfaccia
 */
typedef struct
{
	PMD_InterfaceType type; /**< Tipo dell'interfaccia */
	uint8_t count;			/**< Numero di interfaccie */
} PMD_InterfaceTypeConfig;

/**
 * @}
 */

/* Exported Variables **********************************************************/

/**
 * @defgroup CAL_PMD_CONF_Exported_Variables Exported Variables
 * @brief Variabili esportate
 * @{
 */

/**
 * @brief Vettore di configurazione delle interfacce. Fornisce per ogni tipo,
 * 		  il numero effettivo di interfacce presenti.
 */
static const PMD_InterfaceTypeConfig interfacesConfig[IFX_TYPES_COUNT] =
{
	{ PMD_SPI, SPI_NUM_INTERFACES }, /**< SPI */
	{ PMD_UART, UART_NUM_INTERFACES }, /**< UART */
	{ PMD_I2C, I2C_NUM_INTERFACES } /**< I2C */
	//{PMD_NEW, NEW_PERIPH_NUM_INTERFACES} and increment IF_TYPES_SIZE by one
};

/**
 * @}
 */

/* Exported Functions **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif /* CAL_PMD_CONF_H_ */
