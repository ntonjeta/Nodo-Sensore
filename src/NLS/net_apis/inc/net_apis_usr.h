/*
 * net_apis_usr.h
 *
 *  Created on: 04/lug/2015
 *      Author: gennaro
 */

#ifndef NET_APIS_USR_H_
#define NET_APIS_USR_H_

#include "datagram_info.h"
#include "net_apis_core.h"


/**
 *  evento utente chiamato quando un datagramma con trailer viene ricevuto
 *  può essere utilizzata per effettuare controlli di integrità/autenticazione.
 *  SI RICHIEDE DI NON DEALLOCARE TRAILER
 *
 *  @param[in] trailer trailer del datagramma
 *
 *
 *
 *  @retval check_status che descrive l'esito del controllo
 */

__attribute__((weak)) check_status on_USR_datagram_check(uint8_t* packet);

/**
 *	@brief funzione che viene invocata alla ricezione della PREP
 *	Puo' essere utilizzata per verificare la ricezione del segret
 *
 *	@retval l'eventuale payload da inserire nella successiva PACK
 */
__attribute__((weak)) uint8_t* on_USR_PREP (uint8_t* secret , uint8_t length);

/**
 *  evento utente chiamato quando viene ricevuto un messaggio PACK che notifica
 *  al CC il ricevimento del segreto. pertanto si consiglia di implementare per questa
 *  funzione della logica apposita per il centro di calcolo, usando la seguente sintassi
 *  SI RICHIEDE DI NON DEALLOCARE PACKET
 *
 *  @code
 *  #ifdef ROOT
 *
 *  ....codice
 *
 *  #endif
 *  @endcode
 *
 *  @param[in] packet payload del datagramma PACK
 *  @retval check_status che descrive l'esito del controllo
 */
__attribute__((weak)) check_status on_USR_PACK_check (uint8_t* packet , int length);


/**
 *
 *  evento utente chiamato alla ricezione di ogni datagramma. può essere usata per
 *  elaborare il datagramma ai livelli superiori
 *
 *  si raccomanda di deallocare packet
 *
 *  @param[in] packet	datagramma privo degli header di livello rete
 *  @param[in] len		lunghezza del pacchetto restituito
 */
__attribute__((weak)) void on_USR_datagram_received(uint8_t* packet , int len , uint16_t addr);

/**
 *
 * evento utente chiamato all'avvio di una path discovery, cioè quando un nodo
 * invia in broadcast una PREQ. può essere utiliut
 *
 * @retval challenge
 *
 */
__attribute__((weak)) challenge_t on_USR_path_discovery ();

/**
 * evento utente chiamato alla ricezione di una PREP
 */
__attribute__((weak)) void on_USR_path_discovered ();

/**
 * evento utente chiamato alla ricezione di una PFWD autenticata
 */
__attribute__((weak)) void on_USR_path_discovered_root (uint16_t node , uint16_t* path , uint8_t length);

/**
 *  evento utente chiamato alla ricezione di una PREQ
 */
__attribute__((weak)) uint8_t* on_USR_PREQ(uint8_t* challenge);

/**
 * @brief funzione chiamata ogni volta che le APIs richiedono la generazione di un
 * trailer
 */
__attribute__((weak)) uint8_t* on_USR_trailer_gen(uint8_t* packet , uint8_t length);


#endif /* NET_APIS_USR_H_ */
