/*
 * Queue.h
 *
 *  Created on: 01/lug/2015
 *      Author: Ciro
 */

#ifndef SUBQUEUE_H_
#define SUBQUEUE_H_


#include "stdint.h"
#include "datagram_info.h"

typedef	datagram_info Value;

struct Queue{
	struct QueueNode* head;		//Puntatore alla testa della coda
	struct QueueNode* tail;		//Puntatore alla fine della coda
	int size;					//Numero di elementi in coda
	float avgSize;
	int minSize;
	int maxSize;
};

struct QueueNode{
	Value* value;
	struct QueueNode* next_node;
	struct QueueNode* previous_node;
};

void queueInitialize(struct Queue*, int , int);
void queueDestroy(struct Queue*);
void queueEnqueue(struct Queue*, Value*);
int queueEnqueueOrDiscard(struct Queue*, Value*);
Value* queueDequeue(struct Queue*);
Value* queueFront(struct Queue*);

int queueEmpty(struct Queue*);
int queueFull(struct Queue*);
int queueSize(struct Queue*);

void queueSetMinimumAverageSize(struct Queue*, int);	//Da testare
void queueSetMaximumAverageSize(struct Queue*, int);	//Da testare

#ifdef NLS_TRACE
void queuePrint(struct Queue*);
#endif

#endif /* SUBQUEUE_H_ */
