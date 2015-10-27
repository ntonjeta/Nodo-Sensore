//Author: Lorenzo
//UpstreamTable header

#ifndef _UPSTREAM_TABLE_
#define _UPSTREAM_TABLE_

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

#define MAIN_LINK_DOES_NOT_EXIST			254
#define UPSTREAM_TABLE_IS_EMPTY				255

typedef struct node{
	struct node *prev;
	uint8_t ifID;
	uint16_t address;
	uint8_t hopCount;
	uint8_t invalid;
	struct node *next;
}Entry;

typedef struct table{
	uint8_t size;
	struct node *head;
	struct node *mainLink;
	SemaphoreHandle_t xSemHandle;
}UpstreamTable;

void UTInitialize(UpstreamTable*);
uint8_t UTInsertEntry(UpstreamTable*, uint8_t, uint8_t , uint16_t);
uint8_t UTGetMainLink(UpstreamTable*);
uint8_t UTSwapMainLink(UpstreamTable*);
uint8_t UTGetSize(UpstreamTable*);
void UTDeleteAll(UpstreamTable*);
void UTDeleteEntry(UpstreamTable*, Entry*);


#ifdef NLS_TRACE
void UTPrintAll(UpstreamTable*);
#endif

#endif
