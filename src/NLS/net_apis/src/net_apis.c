/*
 * net_apis.c
 *
 *  Created on: 03/lug/2015
 *      Author: gennaro
 */

#include "net_apis_LL.h"
#include "net_apis.h"
#include "UpstreamTable.h"
#include "data_plane.h"
#include "NLS_globals.h"
#include "net_apis_usr.h"
#include "datagram_builders.h"
#include "datagram_defs.h"
#include "DownStreamTable.h"
#include "net_apis_RTOS.h"

//extern struct PriorityQueue routing_queue;
//extern UpstreamTable uTable;

//typedef struct {
//	struct NLS_HandleTypedef* hNLS;
//	uint8_t if_src;
//	uint8_t* packet;
//	int packet_length;
//}receive_task_parameters;



uint16_t get_nodeAddr ();


/**
 * inizializza il livello fisico e le strutture dati utilizzate dal livello rete
 */
void NLS_init(struct NLS_HandleTypedef* hNLS)
{

	NLS_LL_init(hNLS);

	hNLS->routing_queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
	hNLS->PREP_queue = (struct SimpleQueue*)malloc(sizeof(struct SimpleQueue));

	priorityQueueInitialize(hNLS->routing_queue , 4 , 10);
	simpleQueueInitialize(hNLS->PREP_queue);

	#ifndef ROOT
	hNLS->uTable = (UpstreamTable*)malloc(sizeof(UpstreamTable));
	UTInitialize(hNLS->uTable);
	#else
	hNLS->dTable = (DownStreamTable*)malloc(sizeof(DownStreamTable));
	downStreamTableInitialize(hNLS->dTable);
	#endif


	hNLS->node_addr = get_nodeAddr();

	hNLS->enabled_ifs_num = 0;

	NLS_RTOS_init(hNLS);
}

void NLS_deinit(struct NLS_HandleTypedef* hNLS)
{
	priorityQueueDestroy(hNLS->routing_queue);


	free(hNLS->routing_queue);

	#ifndef ROOT
	UTDeleteAll(hNLS->uTable);
	free(hNLS->uTable);
	#else
	downStreamTableDestroy(hNLS->dTable);
	free(hNLS->dTable);
	#endif

	NLS_RTOS_deinit(hNLS);


	free(hNLS);
}


uint16_t get_nodeAddr ()
{
	return (uint16_t)MY_ADDRESS;

}
#ifdef ROOT
void send_datagram (struct NLS_HandleTypedef* hNLS , uint8_t* packet , int length , datagram_address_t dest_address , datagram_qos_t qos , uint8_t retry)
{
	if(retry != 0)
	{

		downStreamTablePenaliziesBestPath(hNLS->dTable , dest_address);
	}

	//lookup downstream table
	datagram_if_id_t dspath[MAX_HOP_COUNT];
	uint8_t ds_path_len;


	if(downstreamTableGetBestPath(hNLS->dTable , dest_address ,dspath , &ds_path_len )==1){
		printf("IMPOSSIBILE INVIARE _ NO BEST PATH PER %x \n\r",dest_address);
		return;
	}

	//printf(" dspath[0] : %d , dspath[1] : %d \n\r" , dspath[0] , dspath[1]);

	//costruisci un pacchetto downstream

	dsData_typedef data;
	data.address = dest_address;
	data.qos = qos;
	data.ds_path = dspath;
	data.ds_path_length = ds_path_len;
	data.payload_length = length;
	data.payload = packet;
	data.trailer = trailer_gen(packet , length);

	int datagram_len;
	uint8_t* to_send = build_dsData(data , &datagram_len);
//	printf("PACCHETTO DOWNSTREAM \n\r");
//
//	print_dsData(to_send);
	//costruisci struttura datagram info
	datagram_info* d_info = init_datagram_info(to_send , NO_SRC_IF , datagram_len, 0);

	//invia
	send_downstream(hNLS , d_info);

}

#else
void send_datagram (struct NLS_HandleTypedef* hNLS , uint8_t* packet , int length , datagram_qos_t qos)
{
	int datagram_length;
	//costruisci un pacchetto upstream
	usData_typedef usdata;
	usdata.qos = qos;
	usdata.payload_length = (datagram_dataup_len_payload_t)length;
	usdata.payload = packet;

	//TODO funzione che fa o fatt del trailer
	uint8_t trailer[1] = {0x1};
	usdata.trailer = trailer;

	datagram_info* d_info =NULL;
	uint8_t* pacchetto = build_usData(usdata , &datagram_length);
	d_info = init_datagram_info(pacchetto , NO_SRC_IF , datagram_length, 0);

	priorityQueueEnqueueOrDiscard(hNLS->routing_queue , qos , d_info );
}
#endif

/**
 * funzione invocata dal livello inferiore per la ricezione di un datagramma
 * se eseguita dal CC, trasporta i datagrammi al livello superiore (tramite callback o funzione weak)
 * mentre le preq/pfwd chiamano funzioni di autenticazione e generano pacchetti di prep
 *
 * se eseguita da un normale nodo, accoda il datagramma
 *
 *  TODO:
 *  1.inserire controllo autenticazione
 *  2.codice root
 *
 *  CODICE COMMENTATO SICURO
 */

void receive_datagram(struct NLS_HandleTypedef* hNLS , uint8_t if_src, uint8_t* packet, int packet_length)
{
	datagram_info* d_info =NULL;
	d_info = init_datagram_info(packet , if_src , packet_length, 0);

	if(d_info->type == BSRP_PREP && d_info->address == MY_ADDRESS)
	{
		simpleQueueEnqueue(hNLS->PREP_queue , d_info);
		return;
	}

	if(on_datagram_check(d_info) == CHECK_FAILED) return;


	//TODO callback congestione
	priorityQueueEnqueueOrDiscard(hNLS->routing_queue , get_datagram_QoS(d_info->packet) , d_info);
}


