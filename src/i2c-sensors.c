#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "globals.h"
#include "hmc5883.h"
#include "mpu6500.h"

#include "timer.h"
#include "control.h"
#include "sensors.h"
#include "display.h"

int main(int argc, char *argv[]) {
    // Configure the runtime options.
    int opt;
    showCompass = 0;
    showI2C     = 0;
    showTiming  = 0;
    showAHRS    = 0;
    
    while ((opt = getopt(argc, argv, "CITA")) != -1) {
        switch (opt) {
            case 'C':
                showCompass = 1;
                break;
            case 'I':
                showI2C = 1;
                break;
            case 'T':
                showTiming = 1;
                break;
            case 'A':
                showAHRS = 1;
                break;
        }
    }
    // Create the required threads...
    pthread_t timer_thread;
    int       timer_thread_id;
    pthread_t sensor_thread;
    int       sensor_thread_id;
    pthread_t control_thread;
    int       control_thread_id;
    pthread_t display_thread;
    int       display_thread_id;

    
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

    if (pthread_create(&display_thread, NULL, display_thread_function, &display_thread_id) != 0) {
        perror("Failed to create display thread");
        return 1;
    }

    pthread_join(timer_thread, NULL);
    pthread_join(sensor_thread, NULL);
    pthread_join(control_thread, NULL);
    pthread_join(display_thread, NULL);
    
    printf("All threads completed.\n");
    return 0;
}
