/*
 * TL_table.c
 *
 *  Created on: 07/lug/2015
 *      Author: lorenzo
 */

#include <stdio.h>
#include <stdlib.h>
#include "TL_table.h"

void TLInitialize(TL_table *t){
	t->xSemHandle=xSemaphoreCreateRecursiveMutex();
	t->head = NULL;
	t->size = 0;
}

TL_Entry* TLFindEntryBySeqNum(TL_table *t, uint16_t seqNum){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	TL_Entry* e=t->head;

	while(e!=NULL){
		if(e->seqNum == seqNum){
			xSemaphoreGiveRecursive(t->xSemHandle);
			return e;
		}else
			e=e->next;
	}
	xSemaphoreGiveRecursive(t->xSemHandle);
	return NULL;
}

TL_Entry* TLFindEntryByTimeout(TL_table *t, uint16_t timeout){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	TL_Entry* e=t->head;

	while(e!=NULL){
		if(e->actual_time == timeout){
			xSemaphoreGiveRecursive(t->xSemHandle);
			return e;
		}else
			e=e->next;
	}
	xSemaphoreGiveRecursive(t->xSemHandle);
	return NULL;
}

void TLInsertEntry(TL_table *t, uint16_t seqNum, uint16_t time, uint8_t retry, uint16_t segment_size, uint16_t dest_address,uint8_t* packet){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	TL_Entry *e = (TL_Entry*) malloc (sizeof(TL_Entry));
	
	e->seqNum = seqNum;
	e->original_time = time;
	e->actual_time = time;
	e->retry = retry;
	e->segment_size = segment_size;
	e->dst_address = dest_address;
	e->packet = packet;
	
	e->next = t->head;
	if (t->head!=NULL)
		t->head->prev=e;
	t->head = e;
	e->prev = NULL;
	
	t->size++;

	xSemaphoreGiveRecursive(t->xSemHandle);
}



void TLDeleteAll(TL_table *t){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	while(t->head!=NULL)
		TLDeleteEntry(t,t->head);
	xSemaphoreGiveRecursive(t->xSemHandle);
} 


void TLDeleteEntry(TL_table *t, TL_Entry *e){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	if (e->prev != NULL)
		e->prev->next = e->next;
	else
		t->head = e->next;
	if (e->next != NULL)
		e->next->prev=e->prev;

	free(e->packet);
	free(e);
	t->size--;
	xSemaphoreGiveRecursive(t->xSemHandle);
}


void TLDecrementTime(TL_table *t,uint16_t dec_time){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	TL_Entry *e = t->head;

	while(e!=NULL){
		if(e->actual_time > dec_time)
			e->actual_time=e->actual_time-dec_time;
		else
			e->actual_time = 0;
		e=e->next;
	}
	xSemaphoreGiveRecursive(t->xSemHandle);
}


uint8_t TLGetSize(TL_table *t){
	uint8_t return_value = 0;
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	return_value = t->size;
	xSemaphoreGiveRecursive(t->xSemHandle);
	return return_value;
}


#ifdef TL_DEBUG
void TLPrintAll(TL_table *t){
	TL_Entry *e = t->head;
	
	while(e!=NULL){
		printf("[%d,%d,%d,%d,%d,%d,%d] - ", e->seqNum, e->original_time, e->actual_time, e->retry, e->segment_size, e->dst_address, *(e->packet));
		e=e->next;
	}
	printf("NIL\n");
}
#endif

