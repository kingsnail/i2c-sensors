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
    uint8_t data = 0;

    if (device_open != 1) openI2C();

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        perror("Failed to set I2C address");
        return 0;
    }

    if (write(fd, &reg, 1) != 1) {
        perror("Failed to write register address");
        return 0;
    }

    if (read(fd, &data, 1) != 1) {
        perror("Failed to read register data");
        return 0;
    }

    return data;
}



/******************************************************
 * writeRegister - writess a single byte value to the *
 * specified address and register combination         *
 ******************************************************/
uint8_t writeRegister( uint8_t addr, uint8_t reg, uint8_t val ){
    if ( device_open != 1 ) {
        openI2C();
    }
    if(ioctl(fd, I2C_SLAVE, addr) < 0) {
        printf("Could not set I2C device address %02x\r\n", addr);
        return 0;
    }
    // Write the register number
    buff[0] = reg;
    buff[1] = val;
    if(write(fd,&buff,2) != 2) {
        printf("Could not write the pointer register and data %02x, %02x, %02x.\r\n", addr, reg, val);
        return( 0 );
    }
    printf("writeRegister(%02x, %02x, %02x)\n", addr, reg, val);
    return( 1 );
}
     
