#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

u8 I2C1_ADDRESS = 0XBC;

//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
	
	//i2c从机的配置
	I2C_InitTypeDef I2C_InitStructure;
	
	I2C_DeInit(I2C1);

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//从模式
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2C1_ADDRESS;//这个就是作为从机的地址，一定要配置正确0XBC
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//7位的地址
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_Init(I2C1, &I2C_InitStructure);	
	

/* Configure and enable I2Cx event interrupt -------------------------------*/
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;    //从优先级0级     
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IRQ通道被使能  
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC寄存器
	

    /* Configure and enable I2C1 error interrupt -------------------------------*/
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&NVIC_InitStructure);	
	I2C_Cmd(I2C2,ENABLE); //使能I2C2
	
//使能了I2C1的这三个中断
/* Enable I2C1 event and buffer interrupts */
 
	I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_BUF, ENABLE);
	 
	/* Enable I2C1 Error interrupts */
	 
	I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE);	
}

//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


//Clear ADDR by reading SR1, then SR2

void I2C_clear_ADDR(I2C_TypeDef* I2Cx) {
    I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR);
    ((void)(I2Cx->SR2));
}

//Clear STOPF by reading SR1, then writing CR1

void I2C_clear_STOPF(I2C_TypeDef* I2Cx) {
    I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF);
    I2C_Cmd(I2Cx, ENABLE);
}

/*--------------------------------------------------------------------------------
调用方式：void I2C1_EV_IRQHandler(void) 
函数说明：私有函数，I2C专用，中断按键处理函数，从机中断都在这里面执行
---------------------------------------------------------------------------------*/

/*uint8_t data = 0;
uint8_t S_data=0;
void I2C1_EV_IRQHandler(void) 
{
//        KV1=0;                                 //只是一个测试灯
        //Clear AF from slave-transmission end
        if(I2C_GetITStatus(I2C1, I2C_IT_AF)) 
        {
            I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
        }
        //Big state machine response, since doesn't actually keep state
        switch(I2C_GetLastEvent(I2C1)) 
            {
            //SLAVE
            //Receive
            case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED: //EV1
                I2C_clear_ADDR(I2C1);
                break;
            case I2C_EVENT_SLAVE_BYTE_RECEIVED: //EV2
                //Read it, so no one is waiting, clears BTF if necessary
                b[data] = I2C_ReceiveData(I2C1);
        //      printf("%c",b[data]);
                data++;
                if(data>=5)
                {
                                data=0;
                                if((b[0]==0xFA)&&(b[4]==0xFB))
                                {
                                    a[1]=b[1];
                                    Wifi_Set=b[2];
                                    flag=b[3];
                //                    printf("%c",a[1]);
                                }

                }
                if(I2C_GetFlagStatus(I2C1, I2C_FLAG_DUALF)) 
                {//Secondary Receive
                } 
                else if(I2C_GetFlagStatus(I2C1, I2C_FLAG_GENCALL)) 
                {//General Receive
                } 
                else 
                {//Normal
                }
                break;
            case I2C_EVENT_SLAVE_STOP_DETECTED: //End of receive, EV4
                I2C_clear_STOPF(I2C1);
                break;

            //Transmit
            case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED: //EV1
                I2C_clear_ADDR(I2C1);
                //Send first byte
               I2C_SendData(I2C1, 0x00);
            
                break;
            case I2C_EVENT_SLAVE_BYTE_TRANSMITTED: //EV3
                //Determine what you want to send
                //data = 5;
                if(I2C_GetFlagStatus(I2C1, I2C_FLAG_DUALF)) 
                {//Secondary Transmit
                } 
                else if(I2C_GetFlagStatus(I2C1, I2C_FLAG_GENCALL)) 
                {//General Transmit
                } 
                else 
                {//Normal
                }
                //Read flag and write next byte to clear BTF if present
                I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF);
                I2C_SendData(I2C1, a[S_data]);
                S_data++;
                if(S_data>=5)
                S_data=0;
                break;
            case I2C_EVENT_SLAVE_ACK_FAILURE://End of transmission EV3_2
                //TODO: Doesn't seem to be getting reached, so just
                //check at top-level
                I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
                break;
            //Alternative Cases for address match
            case I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED:    //EV1
                break;
            case I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED: //EV1
                break;
            case I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED:        //EV1
                break;


            //MASTER
            case I2C_EVENT_MASTER_MODE_SELECT: //EV5, just sent start bit
                break;
            //Receive
            case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED: //EV6, just sent addr    
                break;
            case I2C_EVENT_MASTER_BYTE_RECEIVED: //EV7
                break;
            //Transmit
            case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED: //EV6, just sent addr     
                break;
            case I2C_EVENT_MASTER_BYTE_TRANSMITTING: //EV8, about to send data
                break;
            case I2C_EVENT_MASTER_BYTE_TRANSMITTED: //EV8_2, just sent data
                break;

            //Alternative addressing stuff, not going to worry about
            case I2C_EVENT_MASTER_MODE_ADDRESS10: //EV9
                break;
            default:
                //How the FUCK did you get here?
                //I should probably raise some error, but fuck it,
                //it's late
                break;

        }


}

void I2C1_ER_IRQHandler(void) {
 //       GPIO_SetBits(GPIOD, RED);
//    LED3=0;
        //Can't use nice switch statement, because no fxn available
        if(I2C_GetITStatus(I2C1,        I2C_IT_SMBALERT)) {
        } else if(I2C_GetITStatus(I2C1, I2C_IT_TIMEOUT)) {
        } else if(I2C_GetITStatus(I2C1, I2C_IT_PECERR)) {
        } else if(I2C_GetITStatus(I2C1, I2C_IT_OVR)) {
            //Overrun
            //CLK stretch disabled and receiving
            //DR has not been read, b4 next byte comes in
            //effect: lose byte
            //should:clear RxNE and transmitter should retransmit

            //Underrun
            //CLK stretch disabled and I2C transmitting
            //haven't updated DR since new clock
            //effect: same byte resent
            //should: make sure discarded, and write next
        } else if(I2C_GetITStatus(I2C1, I2C_IT_AF)) {
            //Detected NACK
            //Transmitter must reset com
                //Slave: lines released
                //Master: Stop or repeated Start must must be generated
                //Master = MSL bit
            //Fixup
            I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
        } else if(I2C_GetITStatus(I2C1, I2C_IT_ARLO)) {
            //Arbitration Lost
            //Goes to slave mode, but can't ack slave address in same transfer
            //Can after repeat Start though
        } else if(I2C_GetITStatus(I2C1, I2C_IT_BERR)) {
            //Bus Error
            //In slave mode: data discarded, lines released, acts like restart
            //In master mode: current transmission continues
        }
}
*/

