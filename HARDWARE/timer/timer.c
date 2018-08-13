#include "timer.h"
#include "SR04.h"

//����������
extern u16 msHcCount;//�����жϵĴ���

//��ʱ��4���ã�	//�ж����ȼ�NVIC����
void hcsr04_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //�����ȼ�0��     
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IRQͨ����ʹ��  
	NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC�Ĵ���
}

//�򿪶�ʱ��4
void OpenTimerForHc(void)  
{
   TIM_SetCounter(TIM4,0);
   msHcCount = 0;
   TIM_Cmd(TIM4, ENABLE); 
}


//�رն�ʱ��4
void CloseTimerForHc(void)    
{
   TIM_Cmd(TIM4, DISABLE); 
}


//��ʱ��4�ж�
void TIM4_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM4�����жϷ������
   {
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); //���TIMx�����жϱ�־
       msHcCount++;//�����жϵĴ���
   }
}

