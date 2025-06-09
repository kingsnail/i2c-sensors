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
        printf("Tick\n" );
        nanosleep(&ts, NULL);
    }
    return NULL;
}
