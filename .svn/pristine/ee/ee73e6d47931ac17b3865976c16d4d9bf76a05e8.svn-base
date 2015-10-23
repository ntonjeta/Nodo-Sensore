/*
 * CateMessage.h
 *
 *  Created on: 09/giu/2014
 *      Author: ing. Mario Barbareschi
 */

#include "FIPMessage.h"

FIPMessage* emptyFIPMessage()
{
	return (FIPMessage*)malloc(sizeof(FIPMessage));
}

FIPMessage* newFIPMessage(uint8_t header, uint8_t* payload, uint16_t payloadSize)
{
	FIPMessage* ret = (FIPMessage*)malloc(sizeof(FIPMessage));
	ret->header = header;
	ret->length = payloadSize;
	ret->payload = (uint8_t*)malloc(payloadSize*sizeof(uint8_t));
	memcpy(payload, ret->payload, payloadSize);
	return ret;
}

void destroyFIPMessage(FIPMessage* inMessage)
{
	free(inMessage->payload);
	free(inMessage);
}


size_t serializeFIPMessage(FIPMessage* inFIP, uint8_t* inUint8Pt)
{
	size_t dimToSend = (inFIP->length)+FIP_HEADER_LENGTH;
	//*inUint8Pt = (uint8_t*)malloc(dimToSend);

	//concatenazione dell'header alla sequenza di Byte da inviare
	memcpy ( inUint8Pt, &(inFIP->header), 1 );
	//concatenazione della length alla sequenza di Byte da inviare
	memcpy ( inUint8Pt+1, &(inFIP->length), 2 );
	//concatenazione del payload alla sequenza di Byte da inviare
	memcpy ( inUint8Pt+3, inFIP->payload, inFIP->length );
	return dimToSend;
}



