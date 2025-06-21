#ifndef APPLICATION_USER_CORE_INC_OLED_UTILS_H_
#define APPLICATION_USER_CORE_INC_OLED_UTILS_H_

void fill_picture(uint8_t fill_Data);

void OLED_Set_Pos(uint8_t x, uint8_t y);

void OLED_Display_On(void);

void OLED_Display_Off(void);

void OLED_Clear(void);

void OLED_On(void);

void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);

void OLED_ShowNum(uint8_t x, uint8_t y, int num, uint8_t len, uint8_t size2);

void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size);

void OLED_DrawBMP(unit8_t x0, unit8_t y0, unit8_t x1, unit8_t y1, unit8_t BMP[]);

void OLED_Init(void);

#endif
