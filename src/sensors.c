#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include "globals.h"
#include "i2c-utils.h"
#include "qmc5883.h"
#include "mpu6500.h" 

int calibrateCount = 0;
int orientateCount = 0;

void initCompass( void ) {
    
	uint8_t chipid = readRegister(QMC5883L_ADDR, QMC5883L_REG_CHIP_ID);
	printf("QMC5883L ID=%2x\r\n", chipid);

	writeRegister(QMC5883L_ADDR,
	 	      QMC5883L_REG_CONTROL_1,
	 	      QMC5883L_MODE_CONTINUOUS || QMC5883L_ODR_50HZ || QMC5883L_RNG_8G || QMC5883L_OSR_128
                     );

	writeRegister(QMC5883L_ADDR,
	 	      QMC5883L_REG_SR_PERIOD,
  	              QMC5883L_INT_ENABLE || 0x02
		     );
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

    writeRegister(MPU6500_ADDR,
	 	  MPU6500_R_SMPLRT_DIV,
	 	  0x31 // 49
                 );
	
}

void calibrateSensors( void ) {

    if ( calibrateCount == 0 ) {
        printf("Calibrating...\r\n");
    }

    //printf("..%i", calibrateCount);

    offsX += (int)gyroX;
    offsY += (int)gyroY;
    offsZ += (int)gyroZ;

    if ( calibrateCount >= CALIBRATE_FRAMES ) {
	// Define the gyro offsets
	offsX /= CALIBRATE_FRAMES;
	offsY /= CALIBRATE_FRAMES;
	offsZ /= CALIBRATE_FRAMES;
	printf("OFFSETS: X:%i Y:%i Z:%i\n", offsX, offsY, offsZ);
        
	// write the offsets to the MPU6500
        writeRegister(MPU6500_ADDR,
  	 	      MPU6500_R_XG_OFFSET_L ,   
	 	      (uint8_t)(offsX && 0xFF)
                     );	    
        writeRegister(MPU6500_ADDR,
  	 	      MPU6500_R_XG_OFFSET_H ,   
	 	      (uint8_t)((offsX >> 8 )&& 0xFF)
                     );
        writeRegister(MPU6500_ADDR,
  	 	      MPU6500_R_YG_OFFSET_L ,   
	 	      (uint8_t)(offsX && 0xFF)
                     );
	    
        writeRegister(MPU6500_ADDR,
  	 	      MPU6500_R_YG_OFFSET_H ,   
	 	      (uint8_t)((offsX >> 8 )&& 0xFF)
                     );
        writeRegister(MPU6500_ADDR,
  	 	      MPU6500_R_ZG_OFFSET_L ,   
	 	      (uint8_t)(offsX && 0xFF)
                     );
	    
        writeRegister(MPU6500_ADDR,
  	 	      MPU6500_R_ZG_OFFSET_H ,   
	 	      (uint8_t)((offsX >> 8 )&& 0xFF)
                     );
	    
	    
	// Trigger calibration mode exit
	calibDone = 1;
    }
    calibrateCount++;
}

void orientateSensors( void ) {

    if ( orientateCount == 0 ) {
        printf("Orientating...\r\n");
	pitchOffset = 0;
	rollOffset  = 0;
	yawOffset   = 0;
    }

    if ( (orientateCount >= ORIENTATE_FRAMES) && ( orientDone != 1 ) ) {
	// Define the attitude offsets
	pitchOffset = -pitch;
	rollOffset  = -roll;
	yawOffset   = -yaw;
	printf("Orient: %i, %i, %i \n", (int)pitch, (int)roll,  (int)yaw );
	orientDone = 1;
    }
    orientateCount++;
}

void readCompass( void ) {
    uint8_t buffer[6];
    if ( showCompass == 1) { printf("A:buffer=%x \n", &buffer[0]); }
    readRegisters(QMC5883L_ADDR, QMC5883L_REG_X_LSB, buffer, 6 );
    if ( showCompass == 1 ) {
	printf("C:buffer=%02x%02x%02x%02x%02x%02x\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
    }
    compX = (int16_t)(((uint16_t)buffer[1] << 8) | (uint16_t)buffer[0]);
    compY = (int16_t)(((uint16_t)buffer[3] << 8) | (uint16_t)buffer[2]);
    compZ = (int16_t)(((uint16_t)buffer[5] << 8) | (uint16_t)buffer[4]);
	
    //uint8_t dataXMSB = readRegister(QMC5883L_ADDR, QMC5883L_REG_X_MSB);
    //uint8_t dataXLSB = readRegister(QMC5883L_ADDR, QMC5883L_REG_X_LSB);
    //compX            = (int16_t)(((uint16_t)dataXMSB << 8) | (uint16_t)dataXLSB);

    //uint8_t dataYMSB = readRegister(QMC5883L_ADDR, QMC5883L_REG_Y_MSB);
    //uint8_t dataYLSB = readRegister(QMC5883L_ADDR, QMC5883L_REG_Y_LSB);
    //compX            = (int16_t)(((uint16_t)dataYMSB << 8) | (uint16_t)dataYLSB);

    //uint8_t dataZMSB = readRegister(QMC5883L_ADDR, QMC5883L_REG_Z_MSB);
    //uint8_t dataZLSB = readRegister(QMC5883L_ADDR, QMC5883L_REG_Z_LSB);
    //compX            = (int16_t)(((uint16_t)dataZMSB << 8) | (uint16_t)dataZLSB);

    if ( showCompass == 1 ) {
        printf("Compass = %i, %i, %i\n", compX, compY, compZ );
    } 
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

    sGyroX = (gyroX / 131.0f) * M_PI / 180.0f;
    sGyroY = (gyroY / 131.0f) * M_PI / 180.0f;
    sGyroZ = (gyroZ / 131.0f) * M_PI / 180.0f;

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
                        initCompass();
                        initIMU();
                        initDone       = 1; 
			calibrateCount = 0;
			orientateCount = 0;
			pitchOffset = 0;
	                rollOffset  = 0;
	                yawOffset   = 0;
		    }
		    break;
                
                case SYS_STATE_CALIB :
                    // read sensors for calibration
		    readCompass();
		    readIMU();
		    calibrateSensors();
                    break;
		    
		case SYS_STATE_ORIENT :
		    readCompass();
		    readIMU();
                    orientateSensors();
		    break;

                case SYS_STATE_RUN :
                    //read sensors for operation
		    readCompass();
                    readIMU();
		    break;
            }
	    clock_gettime(CLOCK_MONOTONIC, &end);
	    sensorFrameTimeMs = MAX( sensorFrameTimeMs, ((double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9) * 1e3);
        }
    }
    return NULL;
}
