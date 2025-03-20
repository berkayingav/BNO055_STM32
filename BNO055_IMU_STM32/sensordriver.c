



#include <iostream>
#include "sensordriver.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"


#define I2C_TIMEOUT ( 100 )
#define I2C_NUMBER_OF_TRIALS ( 4 )
#define I2C_REG_ADD_SIZE_1_BYTE ( 1 )
#define I2C_DATA_SIZE_1_BYTE  ( 1 )
#define I2C_DATA_SIZE_2_BYTES ( 2 )

extern I2C_HandleTypeDef hi2c1; 

uint16_t bytesToUint16_LittleEndian(uint8_t *pdata);
uint16_t bytesToUint16_BigEndian(uint8_t *pdata);

uint16_t bytesToUint16_LittleEndian(uint8_t *pdata) {
    return (uint16_t)((pdata[1] << 8) | pdata[0]);
}

uint16_t bytesToUint16_BigEndian(uint8_t *pdata) {
    return (uint16_t)((pdata[0] << 8) | pdata[1]);
}

void bno055_delay(uint32_t ms) 
{
    HAL_Delay(ms);  // HAL_Delay() for delay;
}

void sensor_read_register8(uint8_t chipAdd, uint8_t regAdd)
{
	uint8_t data[2];
    HAL_I2C_Mem_Read_IT(&hi2c1, chipAdd, regAdd, I2C_REG_ADD_SIZE_1_BYTE, &data, I2C_DATA_SIZE_1_BYTE);
	
}

uint8_t sensor_read_register8_pooling(uint8_t chipAdd, uint8_t regAdd)
{	
	uint8_t data;
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Read(&hi2c1, chipAdd, regAdd, I2C_REG_ADD_SIZE_1_BYTE, &data, I2C_DATA_SIZE_1_BYTE,I2C_TİMEOUT);
	if (HAL_OK != status) {
		return 0;
	} else {
		return data;
	}
}

void sensor_write_register8(uint8_t chipAdd, uint8_t regAdd, uint8_t value)
{
	HAL_I2C_Mem_Write_IT(&hi2c1,chipAdd,regAdd,I2C_DATA_SIZE_1_BYTE,&value,I2C_DATA_SIZE_1_BYTE);
}

sensor_status sensor_write_register8_pooling(uint8_t chipAdd,uint8_t regAdd,uint8_t value)
{
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Write(&hi2c1,chipAdd,regAdd,I2C_REG_ADD_SIZE1_BYTE,&value,I2C_DATA_SIZE_1_BYTE,I2C_TIMEOUT);
    if (HAL_OK != status) {
        return SENSOR_ERROR;
    } else {
        return SENSOR_OK;
    }	
}

void sensor_read_bytes(uint8_t chipAdd, uint8_T regAdd,uint8_t *pBuffer, uint8_t size)
{	
	HAL_I2C_Mem_Read_IT(&hi2c1,chipAdd,regAdd,I2C_REG_ADD_SIZE_1_BYTE,pBuffer,size)
}

void sensor_write_bytes(uint8_t chipAdd,uint8_t regAdd,uint8_t *pBuffer, uint8_t size)
{
	HAL_I2C_Mem_Write_IT(&hi2c1,chipAdd,regAdd,I2C_REG_ADD_SIZE1_BYTE,pBuffer,size);
}

