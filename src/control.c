#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "globals.h"
#include "MadgwickAHRS.h"

#define INTERVAL_MS 500

int calibrateCount = 0;

void calibrateSensors( void ) {

    if ( calibrateCount == 0 ) {
        printf("Calibrating...\r\n");
    }

    //printf("..%i", calibrateCount);

    offsX += gyroX;
    offsY += gyroY;
    offsZ += gyroZ;

    if ( calibrateCount >= CALIBRATE_FRAMES ) {
	offsX /= CALIBRATE_FRAMES;
	offsY /= CALIBRATE_FRAMES;
	offsZ /= CALIBRATE_FRAMES;
	printf("OFFSETS: X:%i Y:%i Z:%i", offsX, offsY, offsZ);
	calibDone = 1;
    }
    calibrateCount++;
}

void executeFilter( void ) {
    MadgwickAHRSupdateIMU(sGyroX, sGyroY, sGyroZ, sAccX, sAccY, sAccZ);
}

void calculateAngles( void ) {
    roll  = rollOffset  + atan2f(( q0 * q1 + q2 * q3) * 2.0f, 1 - 2.0f * (q1 * q1 + q2 * q2));
    pitch = pitchOffset + asinf(( q0 * q2 - q3 * q1) * 2.0f);
    yaw   = yawOffset   + atan2f(( q0 * q3 + q1 * q2) * 2.0f, 1 - 2.0f * (q2 * q2 + q3 * q3));
}

void processFrame( void ) {
    int p = (int)(pitch * 100);
    int r = (int)(roll * 100);
    int y = (int)(yaw * 100);
    printf("AHRS: P:%i R:%i Y:%i\r\n", p, r, y);

    executeFilter();
    calculateAngles();
}


void* control_thread_function(void* arg) {

    int lastFrameCounter = 0;
    int waitCount        = 0;
    systemState          = SYS_STATE_READY; 
    initDone             = 0;
	
    while(1) {
        if ( frameCounter != lastFrameCounter ) {
            lastFrameCounter = frameCounter;
            printf("Tock %i\n", systemState);
            switch ( systemState ) {

  		case SYS_STATE_READY:
                       break;

		case SYS_STATE_ERROR:
		    waitCount = 0;
		    systemState == SYS_STATE_WAIT;
                    break;

		case SYS_STATE_RUN:
		    processFrame();
		    break;

		case SYS_STATE_CALIB:
		    if ( calibDone == 0) {
	  	        calibrateSensors();
		    } else {
			systemState = SYS_STATE_RUN;
		    }
                    break;

		case SYS_STATE_INIT:
		    if ( initDone == 1 ) {
		        systemState = SYS_STATE_CALIB;
		    }
                    break;

		case SYS_STATE_WAIT:
		    waitCount++;
		    if (waitCount > 20) {
			systemState = SYS_STATE_READY;
		    }
                    break;

		default:
		    systemState = SYS_STATE_ERROR;
		}

        }
    }
    return NULL;
}
