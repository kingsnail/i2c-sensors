/*
 * globals.h
 *
 *  Created on: Jun 1, 2025
 *      Author: markp
 */


#ifndef APPLICATION_USER_CORE_INC_GLOBALS_H_
#define APPLICATION_USER_CORE_INC_GLOBALS_H_

#include <stdint.h>
#include <pthread.h>

extern pthread_mutex_t i2cBusLock;

#define SYS_STATE_STOP     ( 0 )
#define SYS_STATE_READY    ( 1 )
#define SYS_STATE_INIT     ( 2 )
#define SYS_STATE_CALIB    ( 3 )
#define SYS_STATE_ORIENT   ( 4 )
#define SYS_STATE_RUN      ( 5 )
#define SYS_STATE_ERROR    ( 6 )
#define SYS_STATE_WAIT     ( 7 )

#define MASTER_IT_RATE_HZ  ( 20 )
#define CALIBRATE_FRAMES   ( 500 )
#define ORIENTATE_FRAMES   ( 200 )
#define ERROR_WAIT_FRAMES  ( 20 )

extern volatile int systemState;

extern volatile int frameCounter;
extern volatile int initDone;
extern volatile int calibDone;
extern volatile int orientDone;

extern volatile int16_t  compX;
extern volatile int16_t  compY;
extern volatile int16_t  compZ;

extern volatile int16_t accX;
extern volatile int16_t accY;
extern volatile int16_t accZ;

extern volatile int16_t  gyroX;
extern volatile int16_t  gyroY;
extern volatile int16_t  gyroZ;

extern volatile int     offsX;
extern volatile int     offsY;
extern volatile int     offsZ;

extern volatile float  sCompX;
extern volatile float  sCompY;
extern volatile float  sCompZ;

extern volatile float  sAccX;
extern volatile float  sAccY;
extern volatile float  sAccZ;

extern volatile float  sGyroX;
extern volatile float  sGyroY;
extern volatile float  sGyroZ;

extern volatile float    pitch;
extern volatile float    roll;
extern volatile float    yaw;

extern volatile float    pitchOffset;
extern volatile float    rollOffset;
extern volatile float    yawOffset;

extern volatile double   sensorFrameTimeMs;
extern volatile double   controlFrameTimeMs;
extern volatile double   displayFrameTimeMs;

#endif /* APPLICATION_USER_CORE_INC_GLOBALS_H_ */

