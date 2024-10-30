#ifndef __LCD1602_H
#define __LCD1602_H

#include "sys.h"

#define    LCD_RS(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET)
#define    LCD_RW(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET)
#define    LCD_EN(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET): HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET)

#define data0(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET)
#define data1(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET)
#define data2(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET)
#define data3(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET)
#define data4(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET)
#define data5(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET)
#define data6(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET)
#define data7(x)  x ? HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET)


void LCD_init                     (void);
void LCD_write_cmd          (unsigned char cmd);
void LCD_write_data         (unsigned char w_data);
void LCD_Write_byte    (unsigned char half_byte);
void LCD_set_xy             (unsigned char x, unsigned char y);
void LCD_write_string       (unsigned char X,unsigned char Y, char *s);


void LCD_wstring(unsigned char X,unsigned char *s);
//==================================================


void lcd_delay_us(unsigned int t);
void lcd_delay_ms(unsigned int t);



#endif


