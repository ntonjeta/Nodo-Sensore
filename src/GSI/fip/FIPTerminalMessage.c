/*
 * FIPTerminalMessage.c
 *
 *  Created on: 20/gen/2015
 *      Author: ing. Mario Barbareschi
 */

#include "FIPTerminalMessage.h"

int createFIPTerminalMessage(TerminalMessageParameters params, FIPMessage**fm){
	*fm = emptyFIPMessage();
	FIPMessage *fipSensorMessage = *fm;
	fipSensorMessage->header = terminal;
	switch (params.operation) {
	case terminal_print:
		if (params.text_lenght < 0xFFFF) {
			fipSensorMessage->length = sizeof(uint8_t) + params.text_lenght;
			fipSensorMessage->payload = malloc(fipSensorMessage->length);
			fipSensorMessage->payload[0] = params.operation;
			memcpy(fipSensorMessage->payload + sizeof(uint8_t),
					params.text_buffer, params.text_lenght);
			return 1;
		} else {
			return 0;
		}
		break;
	case terminal_scan:
		//TODO
		return 0;
		break;
	case terminal_clear:
		//TODO
		return 0;
		break;
	default:
		return -1;
		break;
	}
}

int isTerminalMessage(FIPMessage *fm) {
	return fm->header == terminal;
}

TerminalOperation getTerminalOperation(FIPMessage *fm) {
	return fm->payload[0];
}

