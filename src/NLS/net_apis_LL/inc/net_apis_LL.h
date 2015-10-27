/*
 * net_apis_LL.h
 *
 *  Created on: 12/lug/2015
 *      Author: gennaro
 */

#ifndef NET_APIS_LL_INC_NET_APIS_LL_H_
#define NET_APIS_LL_INC_NET_APIS_LL_H_

#include "net_apis.h"
#include "net_apis_core.h"
#include  "cal.h"


void NLS_LL_init (struct NLS_HandleTypedef* hNLS);
void NLS_LL_deinit (struct NLS_HandleTypedef* hNLS);
void NLS_LL_enable_if (struct NLS_HandleTypedef* hNLS , uint8_t _if);
void NLS_LL_received_datagram (struct NLS_HandleTypedef* hNLS_ , datagram_info* d_info);
NLS_sendStatus NLS_LL_sendPacketTo(CAL_InterfaceNumber ifx, uint8_t *packet, uint16_t packetLength, uint8_t numRetry);
NLS_sendStatus NLS_LL_sendPacketMulticast(CAL_InterfaceNumber *ifxVector, uint8_t ifxVettLength, uint8_t *packet, uint16_t packetLength, uint8_t numRetry);
NLS_sendStatus NLS_LL_sendPacketBroadcast(uint8_t *packet, uint16_t packetLength, uint8_t numRetry);
#endif /* NET_APIS_LL_INC_NET_APIS_LL_H_ */
