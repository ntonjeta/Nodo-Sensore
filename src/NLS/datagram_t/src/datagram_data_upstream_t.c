/*
 * datagram_data_upstream.c
 *
 *  Created on: 02/lug/2015
 *      Author: Paolo
 */


#include "datagram_data_upstream_t.h"

datagram_dataup_len_payload_t get_datagram_dataup_len_payload(uint8_t* packet){

	return (datagram_dataup_len_payload_t)getField(packet,DATAGRAM_DATAUP_LEN_PAYLOAD_DISP, DATAGRAM_DATAUP_LEN_PAYLOAD_LEN);

}


void set_datagram_dataup_len_payload(uint8_t* packet, datagram_dataup_len_payload_t val){

	setField(packet,DATAGRAM_DATAUP_LEN_PAYLOAD_DISP, DATAGRAM_DATAUP_LEN_PAYLOAD_LEN, val);

}


payload_t get_datagram_dataup_payload(uint8_t* packet){

	datagram_dataup_len_payload_t len = get_datagram_dataup_len_payload(packet);
	return getPayload(packet,DATAGRAM_DATAUP_PAYLOAD_DISP,len);

}

void set_datagram_dataup_payload(uint8_t* packet,payload_t payload){

	datagram_dataup_len_payload_t len = get_datagram_dataup_len_payload(packet);
	setPayload(packet,DATAGRAM_DATAUP_PAYLOAD_DISP,len,payload);

}

payload_t get_datagram_dataup_trailer(uint8_t* packet)
{
	if(get_datagram_T(packet) != 0)
	{
		return get_datagram_dataup_payload(packet)+sizeof(uint8_t)*get_datagram_dataup_len_payload(packet);
	}
	else return 0;
}

void set_datagram_dataup_trailer(uint8_t* packet, uint8_t* trailer)
{

		uint8_t* ptrailer =  get_datagram_dataup_trailer(packet);
		memcpy(ptrailer , trailer , TRAILER_LEN_BYTE);

		set_datagram_T(packet , 1);

}
