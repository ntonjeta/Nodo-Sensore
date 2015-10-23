/**
 * \file security.c
 *
 * \brief Funzioni di sicurezza [descrizione da modificare]
 *
 * \author Gruppo 1
 */

#include "security.h"

/**
 * \brief 	Funzione per la cifratura
 * \param[in,out] 	sch:				Struttura di ausilio alle funzioni di crittografia
 * \param[in]		plaintext: 			Puntatore alla variabile che contiene il testo in chiaro
 * \param[in]		plaintext_length: 	Lunghezza del testo in chiaro
 * \param[out]		ciphertext:			Puntatore alla variabile che contiene il testo cifrato
 * \param[out]		ciphertext_length:	Puntatore alla variabile che contiene la lunghezza del testo cifrato
 * \retval			SEC state
 */
SEC_StateTypeDef SEC_Encrypt(
		SEC_cryp_handle *sch,
		uint8 *plaintext,
		uint32 plaintext_length,
		uint8 *ciphertext,
		uint32 *ciphertext_length
)
{
	SEC_StateTypeDef state = SEC_STATE_GENERIC_ERROR;
	uint8 *key = sch->key;
	uint8 *iv = sch->iv;
	uint32 keylen = sch->keylen;
	SEC_CRYP_AlgorithmTypeDef algorithm = sch->algorithm;

#ifdef SEC_MEASURE_TIMES
	/*Abilitazione del DWT e RESET del CYCCNT*/
	DWT_RESET_CYCLECOUNTER
#endif

	/*scelta dell'algoritmo di cifratura a seconda del campo algorithm*/
	switch(algorithm){

	case SEC_AES128:{
		Aes enc;
		unsigned int dim=16;
		if (!key || !iv ||wc_AesSetKey(&enc, key, dim, iv, AES_ENCRYPTION)!= 0){
			/*se non c'è la chiave o l'iv, oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if (keylen!=dim){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* AES accetta ingressi di lunghezza pari a multipli di 16 byte (blocchi di 128 bit).
		 * Se il messaggio ha una lunghezza non corretta viene utilizzato un padding (valori 0x00)*/
		int padding_length = plaintext_length%16==0? 0:16-plaintext_length%16;
		uint8 text[plaintext_length+padding_length];

		//inizializzazione del vettore con valori 0x00
		cleanVector(text,plaintext_length+padding_length);

		//viene copiato il testo in chiaro nel vettore da dare in pasto all'algoritmo
		memcpy(text,plaintext,plaintext_length);
		plaintext_length += padding_length;

		//controllo sulla funzione di cifratura
		int encrypt_result = wc_AesCbcEncrypt(&enc, ciphertext, text, plaintext_length);
		if (encrypt_result != 0){
			state = SEC_STATE_ENCRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*ciphertext_length = plaintext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;
		break;

	}
	case SEC_AES192:{
		Aes enc;
		unsigned int dim=24;
		if (!key || !iv ||wc_AesSetKey(&enc, key, dim, iv, AES_ENCRYPTION)!= 0){
			/*se non c'è la chiave o l'iv, oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if (keylen!=dim){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* AES accetta ingressi di lunghezza pari a multipli di 16 byte (blocchi di 128 bit).
		 * Se il messaggio ha una lunghezza non corretta viene utilizzato un padding (valori 0x00)*/
		int padding_length = plaintext_length%16==0? 0:16-plaintext_length%16;
		uint8 text[plaintext_length+padding_length];

		//inizializzazione del vettore con valori 0x00
		cleanVector(text,plaintext_length+padding_length);

		//viene copiato il testo in chiaro nel vettore da dare in pasto all'algoritmo
		memcpy(text,plaintext,plaintext_length);
		plaintext_length += padding_length;

		//controllo sulla funzione di cifratura
		int encrypt_result = wc_AesCbcEncrypt(&enc, ciphertext, text, plaintext_length);
		if (encrypt_result != 0){
			state = SEC_STATE_ENCRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*ciphertext_length = plaintext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;
		break;

	}
	case SEC_AES256:{
		Aes enc;
		unsigned int dim=32;
		if (!key || !iv ||wc_AesSetKey(&enc, key, dim, iv, AES_ENCRYPTION)!= 0){
			/*se non c'è la chiave o l'iv, oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if (keylen!=dim){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* AES accetta ingressi di lunghezza pari a multipli di 16 byte (blocchi di 128 bit).
		 * Se il messaggio ha una lunghezza non corretta viene utilizzato un padding (valori 0x00)*/
		int padding_length = plaintext_length%16==0? 0:16-plaintext_length%16;
		uint8 text[plaintext_length+padding_length];

		//inizializzazione del vettore con valori 0x00
		cleanVector(text,plaintext_length+padding_length);

		//viene copiato il testo in chiaro nel vettore da dare in pasto all'algoritmo
		memcpy(text,plaintext,plaintext_length);
		plaintext_length += padding_length;

		//controllo sulla funzione di cifratura
		int encrypt_result = wc_AesCbcEncrypt(&enc, ciphertext, text, plaintext_length);
		if (encrypt_result != 0){
			state = SEC_STATE_ENCRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*ciphertext_length = plaintext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;
		break;

	}
	case SEC_DES3:{
		Des3 enc;

		if (!key || wc_Des3_SetKey(&enc, key, iv, DES_ENCRYPTION) != 0){
			/*se non c'è la chiave oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if (keylen != 24){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* DES3 accetta ingressi di lunghezza pari a multipli di 8 byte (blocchi di 64 bit).
		 * Se il messaggio ha una lunghezza non corretta viene utilizzato un padding (valori 0x00)*/
		int padding_length = plaintext_length%8==0? 0:8-plaintext_length%8;
		uint8 text[plaintext_length+padding_length];

		//inizializzazione del vettore con valori 0x00
		cleanVector(text,plaintext_length+padding_length);

		//viene copiato il testo in chiaro nel vettore da dare in pasto all'algoritmo
		memcpy(text,plaintext,plaintext_length);
		plaintext_length += padding_length;

		//controllo sulla funzione di cifratura
		if (wc_Des3_CbcEncrypt(&enc, ciphertext, text, plaintext_length) != 0){
			state = SEC_STATE_ENCRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*ciphertext_length = plaintext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;
		break;
	}
	case SEC_ARC4:{

		Arc4 enc;

		if (!key){
			/*se non c'è la chiave lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if (keylen<=0){
			/*se la lunghezza della chiave non è positiva
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/*settaggio della chiave e cifratura*/
		wc_Arc4SetKey(&enc, key, keylen);
		wc_Arc4Process(&enc, ciphertext, plaintext,	plaintext_length);

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*ciphertext_length = plaintext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;

		break;
	}

	/*caso di default dello switch*/
	default:
		break;
	}

#ifdef SEC_MEASURE_TIMES
	// Il numero di cicli di clock sono salvati nel registro DWT->CYCCNT
	sch->execTime_clockCycles = DWT->CYCCNT;
	sch->execTime_ns=CalcNanosecondsFromStopwatch(sch->execTime_clockCycles);
	/*Disabilitazione del contatore*/
	DWT_STOP_CYCLECOUNTER
#endif
	return state;

}

/**
 * \brief 	Funzione per la decifratura
 * \param[in,out] 	sch:				Struttura di ausilio alle funzioni di crittografia
 * \param[in]		ciphertext:			Puntatore alla variabile che contiene il testo cifrato
 * \param[in]		ciphertext_length:	Lunghezza del testo cifrato
 * \param[out]		plaintext: 			Puntatore alla variabile che contiene il testo in chiaro
 * \param[out]		plaintext_length: 	Puntatore alla variabile che contiene la lunghezza del testo in chiaro
 * \retval			SEC state
 */
SEC_StateTypeDef SEC_Decrypt(
		SEC_cryp_handle *sch,
		uint8 *ciphertext,
		uint32 ciphertext_length,
		uint8 *plaintext,
		uint32 *plaintext_length
){

	SEC_StateTypeDef state = SEC_STATE_GENERIC_ERROR;
	uint8 *key = sch->key;
	uint8 *iv = sch->iv;
	uint32 keylen = sch->keylen;
	SEC_CRYP_AlgorithmTypeDef algorithm = sch->algorithm;

#ifdef SEC_MEASURE_TIMES
	// Abilitazione del DWT e RESET del CYCCNT
	DWT_RESET_CYCLECOUNTER
#endif

	/*scelta dell'algoritmo di decifratura a seconda del campo algorithm*/
	switch(algorithm){
	case SEC_AES128:
	{
		Aes dec;
		unsigned int dim=16;

		if (!key || !iv ||wc_AesSetKey(&dec, key, dim, iv, AES_DECRYPTION)){
			/*se non c'è la chiave o l'iv, oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore*/
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if(	keylen!=dim){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* AES accetta ingressi di lunghezza pari a multipli di 16 byte (blocchi di 128 bit).
		 * Se il messaggio ha una lunghezza non corretta viene cambiata*/
		int padding_length = ciphertext_length%16==0? 0:16-ciphertext_length%16;

		ciphertext_length += padding_length;

		//controllo sulla funzione di decifratura
		if (wc_AesCbcDecrypt(&dec, plaintext, ciphertext, ciphertext_length)!=0){
			state = SEC_STATE_DECRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*plaintext_length = ciphertext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;

		break;
	}
	case SEC_AES192:

	{
		Aes dec;
		unsigned int dim=24;
		if (!key || !iv ||wc_AesSetKey(&dec, key, dim, iv, AES_DECRYPTION)){
			/*se non c'è la chiave o l'iv, oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if(	keylen!=dim){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* AES accetta ingressi di lunghezza pari a multipli di 16 byte (blocchi di 128 bit).
		 * Se il messaggio ha una lunghezza non corretta viene cambiata*/
		int padding_length = ciphertext_length%16==0? 0:16-ciphertext_length%16;

		ciphertext_length += padding_length;

		//controllo sulla funzione di decifratura
		if (wc_AesCbcDecrypt(&dec, plaintext, ciphertext, ciphertext_length)!=0){
			state = SEC_STATE_DECRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*plaintext_length = ciphertext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;

		break;
	}
	case SEC_AES256:

	{
		Aes dec;
		unsigned int dim=32;
		if (!key || !iv ||wc_AesSetKey(&dec, key, dim, iv, AES_DECRYPTION)){
			/*se non c'è la chiave o l'iv, oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if(	keylen!=dim){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* AES accetta ingressi di lunghezza pari a multipli di 16 byte (blocchi di 128 bit).
		 * Se il messaggio ha una lunghezza non corretta viene cambiata*/
		int padding_length = ciphertext_length%16==0? 0:16-ciphertext_length%16;

		ciphertext_length += padding_length;

		//controllo sulla funzione di decifratura
		if (wc_AesCbcDecrypt(&dec, plaintext, ciphertext, ciphertext_length)!=0){
			state = SEC_STATE_DECRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*plaintext_length = ciphertext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;

		break;
	}
	case SEC_DES3:
	{
		Des3 dec ;

		if (!key || wc_Des3_SetKey(&dec, key, iv, DES_DECRYPTION) != 0){
			/*se non c'è la chiave oppure la SetKey restituisce errore
			 * lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if (keylen != 24){
			/*se la lunghezza della chiave è diversa dalla dimensione attesa
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/* DES3 accetta ingressi di lunghezza pari a multipli di 8 byte (blocchi di 64 bit).
		 * Se il messaggio ha una lunghezza non corretta viene utilizzato un padding (valori 0x00)*/
		int padding_length = ciphertext_length%8==0? 0:8-ciphertext_length%8;

		ciphertext_length += padding_length;

		//controllo sulla funzione di decifratura
		if (wc_Des3_CbcDecrypt(&dec, plaintext, ciphertext, ciphertext_length) != 0){
			state = SEC_STATE_DECRYPT_ERROR;
			break;
		}

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*plaintext_length = ciphertext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;
		break;
	}
	case SEC_ARC4:{

		Arc4 dec;

		if (!key){
			/*se non c'è la chiave lo stato viene settato ad errore	 */
			state = SEC_STATE_SETKEY_ERROR;
			break;
		}
		if (keylen<=0){
			/*se la lunghezza della chiave non è positiva
			 * viene impostato un warning, ma l'esecuzione non termina */
			state = SEC_STATE_SIZEKEY_WARNING;
		}

		/*settaggio della chiave e decifratura*/
		wc_Arc4SetKey(&dec, key, keylen);
		wc_Arc4Process(&dec, plaintext, ciphertext, ciphertext_length);

		/*la lunghezza del testo cifrato è uguale a quella del testo in chiaro*/
		*plaintext_length = ciphertext_length;

		/*se non ci sono warning o errori, la procedura è corretta*/
		if(state != SEC_STATE_SIZEKEY_WARNING )
			state = SEC_STATE_OK;

		break;
	}

	/*caso di default dello switch*/
	default:
		break;
	}

#ifdef SEC_MEASURE_TIMES
	// Il numero di cicli di clock sono salvati nel registro DWT->CYCCNT
	sch->execTime_clockCycles = DWT->CYCCNT;
	sch->execTime_ns=CalcNanosecondsFromStopwatch(sch->execTime_clockCycles);
	/*Disabilitazione del contatore*/
	DWT_STOP_CYCLECOUNTER
#endif
	return state;

}

/**
 * \brief 	Funzione per il calcolo del HMAC
 * \param[in,out] 	shh:				Struttura di ausilio per HMAC
 * \param[in]		plaintext:			Puntatore alla variabile che contiene il testo in chiaro
 * \param[in]		plaintext_length:	Lunghezza del testo in chiaro
 * \param[out]		digest:				Puntatore alla variabile che contiene il risultato dell'operazione
 * \retval			SEC State
 */

SEC_StateTypeDef SEC_HMAC(
		SEC_HMAC_handle *shh,
		uint8 *plaintext,
		uint32 plaintext_length,
		uint8 *digest
){

	SEC_StateTypeDef state = SEC_STATE_GENERIC_ERROR;
	uint8 *secret = shh->secret;
	uint32 secretlen = shh->secretlen;
	SEC_HASH_AlgorithmTypeDef algorithm = shh->algorithm;
	uint32 type;

#ifdef SEC_MEASURE_TIMES
	// Abilitazione del DWT e RESET del CYCCNT
	DWT_RESET_CYCLECOUNTER
#endif

	/*scelta dell'algoritmo di hashing a seconda del campo algorithm*/
	switch(algorithm){

	case SEC_MD5:
		type=MD5;
		break;

	case SEC_SHA1:
		type=SHA;
		break;

	case SEC_SHA256:
		type=SHA256;
		break;

	case SEC_SHA384:
		type=SHA384;
		break;

	case SEC_SHA512:
		type=SHA512;
		break;

		/*caso di default : genera un errore nella SetKey*/
	default:
		type = 255;
		break;
	}

	Hmac hmac;

	if (!secret || wc_HmacSetKey(&hmac, type, secret,secretlen)!=0){
		/*se non c'è il segreto oppure la SetKey restituisce errore
		 * lo stato viene settato ad errore	 */
		state = SEC_STATE_HMAC_SETKEY_ERROR;
		return state;
	}
	if(secretlen<=0){
		/*se la lunghezza del segreto non è positiva
		 * viene impostato un warning, ma l'esecuzione non termina */
		state = SEC_STATE_HMAC_SIZEKEY_WARNING;
	}

	//controllo sulla funzione HMAC update
	if (wc_HmacUpdate(&hmac, plaintext, plaintext_length) != 0){
		state = SEC_STATE_HMAC_UPDATE_ERROR;
		return state;
	}

	//controllo sulla funzione HMAC final
	if (wc_HmacFinal(&hmac, digest)!= 0){
		state = SEC_STATE_HMAC_FINAL_ERROR;
		return state;
	}

#ifdef SEC_MEASURE_TIMES
	// Il numero di cicli di clock sono salvati nel registro DWT->CYCCNT
	shh->execTime_clockCycles = DWT->CYCCNT;
	shh->execTime_ns=CalcNanosecondsFromStopwatch(shh->execTime_clockCycles);
	/*Disabilitazione del contatore*/
	DWT_STOP_CYCLECOUNTER
#endif

	if(state != SEC_STATE_SIZEKEY_WARNING)
		state = SEC_STATE_OK;
	return state;



}

/**
 * \brief 	Funzione per la verifica del HMAC
 * \param[in,out] 	shh:				Struttura di ausilio per HMAC
 * \param[in]		plaintext:			Puntatore alla variabile che contiene il testo in chiaro
 * \param[in]		plaintext_length:	Lunghezza del testo in chiaro
 * \param[in]		digest:				Puntatore alla variabile che contiene il digest da verificare
 * \retval			SEC State
 */

SEC_StateTypeDef SEC_HMAC_verify(
		SEC_HMAC_handle *shh,
		uint8 *plaintext,
		uint32 plaintext_length,
		uint8 *digest // forse da mettere const
){
	SEC_StateTypeDef state = SEC_STATE_GENERIC_ERROR;
	SEC_CRYP_AlgorithmTypeDef algorithm = shh->algorithm;

#ifdef SEC_MEASURE_TIMES
	// Abilitazione del DWT e RESET del CYCCNT
	DWT_RESET_CYCLECOUNTER
#endif

	/*scelta dell'algoritmo di hashing a seconda del campo algorithm*/
	switch(algorithm){
	case SEC_MD5:
	{

		/*ricalcola il digest con lo stesso algoritmo*/
		byte newdigest[MD5_DIGEST_SIZE];
		state = SEC_HMAC(shh,plaintext,plaintext_length,newdigest);
		if( state == SEC_STATE_OK){
			/*se non ci sono stati errori nella generazione HMAC*/

			if (memcmp(digest, newdigest, MD5_DIGEST_SIZE) != 0){
				/*se la memcmp non va a buon fine
				  ritorna un errore */
				state = SEC_STATE_HMAC_VERIFY_ERROR;

			}else{
				/*altrimenti la procedura è corretta*/
				state = SEC_STATE_HMAC_VERIFY_OK;
			}

		}
		break;
	}
	case SEC_SHA1:{

		/*ricalcola il digest con lo stesso algoritmo*/
		byte newdigest[SHA_DIGEST_SIZE];
		state = SEC_HMAC(shh,plaintext,plaintext_length,newdigest);
		if( state == SEC_STATE_OK){
			/*se non ci sono stati errori nella generazione HMAC*/

			if (memcmp(digest, newdigest, SHA_DIGEST_SIZE) != 0){
				/*se la memcmp non va a buon fine
				ritorna un errore */
				state = SEC_STATE_HMAC_VERIFY_ERROR;

			}else{
				/*altrimenti la procedura è corretta*/
				state = SEC_STATE_HMAC_VERIFY_OK;
			}

		}
		break;
	}
	case SEC_SHA256:
	{

		/*ricalcola il digest con lo stesso algoritmo*/
		byte newdigest[SHA256_DIGEST_SIZE];
		state = SEC_HMAC(shh,plaintext,plaintext_length,newdigest);
		if( state == SEC_STATE_OK){
			/*se non ci sono stati errori nella generazione HMAC*/

			if (memcmp(digest, newdigest, SHA256_DIGEST_SIZE) != 0){
				/*se la memcmp non va a buon fine
				ritorna un errore */
				state = SEC_STATE_HMAC_VERIFY_ERROR;

			}else{
				/*altrimenti la procedura è corretta*/
				state = SEC_STATE_HMAC_VERIFY_OK;
			}

		}
		break;
	}
	case SEC_SHA384:
	{

		/*ricalcola il digest con lo stesso algoritmo*/
		byte newdigest[SHA384_DIGEST_SIZE];
		state = SEC_HMAC(shh,plaintext,plaintext_length,newdigest);
		if( state == SEC_STATE_OK){
			/*se non ci sono stati errori nella generazione HMAC*/

			if (memcmp(digest, newdigest, SHA384_DIGEST_SIZE) != 0){
				/*se la memcmp non va a buon fine
				ritorna un errore */
				state = SEC_STATE_HMAC_VERIFY_ERROR;

			}else{
				/*altrimenti la procedura è corretta*/
				state = SEC_STATE_HMAC_VERIFY_OK;
			}

		}
		break;
	}
	case SEC_SHA512:{

		/*ricalcola il digest con lo stesso algoritmo*/
		byte newdigest[SHA512_DIGEST_SIZE];
		state = SEC_HMAC(shh,plaintext,plaintext_length,newdigest);
		if( state == SEC_STATE_OK){
			/*se non ci sono stati errori nella generazione HMAC*/

			if (memcmp(digest, newdigest, SHA512_DIGEST_SIZE) != 0){
				/*se la memcmp non va a buon fine
				ritorna un errore */
				state = SEC_STATE_HMAC_VERIFY_ERROR;
			}else{
				/*altrimenti la procedura è corretta*/
				state = SEC_STATE_HMAC_VERIFY_OK;
			}

		}
		break;
	}
	/*caso di default dello switch : errore nel settaggio dell'algoritmo*/
	default:
		state = SEC_STATE_HMAC_ALGORITHM_ERROR;
		break;
	}
#ifdef SEC_MEASURE_TIMES
	// Il numero di cicli di clock sono salvati nel registro DWT->CYCCNT
	shh->execTime_clockCycles = DWT->CYCCNT;
	shh->execTime_ns=CalcNanosecondsFromStopwatch(shh->execTime_clockCycles);
	/*Disabilitazione del contatore*/
	DWT_STOP_CYCLECOUNTER
#endif
	return state;


}


/**
 * \brief 	Funzione per generare un valore random
 * \param[in,out] 	srgvh:		Struttura di ausilio per RNG
 * \param[out]		secret:		Puntatore alla variabile che contiene il segreto
 * \param[in]		dim:		Dimensione del segreto
 * \retval			SEC State
 */

SEC_StateTypeDef SEC_GenarateRandomValue(
		SEC_RVG_handle *srvgh,
		byte *secret,
		uint32 dim
){

	SEC_StateTypeDef state = SEC_STATE_GENERIC_ERROR;
	SEC_CRYP_AlgorithmTypeDef algorithm = srvgh->algorithm;

	RngHandle.Instance = RNG;


	if(HAL_RNG_Init(&RngHandle) != HAL_OK)
	{
		/*se l'inizializzazione della periferica non è andata
		 a buon fine, ritorna un errore */
		state = SEC_STATE_RANDOMVALUE_INIT_ERROR;
		return state;
	}

	uint32_t counter;
	state = SEC_STATE_OK;

#ifdef SEC_MEASURE_TIMES
	// Abilitazione del DWT e RESET del CYCCNT
	DWT_RESET_CYCLECOUNTER

#endif

	/*scelta della lunghezza del segreto da generare a seconda del campo algorithm*/
	switch(algorithm){

	case SEC_AES128:
		dim=4;
		break;

	case SEC_AES192:
	case SEC_DES3:
		dim=6;
		break;

	case SEC_AES256:
		dim=8;
		break;

	default:
		break;
	}

	/*a seconda della variabile dim, genera un numero casuale*/
	for(counter = 0; counter < dim; counter++)
	{
		if( HAL_RNG_GenerateRandomNumber(&RngHandle, ((uint32_t*)secret)+counter)!=HAL_OK)
			/*se la generazione del numero casuale non va a buon fine,
			 ritorna un errore */
			state = SEC_STATE_RANDOMVALUE_GENERATION_ERROR;
	}

	//deinizzializza l'RNG (DA TESTARE)
	HAL_RNG_DeInit(&RngHandle);


#ifdef SEC_MEASURE_TIMES
	// Il numero di cicli di clock sono salvati nel registro DWT->CYCCNT
	srvgh->execTime_clockCycles = DWT->CYCCNT;
	srvgh->execTime_ns=CalcNanosecondsFromStopwatch(srvgh->execTime_clockCycles);
	/*Disabilitazione del contatore*/
	DWT_STOP_CYCLECOUNTER
#endif
	return state;

}

/*Funzione utente per generare numeri casuali di dimensione basata sull'algoritmo scelto*/
SEC_StateTypeDef SEC_GenarateRandomValue_AlgorithmBased(
		SEC_RVG_handle *srgvh,
		byte *secret
)
{
	/*richiama la funzione di libreria impostando dim=0*/
	return SEC_GenarateRandomValue(srgvh,secret,0);
}

/*Funzione utente per generare numeri casuali di dimensione basata sulla scelta dell'utente*/
SEC_StateTypeDef SEC_GenarateRandomValue_CustomLength(
		SEC_RVG_handle *srgvh,
		byte *secret,
		uint32 dim
)
{
	if(srgvh)
		srgvh->algorithm = 0;
	/*richiama la funzione di libreria impostando algorithm=0*/
	return SEC_GenarateRandomValue(srgvh,secret,dim);
}

/**
 * \brief 	Funzione per generare un CRC a partire da un messaggio
 * \param[in,out] 	sch:				Struttura di ausilio per CRC
 * \param[in]		msg:				Puntatore alla variabile che contiene il messaggio di cui calcolare CRC
 * \param[in]		lenght:				Dimensione del messaggio
 * \param[out]		generatedCRC:		Puntatore alla variabile che conterra' il CRC calcolato
 * \retval			SEC State
 */
SEC_StateTypeDef SEC_GenarateCRC(
		SEC_CRC_handle *sch,
		byte *msg,
		uint32 length,
		uint32* generatedCRC
){

	*generatedCRC = 0;

	SEC_StateTypeDef state = SEC_STATE_GENERIC_ERROR;

	CrcHandle.Instance = CRC;

	if(HAL_CRC_Init(&CrcHandle) != HAL_OK)
	{
		/*se l'inizializzazione del calcolatore non è andata
		 a buon fine, ritorna un errore */
		state = SEC_STATE_CRC_INIT_ERROR;
		return state;
	}

#ifdef SEC_MEASURE_TIMES
	// Abilitazione del DWT e RESET del CYCCNT
	DWT_RESET_CYCLECOUNTER

#endif

	//Il CRC accetta ingressi da 32 bit : occorre un padding
	int actualLength = length%4==0? (length/4):(length/4)+1;
	uint32_t actualMsg[actualLength];

	//inizializzazione del vettore con valori 0x00
	cleanVector(actualMsg,actualLength);

	//viene copiato il messaggio nel vettore da dare in pasto al calcolatore
	memcpy((uint8_t*)actualMsg,msg,length);

	//Calcolo il CRC
	*generatedCRC = HAL_CRC_Calculate(&CrcHandle, actualMsg, actualLength);

#ifdef SEC_MEASURE_TIMES
	// Il numero di cicli di clock sono salvati nel registro DWT->CYCCNT
	sch->execTime_clockCycles = DWT->CYCCNT;
	sch->execTime_ns=CalcNanosecondsFromStopwatch(sch->execTime_clockCycles);
	DWT_STOP_CYCLECOUNTER
#endif

	//deinizzializza il CRC (DA TESTARE)
	HAL_CRC_DeInit(&CrcHandle);

	if(*generatedCRC != 0)
		/*se il controllo non va a buon fine, la procedura è corretta*/
		state = SEC_STATE_OK;
	else
		/*altrimenti ritorna un errore */
		state = SEC_STATE_CRC_GENERATION_ERROR;

	return state;

}
