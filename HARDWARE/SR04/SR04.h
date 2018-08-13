#ifndef __SR04_H
#define __SR04_H	 
#include "sys.h"

//������Ӳ���ӿڶ���
#define HCSR04_PORT     GPIOB
#define HCSR04_CLK      RCC_APB2Periph_GPIOB
#define HCSR04_TRIG     GPIO_Pin_11
#define HCSR04_ECHO     GPIO_Pin_10


#define TRIG_Send     PBout(11)
#define ECHO_Reci     PBin(10)

//IO�ڳ�ʼ�� ��������ʼ��
void Hcsr04Init(void);
//��ȡ��ʱ��4������ֵ
u32 GetEchoTimer(void);
//ͨ����ʱ��4������ֵ�������
float Hcsr04GetLength(void );

#endif

