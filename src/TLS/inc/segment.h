/*
 * segment.h
 *
 *  Created on: 07/lug/2015
 *      Author: imma
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "segment_defs.h"

// **** Convenzioni
// ****
// * DISP: displacement - spiazzamento del campo
// * LEN: length	- dimensione in bit del campo

#define SEQUENCE_NUMBER_DISP 0
#define SEQUENCE_NUMBER_LEN 12

#define SERVICE_TYPE_DISP (SEQUENCE_NUMBER_DISP + SEQUENCE_NUMBER_LEN)
#define SERVICE_TYPE_LEN 2

#define CONG_FLAG_DISP (SERVICE_TYPE_DISP + SERVICE_TYPE_LEN)
#define CONG_FLAG_LEN 1

#define ACK_FLAG_DISP (CONG_FLAG_DISP+CONG_FLAG_LEN)
#define ACK_FLAG_LEN 1

#define SEGMENT_DATA_DISP (ACK_FLAG_DISP + ACK_FLAG_LEN)


/*GET e SET specifiche*/

// TYPE SERVICE
segment_typeService_t get_segment_typeService(uint8_t* packet);
void set_segment_typeService(uint8_t* packet, segment_typeService_t typeService);

// SEQUENCE NUMBER
segment_sequenceNumber_t get_segment_sequenceNumber(uint8_t* packet);
void set_segment_sequenceNumber(uint8_t* packet, segment_sequenceNumber_t sequenceNumber);


// CONG FLAG
segment_congFlag_t get_segment_congFlag(uint8_t* packet);
void set_segment_congFlag(uint8_t* packet, segment_congFlag_t congFlag);

// ACK FLAG
segment_ackFlag_t get_segment_ackFlag(uint8_t* packet);
void set_segment_ackFlag(uint8_t* packet, segment_ackFlag_t ackFlag);

// PAYLOAD
payload_t get_segment_payload(uint8_t* packet,int bytelen);
void set_segment_payload(uint8_t* packet,payload_t payload,int bytelen);

#endif /* SEGMENT_H_ */
