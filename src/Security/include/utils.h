/**
 * \file utils.h
 *
 * \brief File Header con tutte le funzioni utili
 *
 * \author Gruppo 1
 */
#ifndef UTILS_H_
#define UTILS_H_

#include "stm32f4xx.h"
#include "stddef.h"

void cleanVector(void* vector,int n);
long long CalcNanosecondsFromStopwatch( long long nStop);


#endif /* UTILS_H_ */
