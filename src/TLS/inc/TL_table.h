/*
 * TL_table.h
 *
 *  Created on: 07/lug/2015
 *      Author: lorenzo
 */

#ifndef TL_TABLE_H_
#define TL_TABLE_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

//#define TL_DEBUG

typedef struct TL_node{
	struct TL_node *prev;
	uint16_t seqNum;
	uint16_t original_time;
	uint16_t actual_time;
	uint8_t retry;
	uint16_t segment_size;
	uint16_t dst_address;
	uint8_t* packet;
	struct TL_node *next;
}TL_Entry;


typedef struct TLtable{
	uint8_t size;
	TL_Entry *head;
	SemaphoreHandle_t xSemHandle;
}TL_table;


void TLInitialize(TL_table*);
void TLInsertEntry(TL_table*, uint16_t, uint16_t, uint8_t, uint16_t, uint16_t,uint8_t*);
uint8_t TLGetSize(TL_table*);
TL_Entry* TLFindEntryBySeqNum(TL_table*, uint16_t);
TL_Entry* TLFindEntryByTimeout(TL_table*, uint16_t);
void TLDecrementTime(TL_table*,uint16_t);
void TLDeleteAll(TL_table*);
void TLDeleteEntry(TL_table*, TL_Entry*);

#ifdef TL_DEBUG
void TLPrintAll(TL_table*);
#endif

#endif
