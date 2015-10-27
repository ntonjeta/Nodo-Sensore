/*
 * DownstreamTableEntryList.h
 *
 *  Created on: 05/lug/2015
 *      Author: Ciro
 */

#ifndef DOWNSTREAMPATHLIST_H_
#define DOWNSTREAMPATHLIST_H_

#define MAX_HOP_COUNT 8 //TODO: Eliminare

#include <stdint.h>
#include <stddef.h>
#include "datagram_t.h"




typedef struct DSPath{
	datagram_if_id_t* path;
	uint8_t length;
	uint8_t penality;

	struct DSPath* next;
	struct DSPath* previous;
} DownStreamPath;

typedef struct{
	datagram_address_t destinationAddress;
	DownStreamPath* head;
	DownStreamPath* tail;
	int size;
} DownStreamPathList;

void downStreamPathPenalizes(DownStreamPath* dowStreamPath);


void downStreamPathListInitialize(DownStreamPathList* list, datagram_address_t destinationAddress);
void downStreamPathListDestroy(DownStreamPathList* list);
void downStreamPathListInsert(DownStreamPathList* list, datagram_if_id_t* path, uint8_t length, uint8_t penality);

void downStreamPathListDelete(DownStreamPathList* list, DownStreamPath* downStreamPath);//TODO: Eliminare per path

void downStreamPathListSetDestinationAddress(DownStreamPathList* list, datagram_address_t address);

DownStreamPath* downStreamPathListGetBestPath(DownStreamPathList* list);
int downStreamPathListEmpty(DownStreamPathList* list);

#endif /* DOWNSTREAMPATHLIST_H_ */
