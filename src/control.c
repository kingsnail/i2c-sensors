#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"

#define INTERVAL_MS 500

void* control_thread_function(void* arg) {

    int lastFrameCounter = 0;
  
    while(1) {
        if ( frameCounter != lastFrameCounter ) {
            lastFrameCounter = frameCounter;
            printf("Tock\n");
        }
        return NULL;
    }
}
