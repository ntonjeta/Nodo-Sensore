//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "diag/Trace.h"
#include "security.h"
#include "applicationConfig.h"
#include "libUART.h"
//#include "projdefs.h"
#include "applayer.h"
#include "FreeRTOS.h"
#include "queue.h"

#ifdef CENTRAL_NODE
#include "hashTable.h"
#endif /* CENTRAL_NODE */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#ifdef CENTRAL_NODE
static whiteList wl;
#endif /* CENTRAL_NODE */

#ifdef OPERATIVE_NODE
extern xQueueHandle SN_mng_queue;
#endif /* OPERATIVE_NODE */


//timestamp
static uint32 timestamp = 0;

//id univoco scheda
uint32_t* STM32_UUID = (uint32_t*)0x1FFF7A10;

static SEC_ApplicationFrameTypedef frame;

byte secret[SECRETLEN];
SEC_cryp_handle sch;
SEC_HMAC_handle shh;

HAL_StatusTypeDef receive(){
	return usart_receive();
}
HAL_StatusTypeDef send(void* frame/*,uint16_t size*/){
	return usart_send(frame);
}

void initialize(){

	sch.algorithm = CRYPTO_ALGORITHM;

#ifdef OPERATIVE_NODE
	sch.key = key;
	sch.iv = key;
#endif

	sch.keylen = KEYLEN;

	shh.algorithm = HASH_ALGORITHM;
	shh.secretlen = SECRETLEN;
	shh.secret = secret;

#ifdef CENTRAL_NODE

	//inizializzo a zero il riempimento della whitelist
	WLriemp = 0;

	cleanVector(wl,N*sizeof(SEC_hashTableTypedef));
	//scheda 9
	insertNode(&wl, "\x29\x00\x2b\x00\x06\x47\x32\x35\x31\x38\x31\x30", "1234567891234567" );

	//genarazione segreto per HMAC
	SEC_RVG_handle srgvh;
	SEC_GenarateRandomValue_CustomLength(&srgvh,secret,SECRETLEN/4);
	timestamp = 1;

#endif /* CENTRAL_NODE */

	//attiva le interruzioni dal livello sottostante per la ricezione di un pacchetto
	receive();

}

void netLevelCallback(uint8_t *pData){
	cleanVector((uint8*)&frame,sizeof(frame));
	memcpy(&(frame.ID),pData,FRAMEIDLEN);
	memcpy(frame.sourceID,(pData+FRAMEIDLEN),IDLEN);
	memcpy(frame.timestamp,(pData+FRAMEIDLEN+IDLEN),TIMESTAMPLEN);
	memcpy(frame.msg,(pData+FRAMEIDLEN+IDLEN+TIMESTAMPLEN),MAX_LENGTH);
	memcpy(frame.digest,(pData+FRAMEIDLEN+IDLEN+TIMESTAMPLEN+MAX_LENGTH),DIGESTLEN);

	switch(frame.ID){
	case SEC_JOIN_REQ:

#ifdef CENTRAL_NODE
		onJoinRequest();
#endif /* CENTRAL_NODE */
		break;

	case SEC_JOIN_RES:

#ifdef OPERATIVE_NODE
		onJoinResponse(&sch,&shh);
#endif /* OPERATIVE_NODE */
		break;

	case SEC_JOIN_ACK:

#ifdef CENTRAL_NODE
		onJoinAck();
#endif /* CENTRAL_NODE */

		break;
	case SEC_SECRETCHANGE_START: 	// X protocollo di aggiornamento

#ifdef OPERATIVE_NODE

		onSecretChangeStart();
#endif /* OPERATIVE_NODE */
		break;
	case SEC_SECRETCHANGE_ACK: 		// X protocollo di aggiornamento

#ifdef CENTRAL_NODE

		onSecretChangeAck();

#endif /* CENTRAL_NODE */

		break;
	case SEC_SECRETCHANGE_OK: 	// X protocollo di aggiornamento

#ifdef OPERATIVE_NODE

		onSecretChangeOk();
#endif /* OPERATIVE_NODE */
		break;

	default: //arriva frame "dati"

#ifdef OPERATIVE_NODE
		onDataPacketReceived();
#endif /* OPERATIVE_NODE */


	}
}
#ifdef OPERATIVE_NODE

/*funzione di invio della prima frame da parte del nodo operativo
 * per connettersi alla retefunzione per creare il messaggio cifrato da inserire
 * nella prima frame*/
void joinRequest() {

	frame.ID=SEC_JOIN_REQ;
	memcpy(frame.sourceID, STM32_UUID, IDLEN);

	// creazione del msg cifrato con all'interno l'ID della scheda
	uint32 ciplen;
	SEC_Encrypt(&sch,frame.sourceID,IDLEN,frame.msg,&ciplen);

	send(&frame);
}

#endif /* OPERATIVE_NODE */

#ifdef CENTRAL_NODE
void onJoinRequest() {

	/* all'atto di una richiesta:
	 * 		- in base al mittente prelevo la chiave in tabella
	 * 		- decifro il messaggio con la chiave prelevata
	 * 		- costruisco il pacchetto di risposta col segreto cifrato
	 * 		- invio il pacchetto cifrato e firmato
	 */

	if (!checkAckByID(&wl, frame.sourceID)) {

		sch.key = SearchKeyByID(&wl, frame.sourceID);
		sch.iv = sch.key;

		//il messaggio conterra' l'id che e' di 12 byte ma AES lavora con blocchi da 16
		uint32 ciplen = 16;
		uint8 plain[16];
		uint32 plainlen;
		SEC_StateTypeDef stato;
		stato = SEC_Decrypt(&sch, frame.msg, ciplen, plain, &plainlen);

		int result = memcmp(plain, frame.sourceID, IDLEN);

		if (result == 0) {
			//Costruisco il pacchetto di risposta della JOIN
			cleanVector((uint8*) &frame, sizeof(frame));
			uint32 ciphertextLen;
			SEC_Encrypt(&sch, secret, SECRETLEN, frame.msg, &ciphertextLen);

			frame.ID = SEC_JOIN_RES;
			memcpy(frame.sourceID, STM32_UUID, IDLEN);
			memcpy(frame.timestamp, &timestamp,TIMESTAMPLEN);
			timestamp++;
			SEC_HMAC(&shh, (uint8*) &frame, HMAC_LENGTH, frame.digest);
			send((uint8*) &frame);
		}
	} else {
		/* utente gi������ presente in rete (gi������ ������ stato ricevuto l'ack) oppure non in whitelist.
		 * invia un alert all'amministratore che deve controllare se il nodo ������ fidato e, quindi,
		 * pu������ riattivarlo (mettendo il campo 'ack' a 0) oppure si tratta di un tentativo
		 * malevolo di accedere alla rete */
	}
}

#endif /*CENTRAL_NODE*/

#ifdef OPERATIVE_NODE

/*funzione di ricezione della frame inviata dal nodo di controllo
 * contenente il segreto cifrato
 */
void onJoinResponse(){

	if(!memcmp(frame.sourceID,IDCONTROLLO,IDLEN) && *((uint32_t*)frame.timestamp)>timestamp){

		uint32 cipherlen=SECRETLEN;

		//decifratura del msg e inserimento del segreto nella struttura SEC_HMAC_handle
		if(SEC_Decrypt(&sch,frame.msg,cipherlen,shh.secret,&(shh.secretlen)) != SEC_STATE_OK){
			//LOG
		}

		if(SEC_HMAC_verify(&shh,&frame,HMAC_LENGTH,frame.digest)==SEC_STATE_HMAC_VERIFY_OK){

			timestamp = *((uint32_t*)frame.timestamp);
			cleanVector(&frame,sizeof(frame));
			//preparo la frame di ack
			frame.ID=SEC_JOIN_ACK;
			memcpy(frame.sourceID, STM32_UUID, IDLEN);
			//	memcpy(frame.msg, STM32_UUID, IDLEN);

			SEC_HMAC(&shh,&frame,HMAC_LENGTH,frame.digest);


			// invio la frame di ack
			send(&frame);

		}else{
			//hmac non verificato: rifiuta il segreto e ricomincio la procedura di join
			cleanVector(shh.secret,SECRETLEN);
			joinRequest();
		}
	}
	//identita' non verificata, faccio qualcosa

}

#endif /* OPERATIVE_NODE */

#ifdef CENTRAL_NODE

void onJoinAck() {

	/* all'atto della ricezione dell'ack
	 * 		- verifica HMAC
	 * 		- cerca nella whitelist l'id corrispondente al campo sourceID
	 * 		- check flag 'ack'
	 */

	if (SEC_HMAC_verify(&shh, (uint8_t*)&frame, HMAC_LENGTH, frame.digest) == SEC_STATE_HMAC_VERIFY_OK) {
		if(!setAckByID(&wl, frame.sourceID)){
			//LOG
		}
		secretChangeStart();
	}
}

//funzione di inizio protocollo cambio segreto
void secretChangeStart(){
	//	Frame CAMBIO SEGRETO
	//	1.ID Frame=0xAA
	//	2.ID Source=Controllo
	//	3.Set timestamp (e post incremento)
	//	4.Msg vuoto
	//	5.Calcolo HMAC con il vecchio segreto��
	//	6.Invio frame

	int i=0;
	for(i=0;i<N;i++){
		if(wl[i].ack == (byte)1){
			frame.ID=SEC_SECRETCHANGE_START;
			memcpy(frame.sourceID, STM32_UUID, IDLEN);
			memcpy(frame.timestamp, &timestamp,TIMESTAMPLEN);
			timestamp++;
			SEC_HMAC(&shh,&frame,HMAC_LENGTH,frame.digest);
			send((uint8*) &frame);
		}
	}

}

#endif /* CENTRAL_NODE */

#ifdef OPERATIVE_NODE

/*funzione di ricezione della frame inviata dal nodo di controllo
 * contenente "l'intenzione" di cambiare il segreto
 */
//		Quando il nodo OPERATIVO riceve la frame di CAMBIO SEGRETO start(guarda l��� ID frame):
//		SE "ID Source==ID_CONTROLLO��� && CheckTimestamp==OK
//		Verifica dell���HMAC(attraverso la verify con il vecchio segreto )
//		SE la verifica �� OK allora prepara la "Frame di ACK���
//		Salva la coppia TIMESTAMP per evitare replay attack
void onSecretChangeStart(){

	if(!memcmp(frame.sourceID,IDCONTROLLO,IDLEN) && *((uint32_t*)frame.timestamp)>timestamp){

		if(SEC_HMAC_verify(&shh,&frame,HMAC_LENGTH,frame.digest)==SEC_STATE_HMAC_VERIFY_OK){

			timestamp = *((uint32_t*)frame.timestamp);
			cleanVector(&frame,sizeof(frame));
			//preparo la Frame di ACK:
			//				ID Frame=0xAB
			//				ID Source=ID NODO OPERATIVO
			//				Msg=
			//				Calcolo HMAC con il vecchio segreto

			frame.ID=SEC_SECRETCHANGE_ACK;
			memcpy(frame.sourceID, STM32_UUID, IDLEN);
			//	memcpy(frame.msg, STM32_UUID, IDLEN);
			SEC_HMAC(&shh,&frame,HMAC_LENGTH,frame.digest);


			// invio la frame di ack
			send(&frame);

		}else{
			//LOG
		}

	}
	//identita' non verificata oppure reply attack (timestamp non valido)

}

#endif /* OPERATIVE_NODE */

#ifdef CENTRAL_NODE

void onSecretChangeAck(){
	//		Quando il nodo CONTROLLO riceve la frame di ACK (guarda l��� ID frame):
	//		SE Check_ACK_By_IDsource==1 (ovvero �� la prima volta che ricevo questo tipo di frame da questo SOURCE)
	//		Verifica dell���HMAC(attraverso la verify con il vecchio segreto)
	//		SE la verifica �� OK
	//		allora ClearAckBy_IdSource, azzero il bit nella tabella
	//		SE Is_LastAck()==SI
	//		allora prepara la frame di AckRESET_RETE



	if(checkAckByID(&wl, frame.sourceID)==1){

		if(SEC_HMAC_verify(&shh,&frame,HMAC_LENGTH,frame.digest)==SEC_STATE_HMAC_VERIFY_OK){

			clearAckByID(&wl, frame.sourceID);

			if(checkAllzeroAck(&wl)==1){
				//				preparo la Frame di AckRESET_NETWORK:
				//							Frame AckRESET_RETE:
				//								ID Frame=0xAC
				//								ID Source=ID NODO CONTROLLO
				//								Msg = contiene il timestamp cifrato con la chiave di ogni nodo
				//										NON �� Firmato(perche' i nodi router potrebbero ottenere per primi
				//												il nuovo segreto e non inoltrare i pacchetti in caso di ritrasmissione)


				//genarazione nuovo segreto per HMAC
				SEC_RVG_handle srgvh;
				SEC_GenarateRandomValue_CustomLength(&srgvh,secret,SECRETLEN/4);

				int i=0;
				for(i=0;i<N;i++){
					if(*(wl[i].id) != 0){
						frame.ID=SEC_SECRETCHANGE_OK;
						sch.key = wl[i].key;
						sch.iv = sch.key;
						memcpy(frame.sourceID, STM32_UUID, IDLEN);
						memcpy(frame.timestamp, &timestamp,TIMESTAMPLEN);
						uint32 ciphertextLen;
						SEC_Encrypt(&sch, (uint8_t*)(&timestamp), TIMESTAMPLEN, frame.msg, &ciphertextLen);
						timestamp++;
						send((uint8*) &frame);
					}
				}



			}

		}else{	/*hmac non verificato*/}

	}else{
		// il flag di ack �� a zero quindi ho gi�� ricevuto questo tipo di frame
	}
}

#endif /* CENTRAL_NODE */

#ifdef OPERATIVE_NODE

/*funzione di ricezione della frame inviata dal nodo di controllo
 * contenente l'ok per far partire di nuovo il Join Protocol
 */
void onSecretChangeOk(){
	//	Quando il nodo OPERATIVO riceve la frame di CHANGE OK(guarda l��� ID frame):
	//	SE "ID Source==ID_CONTROLLO���
	//	Decifra il msg
	//	Parsing del MSG che dovr�� avere un TIMESTAMP valido
	//	se CheckTimestamp �� OK
	//	CHIAMA La JOINREQUEST

	if(!memcmp(frame.sourceID,IDCONTROLLO,IDLEN) ){

		uint32 cipherlen = TIMESTAMPLEN;
		uint32 plaintextlen;

		byte in[MAX_LENGTH];
		memcpy(in,frame.msg,MAX_LENGTH);

		//conterr�� il messaggio in chiaro (mi aspetto un timestamp valido)
		uint32_t plaintext;
		//decifratura del msg
		if(SEC_Decrypt(&sch,in,cipherlen,(uint8_t*)(&plaintext),&plaintextlen) != SEC_STATE_OK){
			//LOG
		}

		//se il timestamp �� valido
		if(plaintext>timestamp){
			//lo salvo e inizio la join
			timestamp = plaintext;
			joinRequest();
		}


	}
	else{
		//identita' non verificata, faccio qualcosa
	}

}
#endif /* OPERATIVE_NODE */

#ifdef OPERATIVE_NODE
void onDataPacketReceived(){
	if(SEC_HMAC_verify(&shh,&frame,HMAC_LENGTH,frame.digest)==SEC_STATE_HMAC_VERIFY_OK){
		//		xQueueSendToBack(SN_tx_queue,&ap_package,MAX_WAIT);
		NetPackage pNetPackage;
		memcpy(&pNetPackage,frame.msg,16);
		xQueueSendFromISR(SN_mng_queue , &pNetPackage, 0);
	}
	else{
		//Butta la frame
		//LOG
	}
}
#endif /* OPERATIVE_NODE */

#ifdef OPERATIVE_NODE
/*Funzione di invio frame Dati*/
void sendDataPacket(void *data){

	SEC_ApplicationFrameTypedef* frameTmp = (SEC_ApplicationFrameTypedef*)malloc(sizeof(SEC_ApplicationFrameTypedef));
	cleanVector(frameTmp,sizeof(SEC_ApplicationFrameTypedef));
	//preparo la frame dati
	frameTmp->ID=DATA_FRAME;
	memcpy(frameTmp->sourceID, STM32_UUID, IDLEN);
	memcpy(frameTmp->msg, data, MAX_LENGTH);

	SEC_HMAC(&shh,frameTmp,HMAC_LENGTH,frameTmp->digest);

	// invio la frame di ack
	send(frameTmp);
}
#endif /* OPERATIVE_NODE */


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
