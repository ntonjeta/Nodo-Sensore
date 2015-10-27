/*
 * segment_defs.h
 *
 *  Created on: 07/lug/2015
 *      Author: imma
 */

#ifndef SEGMENT_DEFS_H_
#define SEGMENT_DEFS_H_

#include <stdint.h>
#include "datagram_defs.h"				//contiene le set e get di base

#define MAX_SEQUENCE_NUMBER 4094 		// 12 bit per Sequence Number
#define BEST_EFFORT_SEQ_NUM 4095

typedef enum {
	SEGMENT_ASYNCHRONOUS	= 0, 		// asincrono - garantito
	SEGMENT_REAL_TIME		= 1, 		// garantito
	SEGMENT_BEST_EFFORT		= 2 		// non garantito
} segment_typeService_t;

typedef uint16_t segment_sequenceNumber_t;
typedef uint8_t segment_congFlag_t;
typedef uint8_t segment_ackFlag_t;


#endif /* SEGMENT_DEFS_H_ */
