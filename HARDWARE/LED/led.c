#include "led.h"
                             
#define DELAY_2N     0

void lcd_delay_us(unsigned int t)
{
	unsigned int i, j;
	
	for(i = 10; i > 0; i--)
		for(j = t; j > 0; j--);
}

void lcd_delay_ms(unsigned int t)
{	
	unsigned int i;
	
	for(i = t; i > 0; i--)
		lcd_delay_us(10);
}

//==================================================
void LCD_init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOC_CLK_ENABLE();           	//开启GPIOA时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10; 
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);

    LCD_RW(0);			//读写位直接低电平，只写不读

    /*********************液晶初始化**************************/        
    lcd_delay_us(340); 
		LCD_RS(0);
   
    LCD_write_cmd(0x38);          // 8bit显示模式,2行,5x7字体
    lcd_delay_ms(4);  
    LCD_write_cmd(0x08);         // 显示关闭 
    lcd_delay_ms(4); 
    LCD_write_cmd(0x01);         // 显示清屏 
    lcd_delay_ms(4); 
    LCD_write_cmd(0x06);         // 显示光标移动设置 
    lcd_delay_ms(4);
    LCD_write_cmd(0x0c);         // 显示开，光标开，光标闪烁
    lcd_delay_ms(4);
		LCD_write_cmd(0x01);         //清屏
		lcd_delay_ms(4);
}
/*--------------------------------------------------
函数说明：写命令到液晶


---------------------------------------------------*/
void LCD_write_cmd(unsigned char cmd)
{
    LCD_RS(0);
    LCD_Write_byte(cmd);
    lcd_delay_us(340);
}
/*--------------------------------------------------
函数说明：写数据到液晶


---------------------------------------------------*/
void LCD_write_data(unsigned char w_data)
{
    LCD_RS(1);
    LCD_Write_byte(w_data);
    lcd_delay_us(340);
}
/*--------------------------------------------------
函数说明：写4bit到液晶
--------------------------------------------------*/
void LCD_Write_byte(unsigned char num)
{  
		if (num&0x01)
				data0(1);
		else
				data0(0);

		if (num&0x02)
				data1(1);
		else
				data1(0);

		if (num&0x04)
				data2(1);
		else
				data2(0);

		if (num&0x08)
				data3(1);
		else
				data3(0);

		if (num&0x10)
				data4(1);
		else
				data4(0);

		if (num&0x20)
				data5(1);
		else
				data5(0);

		if (num&0x40)
				data6(1);
		else
				data6(0);
		
		if (num&0x80)
				data7(1);
		else
				data7(0);
		lcd_delay_us(340);
    LCD_EN(1);
    lcd_delay_us(340);
    LCD_EN(0); 
    lcd_delay_us(340);
}

/*----------------------------------------------------
LCD_set_xy        : 设置LCD显示的起始位置
输入参数：x、y    : 显示字符串的位置，X:0-15，Y:0-1                
-----------------------------------------------------*/
void LCD_set_xy( unsigned char x, unsigned char y )
{
    unsigned char address = 0;
    if (y==0) 
    {
        address=0x80+x;
    }
    else 
    {
        address=0xc0+x;
    }
//		y ? (address=0xc0+x): (address=0x80+x) ;
    LCD_write_cmd(address);
}
/*---------------------------------------------------
LCD_write_string  : 英文字符串显示函数
输入参数：*s      ：英文字符串指针；
          X、Y    : 显示字符串的位置                
---------------------------------------------------*/
void LCD_write_string(unsigned char X,unsigned char Y, char *s)
{
    LCD_set_xy(X,Y);   
    while (*s) 
    {
        LCD_write_data(*s);
        s++;
    }
}

//=======================================================
void LCD_wstring(unsigned char X,unsigned char *s)
{
    LCD_write_cmd(X);   
    while (*s) 
    {
        LCD_write_data(*s);
        s++;
    }
}
