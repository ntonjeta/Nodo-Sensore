#ifndef SIMPLEQUEUE_H_
#define SIMPLEQUEUE_H_

#include "stdint.h"
#include "datagram_info.h"

typedef	datagram_info SimpleQueueValue;

#include "FreeRTOS.h"
#include "semphr.h"

struct SimpleQueueNode{
	SimpleQueueValue* value;
	struct SimpleQueueNode* next_node;
	struct SimpleQueueNode* previous_node;
};

struct SimpleQueue{
	struct SimpleQueueNode* head;		//Puntatore alla testa della coda
	struct SimpleQueueNode* tail;		//Puntatore alla fine della coda
	int size;							//Numero di elementi in coda
	SemaphoreHandle_t xSemHandle;
};

void simpleQueueInitialize(struct SimpleQueue*);
void simpleQueueDestroy(struct SimpleQueue*);
void simpleQueueEnqueue(struct SimpleQueue*, SimpleQueueValue*);
SimpleQueueValue* simpleQueueDequeue(struct SimpleQueue*);
SimpleQueueValue* simpleQueueFront(struct SimpleQueue*);

int simpleQueueEmpty(struct SimpleQueue*);
int simpleQueueFull(struct SimpleQueue*);
int simpleQueueSize(struct SimpleQueue*);

#ifdef NLS_TRACE
void simpleQueuePrint(struct SimpleQueue*);
#endif

#endif /* SIMPLEQUEUE_H_ */
