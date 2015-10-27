/*
 * PriorityQueue.c
 *
 *  Created on: 01/lug/2015
 *      Author: Ciro
 */
//TODO Attenzione!! Utilizzo del while per l'attesa sul semaforo! Modificare solo se porta problemi!!!
//TODO !!!!!!!!!!!!!!!!!!!!!!!!NON SINCRONIZZATO!!!!!!!!!!!!!!!!!!!

#include "PriorityQueue.h"
#include <stdlib.h>
#include "task.h"
#include <stm32f4xx_hal.h>
#include "stm32f4_discovery.h"

#define SCHEDULER_MULTIPLIER 2

int scheduleNextSubQueue(struct PriorityQueue* queue);

int scheduleNextSubQueue(struct PriorityQueue* queue){
	int nextSubQueue;
	if ((queue->currentPriorityCount != 0) && !priorityQueueSubQueueEmpty(queue, queue->currentPriority)){
		nextSubQueue = queue->currentPriority;
		queue->currentPriorityCount--;
	}else{
		do{
			if (queue->currentPriority == 0)
				queue->currentPriority = queue->priorities - 1;
			else
				queue->currentPriority--;
		}while (priorityQueueSubQueueEmpty(queue, queue->currentPriority));
		queue->currentPriorityCount = (queue->currentPriority + 1) * SCHEDULER_MULTIPLIER - 1;
		nextSubQueue = queue->currentPriority;
	}
	return nextSubQueue;
}

void priorityQueueInitialize(struct PriorityQueue* queue, int priorities, int minSize){
	int i;
	queue->xSemHandle=xSemaphoreCreateRecursiveMutex();
	//TODO Check if xSemHandle is NULL
	queue->queueList = (struct Queue*)malloc(priorities*sizeof(struct Queue));
	queue->priorities = priorities;
	queue->size = 0;
	queue->currentPriority = priorities - 1;							//Coda oggetto della successiva schedulazione
	queue->currentPriorityCount = priorities * SCHEDULER_MULTIPLIER;	//Numero di schedulazioni da fare sulla coda corrente
	for (i = 0; i < priorities; i++){
		queueInitialize(&(queue->queueList[i]), minSize, (priorities - i)*minSize + minSize);
	}
}

void priorityQueueDestroy(struct PriorityQueue* queue){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t) 0)!=pdTRUE){}

	int i;
	for (i = 0; i < queue->priorities; i++)
		queueDestroy(&(queue->queueList[i]));
	free(queue->queueList);
	xSemaphoreGiveRecursive(queue->xSemHandle);
	vSemaphoreDelete(queue->xSemHandle);	//TODO: ZUPPA
}

void priorityQueueSetSubQueueSize(struct PriorityQueue* queue, int priority, int minSize, int maxSize){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t)0) != pdTRUE){}
	queueSetMinimumAverageSize(&(queue->queueList[priority]), minSize);
	queueSetMaximumAverageSize(&(queue->queueList[priority]), maxSize);
	xSemaphoreGiveRecursive(queue->xSemHandle);
}

void priorityQueueEnqueue(struct PriorityQueue* queue, int priority, Value* value){

	while(xSemaphoreTakeRecursive(queue->xSemHandle,(portTickType)0) != pdTRUE){}   //attende fin quando il semaforo non si "libera"

	queueEnqueue(&(queue->queueList[priority]), value);
	queue->size++;
	xSemaphoreGiveRecursive(queue->xSemHandle);

}

void priorityQueueEnqueueOrDiscard(struct PriorityQueue* queue, int priority, Value* value){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(portTickType)0) != pdTRUE){}

	if (queueEnqueueOrDiscard(&(queue->queueList[priority]), value) != 0)
		queue->size++;
	xSemaphoreGiveRecursive(queue->xSemHandle);
}

Value* priorityQueueDequeue(struct PriorityQueue* queue){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(portTickType)0) != pdTRUE){}
	if (queue->size==0){
		xSemaphoreGiveRecursive(queue->xSemHandle);
		return NULL;
	}
	else {
		Value* value = queueDequeue(&(queue->queueList[scheduleNextSubQueue(queue)]));
		queue->size--;
		xSemaphoreGiveRecursive(queue->xSemHandle);
		return value;
	}
}

int priorityQueueEmpty(struct PriorityQueue* queue){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(portTickType)0) != pdTRUE){}

	if (queue->size==0){
		xSemaphoreGiveRecursive(queue->xSemHandle);
		return 1;
	}else{
		xSemaphoreGiveRecursive(queue->xSemHandle);
		return 0;
	}

}

int priorityQueueFull(struct PriorityQueue* queue){
	return 0;
}

int priorityQueueSize(struct PriorityQueue* queue){

	int res;
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(portTickType)0) != pdTRUE){}
	res = queue->size;
	xSemaphoreGiveRecursive(queue->xSemHandle);
	return res;

}

int priorityQueueSubQueueSize(struct PriorityQueue* queue, int priority){
	int res;
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(portTickType)0) != pdTRUE){}
	res=queueSize(&(queue->queueList[priority]));
	xSemaphoreGiveRecursive(queue->xSemHandle);
	return res;
}

int priorityQueueSubQueueEmpty(struct PriorityQueue* queue, int priority){
	int res;
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(portTickType)0) != pdTRUE){}
	res = (priorityQueueSubQueueSize(queue, priority) == 0);
	xSemaphoreGiveRecursive(queue->xSemHandle);
	return res;
}

