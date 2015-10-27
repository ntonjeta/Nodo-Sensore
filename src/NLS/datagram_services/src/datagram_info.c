/*
 * datagram_info.c
 *
 *  Created on: 02/lug/2015
 *      Author: gennaro
 */

#include "datagram_info.h"
#include "datagram_builders.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * TODO memcpy
 */
datagram_info* init_datagram_info (uint8_t* packet , datagram_if_id_t src_if , int datagram_length, uint8_t retry)
{
	datagram_info* d_info = (datagram_info*)malloc(sizeof(datagram_info));
	d_info->packet = (uint8_t*)malloc(datagram_length*sizeof(uint8_t));
	memcpy(d_info->packet,  packet, datagram_length);

	d_info->packet_length = datagram_length;
	d_info->source_if = src_if;
	d_info->type = get_datagram_type(packet);
	d_info->address = get_datagram_address(packet);
	d_info->retry = retry;
	return d_info;

}

void free_datagram_info(datagram_info* d_info)
{
	free(d_info->packet);
	free(d_info);
}



void print_datagram_info(datagram_info* d_info){
	printf("DATAGRAM INFO\n\r");
	printf("\tSource interface ->\t%i\n\r", d_info->source_if);
	printf("\tPacket length ->\t%i\n\r", d_info->packet_length);
	printf("\tRetry ->\t%i\n\r", d_info->retry);
	switch (get_datagram_type(d_info->packet)) {
		case DATA_UP:
			printf("\tTYPE ->\tDATA_UP\n\r");
			printf("\tPACKET\n\r");
			print_usData(d_info->packet);
			break;
		case DATA_DOWN:
			printf("\tTYPE ->\tDATADOWN\n\r");
			printf("\tPACKET\n\r");
			print_dsData(d_info->packet);
			break;
		case BSRP_PREQ:
			printf("\tTYPE ->\tBSRP_PREQ\n\r");
			printf("\tPACKET\n\r");
			print_PREQ(d_info->packet);
			break;
		case BSRP_PREP:
			printf("\tTYPE ->\tBSRP_PREP");
			printf("\tPACKET\n\r");
			print_dsData(d_info->packet);
			break;
		case BSRP_PFWD:
			printf("\tTYPE ->\tBSRP_PFWD");
			printf("\tPACKET\n\r");
			print_PFWD(d_info->packet);
			break;
		case BSRP_PACK:
			printf("\tTYPE ->\tBSRP_PACK");
			printf("\tPACKET\n\r");
			print_PACK(d_info->packet);
	}
}

