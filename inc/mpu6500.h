*
 * mpu6500.h
 *
 *  Created on: Jun 8, 2025
 *      Author: markp
 */

#ifndef APPLICATION_USER_CORE_INC_MPU6500_H_
#define APPLICATION_USER_CORE_INC_MPU6500_H_

#define MPU6500_ADDR    (0x68 << 1)

/*
 * Register Definitions
 */

#define MPU6500_R_INT_PIN_CFG     (0x37)
#define MPU6500_R_ACCEL_X_OUT_H   (0x3B)
#define MPU6500_R_ACCEL_X_OUT_L   (0x3C)
#define MPU6500_R_ACCEL_Y_OUT_H   (0x3D)
#define MPU6500_R_ACCEL_Y_OUT_L   (0x3E)
#define MPU6500_R_ACCEL_Z_OUT_H   (0x3F)
#define MPU6500_R_ACCEL_Z_OUT_L   (0x40)
#define MPU6500_R_TEMP_OUT_H      (0x41)
#define MPU6500_R_TEMP_OUT_L      (0x42)
#define MPU6500_R_GYRO_X_OUT_H    (0x43)
#define MPU6500_R_GYRO_X_OUT_L    (0x44)
#define MPU6500_R_GYRO_Y_OUT_H    (0x45)
#define MPU6500_R_GYRO_Y_OUT_L    (0x46)
#define MPU6500_R_GYRO_Z_OUT_H    (0x47)
#define MPU6500_R_GYRO_Z_OUT_L    (0x48)

#define MPU6500_R_USER_CTRL       (0x6A)
#define MPU6500_R_PWR_MGMT_1      (0x6B)
#define MPU6500_R_WHO_AM_I        (0x75)

#endif /* APPLICATION_USER_CORE_INC_MPU6500_H_ */
