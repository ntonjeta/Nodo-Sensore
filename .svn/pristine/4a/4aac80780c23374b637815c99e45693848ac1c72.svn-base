/**
 * \file utils.c
 *
 * \brief File con tutte le funzioni utili
 *
 * Questo file contiene tutte le funzioni che sono tornate spesso utili per lo sviluppo
 * di queste demo
 *
 * \author Gruppo 1
 */

#include "utils.h"

/**
 * \brief Inizializza il vettore vector con tutti caratteri '\0'.
 * \param  vector: vettore da inizializzare
 * \param  n: dimensione del vettore
 * \retval None
 */
void cleanVector(void* vector,int n) {
	//inizializza il vettore a 0
	int i;
	for (i = 0; i < n; i++) {
		((unsigned char*)vector)[i] = 0x00;
	}
}

/**
 * \brief Calcola il numero di colpi di clock e restituisce il numero di nanosecondi
 * \param  Time: numero di colpi di clock
 * \retval Time: numero di nanosecondi
 */
long long CalcNanosecondsFromStopwatch( long long Time) {
	long long nTemp;
	long long n;
	Time *= 1000;            // Scale cycles by 1000.
	n = SystemCoreClock / 1000000;            // Convert Hz to MHz. SystemCoreClock = 168000000
	Time = Time / n;            // nanosec = (Cycles * 1000) / (Cycles/microsec)
	return Time;
}
