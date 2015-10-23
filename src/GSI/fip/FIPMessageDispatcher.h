/*
 * CateMessage.h
 *
 *  Created on: 09/giu/2014
 *      Author: ing. Mario Barbareschi
 */

#ifndef FIPMESSAGEDISPATCHER_H_
#define FIPMESSAGEDISPATCHER_H_

#include "FIPMessage.h"

typedef enum {
	HEADER_RECEIVED, length_INCOMPLETE, length_COMPLETE, PAYLOAD_INCOMPLETE, COMPLETE, DISPATCHED
}messageStateType;

int dispatch(uint8_t* buffer, uint16_t length);
void enableDispatching();
void disableDispatcing();

#ifdef callback
#define messageReceivedCallback() FIPMessageReceivedCallBack()
void* FIPMessageReceivedCallBack;
void setFIPMessageReceivedCallBack(void* callback);
#else
#define messageReceivedCallback() internalCallBack();
#define FIP_QUEUE_LENGHT 10
int dequeueMessage(FIPMessage** fipm);
#endif

#endif /* FIPMESSAGEDISPATCHER_H_ */
