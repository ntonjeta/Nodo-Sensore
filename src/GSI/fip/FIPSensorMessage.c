/*
 * CateMessage.h
 *
 *  Created on: 09/giu/2014
 *      Author: ing. Mario Barbareschi
 */

#include "FIPSensorMessage.h"

int createFIPSensorMessage(SensorMessageParameters params, FIPMessage**fm) {
	*fm = emptyFIPMessage();
	FIPMessage *fipSensorMessage = *fm;
	fipSensorMessage->header = read_sensor;
	switch (params.operation) {
	case sensor_one_read ://|  sensor_lists | sensor_unregist_periodic_read:
		fipSensorMessage->length = sizeof(uint8_t) + sizeof(uint64_t);
		fipSensorMessage->payload = malloc(fipSensorMessage->length);
		fipSensorMessage->payload[0] = params.operation;
		memcpy(fipSensorMessage->payload + sizeof(uint8_t), &params.sensorMask,sizeof(uint64_t));
		break;
	case sensor_lists:
		fipSensorMessage->length = sizeof(uint8_t) + sizeof(uint64_t);
		fipSensorMessage->payload = malloc(fipSensorMessage->length);
		fipSensorMessage->payload[0] = params.operation;
		memcpy(fipSensorMessage->payload + sizeof(uint8_t), &params.sensorMask,	sizeof(uint64_t));
		break;
	case sensor_unregist_periodic_read:
		fipSensorMessage->length = sizeof(uint8_t) + sizeof(uint64_t);
		fipSensorMessage->payload = malloc(fipSensorMessage->length);
		fipSensorMessage->payload[0] = params.operation;
		memcpy(fipSensorMessage->payload + sizeof(uint8_t), &params.sensorMask,	sizeof(uint64_t));
		break;
	case sensor_periodic_read:
		fipSensorMessage->length = sizeof(uint8_t) + sizeof(uint64_t)
				+ sizeof(uint32_t);
		fipSensorMessage->payload = malloc(fipSensorMessage->length);
		fipSensorMessage->payload[0] = params.operation;
		memcpy(fipSensorMessage->payload + sizeof(uint8_t), &params.sensorMask,
				sizeof(uint64_t));
		memcpy(fipSensorMessage->payload + sizeof(uint8_t) + sizeof(uint64_t),
				&params.period, sizeof(uint32_t));
		break;
	case sensor_event_read:
		fipSensorMessage->length = sizeof(uint8_t) + sizeof(uint64_t)+sizeof(uint8_t)
				+ sizeof(float) * 2;
		fipSensorMessage->payload = malloc(fipSensorMessage->length);
		fipSensorMessage->payload[0] = params.operation;
		memcpy(fipSensorMessage->payload + sizeof(uint8_t), &params.sensorMask,
				sizeof(uint64_t));
		fipSensorMessage->payload[sizeof(uint8_t)+sizeof(uint64_t)] = params.guard;
		memcpy(fipSensorMessage->payload + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint8_t),
				&params.lowThreshold, sizeof(float));
		memcpy(
				fipSensorMessage->payload + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint8_t)
						+ sizeof(float), &params.highThreshold, sizeof(float));
		break;
	default:
		return -1;
		break;
	}
	return 1;
}

int isSensorMessage(FIPMessage *fm) {
	return fm->header == read_sensor;
}

SensorOperation getSensorOperation(FIPMessage *fm) {
	return fm->payload[0];
}

void getSensorsMask(FIPMessage *fm, uint64_t* mask) {
	memcpy(mask, fm->payload + 1, sizeof(uint64_t));
}

int hasSensorsMask(FIPMessage *fm, uint64_t sensorsMask) {
	uint64_t mask;
	getSensorsMask(fm, &mask);
	return isSensorMessage(fm) && (mask & sensorsMask);
}

int hasAcceleratorX(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_ACCELERATOR_X);
}

int hasAcceleratorY(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_ACCELERATOR_Y);
}

int hasAcceleratorZ(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_ACCELERATOR_Z);
}

int hasLight(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_LIGHT);
}

int hasGravityX(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_GRAVITY_X);
}

int hasGravityY(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_GRAVITY_Y);
}

int hasGravityZ(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_GRAVITY_Z);
}

int hasTemperature(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_TEMPERATURE);
}

int hasGyroscopeX(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_GYROSCOPE_X);
}

int hasGyroscopeY(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_GYROSCOPE_Y);
}

int hasGyroscopeZ(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_GYROSCOPE_Z);
}

int hasProximity(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_PROXIMITY);
}

int hasMagneticX(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_MAGNETIC_X);
}

int hasMagneticY(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_MAGNETIC_Y);
}

int hasMagneticZ(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_MAGNETIC_Z);
}

int hasHumidity(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_HUMIDITY);
}

int hasPressure(FIPMessage *fm) {
	return hasSensorsMask(fm, SENSOR_MASK_PRESSURE);
}

int isOneRead(FIPMessage *fm) {
	return getSensorOperation(fm) == sensor_one_read;
}

int isPeriodicRead(FIPMessage *fm) {
	return getSensorOperation(fm) == sensor_periodic_read;
}

int isEventRead(FIPMessage *fm) {
	return getSensorOperation(fm) == sensor_event_read;
}

int isList(FIPMessage *fm) {
	return getSensorOperation(fm) == sensor_lists;
}

int isMissingSensor(FIPMessage *fm) {
	return getSensorOperation(fm) == missing_sensor;
}

float getSensorValue(FIPMessage *fm, uint8_t sensor) {
	if (!isMissingSensor(fm) && !isList(fm)) {
		uint64_t mask = 0x0000000000000001 << sensor;
		uint64_t sensorsMask;
		int additional_shift=0;
		getSensorsMask(fm, &sensorsMask);
		if (hasSensorsMask(fm, mask)) {
			mask--;
			int previousSensors = __builtin_popcount(mask & sensorsMask);
			if(isEventRead(fm)){
				additional_shift = sizeof(float)*2+sizeof(uint8_t);
			}
				return *(float*) (fm->payload + sizeof(uint8_t)
						+ sizeof(uint64_t) + additional_shift + previousSensors * sizeof(float));
		} else {
			return 0;
		}
	}else{
		return 0;
	}
}

float getAcceleratorX(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_ACCELERATOR_X);
}

float getAcceleratorY(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_ACCELERATOR_Y);
}

float getAcceleratorZ(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_ACCELERATOR_X);
}

float getLight(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_LIGHT);
}

float getGravityX(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_GRAVITY_X);
}

float getGravityY(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_GRAVITY_Y);
}

float getGravityZ(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_GRAVITY_Z);
}

float getTemperature(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_TEMPERATURE);
}

float getGyroscopeX(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_GYROSCOPE_X);
}

float getGyroscopeY(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_GYROSCOPE_Y);
}

float getGyroscopeZ(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_GYROSCOPE_Z);
}

float getProximity(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_PROXIMITY);
}

float getMagneticX(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_MAGNETIC_X);
}

float getMagneticY(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_MAGNETIC_Y);
}

float getMagneticZ(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_MAGNETIC_Z);
}

float getHumidity(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_HUMIDITY);
}

float getPressure(FIPMessage *fm) {
	return getSensorValue(fm, SENSOR_PRESSURE);

}

