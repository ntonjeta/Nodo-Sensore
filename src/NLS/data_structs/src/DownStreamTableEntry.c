/*
 * DownStreamTableEntry.c
 *
 *  Created on: 04/lug/2015
 *      Author: Ciro
 */


#include "DownstreamTableEntry.h"
#include <stdlib.h>

void DownStreamEntryCreate(DownStreamTableEntry* entry, datagram_if_id_t* path, uint8_t length, uint8_t penality){
	entry->path = (datagram_if_id_t*)malloc(length*sizeof(datagram_if_id_t));
	memcpy(entry->path, path, length*sizeof(datagram_if_id_t));
	entry->length = length;
	entry->penality = penality;

}

void DownStreamEntryDestroy(DownStreamTableEntry* entry){
	free(entry->path);
}

void DownstreamEntrySetPath(DownStreamTableEntry* entry, datagram_if_id_t* path, uint8_t length){
	entry->length = length;
	free(entry->path);
	entry->path = (datagram_if_id_t*)malloc(length*sizeof(datagram_if_id_t));
}

void DownStreamEntrySetPenality(DownStreamTableEntry* entry, uint8_t penality){
	entry->penality = penality;
}

datagram_if_id_t* DownstreamEntryGetPath(DownStreamTableEntry* entry){
	return entry->path;
}

uint8_t DownStreamEntryGetLength(DownStreamTableEntry* entry){
	return entry->length;
}

uint8_t DownstreamEntryGetPenality(DownStreamTableEntry* entry){
	return entry->penality;
}
