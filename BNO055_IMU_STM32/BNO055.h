

 #ifndef DRIVERS_BNO055_H_
 #define DRIVERS_BNO055_H_ 
 
 #include <stdint.h>
 #include "stm32f4xx_hal.h"
 #include "sensordriver.h"
 
//I2C ADDRESS
 
 #define BNO055_I2C_ADDRESS_HIGH ( 0x29<<1 ) 
 #define BNO055_I2C_ADDRESS_LOW ( 0x28<<1 ) 

// Offset Registers
#define BNO055_ID ( 0xA0 )
#define BNO055_SYS_TRIGGER ( 3F )
#define BNO055_CHIP_ID ( 0 )
#define MAG_RADIUS_MSB ( 6A )
#define MAG_RADIUS_LSG ( 69 )
#define ACC_RADIUS_MSB ( 68 )
#define ACC_RADIUS_LSB ( 67 )
#define GYR_OFFSET_Z_MSB ( 66 ) 
#define GYR_OFFSET_Z_LSB ( 65 ) 
#define GYR_OFFSET_Y_MSB ( 64 ) 
#define GYR_OFFSET_Y_LSB ( 63 ) 
#define GYR_OFFSET_X_MSB ( 62 ) 
#define GYR_OFFSET_X_LSB ( 61 ) 
#define MAG_OFFSET_Z_MSB ( 60 ) 
#define MAG_OFFSET_Z_LSB ( 5F ) 
#define MAG_OFFSET_Y_MSB ( 5E ) 
#define MAG_OFFSET Y_LSB ( 5D ) 
#define MAG_OFFSET_X_MSB ( 5C ) 
#define MAG_OFFSET_X_LSB ( 5B )
#define ACC_OFFSET_Z_MSB ( 5A )
#define ACC_OFFSET_Z_LSB ( 59 )
#define ACC_OFFSET_Y_MSB ( 58 )
#define ACC_OFFSET_Y_LSB ( 57 )
#define ACC_OFFSET_X_MSB ( 56 ) 
#define ACC_OFFSET_X_LSB ( 55 ) 

// Data Registers 
#define EUL_Pitch_MSB ( 1F )
#define EUL_Pitch_LSB ( 1E )
#define EUL_Roll_MSB ( 1D )
#define EUL_Roll_LSB ( 1C )
#define EUL_Heading_MSB ( 1B )
#define EUL_Heading_LSB ( 1A )
#define GYR_DATA_Z_MSB ( 19 ) 
#define GYR_DATA_Z_LSB ( 18 ) 
#define GYRO_DATA_Y_MSB ( 17 )
#define GYRO_DATA_Y_LSB ( 16 ) 
#define GYRO_DATA_X_MSB ( 15 )
#define GYRO_DATA_X_LSB ( 14 ) 
#define MAG_DATA_Z_MSB ( 13 ) 
#define MAG_DATA_Z_LSB ( 12 )
#define MAG_DATA_Y_MSB ( 11 )
#define MAG_DATA_Y_LSB ( 10 )
#define MAG_DATA_X_MSB ( F )
#define MAG_DATA_X_LSB ( E )
#define ACC_DATA_Z_MSB ( D )
#define ACC_DATA_Z_LSB ( C )
#define ACC_DATA_Y_MSB ( B )
#define ACC_DATA_Y_LSB ( A )
#define ACC_DATA_X_MSB ( 9 )
#define ACC_DATA_X_LSB ( 8 )

// Chip ID
#define GYR_ID ( 3 )
#define GYRO_ID_C ( 0x0F ) 
#define MAG_ID ( 2 ) 
#define MAG_ID_C ( 0x32 )
#define ACC_ID ( 1 ) 
#define ACC_ID_C ( 0xFB ) 
#define CHIP_ID ( 0 )
#define CHIP_ID_C ( 0xA0 ) 

// MODE ID 
//Config registerine yazabilmek için OPR_MODE normal modda yani configmode'de olmalıdır. 
#define PWR_MODE ( 3E )
#define OPR_MODE ( 3D )
#define GYR_Config (  )
#define GYR_Config1 (  )
#define ACC_Config (  )
#define MAG_Config (  ) 

/* Default Sensor Configuration
Accelerometer -> Power Mode -> Normal 
			  -> Range -> +/- 4g 
			  -> Bandwith -> 62.5Hz 
			  -> Resolution -> 14 bits 
Gyroscope 
			  -> Power Mode -> Normal 
			  -> Range -> +/- 2000 deg/s 
			  -> Bandwidth -> 32Hz 
			  -> Resolution -> 16 bits 
Magnetometer
			  -> Power Mode -> Forced 
			  -> ODR -z 20Hz 
			  -> XY Repetition -> 15 
			  -> Z Repetition -> 16 
			  -> Resolution x/y/z -> 13/13/15 bits 
*/

typedef enum {
	M_Config = 0,
	M_AMG = 7,
	M_IMU = 8
}sensor_opr_mode;

typedef enum {
	P_Normal, //0
	P_Low,   //1
	P_Suspend,  //2
}sensor_pow_mode;

typedef enum {
	A_2G, //0
	A_4G, //1
	A_8G, //2
	A_16G //3
}accel_g_range;

typedef enum {
	A_7_81Hz, //0
	A_15_63Hz, //1
	A_31_25Hz, //2
	A_62_5Hz, //3
	A_125Hz, //4
	A_250Hz, //5 
	A_500Hz, //6
	A_1000Hz //7 
}accel_bw; 

typedef enum {
	A_Normal, //0
	A_Suspend, //1
	A_LowP1, //2
	A_Standby, //3 
	A_LowP2, //4 
	A_DeepSuspend //5
}accel_op;

typedef enum {
	G_2000,  //0
	G_1000,  //1
	G_500,   //2
	G_250,   //3
	G_125    //4
}gyroscope_dps_rate;

typedef enum {
	G_523Hz, //0
	G_230Hz, //1
	G_116Hz, //2
	G_47Hz,  //3
	G_23Hz, //4
	G_12Hz, //5
	G_64Hz, //6
	G_32Hz //7 
}gyroscope_bw;

typedef enum {
	G_Normal, //0
	G_Fast, //1
	G_DeepSuspend, //2
	G_Suspend,  //3
	G_Advanced, //4
}gyroscope_op;

typedef enum {
	M_2, //0 
	M_6, //1
	M_8, //2
	M_10, //3
	M_15, //4
	M_20, //5
	M_25, //6
	M_30 //7 
}magneto_out_rate;

typedef enum {
	M_LowPow, //0
	M_Regular, //1
	M_EnchancedReg, //2
	M_HighAcc //3 
}magneto_op;

typedef enum {
	M_Normal,  //0
	M_Sleep,   //1
	M_Suspend, //2
	M_Force  //3
}magneto_power;

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
}rawData;

typedef struct{
	double x;
	double y;
	double z;
}valueData;

typedef struct {
	rawData accRaw;
	rawData gyroRaw;
	rawData magRaw;
	valueData accVal;
	valueData gyroVal;
	valueData magVal;
	double acc_co;
	double gyro_co;
	double mag_co;
	double accOffset;
	double gyroOffset;
	double magOffset;
}SensorData;


// Functions
void BNO055_Reset(void);
void BNO055_Setup(void);
sensor_status BNO055_set_opr(SensorData *pSensor, sensor_opr_mode sensorOpr);
sensor_status BNO055_set_gyro_range(SensorData *pSensor, gyroscope_dps_rate gyroRange,gyroscope_bw gyroBand,gyroscope_op gyroOper);
sensor_status BNO055_set_magneto_range(SensorData *pSensor, magneto_out_rate magneto_rate,magneto_op magnetOper,magneto_power magnetPow);
sensor_status BNO055_set_accel_range(SensorData *pSensor,accel_g_range accelRange,accel_bw accelBand,accel_op accelOper);
sensor_status BNO055_set_Power_Mode(SensorData *pSensor,sensor_pow_mode sensorPow);
void BNO055_read_data(SensorData *pSensorData);
void BNO055_read_data_Callback();


