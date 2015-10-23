#ifndef __LIBUART_H__
#define __LIBUART_H__

#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "applicationConfig.h"


#define PRIORITY 0
#define SUBPRIORITY 0
#define MAX_STRLEN (1+IDLEN+TIMESTAMPLEN+MAX_LENGTH+DIGESTLEN)
#define	MAX_BUFFER (1+IDLEN+TIMESTAMPLEN+MAX_LENGTH+DIGESTLEN)

//USART4

#define BAUDRATE 9600

void setup();
void getFrame();
HAL_StatusTypeDef usart_send(void* frame/*,uint16_t size*/);
void initUART();
HAL_StatusTypeDef usart_receive();

void Delay( uint32_t nTime);

#endif /* __LIBUART_H__ */
