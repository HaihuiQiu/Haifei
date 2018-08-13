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
float length;
//����������
int main(void)
{	 
	
	delay_init();	   	//��ʱ������ʼ��	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	//���ڳ�ʼ��Ϊ9600
	Hcsr04Init();
	Lcd_Init();//lcd��ʼ��
	Lcd_Clear(GRAY0);
	printf("���������ڲ���\r\n");  
		
   Hcsr04Init();    
   printf("��������ʼ���ɹ�!\n");
	Gui_DrawFont_GBK16(0,80,BLACK,GRAY0, "NRF24L01 Error");
   while(1) 
	{	 
		 //length = Hcsr04GetLength();
		 
		//length=Single_Read(0XBC,0);
		//Single_Write(0XBC,0,length) ;
		printf("����Ϊ:%.3fcm\n",length);
		unsigned char tmp[5];
		//sprintf(tmp,"%1.lf",length);
		Gui_DrawFont_GBK16(16,0,BLUE,GRAY0,tmp);
		delay_ms(100);    
	}	
 }

