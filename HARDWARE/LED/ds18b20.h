#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   

////IO��������											   
#define	   DS18B20_DQ_IN  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)  //���ݶ˿�	PA0 

#define    DS18B20_DQ_OUT(x)  x ? HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET)


u8 DS18B20_Init(void);//��ʼ��DS18B20
short DS18B20_Get_Temp(void);//��ȡ�¶�
void DS18B20_Start(void);//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);//����һ���ֽ�
u8 DS18B20_Read_Bit(void);//����һ��λ
u8 DS18B20_Check(void);//����Ƿ����DS18B20
void DS18B20_Rst(void);//��λDS18B20 




#endif















