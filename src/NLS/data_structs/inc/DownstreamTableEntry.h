/*
 * DownstreamTableEntry.h
 *
 *  Created on: 04/lug/2015
 *      Author: Ciro
 */

#ifndef INC_DOWNSTREAMTABLEENTRY_H_
#define INC_DOWNSTREAMTABLEENTRY_H_

#include "datagram_defs.h"

typedef struct DSTEntry {
	datagram_if_id_t* path;
	uint8_t length;
	uint8_t penality;
} DownStreamTableEntry;


void DownStreamEntryCreate(DownStreamTableEntry* entry, datagram_if_id_t* path, uint8_t length, uint8_t penality);
void DownStreamEntryDestroy(DownStreamTableEntry* entry);

void DownstreamEntrySetPath(DownStreamTableEntry* entry, datagram_if_id_t* path, uint8_t length);
void DownStreamEntrySetPenality(DownStreamTableEntry* entry, uint8_t penality);

datagram_if_id_t* DownstreamEntryGetPath(DownStreamTableEntry* entry);
uint8_t DownStreamEntryGetLength(DownStreamTableEntry* entry);
uint8_t DownstreamEntryGetPenality(DownStreamTableEntry* entry);

#endif /* INC_DOWNSTREAMTABLEENTRY_H_ */
