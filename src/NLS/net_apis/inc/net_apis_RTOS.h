/*
 * net_apis_RTOS.h
 *
 *  Created on: 12/lug/2015
 *      Author: gennaro
 */

#ifndef NET_APIS_INC_NET_APIS_RTOS_H_
#define NET_APIS_INC_NET_APIS_RTOS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "net_apis.h"


#define NLS_DISPATCHER_DELAY				300
#define NLS_DISPATCHER_WAITING_PREP_TIME	300
#define NLS_RECEIVE_TASK_STACK_SIZE 		400
#define NLS_SEND_TASK_STACK_SIZE			400
#define NLS_EVENT_QUEUE_SIZE				100
#define NLS_RECEIVE_TASK_PRIORITY 			tskIDLE_PRIORITY+2
#define NLS_SEND_TASK_PRIORITY				tskIDLE_PRIORITY+2

void NLS_RTOS_init (struct NLS_HandleTypedef* hNLS);

void NLS_RTOS_deinit (struct NLS_HandleTypedef* hNLS);

/**
 * @brief task di ricezione dal livello fisico. riceve su una coda i pacchetti entranti e li manda allo scheduler
 * attraverso la primitiva receive_datagram()
 *
 * Lo switch del main link in caso di ritrasmissione � gestito nel task poich� l'evento deve essere notificato
 * quanto prima, cio� prima dell'accodamento di datagrammmi che potrebbero essere destinati in upstream verso
 * un' interfaccia non pi� funzioanante
 */
void receive_task(void* pvParameters);

/**
 * @brief task di invio. Implementa il dispatching dei datagrammi. Il nodo root deaccoda dalla coda a priorit�
 * e manda i datagrammi dati ai livelli superiori, oppure risponde ai messaggi di controllo
 *
 * il nodo generico manda i datagrammi dati di cui � destinatario ai livelli superiori, instrada gli altri e implementa
 * il control plane
 */
void send_task(void* pvParameters);


#endif /* NET_APIS_INC_NET_APIS_RTOS_H_ */
