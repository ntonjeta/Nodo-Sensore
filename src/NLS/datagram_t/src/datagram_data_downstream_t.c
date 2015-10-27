/*
 * datagram_data_upstream.c
 *
 *  Created on: 02/lug/2015
 *      Author: Paolo
 */


#include "datagram_data_downstream_t.h"

datagram_datadown_len_payload_t get_datagram_datadown_len_payload(uint8_t* packet){

	return (datagram_datadown_len_payload_t)getField(packet,DATAGRAM_DATADOWN_LEN_PAYLOAD_DISP, DATAGRAM_DATADOWN_LEN_PAYLOAD_LEN);

}


void set_datagram_datadown_len_payload(uint8_t* packet, datagram_datadown_len_payload_t val){

	setField(packet,DATAGRAM_DATADOWN_LEN_PAYLOAD_DISP, DATAGRAM_DATADOWN_LEN_PAYLOAD_LEN, val);

}

datagram_datadown_hop_count_t get_datagram_datadown_hop_count(uint8_t* packet){

	return (datagram_datadown_hop_count_t)getField(packet,DATAGRAM_DATADOWN_HOPCOUNT_DISP,DATAGRAM_DATADOWN_HOPCOUNT_LEN);

}

void set_datagram_datadown_hop_count(uint8_t* packet , datagram_datadown_hop_count_t hop_count){

	setField(packet,DATAGRAM_DATADOWN_HOPCOUNT_DISP, DATAGRAM_DATADOWN_HOPCOUNT_LEN, hop_count);

}

datagram_datadown_ds_path_length_t get_datagram_datadown_ds_path_length(uint8_t* packet){

	return (datagram_datadown_ds_path_length_t)getField(packet,DATAGRAM_DATADOWN_DSPATH_LENGTH_DISP,DATAGRAM_DATADOWN_DSPATH_LENGTH_LEN);
}


void set_datagram_datadown_ds_path_length(uint8_t* packet , datagram_datadown_ds_path_length_t length){

	setField(packet,DATAGRAM_DATADOWN_DSPATH_LENGTH_DISP,DATAGRAM_DATADOWN_DSPATH_LENGTH_LEN,length);

}


payload_t get_datagram_datadown_payload(uint8_t* packet){

	datagram_datadown_len_payload_t len = get_datagram_datadown_len_payload(packet);
	return getPayload(packet,DATAGRAM_DATADOWN_PAYLOAD_DISP,len);

}


void set_datagram_datadown_payload(uint8_t* packet,payload_t payload){

	datagram_datadown_len_payload_t len = get_datagram_datadown_len_payload(packet);
	setPayload(packet,DATAGRAM_DATADOWN_PAYLOAD_DISP,len,payload);

}


datagram_hop_if_t get_datagram_datadown_next_hop_if(uint8_t* packet){

	datagram_datadown_hop_count_t hc = get_datagram_datadown_hop_count(packet);

	return (datagram_hop_if_t) getField(packet,DATAGRAM_DATADOWN_DSPATH_LIST_DISP + 4*(hc-1),4);

}


void set_datagram_datadown_hop_if(uint8_t* packet,int hop,datagram_hop_if_t interface){

	setField(packet,DATAGRAM_DATADOWN_DSPATH_LIST_DISP+4*hop,4,interface);

}


datagram_hop_if_t get_datagram_datadown_hop_if(uint8_t* packet,int hop){

	return (datagram_hop_if_t)getField(packet,DATAGRAM_DATADOWN_DSPATH_LIST_DISP+4*hop,4);

}


void set_datagram_datadown_ds_path(uint8_t* packet,datagram_hop_if_t* interface){

	int i;
	datagram_datadown_ds_path_length_t length = get_datagram_datadown_ds_path_length(packet);
	for(i=0;i<length;i++){
		setField(packet,DATAGRAM_DATADOWN_DSPATH_LIST_DISP+4*i,4,interface[i]);
	}

}

payload_t get_datagram_datadown_trailer(uint8_t* packet)
{
	if(get_datagram_T(packet) != 0)
	{
		return get_datagram_datadown_payload(packet)+sizeof(uint8_t)*get_datagram_datadown_len_payload(packet);
	}
	else return 0;
}

void set_datagram_datadown_trailer(uint8_t* packet, uint8_t* trailer)
{

		setPayload(packet , DATAGRAM_DATADOWN_HEADER_LEN+get_datagram_datadown_len_payload(packet), TRAILER_LEN_BYTE/8 , trailer);
		set_datagram_T(packet , 1);

}
