/*
 * CateMessage.h
 *
 *  Created on: 09/giu/2014
 *      Author: ing. Mario Barbareschi
 */

#ifndef FIPMESSAGE_H_
#define FIPMESSAGE_H_
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


#define MAX_MESSAGE_LENGHT 1024
#define FIP_HEADER_LENGTH 3

	/*
	 * Definitions for the first header byte, the command
	 */

#define READ_SENSOR 		0x00
#define TERMINAL 			0x01 //inivio, registrazione su un particolare numero
#define NETWORKING			0x02
#define CALL				0x03
#define HE_CMD				0x04 //accendi il led, alza volume, play, stop, display, etc. etc.
#define OS_CMD				0x05 //stessi comandi file linux (mkdir, touch, write, read, seek, etc.)
#define NOTIFICATION		0x06 //print su activity, scan su activity, ballon, notification, etc.
#define INTRA_COM			0x07 //print su activity, scan su activity, ballon, notification, etc.
#define INTER_COM			0x08 //print su activity, scan su activity, ballon, notification, etc.



typedef enum {
	read_sensor = READ_SENSOR,
	terminal = TERMINAL,
	networking = NETWORKING,
	call = CALL,
	he_cmd = HE_CMD,
	os_cmd = OS_CMD,
	notification = NOTIFICATION,
	intra_com = INTRA_COM,
	inter_com = INTER_COM
}FIPHeader;

typedef struct {
	FIPHeader header;
	uint16_t length;
	uint8_t* payload;
}FIPMessage;

FIPMessage* emptyFIPMessage();
FIPMessage* newFIPMessage(uint8_t header, uint8_t* payload, uint16_t payloadSize);
void destroyFIPMessage(FIPMessage* inMessage);
typedef uint8_t* ptrToUint8;
size_t serializeFIPMessage(FIPMessage* inFIP, uint8_t* inUint8Pt);

#endif /* FIP_MESSAGE_H_ */
