#include "SR04.h"
#include "timer.h"
#include "delay.h"

u16 msHcCount = 0;
//IO口初始化 及其他初始化
void Hcsr04Init(void)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(HCSR04_CLK, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin =HCSR04_TRIG;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设为推挽输出模式
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
     
    GPIO_InitStructure.GPIO_Pin =   HCSR04_ECHO;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//设为输入
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);  
    GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);    
     
          
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   
     
    TIM_DeInit(TIM2);//复位timX的所有寄存器，也就是将外设 TIMx 寄存器重设为缺省值
    TIM_TimeBaseStructure.TIM_Period = (1000-1); //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式 
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);   //根据指定的参数初始化TIM4的时间基数单位       
        
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  //清除TIMx 的待处理标志位
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);   //使能指定的TIM4中断,允许更新中断 
    hcsr04_NVIC();//中断优先级NVIC设置
    TIM_Cmd(TIM4,DISABLE);  //不使能定时器TIM4 
}

//获取定时器4计数器值
u32 GetEchoTimer(void)
{
   u32 t = 0;
   t = msHcCount*1000;
   t += TIM_GetCounter(TIM4);
   TIM4->CNT = 0;  
   delay_ms(50);
   return t;
}
 
//通过定时器4计数器值推算距离
float Hcsr04GetLength(void )
{
   u32 t = 0;
   int i = 0;
   float lengthTemp = 0;
   float sum = 0;
   while(i!=5)
   {
      TRIG_Send = 1;      
      delay_us(20);
      TRIG_Send = 0;
      while(ECHO_Reci == 0);      
      OpenTimerForHc();        
      i = i + 1;
      while(ECHO_Reci == 1);
      CloseTimerForHc();        
      t = GetEchoTimer();        
      lengthTemp = ((float)t/58.0);//cm
      sum = lengthTemp + sum ;
        
    }
    lengthTemp = sum/5.0;
    return lengthTemp;

}


