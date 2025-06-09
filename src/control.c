#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"

#define INTERVAL_MS 500

void* control_thread_function(void* arg) {

    int lastFrameCounter = 0;
    int waitCount        = 0;
    
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
			    	   //processFrame();
			    	   break;

			       case SYS_STATE_CALIB:
					   if ( calibDone == 0) {
	  				       //calibrateSensors();
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
