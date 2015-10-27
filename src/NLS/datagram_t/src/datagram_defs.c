/*
 * datagram_defs.c
 *
 *  Created on: 02/lug/2015
 *      Author: Paolo
 */

#include "datagram_defs.h"
#include "datagram_t.h"
#include "datagram_data_upstream_t.h"
#include "datagram_data_downstream_t.h"
#include "datagram_pfwd_t.h"

int getField(uint8_t* packet, int disp, int len){
	int index=floor(disp/8);
	int mod=disp%8;

	// se il campo è contenuto in un byte, leggi normalmente
	if(mod+len <= 8) {
		return (packet[index] & (((int)(pow(2,len)-1))<<(8-len-mod)))>>(8-len-mod);
	} else {
		int tempLen = 8 - mod;
		int tempField = (packet[index] & (((int)(pow(2,tempLen)-1))<<(8-tempLen-mod)))>>(8-tempLen-mod);
		int tempField2 = getField(packet+index+1, 0, len - tempLen);
		return (tempField << (len-tempLen)) | tempField2;
	}
}

void setField(uint8_t* packet, int disp, int len,int val){
	int index=floor(disp/8);
	int mod=disp%8;
	uint8_t mask;

	// se il campo è contenuto in un byte, leggi normalmente
	if(mod+len <= 8) {
		//(packet[index] & (((int)(pow(2,len)-1))<<(8-len-mod)))>>(8-len-mod);
		mask = ((int)(pow(2,len)-1)) << (8-len-mod);
		packet[index]=(packet[index] & (~mask)) | (val << (8-len-mod));
	}
	else {
		int tempLen = 8 - mod;
		int tempVal = (val & (((int)(pow(2,tempLen)-1))<<(len-tempLen-mod)))>>(len-tempLen-mod);
		mask = ((int)(pow(2,tempLen)-1)) << (8-tempLen-mod);
		packet[index]=(packet[index] & (~mask)) | (tempVal << (8-tempLen-mod));

		int newVal = val - (tempVal >> (32-tempLen-mod));
		setField(packet+index+1, 0, len - tempLen,newVal);
	}
}

payload_t getPayload(uint8_t* packet,int disp,int nbyte)
{

	return packet+(disp/8);
}

void setPayload(uint8_t* packet , int disp,int nbyte , payload_t payload){

	int i = 0;
		for(i=0;i<nbyte;i++){
			setField(packet,disp+8*i,8,payload[i]);
		}
}

int getDatagramLength (uint8_t* packet) {

	return 0;
}


