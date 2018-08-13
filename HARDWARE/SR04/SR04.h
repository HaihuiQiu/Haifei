#ifndef __SR04_H
#define __SR04_H	 
#include "sys.h"

//超声波硬件接口定义
#define HCSR04_PORT     GPIOB
#define HCSR04_CLK      RCC_APB2Periph_GPIOB
#define HCSR04_TRIG     GPIO_Pin_11
#define HCSR04_ECHO     GPIO_Pin_10


#define TRIG_Send     PBout(11)
#define ECHO_Reci     PBin(10)

//IO口初始化 及其他初始化
void Hcsr04Init(void);
//获取定时器4计数器值
u32 GetEchoTimer(void);
//通过定时器4计数器值推算距离
float Hcsr04GetLength(void );

#endif

