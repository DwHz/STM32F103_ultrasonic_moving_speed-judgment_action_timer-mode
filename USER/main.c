#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "ds18b20.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
    float SRF04_Value = 123.45;
    float previous_SRF04_Value = 123.45;
    float rate_of_change = 0;
    char classification[17] = {0};  // Increased size to 17 for safety
    char adcxxx[16] = {0};  // Increased size
    HAL_Init();                     
    Stm32_Clock_Init(RCC_PLL_MUL9);   
    delay_init(72);                   
    LCD_init();  
    delay_ms(100);  // Ensure LCD is ready
    SRF04_init();
    TIM3_Init(1000-1, 72-1);      
    while(1)
    {
        previous_SRF04_Value = SRF04_Value;

        SRF04_Value = Hcsr04GetLength() - 2;
        if(SRF04_Value >= 600)
            SRF04_Value = 400;
        
        sprintf(adcxxx, "%.2f cm", SRF04_Value);

        rate_of_change = SRF04_Value - previous_SRF04_Value;

        if (rate_of_change >= 10) // 10 cm per 0.2s
            strcpy(classification, "Quickly away ");
        else if (rate_of_change >= 2)
            strcpy(classification, "Slowly away  ");
        else if (rate_of_change <= -10)
            strcpy(classification, "Quickly close");
        else if (rate_of_change <= -2)
            strcpy(classification, "Slowly close ");
        else
            strcpy(classification, "Stationary   ");

        LCD_write_string(0, 0, "Distance:");
        LCD_write_string(10, 0, adcxxx);
        LCD_write_string(0, 1, classification);
        
        delay_ms(200);                
    }
}
