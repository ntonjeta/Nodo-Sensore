/*
 * datagram_info.h
 *
 *  Created on: 02/lug/2015
 *      Author: gennaro
 */

#ifndef DATAGRAM_INFO_H_
#define DATAGRAM_INFO_H_

#include "datagram_defs.h"

#define NO_SRC_IF 0xff


typedef struct
{
	uint8_t* packet;
	datagram_if_id_t source_if;
	datagram_type_t type;
	int packet_length;
	datagram_address_t address;
	uint8_t retry;

}datagram_info;

datagram_info* init_datagram_info (uint8_t* packet , datagram_if_id_t src_if , int datagram_length, uint8_t retry );
void free_datagram_info(datagram_info* d_info);


void print_datagram_info(datagram_info* d_info);


#endif /* DATAGRAM_INFO_H_ */
