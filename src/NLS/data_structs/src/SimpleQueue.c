#include "SimpleQueue.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


void simpleQueueInitialize(struct SimpleQueue* queue){
	queue->xSemHandle=xSemaphoreCreateRecursiveMutex();
	  //TODO Check if xSemHandle is NULL
	queue->head = NULL;
	queue->tail= NULL;
	queue->size = 0;

}


void simpleQueueDestroy(struct SimpleQueue* queue){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t) 0)!=pdTRUE){}

	while(!simpleQueueEmpty(queue))
		simpleQueueDequeue(queue);
	 xSemaphoreGiveRecursive(queue->xSemHandle);
	 vSemaphoreDelete(queue->xSemHandle);	//TODO: ZUPPA
}

void simpleQueueEnqueue(struct SimpleQueue* queue, SimpleQueueValue* value){
//	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t)0) != pdTRUE){}
	struct SimpleQueueNode* new_node = (struct SimpleQueueNode*)malloc(sizeof(struct SimpleQueueNode));
	new_node->value = value;
	new_node->next_node = queue->tail;
	new_node->previous_node = NULL;
	if (!simpleQueueEmpty(queue))
		new_node->next_node->previous_node = new_node;
	else
		queue->head = new_node;
	queue->tail = new_node;
	queue->size++;
//	xSemaphoreGiveRecursive(queue->xSemHandle);	//TODO: Decommentare
}


SimpleQueueValue* simpleQueueDequeue(struct SimpleQueue* queue){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t)0) != pdTRUE){}
	SimpleQueueValue* return_Value = NULL;
	if (simpleQueueEmpty(queue))
		return_Value = NULL;
	else{
		struct SimpleQueueNode* old_head = queue->head;
		return_Value = queue->head->value;

		if (old_head->previous_node != NULL){
			old_head->previous_node->next_node = NULL;
		}

		queue->head = old_head->previous_node;
		if (queue->size == 1)
			queue->tail = NULL;

		free(old_head);
		queue->size--;
	}
	xSemaphoreGiveRecursive(queue->xSemHandle);
	 return return_Value;
}




SimpleQueueValue* simpleQueueFront(struct SimpleQueue* queue){
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t)0) != pdTRUE){}
	SimpleQueueValue* return_Value = NULL;
	if (simpleQueueEmpty(queue))
		return_Value =  NULL;
	else
		return_Value =  queue->head->value;
	xSemaphoreGiveRecursive(queue->xSemHandle);
	 return return_Value;
}


int simpleQueueEmpty(struct SimpleQueue* queue){
	int return_value;
//	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t)0) != pdTRUE){}
	return_value = queue->size == 0;
//	xSemaphoreGiveRecursive(queue->xSemHandle); //TODO: Decommentare
	return return_value;
}


int simpleQueueFull(struct SimpleQueue* queue){
	return 0;
}


int simpleQueueSize(struct SimpleQueue* queue){
	int return_value;
	while(xSemaphoreTakeRecursive(queue->xSemHandle,(TickType_t)0) != pdTRUE){}
	return_value = queue->size;
	xSemaphoreGiveRecursive(queue->xSemHandle);
	return return_value;
}

#ifdef NLS_TRACE
void simpleQueuePrint(struct SimpleQueue* queue){
	struct SimpleQueueNode* it = queue->head;
	while(it != NULL){
		printf("%d - ", *(it->value));
		it = it->previous_node;
	}
	printf("\n\r"); //XXX PER PAOLO: Attenzione a questa printf!!
}
#endif




