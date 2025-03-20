#include "BNO055.h"
#include "sensordriver.h"

void BNO055_Reset() 
{
  sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,BNO055_SYS_TRIGGER,0X20);
  bno055_delay(700);
}

void BNO055_Setup()
{
	BNO055_Reset();
	uint8_t id = 0;
	id = sensor_read_register8_pooling(BNO055_I2C_ADDRESS_HIGH,BNO055_CHIP_ID);
	if(id != BNO055_ID){
		printf("Can't find BNO055, id: 0x%02x. Please check your wiring.\r\n", id);
		return;  // For Error
	}
	sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,BNO055_SYS_TRIGGER,0X00);
	sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,OPR_MODE,0X00);  //Config Mode;
	bno055_delay(10);
}

sensor_status BNO055_set_opr(SensorData *pSensor, sensor_opr_mode sensorOpr)
{
	sensor_status = retVal; 
	uint8_t configReg = sensor_read_register8_pooling(BNO055_I2C_ADDRESS_HIGH,OPR_MODE);
	configReg |= ((uint32_t)sensorOpr << 0);
	retVal = sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,OPR_MODE,configReg);
	return retVal;
}

sensor_status BNO055_set_gyro_range(SensorData *pSensor, gyroscope_dps_rate gyroRange,gyroscope_bw gyroBand,gyroscope_op gyroOper)
{	
	BNO055_set_opr(pSensor,M_Config);
	sensor_status retVal;
	sensor_status retVal1;
	uint8_t configReg = sensor_read_register8_pooling(BNO055_I2C_ADDRESS_HIGH,GYR_Config);
	configReg |= ((uint32_t)gyroRange << 0);
	configReg |= ((uint32_t)gyroBand << 3);
	uint8_t configReg1 = sensor_read_register8_pooling(BNO055_I2C_ADDRESS_HIGH,GYR_Config1);
	configReg1 |= ((uint32_t)gyroOper << 0);
	retVal = sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH, GYR_Config, configReg);
	retVal1 = sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,GYR_Config1,configReg1);
		
	switch(gyroRange)
	{
		case G_2000: pSensor->gyro_co = 16.4; break;
		case G_1000: pSensor->gyro_co = 32.8; break;
		case G_500: pSensor->gyro_co = 65.5; break;
		case G_250: pSensor->gyro_co = 131.0; break;
		case G_125: pSensor->gyro_co = 262.0; break;
		default: pSensor->gyro_co = 16.4;
        printf("ERROR! This value is invalid. The default value of G_2000 is used.\n");
		break;
	}
	BNO055_set_opr(pSensor,M_IMU);
	return retVal;
}

sensor_status BNO055_set_magneto_range(SensorData *pSensor, magneto_out_rate magneto_rate,magneto_op magnetOper,magneto_power magnetPow)
{
	BNO055_set_opr(pSensor,M_Config);
	sensor_status retVal;
	uint8_t configReg = sensor_read_register8_pooling(BNO055_I2C_ADDRESS_HIGH,MAG_Config);
	configReg |= ((uint32_t)magneto_rate << 0);
	configReg |= ((uint32_t)magnetOper << 3);
	configReg |= ((uint32_t)magnetPow << 5);
	retVal = sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,MAG_Config,configReg);
	BNO055_set_opr(pSensor,M_IMU);
	return retVal;
}

sensor_status BNO055_set_accel_range(SensorData *pSensor,accel_g_range accelRange,accel_bw accelBand,accel_op accelOper)
{  
	BNO055_set_opr(pSensor,M_Config);
	sensor_status retVal;
	uint8_t configReg = sensor_read_register8_pooling(BNO055_I2C_ADDRESS_HIGH,ACC_Config);
	configReg |= ((uint32_t)accelRange << 0);
	configReg |= ((uint32_t)accelBand << 2);
	configReg |= ((uint32_t)accelOp << 5);
	retVal = sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,ACC_Config,configReg);
	
	switch(accelRange)
	{
		case A_2G: pSensor->acc_co = 16384; break;
		case A_4G: pSensor->acc_co = 8192; break;
		case A_8G: pSensor->acc_co = 4096; break;
		case A_16G: pSensor->acc_co = 2048; break;
		default: pSensor->acc_co = 8192;
        printf("ERROR! This value is invalid. The default value of A_4G is used.\n");
		break; 
	}
	BNO055_set_opr(pSensor,M_IMU);
	return retVal;
}

sensor_status BNO055_set_Power_Mode(SensorData *pSensor,sensor_pow_mode sensorPow)
{
	sensor_status retVal;
	uint8_t configReg = sensor_read_register8_pooling(BNO055_I2C_ADDRESS_HIGH,PWR_MODE);
	configReg |= ((uint32_t)sensorPow << 0);
	retVal = sensor_write_register8_pooling(BNO055_I2C_ADDRESS_HIGH,PWR_MODE,configReg);
	return retVal;
}



void BNO055_read_data(SensorData *pSensorData)
{
	uint8_t buffer[18];
	BNO055_set_opr(pSensor,M_IMU);
	sensor_read_bytes(BNO055_I2C_ADDRESS_HIGH,ACC_DATA_X_LSB,buffer,18);
}


void BNO055_read_data_Callback()
{		
		if (pSensorData->acc_co == 0){
			pSensorData->acc_co = 8192;
		}
		
		if (pSensorData->gyro_co == 0){
			pSensorData->gyro_co = 16.4;
		}

		//Accelerometeter Datas
		pSensorData->accRaw.x = (int16_t) ((buffer[1] << 8) | buffer[0]);
		pSensorData->accRaw.y = (int16_t) ((buffer[3] << 8) | buffer[2]);
		pSensorData->accRaw.z = (int16_t) ((buffer[5] << 8) | buffer[4]);
		pSensorData->accVal.x = (pSensorData->accRaw.x)/(pSensorData->acc_co)*9.81f;
		pSensorData->accVal.y = (pSensorData->accRaw.y)/(pSensorData->acc_co)*9.81f;
		pSensorData->accVal.z = (pSensorData->accRaw.z)/(pSensorData->acc_co)*9.81f;
		//Magnetometer Datas 
		pSensorData->magRaw.x = (int16_t) ((buffer[7] << 8) | buffer[6]);
		pSensorData->magRaw.y = (int16_t) ((buffer[9] << 8) | buffer[8]);
		pSensorData->magRaw.z = (int16_t) ((buffer[11] << 8) | buffer[10]);
		pSensorData->magVal.x = (pSensorData->magRaw.x)/16.0f;
		pSensorData->magVal.y = (pSensorData->magRaw.y)/16.0f;
		pSensorData->magVal.z = (pSensorData->magRaw.z)/16.0f;
		//Gyrscope Datas 
		pSensorData->gyroRaw.x = (int16_t) ((buffer[13] << 8) | buffer[12]);
		pSensorData->gyroRaw.y = (int16_t) ((buffer[15] << 8) | buffer[14]);
		pSensorData->gyroRaw.z = (int16_t) ((buffer[17] << 8) | buffer[16]);
		pSensorData->gyroVal.x = (pSensorData->gyroRaw.x)/(pSensorData->gyro_co);
		pSensorData->gyroVal.y = (pSensorData->gyroRaw.y)/(pSensorData->gyro_co);
		pSensorData->gyroVal.z = (pSensorData->gyroRaw.z)/(pSensorData->gyro_co);
}


