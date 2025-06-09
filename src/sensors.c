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
    
	uint8_t chipidA = ReadRegister(HMC5883L_ADDR, HMC5883L_REG_IR_A);
	uint8_t chipidB = ReadRegister(HMC5883L_ADDR, HMC5883L_REG_IR_B);
	uint8_t chipidC = ReadRegister(HMC5883L_ADDR, HMC5883L_REG_IR_C);
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
                    initCompass();
                    initIMU();
                    initDisplay();
                    initDone = 1; 
                    break;
                
                case SYS_STATE_CALIB :
                    // read sensors for calibration
                    break;

                case SYS_STATE_RUN :
                    //read sensors for operation
                    break;
            }
        }
    }
    return NULL;
}
