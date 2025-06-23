#include <stdint.h>
#include <pthread.h>

pthread_mutex_t i2cBusLock = PTHREAD_MUTEX_INITIALIZER;

volatile int systemState  = 0;
volatile int frameCounter = 0;
volatile int initDone     = 0;
volatile int calibDone    = 0;
volatile int orientDone   = 0;

// Runtime Options 


volatile int16_t  accX    = 0;
volatile int16_t  accY    = 0;
volatile int16_t  accZ    = 0;

volatile int16_t  gyroX   = 0;
volatile int16_t  gyroY   = 0;
volatile int16_t  gyroZ   = 0;

volatile int      offsX   = 0;
volatile int      offsY   = 0;
volatile int      offsZ   = 0;

volatile int16_t  compX   = 0;
volatile int16_t  compY   = 0;
volatile int16_t  compZ   = 0;

volatile float    sCompX  = 0.0;
volatile float    sCompY  = 0.0;
volatile float    sCompZ  = 0.0;

volatile float    sAccX   = 0.0;
volatile float    sAccY   = 0.0;
volatile float    sAccZ   = 0.0;

volatile float    sGyroX  = 0.0;
volatile float    sGyroY  = 0.0;
volatile float    sGyroZ  = 0.0;

volatile float    pitch   = 0.0;
volatile float    roll    = 0.0;
volatile float    yaw     = 0.0;

volatile float    pitchOffset = 0.0f;
volatile float    rollOffset  = 0.0f;
volatile float    yawOffset   = 0.0f;

volatile double   sensorFrameTimeMs  = 0.0;
volatile double   controlFrameTimeMs = 0.0;
volatile double   displayFrameTimeMs = 0.0;
