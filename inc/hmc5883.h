#ifndef APPLICATION_USER_CORE_INC_HMC5883L_H_
#define APPLICATION_USER_CORE_INC_HMC5883L_H_


#define HMC5883L_ADDR      (0x1e << 1)

// Register Definitions
#define HMC5883L_REG_CRA   (0x00)  // Configuration Register A
#define HMC5883L_REG_CRB   (0x01)  // Configuration Register B
#define HMC5883L_REG_MR    (0x02)  // Mode Register

#define HMC5883L_REG_X_MSB (0x03)
#define HMC5883L_REG_X_LSB (0x04)

#define HMC5883L_REG_Z_MSB (0x05)
#define HMC5883L_REG_Z_LSB (0x06)

#define HMC5883L_REG_Y_MSB (0x07)
#define HMC5883L_REG_Y_LSB (0x08)

#define HMC5883L_REG_SR    (0x09)  // Status Register

#define HMC5883L_REG_IR_A  (0x0A)  // Identification Register A
#define HMC5883L_REG_IR_B  (0x0B)  // Identification Register B
#define HMC5883L_REG_IR_C  (0x0C)  // Identification Register C

// Configuration Register A
#define HMC5883L_CRA_MA_SAMPLES_1  (0x00)
#define HMC5883L_CRA_MA_SAMPLES_2  (0x20)
#define HMC5883L_CRA_MA_SAMPLES_4  (0x40)
#define HMC5883L_CRA_MA_SAMPLES_8  (0x60)

#define HMC5883L_CRA_DO_RATE_0_75  (0x00)
#define HMC5883L_CRA_DO_RATE_1_50  (0x04)
#define HMC5883L_CRA_DO_RATE_3_00  (0x80)
#define HMC5883L_CRA_DO_RATE_7_50  (0xC0)
#define HMC5883L_CRA_DO_RATE_15_0  (0x10)
#define HMC5883L_CRA_DO_RATE_30_0  (0x14)
#define HMC5883L_CRA_DO_RATE_75_0  (0x18)

#define HMC5883L_CRA_MS_NORMAL     (0x00)
#define HMC5883L_CRA_MS_POSITIVE   (0x01)
#define HMC5883L_CRA_MS_NEGATIVE   (0x02)

// Configuration Register B
#define HMC5883L_CRB_GN_1370       (0x00)
#define HMC5883L_CRB_GN_1090       (0x20)
#define HMC5883L_CRB_GN_0820       (0x40)
#define HMC5883L_CRB_GN_0660       (0x60)
#define HMC5883L_CRB_GN_0440       (0x80)
#define HMC5883L_CRB_GN_0390       (0xA0)
#define HMC5883L_CRB_GN_0330       (0xC0)
#define HMC5883L_CRB_GN_0230       (0xE0)

// Mode Register
#define HMC5883L_MR_HS_OFF         (0x00)
#define HMC5883L_MR_HS_ON          (0x80)
#define HMC5883L_MR_MODE_CONT_M    (0x00)
#define HMC5883L_MR_MODE_SINGLE_M  (0x01)
#define HMC5883L_MR_MODE_IDLE_1    (0x02)
#define HMC5883L_MR_MODE_IDLE_2    (0x03)

// Status Register
#define HMC5883L_SR_LOCK           (0x02)
#define HMC5883L_SR_RDY            (0x01)

#endif /* APPLICATION_USER_CORE_INC_HMC5883L_H_ */
