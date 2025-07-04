#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "globals.h"
#include "i2c-utils.h"
#include "oled-utils.h"

void initDisplay( void ) {
    OLED_Init();
    OLED_Display_On();
    OLED_Clear();
    OLED_ShowChar( 0, 0,  'A', 8);
    OLED_ShowChar( 8, 0,  'B', 8);
}

void processDisplay( void ) {
    switch ( frameCounter % 8 ) {
        case 0:
            OLED_ShowChar( 0, 0, 'M', 8);
            OLED_ShowChar( 8, 0, ':', 8);
	    break;
	case 1:
            OLED_ShowChar( 0, 1, 'P', 8);
            OLED_ShowChar( 8, 1, ':', 8);
	    break;
	case 2: 
            OLED_ShowChar( 0, 2, 'R', 8);
            OLED_ShowChar( 8, 2, ':', 8);
	    break;
	case 3:
            OLED_ShowChar( 0, 3, 'Y', 8);
            OLED_ShowChar( 8, 3, ':', 8);
	    break;
	case 4:
            OLED_ShowNum(  16, 0, systemState, 1, 8);
	    break;
	case 5:
            if ( pitch < 0 ) {
                OLED_ShowChar( 16, 1, '-', 8); 
            } else {
                OLED_ShowChar( 16, 1, '+', 8); 
            }
            OLED_ShowNum(  20, 1, abs( (int)pitch ), 3, 8);
	    break;
	case 6:
            if ( roll < 0 ) {
                OLED_ShowChar( 16, 2, '-', 8); 
            } else {
                OLED_ShowChar( 16, 2, '+', 8); 
            }
            OLED_ShowNum(  20, 2, abs( (int)roll ), 3, 8);
	    break;
	case 7:
            if ( yaw < 0 ) {
                OLED_ShowChar( 16, 3, '-', 8); 
            } else {
                OLED_ShowChar( 16, 3, '+', 8); 
            }
            OLED_ShowNum(  20, 3, abs( (int)yaw ), 3, 8);
	    break;
     }
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
				dispInitDone = 1;
			        break;
			  
		            case SYS_STATE_RUN:
	  		    case SYS_STATE_CALIB:
			    case SYS_STATE_ORIENT:
				processDisplay();
		                break;

    		        default:
		                // Do nothing
		        }
            clock_gettime(CLOCK_MONOTONIC, &end);
            displayFrameTimeMs = MAX( displayFrameTimeMs, ((double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9) * 1e3);
        }
    }
    return NULL;
}
