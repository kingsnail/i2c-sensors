/*
 * control.h
 *
 *  Created on: Jun 3, 2025
 *      Author: markp
 */

#ifndef APPLICATION_USER_CORE_INC_I2C_UTILS_H_
#define APPLICATION_USER_CORE_INC_I2C_UTILS_H_

#include <stdint.h>

uint8_t readRegister( uint8_t addr, uint8_t reg );

uint8_t writeRegister( uint8_t addr, uint8_t reg, uint8_t val )

#endif /* APPLICATION_USER_CORE_INC_I2C_UTILS_H_ */
