/*
 * clock.c
 *
 *  Created on: Jun 25, 2015
 *      Author: andrea
 */

#include "clock.h"
#include "stm32f4_discovery.h"
/*Exported variables*/
sys_time _sys_time;
static uint32_t _timeout;	//timeout per la risincronizzazione col server
static uint32_t _count;		//conteggio per il timeout

/*Private variables*/
static uint8_t time_enabled = 0;
static uint32_t sync_init = 0;
static uint32_t sync_end = 0;

/*Private functions*/
static void start_time();
static void suspend_time();

/*
 * Funzione : init_time(uint32_t timeout)
 * Parametri: timeout: tempo espresso in secondi dopo il quale il nodo si sincronizza con il server
 * @brief : Inizializzazione del tempo di sistema
 *
 * */
void init_time(uint32_t timeout){

	_sys_time.year = 0;
	_sys_time.month = 0;
	_sys_time.day = 0;
	_sys_time.hour = 0;
	_sys_time.minutes = 0;
	_sys_time.seconds = 0;
	_sys_time.milliseconds = 0;

#if TIME_SERVER == 0
	_timeout = timeout;
#endif
	 start_time();

}

/* Funzione : set_timeout(uint32 timeout)
 * Parametri: timeout: tempo espresso in secondi dopo il quale il nodo si sincronizza con il server
 * @brief : Settaggio del timeout per la risincronizzazione
 *
 * */
void set_timeout(uint32_t timeout){
	_timeout = timeout;
}

/* Funzione: set_time(sys_time _time)
 * Parametri:
 * 		sys_time _time : tempo di riferimento a cui settare il tempo di sistema
 *
 * @brief : Settaggio tempo di sistema
 *
 * */
void set_time(sys_time time){

	suspend_time();

	_sys_time.year 		= 	 time.year;
	_sys_time.month 	=	 time.month;
	_sys_time.day 		=	 time.day;
	_sys_time.hour 		=	 time.hour;
	_sys_time.minutes 	= 	 time.minutes;
	_sys_time.seconds 	= 	 time.seconds;
	_sys_time.milliseconds = time.milliseconds;

	start_time();

}

#if TIME_SERVER==1
/* Funzione: host_send_time(uint8_t client_id)
 * Parametri: client_id: id del nodo che ha effettuato la richiesta
 * @brief : invia a client_id il valore dell'orologio di sistema dell'host
 *
 * */
void host_send_time(uint8_t client_id){

sys_time temp;

	temp.year =		_sys_time.year;
	temp.month = 	_sys_time.month;
	temp.day = 		_sys_time.day;
	temp.hour = 	_sys_time.hour;
	temp.minutes = 	_sys_time.minutes;
	temp.seconds = 	_sys_time.seconds;
	temp.milliseconds = _sys_time.milliseconds;

	//impacchettamento
	//network_level_send_time(node_id, &temp);

}
#else

/* Funzione: client_request_time(uint8_t client_id)
 * Parametri: client_id: id del nodo che effettua la richiesta
 * @brief : chiede all'host di sincronizzare gli orologi
 *
 * */
void client_sync_time(sys_time temp){


	suspend_time();



	sync_end = HAL_GetTick();

	uint16_t delay = (sync_end - sync_init) / 2;

	uint16_t delay_millis;
	uint8_t delay_sec;


	if(delay >= 1000){

		delay_millis = delay%1000;
		delay_sec = (int) (delay/1000);

	}
	else{
		delay_millis = delay;
		delay_sec = 0;
	}


	if((temp.milliseconds+=delay_millis) >= 1000){
		_sys_time.milliseconds = temp.milliseconds - 1000;
					if (++_sys_time.seconds % 60 == 0) { /*Incrementa secondi. Se sono arrivati a 60 ==> ho contato 1 minuto*/

						_sys_time.seconds = 0;
						if (++_sys_time.minutes % 60 == 0) { /*Incrementa minuti. Se sono arrivati a 60 ==> ho contato 1 ora*/

							_sys_time.minutes = 0;
							if (++_sys_time.hour % 24 == 0) { /*Incrementa ore. Se sono arrivate a 24 ==> ho contato 1 giorno*/

								_sys_time.hour = 0;
								_sys_time.day++; /*Incrementa giorni.*/

								/*Controlla valore del giorno a seconda del mese per capire se si deve incrementare il mese*/

								if (((_sys_time.month & 1) && (_sys_time.month < 8)) || //gennaio, marzo, maggio ,luglio,
										(!(_sys_time.month & 1)
												&& (_sys_time.month >= 8))) { //agosto, ottobre, dicembre

									if (_sys_time.day % 32 == 0) {
										_sys_time.day = 1;
										_sys_time.month++;
									}
								} else if (_sys_time.month == 2) {			//febbraio

									if (_sys_time.day % 29 == 0) {
										_sys_time.day = 1;
										_sys_time.month++;
									}

								} else {
									if (_sys_time.day % 31 == 0) {		//restanti mesi
										_sys_time.day = 1;
										_sys_time.month++;
									}
								}

								if (_sys_time.month % 13 == 0) {//Se i mesi sono arrivati a 12 ==> ho contato un anno

									_sys_time.month = 1;
									_sys_time.year++;

								}

							}

						}
					}
				}


	if ((temp.seconds += delay_sec) >= 60) {
		_sys_time.seconds = temp.seconds - 60;
		if (++_sys_time.minutes % 60 == 0) { /*Incrementa minuti. Se sono arrivati a 60 ==> ho contato 1 ora*/

			_sys_time.minutes = 0;
			if (++_sys_time.hour % 24 == 0) { /*Incrementa ore. Se sono arrivate a 24 ==> ho contato 1 giorno*/

				_sys_time.hour = 0;
				_sys_time.day++; /*Incrementa giorni.*/

				/*Controlla valore del giorno a seconda del mese per capire se si deve incrementare il mese*/

				if (((_sys_time.month & 1) && (_sys_time.month < 8)) || //gennaio, marzo, maggio ,luglio,
						(!(_sys_time.month & 1) && (_sys_time.month >= 8))) { //agosto, ottobre, dicembre

					if (_sys_time.day % 32 == 0) {
						_sys_time.day = 1;
						_sys_time.month++;
					}
				} else if (_sys_time.month == 2) {			//febbraio

					if (_sys_time.day % 29 == 0) {
						_sys_time.day = 1;
						_sys_time.month++;
					}

				} else {
					if (_sys_time.day % 31 == 0) {		//restanti mesi
						_sys_time.day = 1;
						_sys_time.month++;
					}
				}

				if (_sys_time.month % 13 == 0) {//Se i mesi sono arrivati a 12 ==> ho contato un anno

					_sys_time.month = 1;
					_sys_time.year++;

				}

			}

		}
	}
	start_time();

}

/* Funzione: client_process()
 *
 * @brief : processo client che allo scadere di ogni timeout chiede la sincronizzazione del server
 *
 * */
#endif

/* Funzione: Time_SYSTICK_Callback(void)
 * @brief : callback per il systick che incrementa, sulla base del tick di sitema, l'orologio
 *
 * */
void IncTime(void) {

	if (is_time_enabled()) {

		BSP_LED_Toggle(LED4);
		if (++_sys_time.milliseconds % 1000 == 0) { /*Incrementa millisecondi. Se sono arrivati a 1000 ==> ho contato 1 secondo*/

			BSP_LED_Toggle(LED6);
#if TIME_SERVER==0
			_count++;
#endif
			_sys_time.milliseconds = 0;
			if (++_sys_time.seconds % 60 == 0) { /*Incrementa secondi. Se sono arrivati a 60 ==> ho contato 1 minuto*/

				BSP_LED_Toggle(LED5);
				_sys_time.seconds = 0;
				if (++_sys_time.minutes % 60 == 0) { /*Incrementa minuti. Se sono arrivati a 60 ==> ho contato 1 ora*/

					_sys_time.minutes = 0;
					if (++_sys_time.hour % 24 == 0) { /*Incrementa ore. Se sono arrivate a 24 ==> ho contato 1 giorno*/

						BSP_LED_Toggle(LED3);
						_sys_time.hour = 0;
						_sys_time.day++; /*Incrementa giorni.*/

						/*Controlla valore del giorno a seconda del mese per capire se si deve incrementare il mese*/

						if (((_sys_time.month & 1) && (_sys_time.month < 8)) || //gennaio, marzo, maggio ,luglio,
								(!(_sys_time.month & 1)
										&& (_sys_time.month >= 8))) { //agosto, ottobre, dicembre

							if (_sys_time.day % 32 == 0) {
								_sys_time.day = 1;
								_sys_time.month++;
							}
						} else if (_sys_time.month == 2) {			//febbraio

							if (_sys_time.day % 29 == 0) {
								_sys_time.day = 1;
								_sys_time.month++;
							}

						} else {
							if (_sys_time.day % 31 == 0) {		//restanti mesi
								_sys_time.day = 1;
								_sys_time.month++;
							}
						}

						if (_sys_time.month % 13 == 0) {//Se i mesi sono arrivati a 12 ==> ho contato un anno

							_sys_time.month = 1;
							_sys_time.year++;

						}

					}

				}
			}
		}

	}
#if TIME_SERVER == 0

	if( _count == _timeout ){
		_count = 0;
		sync_init = HAL_GetTick();
		//impacchetamento
		//send();



	}
#endif

} // end callback

/* Funzione: is_time_enabled()
 * @brief : ritorna 1 se il conteggio del tempo è abilitato, 0 altrimenti
 *
 * */
uint8_t is_time_enabled(){ return time_enabled;}

/* Funzione: start_time()
 *
 * @brief : (ri)abilita il conteggio del tempo di sistema
 *
 * */
void start_time(){
	time_enabled = 1;
}

/* Funzione: start_time()
 *
 * @brief : disabilita il conteggio del tempo di sistema
 *
 * */
void suspend_time(){
	time_enabled = 0;
}



