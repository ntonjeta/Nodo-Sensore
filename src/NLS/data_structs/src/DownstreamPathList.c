
#include "DownstreamPathList.h"
#include <strings.h>
#include <stdlib.h>

void downStreamPathPenalizes(DownStreamPath* dowStreamPath){
	dowStreamPath->penality = dowStreamPath->penality + 1;
}

void downStreamPathInitialize(DownStreamPath* downStreamPath, datagram_if_id_t* path, uint8_t length, uint8_t penality){
	downStreamPath->path = (datagram_if_id_t*)malloc(length*sizeof(datagram_if_id_t));
	memcpy(downStreamPath->path, path, length);
	downStreamPath->length = length;
	downStreamPath->penality = penality;
	downStreamPath->next = NULL;
	downStreamPath->previous = NULL;
}

void downStreamPathDestroy(DownStreamPath* downStreamPath){
	free(downStreamPath->path);
	downStreamPath->path = NULL;
	downStreamPath->length = 0;
	downStreamPath->penality = 0;
	downStreamPath->next = NULL;
	downStreamPath->previous = NULL;
}


void downStreamPathListInitialize(DownStreamPathList* list, datagram_address_t destinationAddress){
	list->destinationAddress = destinationAddress;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

void downStreamPathListDestroy(DownStreamPathList* list){
	while(!downStreamPathListEmpty(list))
		downStreamPathListDelete(list, list->head);
}

void downStreamPathListInsert(DownStreamPathList* list, datagram_if_id_t* path, uint8_t length, uint8_t penality){
	DownStreamPath* dsPath = (DownStreamPath*)malloc(sizeof(DownStreamPath));
	downStreamPathInitialize(dsPath, path, length, penality);
	dsPath->next = list->head;
	if (list->head != NULL)
		list->head->previous = dsPath;
	list->head = dsPath;
	dsPath->previous = NULL;
	list->tail = dsPath;
	list->size++;
}

void downStreamPathListDelete(DownStreamPathList* list, DownStreamPath* downStreamPath){
	if (downStreamPath->previous != NULL)
		downStreamPath->previous->next = downStreamPath->next;
	else
		list->head = downStreamPath->next;
	if (downStreamPath->next != NULL)
		downStreamPath->next->previous = downStreamPath->previous;
	downStreamPathDestroy(downStreamPath);
	free(downStreamPath);
	list->size--;
	if (list->size == 0)
		list->tail = NULL;
}

void downStreamPathListSetDestinationAddress(DownStreamPathList* list, datagram_address_t address){
	list->destinationAddress = address;
}

DownStreamPath* downStreamPathListGetBestPath(DownStreamPathList* list){
	DownStreamPath* it = list->head;
	DownStreamPath* bestPath = list->head;
	int bestCost = 0;
	if (!downStreamPathListEmpty(list))
		bestCost = list->head->length + (list->head->penality)*MAX_HOP_COUNT;
	while (it != NULL){
		int it_cost = it->length + (it->penality)*MAX_HOP_COUNT;
		if (it_cost < bestCost){
			bestCost = it_cost;
			bestPath = it;
		}
		it = it->next;
	}
	return bestPath;
}

int downStreamPathListEmpty(DownStreamPathList* list){
	return list->size == 0;
}
