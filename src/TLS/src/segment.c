/*
 * segment.c
 *
 *  Created on: 07/lug/2015
 *      Author: imma
 */

#include "segment.h"

/** @addtogroup	DEFINIZIONE SEGMENTO LIVELLO TRASPORTO
  * @{
  */

/** @defgroup	GET e SET dei campi del segmento
  * @brief Questo file implementa tutte le get e set dei campi del segmento
  * @{
  */

/**
  * @brief 	Funzione Get relativa al tipo di servizio.
  * @param  packet: puntatore al segmento
  * @retval Tipo di Servizio
  */

// TYPE SERVICE
segment_typeService_t get_segment_typeService(uint8_t* packet){
	return (segment_typeService_t)getField(packet,SERVICE_TYPE_DISP,SERVICE_TYPE_LEN);
}

/**
  * @brief  Funzione Set relativa al tipo di servizio.
  * @param  packet: puntatore al segmento
  * @param  typeService: tipo di servizio
  * @retval None
  */

void set_segment_typeService(uint8_t* packet, segment_typeService_t typeService){
	setField(packet , SERVICE_TYPE_DISP , SERVICE_TYPE_LEN , typeService);
}

/**
  * @brief  Funzione Get relativa al sequence number.
  * @param  packet: puntatore al segmento
  * @retval Sequence Number
  */

// SEQUENCE NUMBER
segment_sequenceNumber_t get_segment_sequenceNumber(uint8_t* packet){
	return (segment_sequenceNumber_t)getField(packet,SEQUENCE_NUMBER_DISP,SEQUENCE_NUMBER_LEN);
}

/**
  * @brief  Funzione Set relativa al sequence number.
  * @param  packet: puntatore al segmento
  * @param  sequenceNumber: valore del sequence number
  * @retval None
  */

void set_segment_sequenceNumber(uint8_t* packet, segment_sequenceNumber_t sequenceNumber){
	setField(packet , SEQUENCE_NUMBER_DISP , SEQUENCE_NUMBER_LEN , sequenceNumber);
}

/**
  * @brief  Funzione Get relativa al flag di congestione.
  * @param  packet: puntatore al segmento
  * @retval Flag di Congestione
  */

// CONG FLAG
segment_congFlag_t get_segment_congFlag(uint8_t* packet){
	return (segment_congFlag_t) getField(packet,CONG_FLAG_DISP,CONG_FLAG_LEN);
}

/**
  * @brief  Funzione Set relativa al flag di congestione.
  * @param  packet: puntatore al segmento
  * @param  congFlag: valore del flag (0:assenza,1:presenza)
  * @retval None
  */

void set_segment_congFlag(uint8_t* packet, segment_congFlag_t congFlag){
	setField(packet,CONG_FLAG_DISP,CONG_FLAG_LEN,congFlag);
}

/**
  * @brief  Funzione Get relativa al flag di ack.
  * @param  packet: puntatore al segmento
  * @retval Flag di Ack
  */

// ACK FLAG
segment_ackFlag_t get_segment_ackFlag(uint8_t* packet){
	return (segment_ackFlag_t) getField(packet,ACK_FLAG_DISP,ACK_FLAG_LEN);
}

/**
  * @brief  Funzione Set relativa al flag di ack.
  * @param  packet: puntatore al segmento
  * @param  ackFlag: valore del flag (0:assenza,1:presenza)
  * @retval None
  */

void set_segment_ackFlag(uint8_t* packet, segment_ackFlag_t ackFlag){
	setField(packet,ACK_FLAG_DISP,ACK_FLAG_LEN,ackFlag);
}

/**
  * @brief  Funzione Get relativa al payload.
  * @param  packet: puntatore al segmento
  * @param	bytelen: numero di byte del packet
  * @retval puntatore al payload
  */

// PAYLOAD
payload_t get_segment_payload(uint8_t* packet, int bytelen){
	return getPayload(packet,SEGMENT_DATA_DISP,bytelen);
}

/**
  * @brief  Funzione Set relativa al payload.
  * @param  packet: puntatore al segmento
  * @param  payload: puntatore al payload
  * @param	bytelen: numero di byte del packet
  * @retval None
  */

void set_segment_payload(uint8_t* packet,payload_t payload, int bytelen){
//	setPayload(packet,SEGMENT_DATA_DISP,bytelen,payload);
	memcpy(packet+(SEGMENT_DATA_DISP/8),payload,bytelen); // todo cambiata
}

/**
  * @}
  */
/**
  * @}
  */
