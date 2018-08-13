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
extern u8 length;
 
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


	__IO uint16_t SR1Register =0;
  __IO uint16_t SR2Register =0;

  SR1Register = I2C1->SR1;                       //读取状态
  SR2Register = I2C1->SR2;

//  /* I2C1是从机(MSL = 0) */
  if((SR2Register & 0x0001) != 0x0001)
  {
		//ADDR
		if((SR1Register & 0x0002) == 0x0002)
    {
      /* 清除标志，准备接收数据 */
      SR1Register = 0;
      SR2Register = 0;
			length= 0;	

    }

		//TxE
		if((SR1Register & 0x0080) == 0x0080)
		{
			 SR1Register = 0;
      SR2Register = 0;
			I2C1->DR =length;

		}

		//STOPF
		if((SR1Register & 0x0010) == 0x0010)
		{
			I2C1->CR1 |= CR1_PE_Set;
      SR1Register = 0;
      SR2Register = 0;
			length= 5;	

		}
		
		//TIME_OUT
		if((SR1Register & 0x4000) == 0x4000)
		{
			I2C1->CR1 |= CR1_PE_Set;
			 SR1Register = 0;
      SR2Register = 0;

		}
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
