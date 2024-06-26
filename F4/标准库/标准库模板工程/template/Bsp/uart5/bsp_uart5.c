#include <stdarg.h>
#include <stdio.h>
#include "sys.h"
#include "bsp_uart5.h"
/*****************************************************/
#define UART_PORT UART5

uint8_t U5_RxBuf[RX5_BUFLEN + 1]; // 接收数据缓冲区
uint32_t U5_RxBufWp;              // 接收缓存区写指针
uint32_t U5_RxBufRp;              // 接收缓存区读指针

uint8_t U5_TxBuf[TX5_BUFLEN + 1]; // 发送数据缓冲区
uint32_t U5_TxBufWp;              // 发送缓存区写指针
uint32_t U5_TxBufRp;              // 发送缓存区读指针

uint8_t U5_RevDataFlag;
uint8_t U5_Start1, U5_Start2, U5_End1, U5_End2;

/*
    Tx_GPIO_PinSourceX: GPIO_PinSource0
    Tx_GPIO_PinSourceX: GPIO_PinSource1
    GPIO_Pin_x: GPIO_Pin_0|GPIO_Pin_1

    GPIO_AF_x:
        GPIO_AF_USART1
        GPIO_AF_USART2
        GPIO_AF_USART3
        GPIO_AF_UART4
        GPIO_AF_UART5
        GPIO_AF_USART6
        GPIO_AF_UART7
        GPIO_AF_UART8
 */
static void UART_GPIO_Config(GPIO_TypeDef *GPIOx, uint8_t Tx_GPIO_PinSourceX, uint8_t Rx_GPIO_PinSourceX, uint16_t GPIO_Pin_x, uint8_t GPIO_AF_x)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_x);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_x);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/* 注意修改时钟
    RCC_APB1Periph_USART2
    RCC_APB1Periph_USART3
    RCC_APB1Periph_UART4
    RCC_APB1Periph_UART5
    RCC_APB1Periph_UART7
    RCC_APB1Periph_UART8

    RCC_APB2Periph_USART1
    RCC_APB2Periph_USART6
    RCC_APB2Periph_UART9
    RCC_APB2Periph_UART10
 */
static void UART_Config(USART_TypeDef *UARTx, uint32_t BaudRate, uint32_t RCC_APBxPeriph_UARTx)
{
    // 启用UART的时钟
    RCC_APB1PeriphClockCmd(RCC_APBxPeriph_UARTx, ENABLE);

    // 初始化USART_InitStructure，设置UART4的参数
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = BaudRate;                                  // 设置波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 设置数据位长度为8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 设置停止位为1位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             // 设置无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 设置无硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 设置为收发模式
    USART_Init(UARTx, &USART_InitStructure);

    // 使能UARTx
    USART_Cmd(UARTx, ENABLE);

    // 清除传输完成标志，以解决第一个字节发送不出去的问题
    USART_ClearFlag(UARTx, USART_FLAG_TC);
}

/*
    UART: UART4,UART5,UART7,UART8
    USART: USART1,USART2,USART3,USART6,USART9,USART10
    UARTx_IRQn: 上述uart和usart标号一致
    Priority: 默认NVIC_PriorityGroup_4: 只有0-15抢占优先级
 */
static void NVIC_UART_Config(USART_TypeDef *USARTx, uint8_t UARTx_IRQn, uint8_t Priority)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    NVIC_InitStructure.NVIC_IRQChannel = UARTx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Priority; // 0-15
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;               // 0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* 使能发送缓冲区空中断 */
    USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
    /* 使能接受中断 */
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
}

void U5_Putc(uint8_t c)
{
    USART_SendData(UART_PORT, c);
    while (USART_GetFlagStatus(UART_PORT, USART_FLAG_TXE) == RESET)
        ;
}

void U5_PutsNum(char *str, uint32_t Num)
{
    while (Num)
    {
        Num--;
        USART_SendData(UART_PORT, *str++);
        /* Loop until the end of transmission */
        while (USART_GetFlagStatus(UART_PORT, USART_FLAG_TXE) == RESET)
            ;
    }
}

void U5_Puts(char *str)
{
    while (*str)
    {
        USART_SendData(UART_PORT, *str++);
        /* Loop until the end of transmission */
        while (USART_GetFlagStatus(UART_PORT, USART_FLAG_TXE) == RESET)
            ;
    }
}

// 串口3,printf 函数
// 确保一次发送数据不超过UART_MAX_SEND_LEN字节
void U5_printf(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char *)U5_TxBuf, fmt, ap);
    va_end(ap);

    U5_Puts((char *)U5_TxBuf);
}

void Bsp_UART5_Init(void)
{
    UART_GPIO_Config(NULL, NULL, NULL, NULL, GPIO_AF_UART5);
    UART_Config(UART_PORT, 9600, RCC_APB1Periph_UART5);
    NVIC_UART_Config(UART_PORT, UART5_IRQn, 4);
}

void UART5_IRQHandler(void)
{
    uint8_t U5_Rec_Data;

    /* 处理接收中断  */
    if (USART_GetITStatus(UART_PORT, USART_IT_RXNE) == SET)
    {
        USART_ClearITPendingBit(UART_PORT, USART_IT_RXNE);
        U5_Rec_Data = USART_ReceiveData(UART_PORT);
        U5_Start1 = U5_Start2;
        U5_Start2 = U5_Rec_Data;

        if ((U5_Start1 == 0x7b) && (U5_Start2 == 0x7b))
        {
            U5_RevDataFlag = 1;
        }

        U5_RxBuf[U5_RxBufWp] = U5_Rec_Data; // 接收数据放入缓冲区。
        U5_RxBufWp = (U5_RxBufWp + 1) % RX5_BUFLEN;
        U5_End1 = U5_End2;
        U5_End2 = U5_Rec_Data;

        if ((U5_End1 == 0x7d) && (U5_End2 == 0x7d) && (U5_RevDataFlag == 1))
        {
            // isr_evt_set(0x0008,t_USARTx_Data);//发送信号。
            U5_printf("\n-----> U5_Received <------\n");
            U5_RevDataFlag = 0;
        }
    }
    /* 处理发送缓冲区空中断 */
    if (USART_GetITStatus(UART_PORT, USART_IT_TXE) == SET)
    {
        USART_ClearITPendingBit(UART_PORT, USART_IT_TXE);
        //		  /* 发送数据 */
        //		  USART_SendData(UART4, aTxBuffer[ubTxIndex++]);
        /* 禁止发送缓冲区空中断 */
        USART_ITConfig(UART_PORT, USART_IT_TXE, DISABLE);
    }

    // 溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
    if (USART_GetFlagStatus(UART_PORT, USART_FLAG_ORE) == SET)
    {
        USART_ClearFlag(UART_PORT, USART_FLAG_ORE); // 读SR
        USART_ReceiveData(UART_PORT);               // 读DR
    }
}
