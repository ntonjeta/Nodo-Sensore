/*
 * PriorityQueue.h
 *
 *  Created on: 01/lug/2015
 *      Author: Ciro
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include "SubQueue.h"
#include "FreeRTOS.h"
#include "semphr.h"

struct PriorityQueue {
	struct Queue* queueList;
	int priorities;
	int size;
	SemaphoreHandle_t xSemHandle;
	int currentPriority;
	int currentPriorityCount;
};

void priorityQueueInitialize(struct PriorityQueue*, int, int);
void priorityQueueDestroy(struct PriorityQueue*);
void priorityQueueEnqueue(struct PriorityQueue*, int, Value*);
void priorityQueueEnqueueOrDiscard(struct PriorityQueue*, int, Value*);
Value* priorityQueueDequeue(struct PriorityQueue*);
Value* priorityQueueDequeueOnly(struct PriorityQueue* , int);
void priorityQueueSetSubQueueSize(struct PriorityQueue*, int, int, int);

int priorityQueueEmpty(struct PriorityQueue*);
int priorityQueueFull(struct PriorityQueue*);
int priorityQueueSize(struct PriorityQueue*);
int priorityQueueSubQueueSize(struct PriorityQueue*, int);
int priorityQueueSubQueueEmpty(struct PriorityQueue*, int);

#endif /* PRIORITYQUEUE_H_ */
