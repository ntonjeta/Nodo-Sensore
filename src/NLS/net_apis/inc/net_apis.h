/*
 * net_apis.h
 *
 *  Created on: 02/lug/2015
 *      Author: gennaro
 */

#ifndef NET_APIS_H_
#define NET_APIS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "NLS_globals.h"

#include "datagram_defs.h"
#include "SimpleQueue.h"
#include "DownstreamTable.h"
#include "network_config.h"

/**
 *  struttura dati usata per la configurazione delle APIs
 */
struct NLS_HandleTypedef
{
	struct PriorityQueue* routing_queue;
	struct SimpleQueue* PREP_queue;

#ifndef ROOT
	UpstreamTable* uTable;
#else
	DownStreamTable* dTable;

#endif

	uint16_t node_addr;
	uint16_t enabled_ifs;
	uint8_t enabled_ifs_num;

	TaskHandle_t receive_task_handle;
	TaskHandle_t send_task_handle;
	xQueueHandle event_queue;

};



/**
 * inizializza le API: code, upstream/downstream table ecc
 */
void NLS_init (struct NLS_HandleTypedef* hNLS);

/**
 *  distrugge la struttura di configurazione
 */
void NLS_deinit (struct NLS_HandleTypedef* hNLS);



/**
 * invia dati generati da un' applicazione sulla rete
 */

#ifdef ROOT
void send_datagram (struct NLS_HandleTypedef* hNLS , uint8_t* packet , int length , datagram_address_t dest_address , datagram_qos_t qos, uint8_t retry);
#else
void send_datagram (struct NLS_HandleTypedef* hNLS , uint8_t* packet , int length , datagram_qos_t qos);
#endif

/**
 *  riceve dati provenienti dalla rete
 */
void receive_datagram(struct NLS_HandleTypedef* hNLS , uint8_t if_src, uint8_t* packet, int packet_length);

#endif /* NET_APIS_H_ */
