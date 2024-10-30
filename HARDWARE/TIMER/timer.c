#include "timer.h"
#include "led.h"

TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 

u16 msHcCount = 0;//ms����

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);


void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE

    HAL_TIM_Base_MspInit(&TIM3_Handler);
    
}

//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM1_CLK_ENABLE();            //ʹ��TIM3ʱ��
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   		
	}
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{	
   msHcCount++;
   HAL_TIM_IRQHandler(&TIM3_Handler);
}

//�ص���������ʱ���жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM3_Handler))
    {
        
    }
}

void SRF04_init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();          
	
    GPIO_Initure.Pin=GPIO_PIN_5; 
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull=GPIO_PULLUP;          
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

    GPIO_Initure.Pin=GPIO_PIN_6; 
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  
    GPIO_Initure.Pull=GPIO_NOPULL;          
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

void Delay_Ms(uint16_t time)  //��ʱ����
{ 
    uint16_t i,j;
    for(i=0;i<time;i++)
          for(j=0;j<10260;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Us
** ��������: ��ʱ1us (��ͨ���������ж�����׼ȷ��)
** ����������time (us) ע��time<65535                 
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //��ʱ����
{ 
    uint16_t i,j;
    for(i=0;i<time;i++)
          for(j=0;j<9;j++);
}
  

//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
        u32 t = 0;
        t = msHcCount*1000;//�õ�MS
        msHcCount = 0;
        t += TIM3->CNT;//�õ�US
          TIM3->CNT = 0;  //��TIM2�����Ĵ����ļ���ֵ����
                Delay_Ms(50);
        return t;
}
 

//һ�λ�ȡ������������� ���β��֮����Ҫ���һ��ʱ�䣬���ϻ����ź�
//Ϊ�����������Ӱ�죬ȡ������ݵ�ƽ��ֵ���м�Ȩ�˲���

float Hcsr04GetLength(void )
{
        u32 t = 0;
        int i = 0;
        float lengthTemp = 0;
        float sum = 0;
    
        while(i<2)
        {
            TRIG_Send(1);      //���Ϳڸߵ�ƽ���
            Delay_Us(20);
            TRIG_Send(0);
                
            while(ECHO_Reci == 0);      //�ȴ����տڸߵ�ƽ���
                
            HAL_TIM_Base_Start_IT(&TIM3_Handler);        //�򿪶�ʱ��
            i = i + 1;
            while(ECHO_Reci == 1);
            
            HAL_TIM_IRQHandler(&TIM3_Handler);
            HAL_TIM_Base_Stop_IT(&TIM3_Handler);        //�رն�ʱ��
            t = GetEchoTimer();        //��ȡʱ��,�ֱ���Ϊ1US
            lengthTemp = ((float)t/51.5);//cm
            sum = lengthTemp + sum ;

        }
        lengthTemp = sum/2.0;
        
        return lengthTemp;
}




