/*
 * network_config.h
 *
 *  Created on: 01/lug/2015
 *      Author: Paolo
 */

#ifndef NETWORK_CONFIG_H_
#define NETWORK_CONFIG_H_

#include <stdint.h>

typedef uint8_t* 				challenge_t;

/************************************************************************************************************
 * 										NETWORK CONFIGURATION												*
 ***********************************************************************************************************/

/**
 * @addtogroup	File di configurazione di rete
 * @{
 */

/** @defgroup Configurazioni architetturali di rete e di nodo
  * @{
  */

/**
 * @brief parametri di inizializzazione di livello trasporto
 *
 * -timeout di ritrasmissione per segmenti di tipo ASYNC (in ms)
 * -numero massimo di trasmissioni per segmenti di tipo ASYNC. comprende la prima tramsissione
 * -numero massimo di trasmissioni per segmenti di tipo REAL TIME. si consiglia un valore inferiore a ASYNC_MAX_TRIALS
 */
#define TL_ASYNC_TIMEOUT  5000				//XXX modificato
#define TL_ASYNC_MAX_TRIALS 4				//XXX modificato: 1��� trasmissione + 3 ritentavivi
#define TL_REAL_TIME_MAX_TRIALS 1			//XXX modificato: 1 sola trasmissione
#define TL_MAX_TIMEOUT	65535				//XXX creare

/**
 * @brief indirizzo di rete NLS del nodo, 16 bit
 *
 * NOTA: il centro di calcolo ha indirizzo 0x0000. Compilare con questo valore per avere il centro di calcolo
 */
#define MY_ADDRESS				0x0009

#if MY_ADDRESS == 0x0000
#define ROOT
#define TL_ROOT
#endif

/**
 * @brief definizione lunghezza dei payload per i pacchetti di routing. Questi possono portare informazioni, in particolar
 * modo di autenticazione, settare qui la lunghezza in byte
 */
#define TRAILER_LEN_BYTE				1
#define CHALLENGE_LEN_BYTE 				4
#define	SECRET_LEN_BYTE					2

/**
 * @brief lunghezza del dspath. Questo valore influenza la lunghezza dei pacchetti downstream e del pacchetto di controllo
 * Path Forward. Un nodo che dovr��� scoprire un path a lunghezza maggiore non pu��� essere gestito in questa versione
 * del protocollo. Previsto meccanismo di "path caching" (v. wiki)
 */
#define MAX_HOP_COUNT					8

/**
 * @brief configurazioni specifiche per il livello fisico CARL. setta il numero di ritrasmissioni e il timeout di ritrasmissione
 * Si consiglia di mantenere un valore basso per le trasmissioni in upstream, dove si pu��� sfruttare lo switching
 * dinamico del path di upstream, mentre le ritrasmissioni in upstream dovrebbe essere pi��� elevato perch��� un pacchetto
 * perso verr��� ritrasmesso soltanto quando i meccanismi di ritrasmissione di alto livello si attiveranno
 */
#define UPSTREAM_SND_RETRY			1
#define DOWNSTREAM_SND_RETRY		5
#define SND_TIMEOUT					100

/**
 * @brief configurazioni per le strutture dati NLS. Quando un main link della upstream table o un path della
 * downstream table cade esso non viene eliminato ma semplicemente penalizzato. qui si pu��� configurare
 * il numero di penalizzazioni prima delle quali eliminare le entries
 * penalizzato. E' p
 */
#define MAX_UPSTREAM_TABLE_PENALIZES	1




#endif /* NETWORK_CONFIG_H_ */
