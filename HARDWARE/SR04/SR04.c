#include "SR04.h"
#include "timer.h"
#include "delay.h"

u16 msHcCount = 0;
//IO�ڳ�ʼ�� ��������ʼ��
void Hcsr04Init(void)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(HCSR04_CLK, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin =HCSR04_TRIG;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��Ϊ�������ģʽ
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
     
    GPIO_InitStructure.GPIO_Pin =   HCSR04_ECHO;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��Ϊ����
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);  
    GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);    
     
          
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   
     
    TIM_DeInit(TIM2);//��λtimX�����мĴ�����Ҳ���ǽ����� TIMx �Ĵ�������Ϊȱʡֵ
    TIM_TimeBaseStructure.TIM_Period = (1000-1); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ 
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);   //����ָ���Ĳ�����ʼ��TIM4��ʱ�������λ       
        
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  //���TIMx �Ĵ������־λ
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);   //ʹ��ָ����TIM4�ж�,��������ж� 
    hcsr04_NVIC();//�ж����ȼ�NVIC����
    TIM_Cmd(TIM4,DISABLE);  //��ʹ�ܶ�ʱ��TIM4 
}

//��ȡ��ʱ��4������ֵ
u32 GetEchoTimer(void)
{
   u32 t = 0;
   t = msHcCount*1000;
   t += TIM_GetCounter(TIM4);
   TIM4->CNT = 0;  
   delay_ms(50);
   return t;
}
 
//ͨ����ʱ��4������ֵ�������
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


