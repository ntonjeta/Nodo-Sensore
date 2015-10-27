/*
 * datagram_builders_fork.c
 *
 *  Created on: 05/lug/2015
 *      Author: gennaro
 */

#include "network_config.h"
#include "datagram_builders_fork.h"
#include "datagram_builders.h"
#include "datagram_t.h"

uint8_t* build_PACK(PACK_typedef pack , int* datagram_length)
{
	usData_typedef data;
	data.payload_length = SECRET_LEN_BYTE;
	data.payload = pack.secret;
	data.qos = CONTROL;
	data.trailer = pack.trailer;

	uint8_t* packet = build_usData(data , datagram_length);

	set_datagram_type(packet , BSRP_PACK);

	return packet;
}


void print_PACK (uint8_t* packet)
{
	print_usData(packet);
}

uint8_t* getTrailer(uint8_t* packet)
{
	uint8_t* out = NULL;

	if(get_datagram_T(packet) == 1)
	{
		if (get_datagram_type(packet) == DATA_UP || BSRP_PACK)
		{
			out = get_datagram_dataup_trailer(packet);
		}
		else if (get_datagram_type(packet) == DATA_DOWN)
		{
			out = get_datagram_datadown_trailer(packet);
		}

	}
	return out;

}
void setTrailer(uint8_t* packet , uint8_t* trailer)
{
	if(get_datagram_T(packet) == 1)
	{
		if (get_datagram_type(packet) == DATA_UP || BSRP_PACK)
		{
			set_datagram_dataup_trailer(packet , trailer);
		}
		else if (get_datagram_type(packet) == DATA_DOWN)
		{
			set_datagram_datadown_trailer(packet , trailer);
		}
	}
}

uint8_t* build_PREP_from_PREQ(uint8_t* packet , int* datagram_length , uint8_t* payload , uint8_t* trailer)
{
	PREP_typedef prep;

	prep.address = get_datagram_address(packet);
	prep.payload = payload;
	prep.payload_length = SECRET_LEN_BYTE;
	prep.qos = CONTROL;
	prep.ds_path_length = 0;
	prep.ds_path = NULL;
	prep.trailer = trailer;

	uint8_t* out = build_PREP(prep , datagram_length);

	return out;
}

