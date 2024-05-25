#include "uart4.h"
#include <stdarg.h>
#include <stdio.h>
/*****************************************************/

unsigned char U4_RxBuf[RX4_BUFLEN+1];					//接收数据缓冲区
unsigned int U4_RxBufWp;             							//接收缓存区写指针
unsigned int U4_RxBufRp;             							//接收缓存区读指针

unsigned char U4_TxBuf[TX4_BUFLEN+1];	    //发送数据缓冲区
unsigned int U4_TxBufWp;             		      //发送缓存区写指针
unsigned int U4_TxBufRp;             		      //发送缓存区读指针


unsigned char Com4RevDataFlag; 
unsigned char Com4Start1,Com4Start2,Com4End1,Com4End2; 


/**
 * @brief 配置UART4的GPIO端口
 * 该函数用于初始化UART4的TX和RX引脚，将其配置为复用功能，以便于UART通信。
 * 
 * @note 该函数不接受参数，也不返回任何值。
 */
void UART4_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* 配置GPIO端口，为UART4的TX和RX引脚开启时钟并进行复用功能配置 */
    /* 打开GPIOA的时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* 配置PA0为UART4_TX */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);

    /* 配置PA1为UART4_RX */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
  
    /* 初始化GPIO结构体，配置TX和RX引脚的参数 */
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 复用功能模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 引脚速度为50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
    /* 根据初始化结构体参数来配置GPIOA的0和1引脚 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief 配置UART4的初始化参数，使能UART4并清除发送完成标志。
 * 这个函数主要用于设置UART4的通信参数，并启动UART4的收发功能。
 * 它不接受参数，也不返回任何值。
 */
void UART4_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
  
    // 启用UART4的时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE); 
  
    // 初始化USART_InitStructure，设置UART4的参数
    USART_InitStructure.USART_BaudRate =9600;         // 设置波特率为9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 设置数据位长度为8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 设置停止位为1位
    USART_InitStructure.USART_Parity = USART_Parity_No; // 设置无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 设置无硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 设置为收发模式 
    USART_Init(UART4, &USART_InitStructure);
  
    // 使能UART4
    USART_Cmd(UART4, ENABLE);    
    
    // 清除传输完成标志，以解决第一个字节发送不出去的问题
    USART_ClearFlag(UART4, USART_FLAG_TC);     
}


void NVIC_UART4_Config(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
   
   NVIC_InitStructure.NVIC_IRQChannel=UART4_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
  
  /* 使能发送缓冲区空中断 */
  USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
  /* 使能接受中断 */
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);  
}



void UART4_Putc(unsigned char c)
{
  USART_SendData(UART4, c);
  while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET );
}


void UART4_PutsNum(char * str,unsigned int Num)
{
    while(Num)
    {
			Num--;
			USART_SendData(UART4, *str++);
			/* Loop until the end of transmission */
			while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
    }

}


void UART4_Puts(char * str)
{
	while(*str)
	{
		USART_SendData(UART4, *str++);
		/* Loop until the end of transmission */
		while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	}

}

//串口3,printf 函数
//确保一次发送数据不超过UART4_MAX_SEND_LEN字节
void u4_printf(char* fmt,...)  
{  
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)U4_TxBuf,fmt,ap);
	va_end(ap);
  
  UART4_Puts((char*)U4_TxBuf);
}


void Bsp_UART4_Init(void)
{
  UART4_GPIO_Config();
  UART4_Config();
  NVIC_UART4_Config();
}

void UART4_IRQHandler(void)
{
	unsigned char Uart4_Get_Data;
  
//  union Float_4uchar FloatTemp;
  
	/* 处理接收中断  */
	if (USART_GetITStatus(UART4, USART_IT_RXNE) == SET)
	{
    USART_ClearITPendingBit(UART4,USART_IT_RXNE);
    Uart4_Get_Data=USART_ReceiveData(UART4);
    Com4Start1=Com4Start2;
    Com4Start2=Uart4_Get_Data;
    if((Com4Start1==0x7b)&&(Com4Start2==0x7b))
    {
      Com4RevDataFlag=1;
    }
    U4_RxBuf[U4_RxBufWp]=Uart4_Get_Data;//接收数据放入缓冲区。
    U4_RxBufWp=(U4_RxBufWp+1)%RX4_BUFLEN;
    Com4End1=Com4End2;
    Com4End2=Uart4_Get_Data;    
    if((Com4End1==0x7d)&&(Com4End2==0x7d)&&(Com4RevDataFlag==1))
    {     
      //isr_evt_set(0x0008,t_USARTx_Data);//发送信号。
      u4_printf("uart 4 rec!!!!!\n");	  		
      Com4RevDataFlag=0;
    }    
	}	
	/* 处理发送缓冲区空中断 */
	if (USART_GetITStatus(UART4, USART_IT_TXE) == SET)
	{
    USART_ClearITPendingBit(UART4,USART_IT_TXE);
//		  /* 发送数据 */
//		  USART_SendData(UART4, aTxBuffer[ubTxIndex++]);
		  /* 禁止发送缓冲区空中断 */
    USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
	}
  
  
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if(USART_GetFlagStatus(UART4,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(UART4,USART_FLAG_ORE);	//读SR
		USART_ReceiveData(UART4);				//读DR
	}
}
