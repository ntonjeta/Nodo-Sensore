/*
 * datagram_t.h
 *
 *  Created on: 30/giu/2015
 *      Author: Ciro
 */

#ifndef DATAGRAM_T_H_
#define DATAGRAM_T_H_

/* Includes ------------------------------------------------------------------*/
#include "datagram_defs.h"

#define DATAGRAM_T_DISP 0
#define DATAGRAM_T_LEN 1

#define DATAGRAM_PADDING2_LEN 2


#define DATAGRAM_TYPE_DISP (DATAGRAM_T_DISP + DATAGRAM_T_LEN)
#define DATAGRAM_TYPE_LEN 3


#define DATAGRAM_QOS_DISP (DATAGRAM_TYPE_DISP + DATAGRAM_TYPE_LEN + DATAGRAM_PADDING2_LEN)
#define DATAGRAM_QOS_LEN 2

#define DATAGRAM_ADDRESS_DISP (DATAGRAM_QOS_DISP + DATAGRAM_QOS_LEN)
#define DATAGRAM_ADDRESS_LEN 16

#define DATAGRAM_FULL_DISP   0
#define DATAGRAM_FULL_LEN_BYTE    3//((DATAGRAM_T_LEN+DATAGRAM_PADDING2_LEN+DATAGRAM_TYPE_LEN+DATAGRAM_QOS_LEN+DATAGRAM_ADDRESS_LEN)/8)
#define DATAGRAM_FULL_LEN			DATAGRAM_FULL_LEN_BYTE*8



uint8_t get_datagram_T(uint8_t*);
void set_datagram_T(uint8_t* , uint8_t);

datagram_type_t get_datagram_type(uint8_t*);
void set_datagram_type(uint8_t* , datagram_type_t);

datagram_qos_t get_datagram_QoS(uint8_t*);
void set_datagram_QoS(uint8_t* , datagram_qos_t);

datagram_address_t get_datagram_address(uint8_t*);
void set_datagram_address(uint8_t* , datagram_address_t);

void get_datagram_header_len (uint8_t*);


#endif /* DATAGRAM_T_H_ */

