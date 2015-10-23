#include "FIPMessageDispatcher.h"

unsigned char dispatchingEnabled = 0;
FIPMessage* receivingFIPMessage = NULL;
uint16_t partialPayloadLenght;
uint8_t* partialPayload;
messageStateType FIPMessageState = COMPLETE;
#ifndef callback
int head = 0, tail = 0;
FIPMessage **fmQueue = NULL;
#endif

/*
 *  Estrae dallo stream di byte ricevuti sulla USB, i messaggi 'cm'.
 *  I messaggi sono composti da header + lunghezza + payload.
 *  I messaggi, di tipo cateMessage, sono salvati nella coda circolare messageQueue
 *  tramite la funzione enqueueMessage.
 */


void enableDispatching(){
	dispatchingEnabled = 1;
}
void disableDispatcing(){
	dispatchingEnabled = 0;
}

int dispatch(uint8_t* buffer, uint16_t length) {
	if(dispatchingEnabled == 1){
	uint8_t target[1024];
	//ByteBuffer target;

	while (length > 0) {
		switch (FIPMessageState) {
		//stato iniziale in cui ogni precedente ricezione Ë terminata
		case COMPLETE:
			FIPMessageState = HEADER_RECEIVED;
			receivingFIPMessage = emptyFIPMessage();
			receivingFIPMessage->header = buffer[0];

			memcpy (target, buffer, length);
			length--;
			memcpy (buffer, target+1,  length);
			break;
		//leggo length del messaggio
		case HEADER_RECEIVED:
			if (length >= 2) {
				//operazioni eseguite se Ë giunto tutto il campo length
				FIPMessageState = length_COMPLETE;
				receivingFIPMessage->length = (uint16_t) (((uint16_t) buffer[1]) << 8 | buffer[0]);

				memcpy (target, buffer, length);
				length -= 2;
				memcpy (buffer, &target[2], length);
			} else {
				//operazioni eseguite se Ë giunto un solo byte del campo length
				FIPMessageState = length_INCOMPLETE;
				receivingFIPMessage->length = (uint16_t) ((uint16_t) buffer[0]);
				memcpy (target, buffer, length);
				length--;
				memcpy (buffer, &target[1], length);
			}
			break;
		//lettura del secondo byte del campo length a seguito di una nuova acquisizione da VCP
		case length_INCOMPLETE:
			//acquisizione del byte rimanente del campo length
			receivingFIPMessage->length = (uint16_t) (receivingFIPMessage->length | ((uint16_t) buffer[0]) << 8);
			FIPMessageState = length_COMPLETE;
			memcpy (target, buffer, length);
			length--;

			memcpy (buffer, &target[1], length);
			break;
		//acquisizione del campo relativo al payload del messaggio
		case length_COMPLETE:
			if (length >= receivingFIPMessage->length) {
				//controllo che sia giunto l'intero payload e lo acquisisco
				uint8_t* bufferPayload = (uint8_t*)malloc((receivingFIPMessage->length)*sizeof(uint8_t));
				memcpy (target, buffer, length);
				length -= receivingFIPMessage->length;
				memcpy (bufferPayload, target, receivingFIPMessage->length);
				memcpy (buffer, target, length);

				receivingFIPMessage->payload = bufferPayload;

				FIPMessageState = COMPLETE;
				messageReceivedCallback();
				return 1;
				} else {
				//se Ë giunta solo una parte del payload la salvo in partialPayload
				partialPayloadLenght = (uint16_t) (length);
				partialPayload = (uint8_t*)malloc(receivingFIPMessage->length);
				memcpy (target, buffer, length);
				memcpy (partialPayload, target, length);
				length = 0;
				FIPMessageState = PAYLOAD_INCOMPLETE;
			}
			break;
		//acquisisco una nuova parte del payload
		case PAYLOAD_INCOMPLETE:
			if (length >= receivingFIPMessage->length - partialPayloadLenght) {
				//acquisisco tutto il payload rimanente, relativo al messaggio
				uint8_t* bufferPayload = (uint8_t*)malloc((receivingFIPMessage->length) - partialPayloadLenght);
				memcpy (target, buffer, length);
				length -= (receivingFIPMessage->length - partialPayloadLenght);
				memcpy (bufferPayload , target , receivingFIPMessage->length-partialPayloadLenght );
				memcpy (&partialPayload[partialPayloadLenght], bufferPayload,receivingFIPMessage->length	- partialPayloadLenght);

				memcpy (buffer,target, length);

				partialPayloadLenght = -1;
				receivingFIPMessage->payload = partialPayload;
				//cancello la memoria puntata da bufferPayload
				free(bufferPayload);
				FIPMessageState = COMPLETE;
				messageReceivedCallback();
				return 1;
			} else {
				//acquisisco una parte del payload rimanente e torno nello stesso stato
				//per acquisisre il restante
				uint8_t* bufferPayload = (uint8_t*)malloc(length*sizeof(uint8_t));
				memcpy (target, buffer, length);
				memcpy (bufferPayload , target, length);
				memcpy (&partialPayload[partialPayloadLenght], bufferPayload, length);

				partialPayloadLenght += (uint16_t) (length);
				length = 0;
				FIPMessageState = PAYLOAD_INCOMPLETE;
			}
			break;
		default:
			return -1;
			break;
		}
	}
		return 0;
	}else{
		return -2;
	}
}

#ifdef callback
void setFIPMessageReceivedCallBack(void* callback){
	FIPMessageReceivedCallBack = callback;
}
#else
void internalCallBack(){
	if(fmQueue == NULL){
		fmQueue = (FIPMessage**) malloc(sizeof(FIPMessage*)*FIP_QUEUE_LENGHT);
	}
	if(receivingFIPMessage != NULL){
		fmQueue[tail] = receivingFIPMessage;
		tail=(tail+1)%FIP_QUEUE_LENGHT;
		if(tail == head){
			head=(head+1)%FIP_QUEUE_LENGHT;
		}
	}
}

int dequeueMessage(FIPMessage** fm){
	if(head == tail){
		return -1;
	}else{
		*fm = fmQueue[head];
		head=(head+1)%FIP_QUEUE_LENGHT;
		return (tail-head+FIP_QUEUE_LENGHT)%FIP_QUEUE_LENGHT;
	}
}

#endif
