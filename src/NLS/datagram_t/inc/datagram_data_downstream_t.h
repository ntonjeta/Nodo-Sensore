/*
 * datagram_data_downstream_t.h
 *
 *  Created on: 30/giu/2015
 *      Author: Ciro
 */

#ifndef DATAGRAM_DATA_DOWNSTREAM_T_H_
#define DATAGRAM_DATA_DOWNSTREAM_T_H_

#include "datagram_t.h"
#include "datagram_defs.h"

#define DATAGRAM_DATADOWN_LEN_PAYLOAD_DISP    (DATAGRAM_FULL_DISP + DATAGRAM_FULL_LEN)
#define DATAGRAM_DATADOWN_LEN_PAYLOAD_LEN     8

#define DATAGRAM_DATADOWN_HOPCOUNT_DISP        (DATAGRAM_DATADOWN_LEN_PAYLOAD_DISP + DATAGRAM_DATADOWN_LEN_PAYLOAD_LEN)
#define DATAGRAM_DATADOWN_HOPCOUNT_LEN			8

#define DATAGRAM_DATADOWN_DSPATH_LENGTH_DISP	(DATAGRAM_DATADOWN_HOPCOUNT_DISP+DATAGRAM_DATADOWN_HOPCOUNT_LEN)
#define DATAGRAM_DATADOWN_DSPATH_LENGTH_LEN		8

#define DATAGRAM_DATADOWN_DSPATH_LIST_DISP      (DATAGRAM_DATADOWN_DSPATH_LENGTH_DISP+DATAGRAM_DATADOWN_DSPATH_LENGTH_LEN)
#define DATAGRAM_DATADOWN_DSPATH_LIST_LEN		32  //supponiamo di preallocare 4 byte per la lista delle interfacce

#define DATAGRAM_DATADOWN_PAYLOAD_DISP        (DATAGRAM_DATADOWN_DSPATH_LIST_DISP+DATAGRAM_DATADOWN_DSPATH_LIST_LEN)

#define DATAGRAM_DATADOWN_HEADER_LEN_BYTE	((DATAGRAM_FULL_LEN + DATAGRAM_DATADOWN_LEN_PAYLOAD_LEN + DATAGRAM_DATADOWN_HOPCOUNT_LEN + DATAGRAM_DATADOWN_DSPATH_LENGTH_LEN + DATAGRAM_DATADOWN_DSPATH_LIST_LEN )/8)
#define DATAGRAM_DATADOWN_HEADER_LEN		DATAGRAM_DATADOWN_HEADER_LEN_BYTE*8


datagram_datadown_len_payload_t get_datagram_datadown_len_payload(uint8_t* packet);
void set_datagram_datadown_len_payload(uint8_t* packet , datagram_datadown_len_payload_t payload);

datagram_datadown_hop_count_t get_datagram_datadown_hop_count(uint8_t* packet);
void set_datagram_datadown_hop_count(uint8_t* packet , datagram_datadown_hop_count_t hop_count);

datagram_datadown_ds_path_length_t get_datagram_datadown_ds_path_length(uint8_t* packet);
void set_datagram_datadown_ds_path_length(uint8_t* packet , datagram_datadown_ds_path_length_t length);

payload_t get_datagram_datadown_payload(uint8_t* packet);
void set_datagram_datadown_payload(uint8_t* packet,payload_t payload);

datagram_hop_if_t get_datagram_datadown_next_hop_if(uint8_t* packet);  //ritorna next_hop in base all'hop count settato nel pacchetto
datagram_hop_if_t get_datagram_datadown_hop_if(uint8_t* packet,int hop);  //ritorna il next dell'hop associato all'hop specificato dal parametro int hop
void set_datagram_datadown_hop_if(uint8_t* packet,int hop,datagram_hop_if_t interface);  //setta il next hop relativo all'hop specificato nel parametro int hop

void set_datagram_datadown_ds_path(uint8_t* packet,datagram_hop_if_t* interface);  //setta la lista completa degli hop

/**
 * getter e setter per il trailer
 */
payload_t get_datagram_datadown_trailer(uint8_t* packet);
void set_datagram_datadown_trailer(uint8_t* packet, uint8_t* trailer);

#endif /* DATAGRAM_DATA_DOWNSTREAM_T_H_ */
