 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/
#include "../MCAL/i2c.h"
#include "MPU6050.h"

// Setup MPU6050
const f64 Accel_Z_corrector = 14418.0;

u32 timer;

Kalman_t KalmanX = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f
};

Kalman_t KalmanY = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f,
};



/**
  * @brief Initializes the MPU6050 sensor.
  * @param I2Cx: Specifies the I2C peripheral to be used.
  * @retval 0 if initialization is successful, otherwise 1.
  *
  * This function initializes the MPU6050 sensor by checking its device ID,
  * configuring power management, setting data rate, and configuring accelerometer
  * and gyroscope parameters. The sensor is expected to have a device ID of 104 (0x68).
  * If initialization is successful, the function returns 0; otherwise, it returns 1.
  */

u8 MPU6050_Init()
{
    u8 check = 0;
    u8 Data = 0;
	
	TWI_init();

    // check device ID WHO_AM_I

    //HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);
    /* I2C READ FROM MEMORY WITH ADDRESS WHO_AM_I_REG THE OUTPUT IN check */////////////////////////////////////////////////////////********
	I2C_Mem_Read(MPU6050_ADDR, WHO_AM_I_REG, &check, 1);

    if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        //HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);
        /* I2C WRITE TO MEMORY WITH ADDRESS PWR_MGMT_1_REG AND DATA = Data *////////////////////////////////////////////////////////********
		I2C_Mem_Write(MPU6050_ADDR, PWR_MGMT_1_REG, &Data);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        //HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);
        /* I2C WRITE TO MEMORY WITH ADDRESS SMPLRT_DIV_REG AND DATA = Data */////////////////////////////////////////////////////////*********
		I2C_Mem_Write(MPU6050_ADDR, SMPLRT_DIV_REG, &Data);
		
        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ? 2g
        Data = 0x00;
        //HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);
        /* I2C WRITE TO MEMORY WITH ADDRESS ACCEL_CONFIG_REG AND DATA = Data */////////////////////////////////////////////////////////*******
		I2C_Mem_Write(MPU6050_ADDR, ACCEL_CONFIG_REG, &Data);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ? 250 ?/s
        Data = 0x00;
        //HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);
        /* I2C WRITE TO MEMORY WITH ADDRESS GYRO_CONFIG_REG AND DATA = Data */////////////////////////////////////////////////////////********
		I2C_Mem_Write(MPU6050_ADDR, GYRO_CONFIG_REG, &Data);
		
        return 0;
    }
    return 1;
}




/**
  * @brief Reads accelerometer, gyroscope, and temperature data from the MPU6050 sensor.
  * @param I2Cx: Specifies the I2C peripheral to be used.
  * @param DataStruct: Pointer to the MPU6050 data structure to store the results.
  *
  * This function reads 14 bytes of data starting from the ACCEL_XOUT_H register of the MPU6050 sensor
  * using I2C communication. It then extracts and converts the raw data into meaningful values for
  * accelerometer, gyroscope, temperature, and Kalman filter angles. The function relies on a timer
  * (in this case, TIMER0_GetTick()) to calculate the time difference for the Kalman filter.
  */

void MPU6050_Read_All(MPU6050_t *DataStruct)
{
    u8 Rec_Data[14];
    s16 temp;

    // Read 14 BYTES of data starting from ACCEL_XOUT_H register

    //HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 14, i2c_timeout);
    /* I2C READ FROM MEMORY WITH ADDRESS ACCEL_XOUT_H_REG THE OUTPUT IN Rec_Data */////////////////////////////////////////////////////////
	I2C_Mem_Read(MPU6050_ADDR, ACCEL_XOUT_H_REG, Rec_Data, 14);

    DataStruct->Accel_X_RAW = (s16) (Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y_RAW = (s16) (Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z_RAW = (s16) (Rec_Data[4] << 8 | Rec_Data[5]);
    temp = (s16) (Rec_Data[6] << 8 | Rec_Data[7]);
    DataStruct->Gyro_X_RAW = (s16) (Rec_Data[8] << 8 | Rec_Data[9]);
    DataStruct->Gyro_Y_RAW = (s16) (Rec_Data[10] << 8 | Rec_Data[11]);
    DataStruct->Gyro_Z_RAW = (s16) (Rec_Data[12] << 8 | Rec_Data[13]);

    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;
    DataStruct->Temperature = (f32) ((s16) temp / (f32) 340.0 + (f32) 36.53);
    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;

    // Kalman angle solve
    /* using Timer0 to get a tick value in Seconds */
    f64 dt = (f64) (TIMER0_GetTick() - timer);
    timer = TIMER0_GetTick();
    f64 roll;
    f64 roll_sqrt = sqrt(
            DataStruct->Accel_X_RAW * DataStruct->Accel_X_RAW + DataStruct->Accel_Z_RAW * DataStruct->Accel_Z_RAW);
    if (roll_sqrt != 0.0) {
        roll = atan(DataStruct->Accel_Y_RAW / roll_sqrt) * RAD_TO_DEG;
    } else {
        roll = 0.0;
    }
    f64 pitch = atan2(-DataStruct->Accel_X_RAW, DataStruct->Accel_Z_RAW) * RAD_TO_DEG;
    if ((pitch < -90 && DataStruct->KalmanAngleY > 90) || (pitch > 90 && DataStruct->KalmanAngleY < -90)) {
        KalmanY.angle = pitch;
        DataStruct->KalmanAngleY = pitch;
    } else {
        DataStruct->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, DataStruct->Gy, dt);
    }
    if (fabs(DataStruct->KalmanAngleY) > 90)
        DataStruct->Gx = -DataStruct->Gx;
    DataStruct->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, DataStruct->Gy, dt);

}



/**
  * @brief Updates the Kalman filter to estimate the current angle.
  * @param Kalman: Pointer to the Kalman filter structure.
  * @param newAngle: The current angle measured by the sensor.
  * @param newRate: The rate of change of the angle measured by the sensor.
  * @param dt: The time difference since the last measurement.
  * @return The updated estimated angle by the Kalman filter.
  *
  * This function takes the current angle, rate of change, and time difference as inputs and
  * updates the Kalman filter to estimate the current angle. It performs various calculations
  * involving the Kalman filter parameters such as angle, bias, and covariance matrix.
  * The result is the filtered angle estimate, which is returned by the function.
  */

f64 Kalman_getAngle(Kalman_t *Kalman, f64 newAngle, f64 newRate, f64 dt)
{
    f64 rate = newRate - Kalman->bias;
    Kalman->angle += dt * rate;

    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
    Kalman->P[0][1] -= dt * Kalman->P[1][1];
    Kalman->P[1][0] -= dt * Kalman->P[1][1];
    Kalman->P[1][1] += Kalman->Q_bias * dt;

    f64 S = Kalman->P[0][0] + Kalman->R_measure;
    f64 K[2];
    K[0] = Kalman->P[0][0] / S;
    K[1] = Kalman->P[1][0] / S;

    f64 y = newAngle - Kalman->angle;
    Kalman->angle += K[0] * y;
    Kalman->bias += K[1] * y;

    f64 P00_temp = Kalman->P[0][0];
    f64 P01_temp = Kalman->P[0][1];

    Kalman->P[0][0] -= K[0] * P00_temp;
    Kalman->P[0][1] -= K[0] * P01_temp;
    Kalman->P[1][0] -= K[1] * P00_temp;
    Kalman->P[1][1] -= K[1] * P01_temp;

    return Kalman->angle;
}

