/*
 * datagram_builders.h
 *
 *  Created on: 02/lug/2015
 *      Author: gennaro
 */

#ifndef DATAGRAM_BUILDERS_H_
#define DATAGRAM_BUILDERS_H_

#include "NLS_globals.h"
#include "datagram_builders_fork.h"

#define NO_SRC_IF 0xff



/**
 *  dsData_typedef: struttura dati che astrae un pacchetto di tipo dati downstream
 *  campi non modificabili
 *
 *  	TYPE:			DATA_DOWN
 *
 *
 *  gli altri campi sono inseriti dalla sorgente
 */
typedef struct
{
	datagram_address_t address;
	datagram_qos_t qos;
	datagram_datadown_len_payload_t payload_length;
	uint8_t* payload;
	datagram_datadown_ds_path_length_t ds_path_length;
	datagram_hop_if_t* ds_path;
	uint8_t* trailer;

}dsData_typedef;

/**
 *  costruisce un pacchetto di downstream. usata solo dalla sorgente del pacchetto
 */
uint8_t* build_dsData (dsData_typedef dsData , int* datagram_length);

/**
 *  modifica un pacchetto di downstream prima di essere inoltrato. usata dai nodi intermedi
 *
 */
uint8_t* modify_dsData (uint8_t* dsData);

/**
 *  stampa formattata di un pacchetto downstream
 */
void print_dsData (uint8_t* packet);
//-----------------------------------------------------------------------------------

/**
 *  usData_typedef: struttura dati che astrae un pacchetto di tipo dati upstream
 *  campi non modificabili
 *
 *  	TYPE:			DATA_UP
 *  	ADDRESS:		MY_ADDRESS
 *
 *
 *  gli altri campi sono inseriti dalla sorgente. i pacchetti upstream non vengono modificati in inoltro
 */
typedef struct
{

	datagram_dataup_len_payload_t payload_length;
	datagram_qos_t qos;
	uint8_t* payload;
	uint8_t* trailer;


}usData_typedef;

uint8_t* build_usData (usData_typedef usData , int* datagram_length);
void print_usData (uint8_t* packet);

//-----------------------------------------------------------------------------------

/**
 * 	PREQ_typedef: astrazione di un pacchetto tipo PREQ. Tale pacchetto è costruito come
 *  un comune pacchetto upstream. L'unica informazione modificabile è la challenge,
 *  inserita come payload in un pacchetto upstream. la lunghezza del payload è
 *  nota
 */
typedef struct
{
	challenge_t challenge;

}PREQ_typedef;

/**
 * costruisce un pacchetto PREQ. chiama la build_usData assegnando la challenge come payload e relativa lunghezza
 * Sovrascrive tipo e qos
 */
uint8_t* build_PREQ (PREQ_typedef preq , int* datagram_length);
void print_PREQ (uint8_t* preq);

//-----------------------------------------------------------------------------------

typedef struct
{
	uint8_t* challenge;

}PFWD_typedef;

uint8_t* build_PFWD (PFWD_typedef pfwd , datagram_address_t source_address, int* datagram_lenght);
void modify_PFWD (uint8_t* pfwd , datagram_hop_if_t hop);

void print_PFWD (uint8_t* pfwd);

//-----------------------------------------------------------------------------------

/**
 * PREP_typedef: costruisce un messaggio di PREP
 *
 *	gli unici campi inseribili sono l'indirizzo (destinazione), payload e relativa lunghezza
 *	è costruito come comune messaggio downstream con tipo e qos fissati
 */
//typedef struct
//{
//
//	payload_t payload;
//	datagram_datadown_len_payload_t payload_len;
//	datagram_address_t address;
//
//}PREP_typedef;

typedef dsData_typedef PREP_typedef;

uint8_t* build_PREP (PREP_typedef prep , int* datagram_lenght);
uint8_t* build_PREP_from_PFWD(uint8_t* packet,  datagram_hop_if_t source_if , int* length , uint8_t* secret , uint8_t* trailer);

void modify_PREP (uint8_t* prep);
void print_PREP (uint8_t* prep);
//-----------------------------------------------------------------------------------

uint8_t* build_PFWD_from_PREQ (uint8_t* preq , datagram_hop_if_t first_hop , int* datagram_length);

/**
 *  stampa byte per byte un payload
 */
void print_payload(uint8_t const* payload , int payload_length , int exadecimal);


#endif /* DATAGRAM_BUILDERS_H_ */
