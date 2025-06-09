#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define INTERVAL_MS 500

void* timer_thread_function(void* arg) {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = INTERVAL_MS * 1000000L;  // Convert ms to ns

    while(1) {
        printf("Tick\n");
    	frameCounter++;
	    if ( frameCounter > 10000 ) {
		       frameCounter = 0;
	    }
        nanosleep(&ts, NULL);
    }
    return NULL;
}



    while ( 1 ) {

    	minorCount = 0;
    	osDelay(0);
    }
