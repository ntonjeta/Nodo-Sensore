/*
 * segment_builder.c
 *
 *  Created on: 07/lug/2015
 *      Author: imma
 */

#include "segment_builder.h"
#include <stdlib.h>

// dichiarazione e inizializzazione della variabile globale sequence number
segment_sequenceNumber_t SeqNum = 0;

/**
 * @addtogroup	COSTRUZIONE SEGMENTO
 */

/**
 * @defgroup	BUILD SEGMENTO
 * @{
 */

/**
 * @brief	Funzione che costruisce un generico segmento
 * @param	data: struttura dati che astrae il segmento
 * @param	segment_length: dimensione in byte del segmento
 * @retval	Puntatore al segmento costruito
 */

uint8_t* build_segment (data_typedef data ,int segment_length){
	uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t)*segment_length);

	set_segment_typeService(packet,data.service_type);
	set_segment_sequenceNumber(packet,data.sequence_number);
	set_segment_congFlag(packet,data.cong_flag);
	set_segment_ackFlag(packet,data.ack_flag);

	set_segment_payload(packet,data.payload,(segment_length - SEGMENT_DATA_DISP/8));

	return packet;
}



/**
 * @brief	Funzione che genera un sequence number
 * @retval	Sequence Number generato
 */

segment_sequenceNumber_t generateSequenceNumber(){
	SeqNum = (SeqNum + 1) % MAX_SEQUENCE_NUMBER ;
	return SeqNum ;
}


#ifdef TL_DEBUG
void print_segment(uint8_t* packet,int segment_length){
	printf("\n Info Segmento");
	printf("\n Tipo di servizio : %d ", get_segment_typeService(packet));
	printf("\n Sequence Number : %d ", get_segment_sequenceNumber(packet));
	printf("\n Flag di congestione : %d ", get_segment_congFlag(packet));
	printf("\n Flag di ack : %d ", get_segment_ackFlag(packet));
	printf("\n Contenuto Payload : %d \n", *(get_segment_payload(packet,(segment_length - SEGMENT_DATA_DISP/8))));
}
#endif


/**
  * @}
  */

/**
   * @}
   */
