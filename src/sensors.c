#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include "globals.h"
#include "i2c-utils.h"
#include "hmc5883.h"
#include "mpu6500.h"

void initCompass( void ) {
    
	uint8_t chipidA = readRegister(HMC5883L_ADDR, HMC5883L_REG_IR_A);
	uint8_t chipidB = readRegister(HMC5883L_ADDR, HMC5883L_REG_IR_B);
	uint8_t chipidC = readRegister(HMC5883L_ADDR, HMC5883L_REG_IR_C);
	printf("HMC5883L ID=%2x%2x%2x\r\n", chipidA, chipidB, chipidC);

	writeRegister(HMC5883L_ADDR,
		      HMC5883L_REG_MR,
	 	      HMC5883L_MR_HS_OFF | HMC5883L_MR_MODE_SINGLE_M
	             );

	uint8_t mode = readRegister(HMC5883L_ADDR, HMC5883L_REG_MR);
	printf("Mode = %2x\r\n", mode);

	writeRegister(HMC5883L_ADDR,
	 	      HMC5883L_REG_MR,
	 	      HMC5883L_MR_HS_OFF | HMC5883L_MR_MODE_CONT_M
                     );

	mode = readRegister(HMC5883L_ADDR, HMC5883L_REG_MR);
	printf("Mode = %2x\r\n", mode);

}

void initIMU( void ) {
	
    uint8_t chipId = readRegister(MPU6500_ADDR, MPU6500_R_WHO_AM_I);
    printf("MPU6500 id = %02x\n", chipId);
	
    writeRegister(MPU6500_ADDR,
	 	  MPU6500_R_PWR_MGMT_1,
	 	  0x00
                 );
    writeRegister(MPU6500_ADDR,
	 	  MPU6500_R_GYRO_CONFIG,
	 	  0x00
                 );
    writeRegister(MPU6500_ADDR,
	 	  MPU6500_R_ACCEL_CONFIG,
	 	  0x00
                 );
	
}

void initDisplay( void ) {

}

void readCompass( void ) {
    uint8_t dataXMSB = readRegister(HMC5883L_ADDR, HMC5883L_REG_X_MSB);
    uint8_t dataXLSB = readRegister(HMC5883L_ADDR, HMC5883L_REG_X_LSB);
    compX            = (int16_t)(((uint16_t)dataXMSB << 8) | (uint16_t)dataXLSB);

    uint8_t dataYMSB = readRegister(HMC5883L_ADDR, HMC5883L_REG_Y_MSB);
    uint8_t dataYLSB = readRegister(HMC5883L_ADDR, HMC5883L_REG_Y_LSB);
    compX            = (int16_t)(((uint16_t)dataYMSB << 8) | (uint16_t)dataYLSB);

    uint8_t dataZMSB = readRegister(HMC5883L_ADDR, HMC5883L_REG_Z_MSB);
    uint8_t dataZLSB = readRegister(HMC5883L_ADDR, HMC5883L_REG_Z_LSB);
    compX            = (int16_t)(((uint16_t)dataZMSB << 8) | (uint16_t)dataZLSB);
	
    //printf("Compass = %2x%2x, %2x%2x, %2x%2x\n", dataXMSB, dataXLSB, dataYMSB, dataYLSB, dataZMSB, dataZLSB );

}

void readIMU( void ) {
    uint8_t dataXMSB = readRegister(MPU6500_ADDR, MPU6500_R_ACCEL_XOUT_H );
    uint8_t dataXLSB = readRegister(MPU6500_ADDR, MPU6500_R_ACCEL_XOUT_L );
    accX             = (int16_t)(((uint16_t)dataXMSB << 8) | (uint16_t)dataXLSB);

    uint8_t dataYMSB = readRegister(MPU6500_ADDR, MPU6500_R_ACCEL_YOUT_H );
    uint8_t dataYLSB = readRegister(MPU6500_ADDR, MPU6500_R_ACCEL_YOUT_L );
    accY             = (int16_t)(((uint16_t)dataYMSB << 8) | (uint16_t)dataYLSB);
    
    uint8_t dataZMSB = readRegister(MPU6500_ADDR, MPU6500_R_ACCEL_ZOUT_H );
    uint8_t dataZLSB = readRegister(MPU6500_ADDR, MPU6500_R_ACCEL_ZOUT_L );
    accZ             = (int16_t)(((uint16_t)dataZMSB << 8) | (uint16_t)dataZLSB);
	
    uint8_t gyroXMSB = readRegister(MPU6500_ADDR, MPU6500_R_GYRO_X_OUT_H );
    uint8_t gyroXLSB = readRegister(MPU6500_ADDR, MPU6500_R_GYRO_X_OUT_L );
    gyroX            = (int16_t)(((uint16_t)gyroXMSB << 8) | (uint16_t)gyroXLSB);

    uint8_t gyroYMSB = readRegister(MPU6500_ADDR, MPU6500_R_GYRO_Y_OUT_H );
    uint8_t gyroYLSB = readRegister(MPU6500_ADDR, MPU6500_R_GYRO_Y_OUT_L );
    gyroY            = (int16_t)(((uint16_t)gyroYMSB << 8) | (uint16_t)gyroYLSB);

    uint8_t gyroZMSB = readRegister(MPU6500_ADDR, MPU6500_R_GYRO_Z_OUT_H );
    uint8_t gyroZLSB = readRegister(MPU6500_ADDR, MPU6500_R_GYRO_Z_OUT_L );
    gyroX            = (int16_t)(((uint16_t)gyroZMSB << 8) | (uint16_t)gyroZLSB);

    //printf("ACC:%04x, %04x, %04x GYRO:%04x, %04x, %04x\n", accX, accY, accZ, gyroX, gyroY, gyroZ );

    // Scale the raw data values to their float equivalents
    sAccX  = accX  * 1.0/256.0;
    sAccY  = accY  * 1.0/256.0;
    sAccZ  = accZ  * 1.0/256.0;

    sGyroX = ((gyroX - offsX) / 131.0f) * M_PI / 180.0f;
    sGyroY = ((gyroY - offsY) / 131.0f) * M_PI / 180.0f;
    sGyroZ = ((gyroZ - offsZ) / 131.0f) * M_PI / 180.0f;

}

void* sensor_thread_function(void* arg) {

    int lastFrameCounter = 0;
    struct timespec start, end;
    while(1) {
        if ( frameCounter != lastFrameCounter ) {
            clock_gettime(CLOCK_MONOTONIC, &start);
	    lastFrameCounter = frameCounter;
            switch( systemState ) {
                
                case SYS_STATE_READY :
                    systemState = SYS_STATE_INIT;
                    break;
                
                case SYS_STATE_INIT :
		    if  ( initDone != 1 ) {
                        //initCompass();
                        initIMU();
                        initDisplay();
                        initDone = 1; 
		    }
		    break;
                
                case SYS_STATE_CALIB :
                    // read sensors for calibration
		    //readCompass();
		    readIMU();
                    break;

                case SYS_STATE_RUN :
                    //read sensors for operation
		    //readCompass();
                    readIMU();
		    break;
            }
	    clock_gettime(CLOCK_MONOTONIC, &end);
	    double elapsed = ((double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9) * 1e3;
            printf("Sense: %0.3fms\n", elapsed);
        }
    }
    return NULL;
}
