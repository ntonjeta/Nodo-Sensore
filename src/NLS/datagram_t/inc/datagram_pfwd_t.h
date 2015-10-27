/*
 * datagram_bsrp_pfwd_t.h
 *
 *  Created on: 30/giu/2015
 *      Author: Ciro
 */

#ifndef DATAGRAM_BSRP_PFWD_T_H_
#define DATAGRAM_BSRP_PFWD_T_H_

#include "datagram_defs.h"
#include "datagram_t.h"
#include "datagram_data_upstream_t.h"
#include "network_config.h"

//#define DATAGRAM_PFWD_DSPATH_LENGTH_DISP  (DATAGRAM_FULL_DISP + DATAGRAM_FULL_LEN)
//#define DATAGRAM_PFWD_DSPATH_LENGTH_LEN   8

//TODO ATTENTI ALLA ZUPPA
#define CHALLENGE_LEN 						CHALLENGE_LEN_BYTE*8
#define DATAGRAM_PFWD_HOP_LIST_LENGTH_DISP  (DATAGRAM_FULL_DISP + DATAGRAM_FULL_LEN)
#define DATAGRAM_PFWD_HOP_LIST_LENGTH_LEN    8

#define DATAGRAM_PFWD_CHALLENGE_DISP   (DATAGRAM_PFWD_HOP_LIST_LENGTH_DISP + DATAGRAM_PFWD_HOP_LIST_LENGTH_LEN)
#define DATAGRAM_PFWD_CHALLENGE_LEN   	CHALLENGE_LEN    //la challenge è supposta a lunghezza configurabile attraverso questo parametro CHALLENGE_LEN contenuto in network_config.h

#define DATAGRAM_PFWD_DS_PATH_DISP		(DATAGRAM_PFWD_CHALLENGE_DISP + DATAGRAM_PFWD_CHALLENGE_LEN)
#define DATAGRAM_PFWD_DS_PATH_LEN		32   ////supponiamo di preallocare 4 byte per la lista delle interfacce

#define DATAGRAM_PFWD_HOP_LIST_DISP     (DATAGRAM_PFWD_DS_PATH_DISP + DATAGRAM_PFWD_DS_PATH_LEN)
#define DATAGRAM_PFWD_HOP_LIST_LEN		128

#define DATAGRAM_PFWD_HEADER_LEN_BYTE		((DATAGRAM_FULL_LEN + DATAGRAM_PFWD_HOP_LIST_LENGTH_LEN + DATAGRAM_PFWD_DS_PATH_LEN + DATAGRAM_PFWD_HOP_LIST_LEN)/8)
#define DATAGRAM_PFWD_HEADER_LEN			DATAGRAM_PFWD_HEADER_LEN_BYTE*8


datagram_pfwd_hop_list_length_t get_datagram_pfwd_hop_list_length(uint8_t* packet);
void set_datagram_pfwd_hop_list_length(uint8_t* packet , datagram_pfwd_hop_list_length_t length);

datagram_pfwd_challenge_t get_datagram_pfwd_challenge(uint8_t* packet);
void set_datagram_pfwd_challenge(uint8_t* packet , datagram_pfwd_challenge_t challenge);

//datagram_hop_if_t get_datagram_pfwd_next_hop_if(uint8_t* packet);
datagram_hop_if_t get_datagram_pfwd_hop_if(uint8_t* packet, int hop);

void set_datagram_pfwd_hop_if(uint8_t* packet, int hop, datagram_hop_if_t interface);
void set_datagram_pfwd_ds_path(uint8_t* packet,datagram_hop_if_t* interface);

//address_t get_datagram_pfwd_next_hop_address(uint8_t* packet);
datagram_address_t get_datagram_pfwd_hop_address(uint8_t* packet, int hop);

void set_datagram_pfwd_hop_address(uint8_t* packet, int hop, datagram_address_t address);
void set_datagram_pfwd_hop_list(uint8_t* packet,datagram_address_t* address);

/**
 *  getter e sett trailer
 */
payload_t get_datagram_pfwd_trailer(uint8_t* packet);
void set_datagram_pfwd_trailer(uint8_t* packet, uint8_t* trailer);


#endif /* DATAGRAM_BSRP_PFWD_T_H_ */
