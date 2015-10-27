/*
 * SN_Type.h
 *
 *  Created on: 07/lug/2015
 *      Author: ntonjeta
 */

#ifndef SN_TYPE_H_
#define SN_TYPE_H_

// Particolarizzare
#define UPPER_TRESHOLD 10
#define LOWER_TRESHOLD 0
#define SN_SENSOR_NUMBER 10
#define MAX_WAIT 0
#define TASK_WAIT 1
//#define TESTING


/* Definizioni di comodo -----------------------------------------*/
typedef int16_t Value_t;

typedef enum {
    FALSE = 0,
    TRUE  = 1
} Bool;


typedef struct {
	uint32_t time_stamp; // particolarizzare con la struttura dati fornita
	Value_t  value;
} Data;


typedef struct {
    Value_t LowThreshold;
    Value_t HighThreshold;
} Threshold_Interval;

typedef enum{
	OP_OK	  		= 0,
	OP_ERR_ID 		= 1,
	OP_ERR_OVERUN	= 2
} OP_STATE;

/*
 * Classificazione dei sensori
 */
typedef enum {
    Temperature 	= 1,
    Pressure		= 2,
	Optical			= 3,
	Acoustic		= 4,
	Mechanical		= 5,
	Motion			= 6,
	Flow			= 7,
	Position		= 8,
	Electromagnetic = 9,
	Chemical		= 10,
	Humidity		= 11,
	Radiation		= 12
} Class_Type;


typedef struct {
	uint8_t				id;
	uint16_t	  		read_period_ms;
	uint8_t		  		priority;
	Bool 		  		alarm;
	Threshold_Interval	treshold;
//	Bool				confidential;
} SN_Sensor;









#endif /* SN_TYPE_H_ */
