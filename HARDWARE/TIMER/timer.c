#include "timer.h"
#include "led.h"

TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 

u16 msHcCount = 0;//ms计数

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);


void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                          //通用定时器3
    TIM3_Handler.Init.Prescaler=psc;                     //分频系数
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM3_Handler.Init.Period=arr;                        //自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE

    HAL_TIM_Base_MspInit(&TIM3_Handler);
    
}

//定时器底册驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM1_CLK_ENABLE();            //使能TIM3时钟
		__HAL_RCC_TIM3_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启ITM3中断   		
	}
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{	
   msHcCount++;
   HAL_TIM_IRQHandler(&TIM3_Handler);
}

//回调函数，定时器中断服务函数调用
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

void Delay_Ms(uint16_t time)  //延时函数
{ 
    uint16_t i,j;
    for(i=0;i<time;i++)
          for(j=0;j<10260;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Delay_Ms_Us
** 功能描述: 延时1us (可通过仿真来判断他的准确度)
** 参数描述：time (us) 注意time<65535                 
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //延时函数
{ 
    uint16_t i,j;
    for(i=0;i<time;i++)
          for(j=0;j<9;j++);
}
  

//获取定时器时间
u32 GetEchoTimer(void)
{
        u32 t = 0;
        t = msHcCount*1000;//得到MS
        msHcCount = 0;
        t += TIM3->CNT;//得到US
          TIM3->CNT = 0;  //将TIM2计数寄存器的计数值清零
                Delay_Ms(50);
        return t;
}
 

//一次获取超声波测距数据 两次测距之间需要相隔一段时间，隔断回响信号
//为了消除余震的影响，取五次数据的平均值进行加权滤波。

float Hcsr04GetLength(void )
{
        u32 t = 0;
        int i = 0;
        float lengthTemp = 0;
        float sum = 0;
    
        while(i<2)
        {
            TRIG_Send(1);      //发送口高电平输出
            Delay_Us(20);
            TRIG_Send(0);
                
            while(ECHO_Reci == 0);      //等待接收口高电平输出
                
            HAL_TIM_Base_Start_IT(&TIM3_Handler);        //打开定时器
            i = i + 1;
            while(ECHO_Reci == 1);
            
            HAL_TIM_IRQHandler(&TIM3_Handler);
            HAL_TIM_Base_Stop_IT(&TIM3_Handler);        //关闭定时器
            t = GetEchoTimer();        //获取时间,分辨率为1US
            lengthTemp = ((float)t/51.5);//cm
            sum = lengthTemp + sum ;

        }
        lengthTemp = sum/2.0;
        
        return lengthTemp;
}




