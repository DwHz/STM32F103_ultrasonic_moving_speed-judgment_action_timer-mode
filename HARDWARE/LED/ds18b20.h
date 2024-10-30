#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   

////IO操作函数											   
#define	   DS18B20_DQ_IN  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)  //数据端口	PA0 

#define    DS18B20_DQ_OUT(x)  x ? HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET)


u8 DS18B20_Init(void);//初始化DS18B20
short DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);//读出一个字节
u8 DS18B20_Read_Bit(void);//读出一个位
u8 DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20 




#endif















