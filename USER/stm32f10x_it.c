/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "stm32f10x_i2c.h"
#include "myiic.h" 
#include "stdio.h" 


extern float length;
extern u8 I2C1_ADDRESS;
vu32 Tx_Counter =0;
vu32 Rx_Counter = 0;
vu32 show_counter1 = 0;
vu32 show_counter2 = 0;	


void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}


/************************************************
函数名称 ： I2C1_EV_IRQHandler
功    能 ： I2C1事件中断
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/

void I2C1_EV_IRQHandler(void)
{
	show_counter2++;
	if(show_counter2>100000)
	{
		show_counter2=0;
		printf("\r\n The I2C1 LastEvent is %x \r\n" , I2C_GetLastEvent(I2C1));
	}
	switch(I2C_GetLastEvent(I2C1))
	{
		case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED: //收到匹配的地址数据
		{
			printf("\r\n The I2C1 is ready \r\n");
			I2C_GenerateSTOP(I2C1, DISABLE);
			break;
		}
		case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:  //发送数据
		{
			printf("\r\n The I2C1 transmits is transmitting \r\n");
			I2C_SendData(I2C1, length);  //总共调用了4次
			break;
		}
		//发送数据，要发送，不然锁死，不过master没收到，不知道干嘛的
		case I2C_EVENT_SLAVE_BYTE_TRANSMITTED:
		{
			printf("\r\n The I2C1 transmits one byte \r\n");
			I2C_SendData(I2C1, length);
			break;
		}
		case I2C_EVENT_SLAVE_STOP_DETECTED:  //收到结束条件
		{
			printf("\r\n The I2C1 is finish \r\n");
			I2C_ClearFlag(I2C1,I2C_FLAG_STOPF);
			I2C_GenerateSTOP(I2C1, ENABLE);
			break;
		}
		default: break;
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
