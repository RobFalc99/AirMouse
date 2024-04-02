/*
 * mpu_6050.h
 *
 *  Created on: May 26, 2022
 *      Author: Acer
 */

#ifndef INC_MPU_6050_H_
#define INC_MPU_6050_H_

#define MPU6050_ADDRESS 0x68 << 1

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define TEMP_OUT_H_REG 0x41
#define PWR_MGMT_REG 0x6B		// Power management register
#define ADDRESS_REGISTER 0x75

#define ACCEL_OUT_REG 0x3B
#define GYRO_OUT_REG 0x43

#include "stdint.h"

typedef struct {
	float x_accel;
	float y_accel;
	float z_accel;
	float x_rot;
	float y_rot;
	float z_rot;
} MPU6050Sensor;

void MPU6050_Init(void);

void get_acceleration(void);
void get_rotation(void);
void MPU6050_Calibration(void);

#endif /* INC_MPU_6050_H_ */
