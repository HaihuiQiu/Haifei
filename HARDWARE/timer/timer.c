#include "timer.h"
#include "SR04.h"

//超声波计数
extern u16 msHcCount;//发生中断的次数

//定时器4设置，	//中断优先级NVIC设置
void hcsr04_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //从优先级0级     
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IRQ通道被使能  
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC寄存器
}

//打开定时器4
void OpenTimerForHc(void)  
{
   TIM_SetCounter(TIM4,0);
   msHcCount = 0;
   TIM_Cmd(TIM4, ENABLE); 
}


//关闭定时器4
void CloseTimerForHc(void)    
{
   TIM_Cmd(TIM4, DISABLE); 
}


//定时器4中断
void TIM4_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
   {
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); //清除TIMx更新中断标志
       msHcCount++;//发生中断的次数
   }
}

