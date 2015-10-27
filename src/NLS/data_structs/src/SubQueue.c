/*
 * Queue.c
 *
 *  Created on: 01/lug/2015
 *      Author: Ciro
 */


#include "SubQueue.h"
#include <stddef.h>
#include <stdlib.h>


void queueUpdateAverageSize(struct Queue* queue){
	queue->avgSize = 0.5*queue->avgSize + 0.5*queue->size;
}

void queueInitialize(struct Queue* queue, int minSize, int maxSize){
	queue->head = NULL;
	queue->tail= NULL;
	queue->size = 0;
	queue->avgSize = 0;
	queue->minSize = minSize;
	queue->maxSize = maxSize;
	srand((int)queue);
}


void queueDestroy(struct Queue* queue){
	while(!queueEmpty(queue))
		queueDequeue(queue);
}

int queueEnqueueOrDiscard(struct Queue* queue, Value* value){
	if (queue->avgSize > queue->maxSize){
		queueUpdateAverageSize(queue);
		return 0;
	}else if (queue->avgSize > queue->minSize){
		float p = (queue->avgSize - queue->minSize)/(queue->maxSize - queue->minSize);
		float r = rand()/(float)RAND_MAX;
		if (r < p){
			queueUpdateAverageSize(queue);
			return 0;
		}
	}

	queueEnqueue(queue, value);
	queueUpdateAverageSize(queue);
	return 1;
}


void queueEnqueue(struct Queue* queue, Value* value){
	struct QueueNode* new_node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	new_node->value = value;
	new_node->next_node = queue->tail;
	new_node->previous_node = NULL;
	if (!queueEmpty(queue))
		new_node->next_node->previous_node = new_node;
	else
		queue->head = new_node;
	queue->tail = new_node;
	queue->size++;
	queueUpdateAverageSize(queue);
}


Value* queueDequeue(struct Queue* queue){
	if (queueEmpty(queue))
		return NULL;
	else{
		struct QueueNode* old_head = queue->head;
		Value* return_value = queue->head->value;

		if (old_head->previous_node != NULL){
			old_head->previous_node->next_node = NULL;
		}

		queue->head = old_head->previous_node;
		if (queue->size == 1)
			queue->tail = NULL;

		free(old_head);
		queue->size--;
		return return_value;
	}
}

Value* queueFront(struct Queue* queue){
	if (queueEmpty(queue))
		return NULL;
	return queue->head->value;
}


int queueEmpty(struct Queue* queue){
	return queue->size == 0;
}


int queueFull(struct Queue* queue){
	return 0;
}


int queueSize(struct Queue* queue){
	return queue->size;
}

void queueSetMinimumAverageSize(struct Queue* queue, int minSize){
	queue->minSize = minSize;
}

void queueSetMaximumAverageSize(struct Queue* queue, int maxSize){
	queue->maxSize = maxSize;
}


#ifdef NLS_TRACE

#include <stdio.h>

void queuePrint(struct Queue *queue){
	struct QueueNode *qn = queue->head;
	Value *v=NULL;

	while(qn!=NULL){
		v = qn->value;
		//printf("[%d] - ", *v);
		qn = qn->previous_node;
	}
	printf("NIL\n\r");
}

#endif


