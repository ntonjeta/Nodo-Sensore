/*
 * gsi.h
 *
 *  Created on: 04/lug/2015
 *      Author: ntonjeta
 */

#ifndef GSI_GSI_H_
#define GSI_GSI_H_

/**
 *  GSI.h
 *   Version: 0.1
 *
 *   Changelog:
*/


#include "gsi_config.h"
#include "SN_Type.h"


#define Calibration_Value 	11.0		// spiazzamento sul valore di temperatura

/* Exported types ------------------------------------------------------------*/

/*
 * Possibili collegamenti
 */
typedef enum {
	I2C			= 1,
	SPI			= 2,
	CATE		= 3,
	Analog		= 4
}Sensor_Link;

/*
 * Struttura che descrive i sensori
 */
typedef struct {
	uint8_t 	  		id;
	Class_Type 	  		sensor_class;
	Sensor_Link 	  	link;
	uint8_t		  		address;	 // solo per i2c, forse in futuro anche per analog
	Bool 				dataread;
	Data 		  		lastData;
} GSI_Sensor;



// ATTENZIONE
/*anche l'msp è roba mia e la registrazione delle callback */


/* Metodi publici -----------------------------------------------------------*/

OP_STATE	initSensors 		(void);
OP_STATE   	readData 			(uint8_t ID,Data *data);

uint16_t	getSensorNumber 	();
void 		getIDSensorList		(uint8_t *ID_array);

void 		destroyGSI	(); //DA FARE





#endif /* GSI_GSI_H_ */
