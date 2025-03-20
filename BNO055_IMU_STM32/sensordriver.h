#ifndef HWDRIVERS_SENSORDRIVER_H_
#define HWDRIVERS_SENSORDRIVER_H_

#include <stdint.h>

typedef enum {
	SENSOR_OK,
	SENSOR_ERROR
}sensor_status;

void bno055_delay(uint32_t ms) ;
void sensor_read_register8(uint8_t chipAdd, uint8_t regAdd);
uint8_t sensor_read_register8_pooling(uint8_t chipAdd, uint8_t regAdd);
void sensor_write_register8(uint8_t chipAdd, uint8_t regAdd, uint8_t value);
sensor_status sensor_write_register8_pooling(uint8_t chipAdd,uint8_t regAdd,uint8_t value);
void sensor_read_bytes(uint8_t chipAdd, uint8_T regAdd,uint8_t *pBuffer, uint8_t size);
void sensor_write_bytes(uint8_t chipAdd,uint8_t regAdd,uint8_t *pBuffer, uint8_t size);
