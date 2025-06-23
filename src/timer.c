#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "globals.h"

#define INTERVAL_MS (1000 / MASTER_IT_RATE_HZ)

void* timer_thread_function(void* arg) {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = INTERVAL_MS * 1000000L;  // Convert ms to ns

    struct timespec start, end;
    double frameTimeMs = 0.0;
    while(1) {
	clock_gettime(CLOCK_MONOTONIC, &start);
	if ( (frameCounter % 10 == 0) && (showTiming == 1) ) {
	    printf("C:%0.3fms S:%0.3fms D:%0.3fms F: %0.3fms\n", controlFrameTimeMs, sensorFrameTimeMs, displayFrameTimeMs, frameTimeMs);
	}
	    
    	frameCounter++;
	    if ( frameCounter > 10000 ) {
		       frameCounter = 0;
	    }
        nanosleep(&ts, NULL);
	clock_gettime(CLOCK_MONOTONIC, &end);
        frameTimeMs = ((double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9) * 1e3;
    }
    return NULL;
}
