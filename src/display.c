#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "globals.h"
#include "i2c-utils.h"
#include "s0018.h"

void initDisplay( void ) {
    writeRegister( S0018_ADDR,
	           S0018_R_COMMAND,
	           S0018_R_ENTIRE_ON
                 );
    writeRegister( S0018_ADDR,
	           S0018_R_COMMAND,
	           S0018_R_NORMAL
                 );
    writeRegister( S0018_ADDR,
	           S0018_R_COMMAND,
	           S0018_R_DISP_ON
                 );
}

void processDisplay( void ) {

}

void* display_thread_function(void* arg) {
    struct timespec start, end;
    int lastFrameCounter = 0;
    int waitCount        = 0;
    systemState          = SYS_STATE_READY; 
    initDone             = 0;
	
    while(1) {
        if ( frameCounter != lastFrameCounter ) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            lastFrameCounter = frameCounter;

	          switch ( systemState ) {

			    case SYS_STATE_INIT: 
			        initDisplay();
			        break;
			  
		            case SYS_STATE_RUN:
		                processDisplay();
		                break;

    		        default:
		                // Do nothing
		        }
            clock_gettime(CLOCK_MONOTONIC, &end);
            displayFrameTimeMs = ((double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9) * 1e3;
        }
    }
    return NULL;
}
