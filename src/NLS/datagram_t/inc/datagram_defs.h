/*
 * datagram_defs.h
 *
 *  Created on: 30/giu/2015
 *      Author: Ciro
 */

#ifndef DATAGRAM_DEFS_H_
#define DATAGRAM_DEFS_H_

#include <stdint.h>
#include <string.h>
#include <math.h>
#include "network_config.h"
//#include "cal_ver1.h"

#define PADDING 1

typedef uint16_t datagram_address_t;
typedef uint8_t datagram_hop_if_t;

//typedef uint16_t datagram_length_t;
//typedef uint16_t* datagram_payload_t;
//typedef uint8_t datagram_dspath_elem_t;

typedef uint8_t datagram_if_id_t;

//CONVENZIONI MACRO
// SPIAZZAMENTO: CAMPO_DISP
// LUNGHEZZA: CAMPO_LEN
// GETTER: get_sottopacchetto_campo ()
// SETTER: set_sottopacchetto_campo ()




typedef enum {
	DATA_UP		= 0,
	DATA_DOWN	= 1,
	BSRP_PREQ 	= 2,
	BSRP_PREP 	= 3,
	BSRP_PFWD 	= 4,
	BSRP_PACK	= 5

} datagram_type_t;


typedef enum {
	CONTROL		= 3,
	REAL_TIME	= 2,
	BEST_EFFORT	= 1,
	ASYNC		= 0

} datagram_qos_t;

typedef uint8_t datagram_dataup_len_payload_t;

typedef uint8_t datagram_datadown_len_payload_t;
typedef uint8_t datagram_datadown_hop_count_t;
typedef uint8_t datagram_datadown_ds_path_length_t;

typedef uint8_t datagram_pfwd_ds_path_length_t;
typedef uint8_t datagram_pfwd_hop_list_length_t;
typedef challenge_t datagram_pfwd_challenge_t;

typedef uint8_t* payload_t;

/**
 * restituisce il valore di un generico campo
 * parametri: pacchetto , spiazzamento , lunghezza
 */
int getField(uint8_t* packet, int disp, int len);

/**
 * inserisce un valore in un generico campo
 * parametri: pacchetto , spiazzamento , lunghezza , valore
 */
void setField(uint8_t* packet, int disp, int len, int val);

/**
 * calcola la lunghezza totale di un datagramma
 */
int getDatagramLength (uint8_t*);

payload_t getPayload(uint8_t* packet,int disp,int nbyte);
void setPayload(uint8_t* packet , int disp,int nbyte , payload_t payload);





#endif /* DATAGRAM_DEFS_H_ */
