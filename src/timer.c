#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "globals.h"

#define INTERVAL_MS 100

void* timer_thread_function(void* arg) {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = INTERVAL_MS * 1000000L;  // Convert ms to ns

    struct timespec start, end;
	
    while(1) {
	if ( frameCounter % 20 == 0 ) {
	    printf("C:%0.3fms S:%0.3fms\n", controlFrameTimeMs, sensorFrameTimeMs);
	}
	    
    	frameCounter++;
	    if ( frameCounter > 10000 ) {
		       frameCounter = 0;
	    }
        nanosleep(&ts, NULL);
    }
    return NULL;
}
