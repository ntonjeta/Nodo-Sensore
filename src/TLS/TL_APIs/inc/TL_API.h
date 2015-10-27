/*
 * TL_API.h
 *
 *  Created on: 07/lug/2015
 *      Author: Lorenzo
 */

#ifndef TL_API_H_
#define TL_API_H_

#include <stdint.h>
#include "network_config.h"
#define TL_TIMER_TIMEOUT		100
#define TL_ASYNC_TIMEOUT  		5000
#define TL_ASYNC_MAX_TRIALS 	4
#define TL_REAL_TIME_MAX_TRIALS 1
#define TL_MAX_TIMEOUT 			65535

#ifdef ROOT
	#define TL_ROOT				//se centro di calcolo => decommenta
#endif

/**
 * @addtogroup	LIVELLO_TRASPORTO_APIs
 * @{
 */


/**
 * @}
 */

/** @defgroup LIVELLO_TRASPORTO_Exported_Functions
  * @{
  */

/**
 * @brief	funzioni che inizializzano e de-inizializzano
 * le strutture di livello trasporto
 * @param	None
 * @retval	None
 */
void TL_init();
void TL_deinit();


/**
 * @brief	funzioni send_segment per ogni tipo di servizio richiesto :
 * 		ASYNCHRONOUS -> consegna garantita
 * 		REAL_TIME 	 -> consegna garantita entro una certa deadline
 * 		BEST_EFFORT  -> consegna non garantita (per dati ordinari)
 */

#ifdef TL_ROOT
void send_segment_asynchronous(uint8_t* packet, int bytelen, uint16_t dst_address);
void send_segment_real_time(uint8_t* packet, int bytelen, uint16_t timeout, uint16_t dst_address);
void send_segment_best_effort(uint8_t* packet, int bytelen, uint16_t dst_address);
#else
void send_segment_asynchronous(uint8_t* packet, int bytelen);
void send_segment_real_time(uint8_t* packet, int bytelen, uint16_t timeout);
void send_segment_best_effort(uint8_t* packet, int bytelen);
#endif


/**
 * @brief	CALLBACK che il livello superiore dovrà implementare
 */
__attribute__((weak)) void on_receive_segment_asynchronous(uint8_t* packet, uint16_t len, uint16_t src_address);
__attribute__((weak)) void on_receive_segment_real_time(uint8_t* packet, uint16_t len, uint16_t src_address);
__attribute__((weak)) void on_receive_segment_best_effort(uint8_t* packet, uint16_t len, uint16_t src_address);
__attribute__((weak)) void on_send_segment_real_time_failed(uint8_t* packet, uint16_t len, uint16_t dest_address);
__attribute__((weak)) void on_send_segment_asynchronous_failed(uint8_t* packet, uint16_t len, uint16_t dest_address);

/**
 * @}
 */
/**
 * @}
 */

#endif /* TL_API_H_ */
