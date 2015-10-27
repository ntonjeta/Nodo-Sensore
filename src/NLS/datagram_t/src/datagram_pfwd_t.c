
#include "datagram_pfwd_t.h"



datagram_pfwd_hop_list_length_t get_datagram_pfwd_hop_list_length(uint8_t* packet){

	return (datagram_pfwd_hop_list_length_t)getField(packet,DATAGRAM_PFWD_HOP_LIST_LENGTH_DISP,DATAGRAM_PFWD_HOP_LIST_LENGTH_LEN);

}

void set_datagram_pfwd_hop_list_length(uint8_t* packet , datagram_pfwd_hop_list_length_t length){

	setField(packet,DATAGRAM_PFWD_HOP_LIST_LENGTH_DISP,DATAGRAM_PFWD_HOP_LIST_LENGTH_LEN,length);

}

datagram_pfwd_challenge_t get_datagram_pfwd_challenge(uint8_t* packet){

	return (datagram_pfwd_challenge_t) getPayload(packet, DATAGRAM_PFWD_CHALLENGE_DISP, CHALLENGE_LEN_BYTE);
}

void set_datagram_pfwd_challenge(uint8_t* packet , challenge_t challenge){

	setPayload(packet,DATAGRAM_PFWD_CHALLENGE_DISP, CHALLENGE_LEN_BYTE, challenge);

}


datagram_hop_if_t get_datagram_pfwd_hop_if(uint8_t* packet,int hop){

	return (datagram_hop_if_t)getField(packet, DATAGRAM_PFWD_DS_PATH_DISP+4*hop,4);

}


void set_datagram_pfwd_hop_if(uint8_t* packet, int hop, datagram_hop_if_t interface){

	setField(packet, DATAGRAM_PFWD_DS_PATH_DISP+4*hop,4,interface);

}


void set_datagram_pfwd_ds_path(uint8_t* packet,datagram_hop_if_t* interface){

	int i;
	datagram_pfwd_ds_path_length_t length = get_datagram_pfwd_hop_list_length(packet);
	for(i=0;i<length;i++){
		setField(packet,DATAGRAM_PFWD_DS_PATH_DISP+4*i,4,interface[i]);
	}

}


datagram_address_t get_datagram_pfwd_hop_address(uint8_t* packet,int hop){

	return (datagram_address_t)getField(packet,DATAGRAM_PFWD_HOP_LIST_DISP+16*hop,16);

}


void set_datagram_pfwd_hop_address(uint8_t* packet, int hop, datagram_address_t address){

	setField(packet, DATAGRAM_PFWD_HOP_LIST_DISP+16*hop,16,address);

}


void set_datagram_pfwd_hop_list(uint8_t* packet,datagram_address_t* address){

	int i;
	datagram_pfwd_hop_list_length_t length = get_datagram_pfwd_hop_list_length(packet);
	for(i=0;i<length;i++){
		setField(packet,DATAGRAM_PFWD_HOP_LIST_DISP+16*i,16,address[i]);
	}

}
