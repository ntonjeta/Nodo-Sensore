/*
 * datagram_builders_fork.h
 *
 *  Created on: 05/lug/2015
 *      Author: gennaro
 */

#ifndef DATAGRAM_BUILDERS_FORK_H_
#define DATAGRAM_BUILDERS_FORK_H_

#include <stdint.h>

#include "datagram_defs.h"

typedef struct
{
	uint8_t* secret;
	uint8_t* trailer;
}PACK_typedef;

uint8_t* build_PACK(PACK_typedef pack , int* datagram_length);
void print_PACK (uint8_t* packet);

uint8_t* getTrailer(uint8_t* packet);
void setTrailer(uint8_t* packet , uint8_t* trailer);

uint8_t* build_PREP_from_PREQ(uint8_t* packet , int* datagram_length , uint8_t* payload , uint8_t* trailer);

#endif /* DATAGRAM_BUILDERS_FORK_H_ */
