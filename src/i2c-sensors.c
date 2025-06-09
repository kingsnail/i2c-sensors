#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "globals.h"
#include "hmc5883.h"
#include "mpu6500.h"

#include "timer.h"
#include "control.h"

void* sensor_thread_function(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        printf("Thread %d: iteration %d\n", thread_id, i);
        sleep(1);  // simulate some work
    }
    return NULL;
}

int main() {
    pthread_t timer_thread;
    int       timer_thread_id;
    pthread_t sensor_thread;
    int       sensor_thread_id;
    pthread_t control_thread;
    int       control_thread_id;

    if (pthread_create(&timer_thread, NULL, timer_thread_function, &timer_thread_id) != 0) {
        perror("Failed to create timer thread");
        return 1;
    }

    if (pthread_create(&sensor_thread, NULL, sensor_thread_function, &sensor_thread_id) != 0) {
        perror("Failed to create sensor thread");
        return 1;
    }

    if (pthread_create(&control_thread, NULL, control_thread_function, &control_thread_id) != 0) {
        perror("Failed to create sensor thread");
        return 1;
    }

    pthread_join(timer_thread, NULL);
    pthread_join(sensor_thread, NULL);
    pthread_join(control_thread, NULL);
    
    printf("All threads completed.\n");
    return 0;
}
