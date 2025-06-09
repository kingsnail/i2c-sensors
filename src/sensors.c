#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "i2c-utils.h"

#define INTERVAL_MS 500

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
                    // Do init tasks
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
