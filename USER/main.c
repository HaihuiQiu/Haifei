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
//测试主函数
int main(void)
{	 
	delay_init();	   	//延时函数初始化	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	//串口初始化为9600
	printf("超声波串口测试\r\n");  
	IIC_Init();	
    Hcsr04Init();    
    printf("超声波初始化成功!\n");
   while(1) 
	{	 
		length = Hcsr04GetLength();//获取超声测的距离
		printf("距离为:%.3fcm\n",length);
		delay_ms(100); 
	}	
 }

