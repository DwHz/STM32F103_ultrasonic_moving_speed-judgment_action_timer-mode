#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"



#define    TRIG_Send(x)  x ? HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET):  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)


#define    ECHO_Reci        HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)


extern TIM_HandleTypeDef TIM3_Handler;      //¶¨Ê±Æ÷¾ä±ú 

void TIM3_Init(u16 arr,u16 psc);

void SRF04_init(void);

float Hcsr04GetLength(void );




#endif





