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

  
//void I2C_clear_ADDR(I2C_TypeDef* I2Cx) 	  
//{
//     I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR);
//     ((void)(I2Cx->SR2));
//}

// void I2C_clear_STOPF(I2C_TypeDef* I2Cx) 
//{
//     I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF);
//     I2C_Cmd(I2Cx, ENABLE);
//}

//void I2C1_EV_IRQHandler(void)
//{

////        KV1=0;      只是一个测试灯
//        
//        if(I2C_GetITStatus(I2C1, I2C_IT_AF)) //Clear AF from slave-transmission end
//        {
//            I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
//        }
//        //Big state machine response, since doesn't actually keep state
//        switch(I2C_GetLastEvent(I2C1)) 
//            {
//            //SLAVE Receive
//            case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED: //EV1
//                I2C_clear_ADDR(I2C1);
//                break;
//            case I2C_EVENT_SLAVE_BYTE_RECEIVED: //EV2  //Read it, so no one is waiting, clears BTF if necessary
//                give_up  = I2C_ReceiveData(I2C1);
//                if(I2C_GetFlagStatus(I2C1, I2C_FLAG_DUALF)) 
//                {//Secondary Receive
//                } 
//                else if(I2C_GetFlagStatus(I2C1, I2C_FLAG_GENCALL)) 
//                {//General Receive
//                } 
//                else 
//                {//Normal
//                }
//                break;	
//            case I2C_EVENT_SLAVE_STOP_DETECTED: //End of receive, EV4
//                I2C_clear_STOPF(I2C1);
//				printf("\r\n The I2C1 is finish \r\n");
//                break;

//            //Transmit
//            case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED: //EV1
//                I2C_clear_ADDR(I2C1);
//                I2C_SendData(I2C1, length);//Send first byte
//			    printf("\r\n The I2C1 is ready \r\n");
//                break;
//			case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:  //发送数据  EV3
//			{
//				printf("\r\n The I2C1 transmits is transmitting \r\n");
//				I2C_SendData(I2C1, length);  //
//				break;
//			}			
//            case I2C_EVENT_SLAVE_BYTE_TRANSMITTED: //EV3//Determine what you want to send
//                
//                if(I2C_GetFlagStatus(I2C1, I2C_FLAG_DUALF)) 
//                {//Secondary Transmit
//                } 
//                else if(I2C_GetFlagStatus(I2C1, I2C_FLAG_GENCALL)) 
//                {//General Transmit
//                } 
//                else 
//                {//Normal
//                }
//                //Read flag and write next byte to clear BTF if present
//                I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF);
//                I2C_SendData(I2C1, length);
//				printf("\r\n已经发送数据了\r\n");
//                break;
//            case I2C_EVENT_SLAVE_ACK_FAILURE://End of transmission EV3_2
//                //TODO: Doesn't seem to be getting reached, so just
//                //check at top-level
//                I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
//                break;
//            //Alternative Cases for address match
//            case I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED:    //EV1
//                break;
//            case I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED: //EV1
//                break;
//            case I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED:        //EV1
//                break;
//	
//	}
//	
//}

//void I2C1_ER_IRQHandler(void) {
// //       GPIO_SetBits(GPIOD, RED);
////    LED3=0;
//        //Can't use nice switch statement, because no fxn available
//        if(I2C_GetITStatus(I2C1,        I2C_IT_SMBALERT)) {
//        } else if(I2C_GetITStatus(I2C1, I2C_IT_TIMEOUT)) {
//        } else if(I2C_GetITStatus(I2C1, I2C_IT_PECERR)) {
//        } else if(I2C_GetITStatus(I2C1, I2C_IT_OVR)) {
//            //Overrun
//            //CLK stretch disabled and receiving
//            //DR has not been read, b4 next byte comes in
//            //effect: lose byte
//            //should:clear RxNE and transmitter should retransmit

//            //Underrun
//            //CLK stretch disabled and I2C transmitting
//            //haven't updated DR since new clock
//            //effect: same byte resent
//            //should: make sure discarded, and write next
//        } else if(I2C_GetITStatus(I2C1, I2C_IT_AF)) {
//            //Detected NACK
//            //Transmitter must reset com
//                //Slave: lines released
//                //Master: Stop or repeated Start must must be generated
//                //Master = MSL bit
//            //Fixup
//            I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
//        } else if(I2C_GetITStatus(I2C1, I2C_IT_ARLO)) {
//            //Arbitration Lost
//            //Goes to slave mode, but can't ack slave address in same transfer
//            //Can after repeat Start though
//        } else if(I2C_GetITStatus(I2C1, I2C_IT_BERR)) {
//            //Bus Error
//            //In slave mode: data discarded, lines released, acts like restart
//            //In master mode: current transmission continues
//        }
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
