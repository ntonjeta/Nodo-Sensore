/*
 * segment_builder.h
 *
 *  Created on: 07/lug/2015
 *      Author: imma
 */

#ifndef SEGMENT_BUILDER_H_
#define SEGMENT_BUILDER_H_

#include "segment.h"

//#define TL_DEBUG
#define TRANSPORT_HEADER_SIZE	2 //byte


typedef struct {
	segment_typeService_t service_type;
	segment_sequenceNumber_t sequence_number;
	segment_congFlag_t cong_flag;
	segment_ackFlag_t ack_flag;

	payload_t payload;
} data_typedef;



uint8_t* build_segment (data_typedef data ,int segment_length);
segment_sequenceNumber_t generateSequenceNumber();

#ifdef TL_DEBUG
void print_segment(uint8_t* packet, int segment_length);
#endif

#endif /* SEGMENT_BUILDER_H_ */
