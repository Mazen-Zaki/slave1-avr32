 /***********************************************************************************************************/
 /* 										Author : Mazen Nasser Zaki										   */
 /* 										MICRO  : STM32F401RCT6											   */
 /* 										LAYER  : HAL													   */
 /* 										DRIVER : MPU6050_Driver											  	   */
 /* 										File   : MPU6050											   */
 /* 										Date   : Feb 9, 2024											   */
 /* 										Version: v02													   */
 /***********************************************************************************************************/

/***********************************************************************************************************/
/*                              			 FILE GUARD   						                           */
/***********************************************************************************************************/

#ifndef HAL_MPU6050_MPU6050_H_
#define HAL_MPU6050_MPU6050_H_

#include "../INC/std_types.h"
#include "../MCAL/TIMER0.h"


/***********************************************************************************************************/
/*                    	     			 REGISTER ADDRESSES   				                               */
/***********************************************************************************************************/

#define RAD_TO_DEG 57.295779513082320876798154814105

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43

#define MPU6050_ADDR 0xD0


/***********************************************************************************************************/
/*                    	     				 MPU STRUCTURE   				                               */
/***********************************************************************************************************/

typedef struct {

	s16 Accel_X_RAW;
	s16 Accel_Y_RAW;
	s16 Accel_Z_RAW;
	f64 Ax;
	f64 Ay;
	f64 Az;

	s16 Gyro_X_RAW;
	s16 Gyro_Y_RAW;
	s16 Gyro_Z_RAW;
	f64 Gx;
	f64 Gy;
	f64 Gz;

	float Temperature;

	f64 KalmanAngleX;
	f64 KalmanAngleY;
} MPU6050_t;


/* Kalman Filter */
/* Sensor Fusion Algorithm */
typedef struct {
	f64 Q_angle;
	f64 Q_bias;
	f64 R_measure;
	f64 angle;
	f64 bias;
	f64 P[2][2];
} Kalman_t;


u8 MPU6050_Init();

void MPU6050_Read_Accel(MPU6050_t *DataStruct);

void MPU6050_Read_Gyro(MPU6050_t *DataStruct);

void MPU6050_Read_Temp(MPU6050_t *DataStruct);

void MPU6050_Read_All(MPU6050_t *DataStruct);

f64 Kalman_getAngle(Kalman_t *Kalman, f64 newAngle, f64 newRate, f64 dt);
 
#endif /* HAL_MPU6050_MPU6050_H_ */
