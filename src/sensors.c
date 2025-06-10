#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "globals.h"
#include "i2c-utils.h"
#include "hmc5883.h"

#define INTERVAL_MS 500

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
	
    printf("Compass = %2x%2x, %2x%2x, %2x%2x\n", dataXMSB, dataXLSB, dataYMSB, dataYLSB, dataZMSB, dataZLSB );

}

void* sensor_thread_function(void* arg) {

    int lastFrameCounter = 0;
  
    while(1) {
        if ( frameCounter != lastFrameCounter ) {
            lastFrameCounter = frameCounter;
            printf("Sense\n");
            switch( systemState ) {
                
                case SYS_STATE_READY :
                    systemState = SYS_STATE_INIT;
                    break;
                
                case SYS_STATE_INIT :
		    if  ( initDone != 1 ) {
                        initCompass();
                        initIMU();
                        initDisplay();
                        initDone = 1; 
		    }
		    break;
                
                case SYS_STATE_CALIB :
                    // read sensors for calibration
		    readCompass();
                    break;

                case SYS_STATE_RUN :
                    //read sensors for operation
		    readCompass();
                    break;
            }
        }
    }
    return NULL;
}
