// led.h
#ifndef LED_H
#define LED_H

#include "stm32f1xx_hal.h"

// LED ??(??????????)
#define LED_MEASURE_FAILED      0
#define LED_HUMAN_APPROACHING   1
#define LED_HUMAN_LEAVING       2

// ????
void LED_Init(void);
void LED_On(uint8_t led);
void LED_Off(uint8_t led);
void LED_Toggle(uint8_t led);

#endif // LED_H
