#ifndef __timer_H
#define __timer_H	 
#include "sys.h"


//定时器4设置
void hcsr04_NVIC(void);
//打开定时器4
void OpenTimerForHc(void);
//关闭定时器4
void CloseTimerForHc(void);
#endif

