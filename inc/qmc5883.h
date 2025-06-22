#ifndef APPLICATION_USER_CORE_INC_QMC5883L_H_
#define APPLICATION_USER_CORE_INC_QMC5883L_H_


#define QMC5883L_ADDR          (0x0D)

// Register Definitions
#define QMC5883L_REG_X_LSB     (0x00)
#define QMC5883L_REG_X_MSB     (0x01)

#define QMC5883L_REG_Z_LSB     (0x02)
#define QMC5883L_REG_Z_MSB     (0x03)

#define QMC5883L_REG_Y_LSB     (0x04)
#define QMC5883L_REG_Y_MSB     (0x05)

#define QMC5883L_REG_STATUS    (0x06)

#define QMC5883L_REG_TEMP_LSB  (0x07)
#define QMC5883L_REG_TEMP_MSB  (0x08)

#define QMC5883L_REG_CONTROL_1     (0x09)
#define   QMC5883L_MODE_STANDBY    (0x00)
#define   QMC5883L_MODE_CONTINUOUS (0x01)
#define   QMC5883L_ODR_10HZ        (0x00)
#define   QMC5883L_ODR_50HZ        (0x04)
#define   QMC5883L_ODR_100HZ       (0x08)
#define   QMC5883L_ODR_200HZ       (0x0C)
#define   QMC5883L_RNG_2G          (0x00)
#define   QMC5883L_RNG_8G          (0x10)
#define   QMC5883L_OSR_512         (0x00)
#define   QMC5883L_OSR_256         (0x40)
#define   QMC5883L_OSR_128         (0x80)
#define   QMC5883L_OSR_64          (0xC0)


#define QMC5883L_REG_CONTROL_2 (0x0A)

#define QMC5883L_REG_SR_PERIOD (0x0B)

#define QMC5883L_REG_CHIP_ID   (0x0D)

#endif /* APPLICATION_USER_CORE_INC_QMC5883L_H_ */
