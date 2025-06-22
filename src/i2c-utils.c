#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include "globals.h"

#define I2C_DEVICE    "/dev/i2c-1"

int fd;
int device_open = 0;
int ret;
uint8_t   buff[8];
uint16_t  temp_reading;
uint8_t   looper;

/*****************************************************
 * openI2C - opens the I2C channel file device.      *
 *****************************************************/
int openI2C( void ) {
    fd = open(I2C_DEVICE, O_RDWR);
    if (fd < 0) {
        printf("Could not open I2C device...");
        return 1;
    }
    printf("I2C device open.\r\n");
    device_open = 1;
    return 0;
}

/*****************************************************
 * readRegister - reads a single byte value from the *
 * specified address and register combination        *
 *****************************************************/
uint8_t readRegister(uint8_t addr, uint8_t reg) {
    pthread_mutex_lock(&i2cBusLock);
    uint8_t data = 0;

    if (device_open != 1) openI2C();

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        perror("Failed to set I2C address");
        pthread_mutex_unlock(&i2cBusLock);
        return 0;
    }

    if (write(fd, &reg, 1) != 1) {
        perror("Failed to write register address");
        pthread_mutex_unlock(&i2cBusLock);
        return 0;
    }

    if (read(fd, &data, 1) != 1) {
        perror("Failed to read register data");
        pthread_mutex_unlock(&i2cBusLock);
        return 0;
    }
    pthread_mutex_unlock(&i2cBusLock);

    return data;
}

/*****************************************************
 * readRegisters - reads a number of byte values     *
 * from the specified address and register           *
 * combination                                       *
 *****************************************************/
void readRegisters(uint8_t addr, uint8_t reg, uint8_t * buf, uint8_t len) {
    printf("B: buffer = %x\n", buf);
    pthread_mutex_lock(&i2cBusLock);
    if (device_open != 1) openI2C();

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        perror("Failed to set I2C address");
        pthread_mutex_unlock(&i2cBusLock);
        return;
    }

    if (write(fd, &reg, 1) != 1) {
        perror("Failed to write register address");
        pthread_mutex_unlock(&i2cBusLock);
        return;
    }

    // Read len registers...
    if (read(fd, buf, len) != len) {
            printf("Failed to read registers %2x length %2x into %8x\n", reg, len, buf);
            perror("readRegisters failed.");
            pthread_mutex_unlock(&i2cBusLock);
            return;
        } 
    pthread_mutex_unlock(&i2cBusLock);
    printf("read %02x%02x%02x%02x%02x%02x\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
}

/******************************************************
 * writeRegister - writess a single byte value to the *
 * specified address and register combination         *
 ******************************************************/
uint8_t writeRegister( uint8_t addr, uint8_t reg, uint8_t val ){

    pthread_mutex_lock(&i2cBusLock);
    //printf("writeRegister(%02x, %02x, %02x)\n", addr, reg, val);
    if ( device_open != 1 ) {
        openI2C();
    }
    if(ioctl(fd, I2C_SLAVE, addr) < 0) {
        printf("Could not set I2C device address %02x\r\n", addr);
        pthread_mutex_unlock(&i2cBusLock);
        return 0;
    }
    // Write the register number
    buff[0] = reg;
    buff[1] = val;
    if(write(fd,&buff,2) != 2) {
        printf("Could not write the pointer register and data %02x, %02x, %02x.\r\n", addr, reg, val);
        pthread_mutex_unlock(&i2cBusLock);
        return( 0 );
    }
    pthread_mutex_unlock(&i2cBusLock);
    return( 1 );
}
     
