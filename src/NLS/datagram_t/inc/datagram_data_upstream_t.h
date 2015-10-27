/*
 * datagram_data_upstream_t.h
 *
 *  Created on: 30/giu/2015
 *      Author: Ciro
 */

#ifndef DATAGRAM_DATA_UPSTREAM_T_H_
#define DATAGRAM_DATA_UPSTREAM_T_H_

#include "datagram_t.h"
#include "datagram_defs.h"



#define DATAGRAM_DATAUP_LEN_PAYLOAD_DISP    (DATAGRAM_FULL_DISP + DATAGRAM_FULL_LEN)

#define DATAGRAM_DATAUP_LEN_PAYLOAD_LEN     8

#define DATAGRAM_DATAUP_PAYLOAD_DISP        (DATAGRAM_DATAUP_LEN_PAYLOAD_DISP+DATAGRAM_DATAUP_LEN_PAYLOAD_LEN)

#define DATAGRAM_DATAUP_HEADER_LEN_BYTE		((DATAGRAM_FULL_LEN + DATAGRAM_DATAUP_LEN_PAYLOAD_LEN)/8)
#define DATAGRAM_DATAUP_HEADER_LEN			DATAGRAM_DATAUP_HEADER_LEN_BYTE*8

datagram_dataup_len_payload_t get_datagram_dataup_len_payload(uint8_t*);
void set_datagram_dataup_len_payload(uint8_t* , datagram_dataup_len_payload_t);

payload_t get_datagram_dataup_payload(uint8_t* packet);
void set_datagram_dataup_payload(uint8_t* packet,payload_t payload);

payload_t get_datagram_dataup_trailer(uint8_t* packet);
void set_datagram_dataup_trailer(uint8_t* packet,payload_t payload);


#endif /* DATAGRAM_DATA_UPSTREAM_T_H_ */
