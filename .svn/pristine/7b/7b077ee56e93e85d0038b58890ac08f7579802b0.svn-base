/*
 * CateMessage.h
 *
 *  Created on: 09/giu/2014
 *      Author: ing. Mario Barbareschi
 */

#ifndef FIPSENSORMESSAGE_H_
#define FIPSENSORMESSAGE_H_
#include "FIPMessage.h"

	/*
	 * Definitions for the sensors read command option
	 */

#define SENSOR_ONE_READ						(uint8_t)0x00
#define SENSOR_PERIODIC_READ				(uint8_t)0x01
#define SENSOR_EVENT_READ					(uint8_t)0x02
#define SENSOR_LISTS								(uint8_t)0x03
#define MISSING_SENSOR						(uint8_t)0xA0


	/*
	 * Definitions for the sensor field type, the command
	 */

#define SENSOR_ACCELERATOR_X						0
#define SENSOR_MASK_ACCELERATOR_X					(uint64_t)0x0000000000000001<<SENSOR_ACCELERATOR_X
#define SENSOR_ACCELERATOR_Y						1
#define SENSOR_MASK_ACCELERATOR_Y					(uint64_t)0x0000000000000001<<SENSOR_ACCELERATOR_Y
#define SENSOR_ACCELERATOR_Z						2
#define SENSOR_MASK_ACCELERATOR_Z					(uint64_t)0x0000000000000001<<SENSOR_ACCELERATOR_Z
#define SENSOR_LIGHT								3
#define SENSOR_MASK_LIGHT							(uint64_t)0x0000000000000001<<SENSOR_LIGHT

#define SENSOR_GRAVITY_X							4
#define SENSOR_MASK_GRAVITY_X						(uint64_t)0x0000000000000001<<SENSOR_GRAVITY_X
#define SENSOR_GRAVITY_Y							5
#define SENSOR_MASK_GRAVITY_Y						(uint64_t)0x0000000000000001<<SENSOR_GRAVITY_Y
#define SENSOR_GRAVITY_Z							6
#define SENSOR_MASK_GRAVITY_Z						(uint64_t)0x0000000000000001<<SENSOR_GRAVITY_Z
#define SENSOR_TEMPERATURE							7
#define SENSOR_MASK_TEMPERATURE						(uint64_t)0x0000000000000001<<SENSOR_TEMPERATURE

#define SENSOR_GYROSCOPE_X							8
#define SENSOR_MASK_GYROSCOPE_X						(uint64_t)0x0000000000000001<<SENSOR_GYROSCOPE_X
#define SENSOR_GYROSCOPE_Y							9
#define SENSOR_MASK_GYROSCOPE_Y						(uint64_t)0x0000000000000001<<SENSOR_GYROSCOPE_Y
#define SENSOR_GYROSCOPE_Z							10
#define SENSOR_MASK_GYROSCOPE_Z						(uint64_t)0x0000000000000001<<SENSOR_GYROSCOPE_Z
#define SENSOR_PROXIMITY							11
#define SENSOR_MASK_PROXIMITY						(uint64_t)0x0000000000000001<<SENSOR_PROXIMITY

#define SENSOR_MAGNETIC_X							12
#define SENSOR_MASK_MAGNETIC_X						(uint64_t)0x0000000000000001<<SENSOR_MAGNETIC_X
#define SENSOR_MAGNETIC_Y							13
#define SENSOR_MASK_MAGNETIC_Y						(uint64_t)0x0000000000000001<<SENSOR_MAGNETIC_Y
#define SENSOR_MAGNETIC_Z							14
#define SENSOR_MASK_MAGNETIC_Z						(uint64_t)0x0000000000000001<<SENSOR_MAGNETIC_Z
#define SENSOR_HUMIDITY								15
#define SENSOR_MASK_HUMIDITY						(uint64_t)0x0000000000000001<<SENSOR_HUMIDITY

#define SENSOR_PRESSURE								16
#define SENSOR_MASK_PRESSURE						(uint64_t)0x0000000000000001<<SENSOR_PRESSURE

#define EVENT_GUARD_DEFAULT					(uint8_t)0x01
#define EVENT_GUARD_LESS					(uint8_t)0x02
#define EVENT_GUARD_GREATER					(uint8_t)0x03
#define EVENT_GUARD_LESOEQ					(uint8_t)0x04
#define EVENT_GUARD_GREOEQ					(uint8_t)0x05
#define EVENT_GUARD_BETWEEN					(uint8_t)0x06
#define EVENT_GUARD_BETOEQ					(uint8_t)0x07


#define SENSOR_UNREGISTER_PERIODIC_READ		(uint8_t)0x80 | SENSOR_PERIODIC_READ
#define SENSOR_UNREGISTER_EVENT_READ		(uint8_t)0x80 | SENSOR_EVENT_READ

typedef enum {
	sensor_one_read = SENSOR_ONE_READ,
	sensor_periodic_read = SENSOR_PERIODIC_READ,
	sensor_event_read = SENSOR_EVENT_READ,
	sensor_lists = SENSOR_LISTS,
	sensor_unregist_periodic_read = SENSOR_UNREGISTER_PERIODIC_READ,
	sensor_unregist_event_read = SENSOR_UNREGISTER_EVENT_READ,
	missing_sensor = MISSING_SENSOR
}SensorOperation;

typedef enum {
	event_guard_default = EVENT_GUARD_DEFAULT,
	event_guard_less_than = EVENT_GUARD_LESS,
	event_guard_greater_than = EVENT_GUARD_GREATER,
	event_guard_less_than_or_equal = EVENT_GUARD_LESOEQ,
	event_guard_greater_than_or_equal = EVENT_GUARD_GREOEQ,
	event_guard_between = EVENT_GUARD_BETWEEN,
	event_guard_between_or_equal = EVENT_GUARD_BETOEQ
}SensorGuard;

struct SensorMessageParameters {
	SensorOperation operation;
	uint64_t sensorMask;
	uint32_t period;
	SensorGuard guard;
	float lowThreshold;
	float highThreshold;
};
typedef struct SensorMessageParameters SensorMessageParameters;

int createFIPSensorMessage(SensorMessageParameters params, FIPMessage**fm);

int isSensorMessage(FIPMessage *fm);
SensorOperation getSensorOperation(FIPMessage *fm);
uint64_t getSensorMask(FIPMessage *fm);
int hasSensorsMask(FIPMessage *fm, uint64_t sensorsMask);
int hasAcceleratorX(FIPMessage *fm);
int hasAcceleratorY(FIPMessage *fm);
int hasAcceleratorZ(FIPMessage *fm);
int hasLight(FIPMessage *fm);
int hasGravityX(FIPMessage *fm);
int hasGravityY(FIPMessage *fm);
int hasGravityZ(FIPMessage *fm);
int hasTemperature(FIPMessage *fm);
int hasGyroscopeX(FIPMessage *fm);
int hasGyroscopeY(FIPMessage *fm);
int hasGyroscopeZ(FIPMessage *fm);
int hasProximity(FIPMessage *fm);
int hasMagneticX(FIPMessage *fm);
int hasMagneticY(FIPMessage *fm);
int hasMagneticZ(FIPMessage *fm);
int hasHumidity(FIPMessage *fm);
int hasPressure(FIPMessage *fm);

int isOneRead(FIPMessage *fm);
int isPeriodicRead(FIPMessage *fm);
int isEventRead(FIPMessage *fm);
int isList(FIPMessage *fm);
int isMissingSensor(FIPMessage *fm);

void getSensorsMask(FIPMessage *fm, uint64_t* mask);
float getAcceleratorX(FIPMessage *fm);
float getAcceleratorY(FIPMessage *fm);
float getAcceleratorZ(FIPMessage *fm);
float getLight(FIPMessage *fm);
float getGravityX(FIPMessage *fm);
float getGravityY(FIPMessage *fm);
float getGravityZ(FIPMessage *fm);
float getTemperature(FIPMessage *fm);
float getGyroscopeX(FIPMessage *fm);
float getGyroscopeY(FIPMessage *fm);
float getGyroscopeZ(FIPMessage *fm);
float getProximity(FIPMessage *fm);
float getMagneticX(FIPMessage *fm);
float getMagneticY(FIPMessage *fm);
float getMagneticZ(FIPMessage *fm);
float getHumidity(FIPMessage *fm);
float getPressure(FIPMessage *fm);

#endif /* FIP_SENSOR_MESSAGE_H_ */
