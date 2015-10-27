/**
 ******************************************************************************
 * @file    cal.h
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    26/giu/2015
 * @brief   Communication Abstraction Layer
 * 			CAL fornisce un livello di astrazione per la comunicazione attraverso
 * 			il contetto di "interfaccia". Un interfaccia è un canale di comunicazione
 * 			bidirezionale indipendente da una particolare tecnologia.
 ******************************************************************************
 */
#ifndef CAL_CAL_H_
#define CAL_CAL_H_

/* Includes ********************************************************************/
#include "conf/cal_conf.h"
#include "cal_def.h"
#include "datalink.h"

/**
 * @defgroup CAL_Module CAL Module
 * @{
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_CAL_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

void calInit();

void enableInterface(CAL_InterfaceNumber ifx);
void disableInterface(CAL_InterfaceNumber ifx);

void sendPacketTo(CAL_InterfaceNumber ifx, uint8_t *packet, uint16_t packetLength, uint8_t numRetry); //ifx = OR Interfacce, numRetry >=0
void sendPacketMulticast(CAL_InterfaceNumber *ifxVector, uint8_t ifxVettLength, uint8_t *packet, uint16_t packetLength, uint8_t numRetry);
void sendPacketBroadcast(uint8_t *packet, uint16_t packetLength, uint8_t numRetry); // Flooding per link state*

void interfaceAttachedCallback(CAL_InterfaceNumber ifx); //In seguito ad un enable
void interfaceDetachedCallback(CAL_InterfaceNumber ifx); //In seguito ad un disable
void sentPacketCallback(CAL_InterfaceNumber ifx, uint8_t *packet, uint16_t packetLength); //Hook che indica la fine trasmissione di un singolo pkt
void receivedPacketCallback(CAL_InterfaceNumber ifx, uint8_t* packet, uint16_t packetLength);
void sendErrorCallback(CAL_InterfaceNumber ifx, uint8_t* packet,uint16_t packetLength);

CAL_Option_Type *getInterfaceStatusMap();
CAL_Option_Type getInterfaceAttachStatus(CAL_InterfaceNumber ifx);

/**
 * @}
 */

/**
 * @}
 */
#endif /* CAL_CAL_H_ */
