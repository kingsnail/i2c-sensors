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

#define I2C_DEVICE    "/dev/i2c-1"

int fd;
int device_open = 0;
int ret;
uint8_t   buff[8];
uint16_t  temp_reading;
uint8_t   looper;

int openI2C( void ) {
    fd = open(I2C_DEVICE, O_RDWR);
    if (fd < 0) {
        printf("Could not open I2C device...");
        return 1;
    }
    device_open = 1;
    return 0;
}

uint8_t readRegister( uint8_t addr, uint8_t reg ){
    if ( device_open != 1 ) {
        openI2C();
    }
    if(ioctl(fd, I2C_SLAVE, addr) < 0) {
        printf("Could not set I2C device address %i\r\n", addr);
        return 0;
    }
    // Write the register number
    buff[0] = reg;
    if(write(fd,buff,1) != 1) {
        printf("Could not write the pointer register %i, %i.\r\n", addr, reg);
        return( 0 );
    }
    if(read(fd, buff, 1) != 1) {
        printf("Could not read the Device Id %i, %i\r\n", addr, reg);
        return ( 0 );
    }
    else {
        return( buff[0] );
    }
}

uint8_t writeRegister( uint8_t addr, uint8_t reg, uint8_t val ){
    if ( device_open != 1 ) {
        openI2C();
    }
    if(ioctl(fd, I2C_SLAVE, addr) < 0) {
        printf("Could not set I2C device address %i\r\n", addr);
        return 0;
    }
    // Write the register number
    buff[0] = reg;
    buff[1] = val;
    if(write(fd,buff,2) != 2) {
        printf("Could not write the pointer register and data %i, %i, %i.\r\n", addr, reg, val);
        return( 0 );
    }
    return( 1 );
}
     
