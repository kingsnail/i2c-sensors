#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "globals.h"
#include "MadgwickAHRS.h"

void executeFilter( void ) {
    //MadgwickAHRSupdateIMU(sGyroX, sGyroY, sGyroZ, sAccX, sAccY, sAccZ);
    MadgwickAHRSupdate(sGyroX, sGyroY, sGyroZ, sAccX, sAccY, sAccZ, sCompX, sCompY, sCompZ);
}

void calculateAngles( void ) {
    roll  = rollOffset  + (atan2f(( q0 * q1 + q2 * q3) * 2.0f, 1 - 2.0f * (q1 * q1 + q2 * q2))) * 180.00 / M_PI;
    pitch = pitchOffset + (asinf(( q0 * q2 - q3 * q1) * 2.0f)) * 180.00 / M_PI;
    yaw   = yawOffset   + (atan2f(( q0 * q3 + q1 * q2) * 2.0f, 1 - 2.0f * (q2 * q2 + q3 * q3))) * 180.00 / M_PI;

    if ( roll >= 360.0 ) {
        roll = roll - 360.0f;
    }
    if ( pitch >= 360.0 ) {
        pitch = pitch - 360.0f;
    }
    if ( yaw >= 360.0 ) {
        yaw = yaw - 360.0f;
    }
}

void processFrame( void ) {
    if ( showAHRS == 1 ) {
        printf("AHRS: M:%i P:%03f\t R:%03f\t Y:%03f\r\n", systemState, pitch, roll, yaw);
    }
    //printf("q0:%f q1:%f q2:%f q3:%f\n", q0, q1, q2, q3 );
    executeFilter();
    calculateAngles();
}


void* control_thread_function(void* arg) {
    struct timespec start, end;
    int lastFrameCounter = 0;
    int waitCount        = 0;
    systemState          = SYS_STATE_READY; 
    initDone             = 0;
    initDisplayDone      = 0;
	
    while(1) {
        if ( frameCounter != lastFrameCounter ) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            lastFrameCounter = frameCounter;

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
		    processFrame();
		    if ( calibDone == 1) {
			systemState = SYS_STATE_ORIENT;
			orientDone = 0;
		    }
                    break;

		case SYS_STATE_ORIENT :
		    processFrame();
                    if ( orientDone == 1 ) {
			systemState = SYS_STATE_RUN;
		    break;
		    
		case SYS_STATE_INIT:
		    if ( initDone == 1 ) {
		        systemState = SYS_STATE_CALIB;
		        sensorFrameTimeMs  = 0.0;
                        controlFrameTimeMs = 0.0;
                        displayFrameTimeMs = 0.0;
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
            clock_gettime(CLOCK_MONOTONIC, &end);
            controlFrameTimeMs = MAX( controlFrameTimeMs, ((double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9) * 1e3);
            }
        }
    }
    return NULL;
}
