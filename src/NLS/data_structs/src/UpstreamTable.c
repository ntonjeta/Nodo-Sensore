//Author: Lorenzo

//UpstreamTable functions

#include <stdio.h>
#include <stdlib.h>
#include "UpstreamTable.h"
#include "NLS_globals.h"
#include "network_config.h"


void UTInitialize(UpstreamTable *t){
	t->xSemHandle=xSemaphoreCreateRecursiveMutex();
	t->head = NULL;
	t->size = 0;
	t->mainLink = NULL;
}


uint8_t UTInsertEntry(UpstreamTable *t, uint8_t ifID, uint8_t hopCount , uint16_t link_addr){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}

	Entry *e = (Entry*) malloc (sizeof(Entry));
		
	e->ifID = ifID;
	e->hopCount = hopCount;
	e->address = link_addr;
	e->invalid = 0;
	
	e->next = t->head;
	if (t->head!=NULL)
		t->head->prev=e;
	t->head = e;
	e->prev = NULL;
	
	t->size++;

	#ifdef NLS_TRACE

	printf("aggiunta all'upstream table interfaccia %i\n\r" ,e->ifID );

	#endif
	xSemaphoreGiveRecursive(t->xSemHandle);
	return 0;
}



uint8_t UTGetMainLink(UpstreamTable *t){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	Entry *e;
	uint8_t min = 255, i=0;
	
	if (t->head == NULL){										//se non esiste alcuna entry nella tabella...ritorna errore
		xSemaphoreGiveRecursive(t->xSemHandle);
		return UPSTREAM_TABLE_IS_EMPTY;			
	}
	if (t->mainLink==NULL){
		while (t->mainLink==NULL && i<MAX_UPSTREAM_TABLE_PENALIZES){
			e = t->head;
			while (e != NULL){
				if (e->hopCount < min && e->invalid==i){
					min = e->hopCount;
					t->mainLink = e;
				}
				e = e->next;
			}
			i++;
		}
	}
	xSemaphoreGiveRecursive(t->xSemHandle);
	return t->mainLink->ifID;
}


uint8_t UTSwapMainLink(UpstreamTable *t){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}

	if(t->head == NULL){
		xSemaphoreGiveRecursive(t->xSemHandle);
		return UPSTREAM_TABLE_IS_EMPTY;
	}

	if (t->mainLink == NULL){
		xSemaphoreGiveRecursive(t->xSemHandle);
		return MAIN_LINK_DOES_NOT_EXIST;
	}else{
		t->mainLink->invalid ++;							//invalida il vecchio padre
		if (t->mainLink->invalid == MAX_UPSTREAM_TABLE_PENALIZES)
			UTDeleteEntry(t, t->mainLink);
		t->mainLink = NULL;									//cancella il vecchio padre come main link
		xSemaphoreGiveRecursive(t->xSemHandle);
		return UTGetMainLink(t);
	}
}


void UTDeleteAll(UpstreamTable *t){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	while(t->head!=NULL)
		UTDeleteEntry(t,t->head);
	xSemaphoreGiveRecursive(t->xSemHandle);
} 


void UTDeleteEntry(UpstreamTable *t, Entry *e){
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	if (e->prev != NULL)
		e->prev->next = e->next;
	else
		t->head = e->next;
	if (e->next != NULL)
		e->next->prev=e->prev;
			
	free(e);
	t->size--;
	xSemaphoreGiveRecursive(t->xSemHandle);
}


uint8_t UTGetSize(UpstreamTable *t){
	uint8_t return_value;
	while(xSemaphoreTakeRecursive(t->xSemHandle,(TickType_t) 0)!=pdTRUE){}
	return_value = t->size;
	xSemaphoreGiveRecursive(t->xSemHandle);
	return return_value;
}



#ifdef NLS_TRACE
void UTPrintAll(UpstreamTable *t){
	Entry *e = t->head;
	
	while(e!=NULL){
		printf("[%d,%d,%d] - ", e->ifID, e->hopCount, e->invalid);
		e=e->next;
	}
	printf("NIL\n\r");
}
#endif

