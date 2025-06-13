/*
 * s0018.h
 *
 *  Created on: Jun 8, 2025
 *      Author: markp
 */

#ifndef APPLICATION_USER_CORE_INC_S0018_H_
#define APPLICATION_USER_CORE_INC_S0018_H_

#define S0018_ADDR                (0x3C)

/*
 * Register Definitions
 */
#define S018_R_COMMAND          (0x80)
#define SO18_R_DATA             (0x00)

// Fundamental Commands
#define S0018_R_CONTRAST        (0x81)
#define S0018_R_ENTIRE_ON       (0xA4)
#define S0018_R_NORMAL          (0xA6)
#define S0018_R_INVERSE         (0xA7)
#define S0018_R_DISP_OFF        (0xAE)
#define S0018_R_DISP_ON         (0xAE)

#define S0018_R_MEM_ADDR        (0x20)
#define S0018_R_COL_ADDR        (0x21)
#define S0018_R_PAGE_ADDR       (0x22)
#define S0018_R_DISP_START_LINE (0x40)
#define S0018_R_SEG_REMAP       (0xA0)
#define S0018_R_MUX_RATIO       (0xA8)
#define S0018_R_COM_OUT_DIR     (0xC0)
#define S0018_R_DISP_OFFSET     (0xD3)
#define S0018_R_COM_PIN_CFG     (0xDA)
#define S0018_R_DISP_CLK_DIV    (0xD5)
#define S0018_R_PRECHARGE       (0xD9)
#define S0018_R_VCOM_DESEL      (0xDB)
#define S0018_R_CHARGE_PUMP     (0x8D)

#endif /* APPLICATION_USER_CORE_INC_S0018_H_ */
