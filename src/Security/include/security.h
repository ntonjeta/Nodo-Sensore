/**
 * \file security.h
 *
 * \brief File Header sicurezza [descrizione da modificare]
 *
 * \author Gruppo 1
 */

#ifndef SECURITY_H_
#define SECURITY_H_

#include "utils.h"
#include "aes.h"
#include "des3.h"
#include "hmac.h"
#include "arc4.h"

#include <stdint.h>
#include "stm32f407xx.h"

#define uint8 unsigned char
#define uint32 unsigned int

/* Define per utilizzare i contatori e calcolare i tempi di esecuzione degli algoritmi*/
#define DWT_RESET_CYCLECOUNTER     { CoreDebug->DEMCR = CoreDebug->DEMCR | CoreDebug_DEMCR_TRCENA_Msk;  \
                                       DWT->CYCCNT = 0;                                   \
                                       DWT->CTRL = DWT->CTRL | DWT_CTRL_CYCCNTENA_Msk ; }
#define DWT_STOP_CYCLECOUNTER     {  	CoreDebug->DEMCR = CoreDebug->DEMCR & 0x00000000;  \
										 DWT->CTRL = DWT->CTRL & 0x40000000 ;}
/* RNG handler declaration */
RNG_HandleTypeDef RngHandle;
/* CRC handler declaration */
CRC_HandleTypeDef CrcHandle;

/*Tipi di chiavi per gli algoritmi di cifratura*/
typedef unsigned char SEC_AES128_Key[16];
typedef unsigned char SEC_AES192_Key[24];
typedef unsigned char SEC_AES256_Key[32];
typedef unsigned char SEC_DES3_Key[24];

/*Tipi di IV (initialization Vector) per gli algoritmi di cifratura*/
typedef unsigned char SEC_AES128_IV[16];
typedef unsigned char SEC_DES3_IV[24];

/**
 * \brief  Definizione struttura degli stati
 */
typedef enum
{
	SEC_STATE_OK							= 0x00,  /**< funzionamento corretto */
	SEC_STATE_SETKEY_ERROR					= 0x01,  /**< errore nel settaggio della chiave */
	SEC_STATE_ENCRYPT_ERROR					= 0x02,  /**< errore nella cifratura */
	SEC_STATE_DECRYPT_ERROR					= 0x03,  /**< errore nella decifratura */
	SEC_STATE_SIZEKEY_ERROR					= 0x04,  /**< errore nella dimensione della chiave */
	SEC_STATE_SIZEKEY_WARNING				= 0x05,  /**< segnalazione dimensione chiave errata */
	SEC_STATE_HMAC_SETKEY_ERROR				= 0x06,  /**< errore nel settaggio della chiave HMAC */
	SEC_STATE_HMAC_SIZEKEY_WARNING			= 0x07,  /**< segnalazione dimensione chiave HMAC errata */
	SEC_STATE_HMAC_UPDATE_ERROR				= 0x08,  /**< errore in fase update HMAC */
	SEC_STATE_HMAC_FINAL_ERROR				= 0x09,  /**< errore in fase final HMAC */
	SEC_STATE_HMAC_VERIFY_ERROR				= 0x0A,  /**< errore nella verifica HMAC*/
	SEC_STATE_HMAC_VERIFY_OK				= 0x0B,  /**< verifica HMAC corretta */
	SEC_STATE_HMAC_ALGORITHM_ERROR			= 0x0C,  /**< errore nell'inserimento dell'algoritmo nel HMAC */
	SEC_STATE_RANDOMVALUE_INIT_ERROR		= 0x0D,  /**< errore nell'inizializzazione del RNG */
	SEC_STATE_RANDOMVALUE_GENERATION_ERROR	= 0x0E,  /**< errore nella generazione numero random */
	SEC_STATE_CRC_INIT_ERROR				= 0x0F,  /**< errore nell'inizializzazione del CRC */
	SEC_STATE_CRC_GENERATION_ERROR			= 0x10,  /**< errore generazione del CRC */
	SEC_STATE_GENERIC_ERROR					= 0xFF,  /**< errore generico */
}SEC_StateTypeDef;

/**
 * \brief  Definizione algoritmi di crittografia utilizzabili
 */
typedef enum
{
	SEC_AES128            = 0x01,  /**< Algoritmo AES con chiave 128 bit*/
	SEC_AES192            = 0x02,  /**< Algoritmo AES con chiave 192 bit */
	SEC_AES256            = 0x03,  /**< Algoritmo AES con chiave 256 bit*/
	SEC_DES3   	          = 0x04,  /**< Algoritmo DES3 */
	SEC_ARC4	          = 0x05,  /**< Algoritmo ARC4 */
	SEC_RABBIT            = 0x06,  /**< Algoritmo Rabbit */
}SEC_CRYP_AlgorithmTypeDef;

/**
 * \brief  Definizione algoritmi di HASH utilizzabili
 */
typedef enum
{
	SEC_MD5		= 0x01,  /**< Algoritmo MD5 con digest da 128 bit */
	SEC_SHA1	= 0x02,  /**< Algoritmo SHA-1 con digest da 160 bit */
	SEC_SHA256	= 0x03,  /**< Algoritmo SHA-256 con digest da 256 bit */
	SEC_SHA384	= 0x04,  /**< Algoritmo SHA-384 con digest da 384 bit */
	SEC_SHA512	= 0x05,  /**< Algoritmo SHA-512 con digest da 512 bit */
}SEC_HASH_AlgorithmTypeDef;

/**
 * \brief 	Struttura di ausilio alle funzioni di crittografia
 */
typedef struct{
	uint8 *key;								///< Puntatore alla variabile contenente la chiave
	uint32 keylen;							///< Lunghezza della chiave
	uint8 *iv;								///< Puntatore alla variabile contenente il vettore di inizializzazione
	SEC_CRYP_AlgorithmTypeDef algorithm;	///< Algoritmo di crittografia scelto
	unsigned int execTime_clockCycles;		///< Numero di cicli di clock nell'esecuzione di un algoritmo
	long long execTime_ns;					///< Numero di nanosecondi nell'esecuzione di un algoritmo
}SEC_cryp_handle;

/**
 * \brief 	Struttura di ausilio a HMAC
 */
typedef struct{
	uint8 *secret;							///< Puntatore alla variabile contenente il segreto
	uint32 secretlen;						///< Lunghezza del segreto
	SEC_HASH_AlgorithmTypeDef algorithm;	///< Algoritmo di hash scelto
	unsigned int execTime_clockCycles;		///< Numero di cicli di clock nell'esecuzione di un algoritmo
	long long execTime_ns;					///< Numero di nanosecondi nell'esecuzione di un algoritmo
}SEC_HMAC_handle;

/**
 * \brief 	Struttura di ausilio al generatore di valori casuali
 */
typedef struct{
	SEC_CRYP_AlgorithmTypeDef algorithm;	///< Scelta dell'algoritmo per la dimensione del numero
	unsigned int execTime_clockCycles;		///< Numero di cicli di clock nell'esecuzione di un algoritmo
	long long execTime_ns;					///< Numero di nanosecondi nell'esecuzione di un algoritmo
}SEC_RVG_handle; //RVG = random value generator

/**
 * \brief 	Struttura di ausilio al calcolatore CRC
 */
typedef struct{
	unsigned int execTime_clockCycles;		///< Numero di cicli di clock nell'esecuzione di un algoritmo
	long long execTime_ns;					///< Numero di nanosecondi nell'esecuzione di un algoritmo
}SEC_CRC_handle;

/*firma delle funzioni utilizzate*/
SEC_StateTypeDef SEC_Encrypt(
		SEC_cryp_handle *sch,
		uint8 *plaintext,
		uint32 plaintext_length,
		uint8 *ciphertext,
		uint32 *ciphertext_length
);

SEC_StateTypeDef SEC_Decrypt(
		SEC_cryp_handle *sch,
		uint8 *ciphertext,
		uint32 ciphertext_length,
		uint8 *plaintext,
		uint32 *plaintext_length
);

SEC_StateTypeDef SEC_HMAC(
		SEC_HMAC_handle *shh,
		uint8 *plaintext,
		uint32 plaintext_length,
		uint8 *digest
);

SEC_StateTypeDef SEC_HMAC_verify(
		SEC_HMAC_handle *shh,
		uint8 *plaintext,
		uint32 plaintext_length,
		uint8 *digest
);

SEC_StateTypeDef SEC_GenarateRandomValue(
		SEC_RVG_handle *srgvh,
		byte *secret,
		uint32 dim
);

SEC_StateTypeDef SEC_GenarateRandomValue_AlgorithmBased(
		SEC_RVG_handle *srgvh,
		byte *secret
);

SEC_StateTypeDef SEC_GenarateRandomValue_CustomLength(
		SEC_RVG_handle *srgvh,
		byte *secret,
		uint32 dim
);

SEC_StateTypeDef SEC_GenarateCRC(
		SEC_CRC_handle *sch,
		byte *msg,
		uint32 length,
		uint32* generatedCRC
);


#endif /* SECURITY_H_ */
