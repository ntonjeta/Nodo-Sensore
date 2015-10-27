/*
 * FIPTerminalMessage.h
 *
 *  Created on: 20/gen/2015
 *      Author: ing. Mario Barbareschi
 */

#ifndef FIP_FIPTERMINALMESSAGE_H_
#define FIP_FIPTERMINALMESSAGE_H_

#include "FIPMessage.h"

#define TERMINAL_PRINT						(uint8_t)0x00
#define TERMINAL_SCAN
#define TERMINAL_CLEAR

typedef enum {
	terminal_print = TERMINAL_PRINT,
	terminal_scan,
	terminal_clear
}TerminalOperation;

struct TerminalMessageParameters {
	TerminalOperation operation;
	uint8_t* text_buffer;
	uint16_t text_lenght;
};
typedef struct TerminalMessageParameters TerminalMessageParameters;

int createFIPTerminalMessage(TerminalMessageParameters params, FIPMessage**fm);
int isTerminalMessage(FIPMessage *fm);
TerminalOperation getTerminalOperation(FIPMessage *fm);



#endif /* FIP_FIPTERMINALMESSAGE_H_ */
