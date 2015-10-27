/*
 * TL_API.c
 *
 *  Created on: 07/lug/2015
 *      Author: Lorenzo
 */
#include "FreeRTOS.h"
#include "timers.h"

#include "TL_API.h"
#include "net_apis_usr.h"
#include "segment_builder.h"
#include "TL_table.h"
#include "net_apis.h"


extern struct NLS_HandleTypedef hNLS;
TimerHandle_t timer;

TL_table table;
uint8_t initialized = 0;

void timer_expired();


void TL_init(){
	TLInitialize(&table);
	NLS_init(&hNLS);

	timer = xTimerCreate("TLS_Timer",
							TL_TIMER_TIMEOUT/portTICK_PERIOD_MS,
							pdTRUE,
							NULL,
							timer_expired);

	xTimerStart(timer,0);

	initialized = 1;
}


void TL_deinit(){
	TLDeleteAll(&table);
	NLS_deinit(&hNLS);
	initialized = 0;
}


#ifdef TL_ROOT
void send_segment_real_time(uint8_t* packet, int bytelen, uint16_t timeout, uint16_t dest_address){
	data_typedef data;

	data.service_type = SEGMENT_REAL_TIME;
	data.sequence_number = generateSequenceNumber();
	data.ack_flag = 0;
	data.cong_flag = 0;
	data.payload = packet;

	uint8_t* segment = build_segment(data, bytelen + TRANSPORT_HEADER_SIZE);

	if(timeout*2 > TL_MAX_TIMEOUT)
		TLInsertEntry(&table, data.sequence_number, TL_MAX_TIMEOUT, TL_REAL_TIME_MAX_TRIALS, bytelen + TRANSPORT_HEADER_SIZE, dest_address, segment);
	else
		TLInsertEntry(&table, data.sequence_number, timeout*2, TL_REAL_TIME_MAX_TRIALS, bytelen + TRANSPORT_HEADER_SIZE, dest_address, segment);

	send_datagram (&hNLS , segment , bytelen + TRANSPORT_HEADER_SIZE , dest_address , REAL_TIME, 0);
}

void send_segment_asynchronous(uint8_t* packet, int bytelen,  uint16_t dest_address){
	data_typedef data;

	data.service_type = SEGMENT_ASYNCHRONOUS;
	data.sequence_number = generateSequenceNumber();
	data.ack_flag = 0;
	data.cong_flag = 0;
	data.payload = packet;

	uint8_t* segment = build_segment(data, bytelen + TRANSPORT_HEADER_SIZE);

	TLInsertEntry(&table, data.sequence_number, TL_ASYNC_TIMEOUT, TL_ASYNC_MAX_TRIALS, bytelen + TRANSPORT_HEADER_SIZE, dest_address, segment);

	send_datagram (&hNLS , segment , bytelen + TRANSPORT_HEADER_SIZE , dest_address , ASYNC, 0);
}

void send_segment_best_effort(uint8_t* packet, int bytelen, uint16_t dest_address){
	data_typedef data;

	data.service_type = SEGMENT_BEST_EFFORT;
	data.sequence_number = BEST_EFFORT_SEQ_NUM;
	data.ack_flag = 0;
	data.cong_flag = 0;
	data.payload = packet;

	uint8_t* segment = build_segment(data, bytelen + TRANSPORT_HEADER_SIZE);

	send_datagram (&hNLS , segment , bytelen + TRANSPORT_HEADER_SIZE , dest_address , BEST_EFFORT, 0);

	free(segment);
}

#else

void send_segment_real_time(uint8_t* packet, int bytelen, uint16_t timeout){
	data_typedef data;

	data.service_type = SEGMENT_REAL_TIME;
	data.sequence_number = generateSequenceNumber();
	data.ack_flag = 0;
	data.cong_flag = 0;
	data.payload = packet;

	uint8_t* segment = build_segment(data, bytelen + TRANSPORT_HEADER_SIZE);

	if (timeout*2 > TL_MAX_TIMEOUT)
		TLInsertEntry(&table, data.sequence_number, TL_MAX_TIMEOUT, TL_REAL_TIME_MAX_TRIALS, bytelen + TRANSPORT_HEADER_SIZE, 0, segment);
	else
		TLInsertEntry(&table, data.sequence_number, timeout*2, TL_REAL_TIME_MAX_TRIALS, bytelen + TRANSPORT_HEADER_SIZE, 0, segment);

	send_datagram (&hNLS , segment , bytelen + TRANSPORT_HEADER_SIZE , REAL_TIME);
}

void send_segment_asynchronous(uint8_t* packet, int bytelen){
	data_typedef data;

	data.service_type = SEGMENT_ASYNCHRONOUS;
	data.sequence_number = generateSequenceNumber();
	data.ack_flag = 0;
	data.cong_flag = 0;
	data.payload = packet;

	uint8_t* segment = build_segment(data, bytelen + TRANSPORT_HEADER_SIZE);

	TLInsertEntry(&table, data.sequence_number, TL_ASYNC_TIMEOUT, TL_ASYNC_MAX_TRIALS, bytelen + TRANSPORT_HEADER_SIZE, 0, segment);

	send_datagram (&hNLS , segment , bytelen + TRANSPORT_HEADER_SIZE , ASYNC);
}

void send_segment_best_effort(uint8_t* packet, int bytelen){
	data_typedef data;

	data.service_type = SEGMENT_BEST_EFFORT;
	data.sequence_number = BEST_EFFORT_SEQ_NUM;
	data.ack_flag = 0;
	data.cong_flag = 0;
	data.payload = packet;

	uint8_t* segment = build_segment(data, bytelen + TRANSPORT_HEADER_SIZE);

	send_datagram (&hNLS , segment , bytelen + TRANSPORT_HEADER_SIZE , BEST_EFFORT);

	free(segment);
}

#endif


void on_USR_datagram_received(uint8_t* packet , int len , uint16_t src_address){
	TL_Entry *e;
	data_typedef data;

	/*
	 * @brief	Se a livello trasporto ricevo un pacchetto di ACK, devo cercare nella
	 * tabella la entry relativa al pacchetto con quel sequence number e cancellarla.
	 * Se non � un pachetto di ACK, controllo se il tipo di servizio �
	 * asincrono o real-time. In questo caso, � necessario preparare ed inviare un
	 * pacchetto di ACK (con lo stesso numero di sequenza della richiesta) prima di
	 * passare il payload al livello applicativo.
	 */

	uint8_t *received_segment = (uint8_t*) malloc (len);
	memcpy(received_segment, packet, len);

	if (get_segment_ackFlag(received_segment) == 1){
		e = TLFindEntryBySeqNum(&table,get_segment_sequenceNumber(received_segment));
		printf("ACK RICEVUTO\n\r");
		if (e != NULL)
			TLDeleteEntry(&table,e);
		else{
			//XXX TRANSPORT LAYER INFO: Ricevuto ACK duplicato o in ritardo per un pacchetto real-time
		}

	}
	else{
		if (get_segment_typeService(received_segment)==SEGMENT_ASYNCHRONOUS || get_segment_typeService(received_segment)==SEGMENT_REAL_TIME){
			data.ack_flag = 1;
			data.sequence_number = get_segment_sequenceNumber(received_segment);
			data.cong_flag = 0;
			data.service_type = SEGMENT_REAL_TIME;
			data.payload = NULL;
			uint8_t* segment = build_segment(data, TRANSPORT_HEADER_SIZE);

			#ifdef TL_ROOT
			send_datagram (&hNLS , segment , TRANSPORT_HEADER_SIZE , src_address, REAL_TIME, 0);
			#else
			send_datagram (&hNLS , segment , TRANSPORT_HEADER_SIZE , REAL_TIME);
			#endif
			printf("ACK INVIATO!\n\r");
			free(segment);

			if (get_segment_typeService(received_segment)==SEGMENT_ASYNCHRONOUS)
				on_receive_segment_asynchronous(get_segment_payload(received_segment, len-TRANSPORT_HEADER_SIZE), len-TRANSPORT_HEADER_SIZE, src_address);	//XXX nuova funzione
			else
				on_receive_segment_real_time(get_segment_payload(received_segment, len-TRANSPORT_HEADER_SIZE), len-TRANSPORT_HEADER_SIZE, src_address);		//XXX nuova funzione

		}
		else
			on_receive_segment_best_effort(get_segment_payload(received_segment, len-TRANSPORT_HEADER_SIZE), len-TRANSPORT_HEADER_SIZE, src_address);		//XXX nuova funzione
	}

	free(received_segment);
}


void timer_expired(){
//	printf("timer expired\n\r");
	if (initialized == 0)
		return;

	TL_Entry *e;

	TLDecrementTime(&table,TL_TIMER_TIMEOUT);		//XXX modificato

	do{
		e = TLFindEntryByTimeout(&table,0);

		if (e!=NULL){
			e->retry--;				//decrementa il campo retry
			if (e->retry == 0){
				if(get_segment_typeService(e->packet) == SEGMENT_REAL_TIME){
					//XXX TRANSPORT LAYER ERROR: Non ricevuto ACK in tempo per un pacchetto real-time
					printf("NON HO RICEVUTO L'ACK DOPO TRE TRASMISSIONI DI UN PACCHETTO REAL TIME\n\r");
					on_send_segment_real_time_failed(get_segment_payload(e->packet,e->segment_size-TRANSPORT_HEADER_SIZE), e->segment_size-TRANSPORT_HEADER_SIZE, e->dst_address);	//XXX nuova funzione
				}
				else{
					//XXX TRANSPORT LAYER ERROR: Non ricevuto ACK dopo 3 ritrasmissioni di un pacchetto asincrono
					printf("NON HO RICEVUTO L'ACK DOPO TRE TRASMISSIONI DI UN PACCHETTO ASINCRONO\n\r");
					on_send_segment_asynchronous_failed(get_segment_payload(e->packet,e->segment_size-TRANSPORT_HEADER_SIZE), e->segment_size-TRANSPORT_HEADER_SIZE, e->dst_address); 	//XXX nuova funzione
				}
				TLDeleteEntry(&table,e);
			}
			else{
				if(get_segment_typeService(e->packet) == SEGMENT_ASYNCHRONOUS){
					printf("RITRASMISSIONE DI UN PACCHETTO ASINCRONO!\n\r");
					//XXX TRANSPORT LAYER WARNING: Ritrasmissione di un pacchetto asincrono
					e->actual_time=e->original_time;
					#ifdef TL_ROOT
					send_datagram (&hNLS , e->packet , e->segment_size , e->dst_address , ASYNC, 1);
					#else
					send_datagram (&hNLS , e->packet , e->segment_size , ASYNC);
					#endif
				}
			}
		}
	}while(e!=NULL);
}



//CALLBACKs
//void on_receive_segment_asynchronous(uint8_t* packet, uint16_t len, uint16_t address){
//	printf("****ASYNC PACKET RECEIVED****\n\r");
//	printf("    from source: %d\n\r",address);
//	printf("    length: %d\n\r",len);
//	//printf("    payload content: %d\n\r", *packet);
//	print_payload(packet, len, 1);
//}

void on_receive_segment_real_time(uint8_t* packet, uint16_t len, uint16_t address){
	printf("****REAL TIME PACKET RECEIVED****\n\r");
	printf("    from source: %d\n\r",address);
	printf("    length: %d\n\r",len);
//	printf("    payload content: %d\n\r", *packet);
	print_payload(packet, len, 1);
}

//void on_receive_segment_best_effort(uint8_t* packet, uint16_t len, uint16_t address){
//	printf("****BEST EFFORT PACKET RECEIVED****\n\r");
//	printf("    from source: %d\n\r",address);
//	printf("    length: %d\n\r",len);
////	printf("    payload content: %d\n\r", *packet);
//	print_payload(packet, len, 1);
//}

void on_send_segment_real_time_failed(uint8_t* packet, uint16_t len, uint16_t address){
	printf("****SEND REAL TIME FAILED****\n\r");
	printf("    for destination: %d\n\r",address);
	printf("    length: %d\n\r",len);
//	printf("    packet: %d\n\r", *packet);
	print_payload(packet, len, 1);
}

void on_send_segment_asynchronous_failed(uint8_t* packet, uint16_t len, uint16_t address){
	printf("****SEND ASYNCHRONOUS FAILED****\n\r");
	printf("    for destination: %d\n\r",address);
	printf("    length: %d\n\r",len);
//	printf("    packet: %d\n\r", *packet);
	print_payload(packet, len, 1);
}


