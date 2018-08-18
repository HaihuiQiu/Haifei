#include "led.h"
#include "sys.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "SR04.h"
#include "stm32f10x.h"
#include "timer.h"
#include "24cxx.h"	
#include "GUI.h"
#include "Lcd_Driver.h"
#include "QDTFT_demo.h"
float length=0;
//����������
int main(void)
{	 
	delay_init();	   	//��ʱ������ʼ��	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	//���ڳ�ʼ��Ϊ9600
	printf("���������ڲ���\r\n");  
	IIC_Init();	
    Hcsr04Init();    
    printf("��������ʼ���ɹ�!\n");
   while(1) 
	{	 
		length = Hcsr04GetLength();//��ȡ������ľ���
		printf("����Ϊ:%.3fcm\n",length);
		delay_ms(100); 
	}	
 }

