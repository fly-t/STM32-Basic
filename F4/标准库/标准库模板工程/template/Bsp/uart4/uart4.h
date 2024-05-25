/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*                                            STemWin CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*                                         STM32f407G-wangbao
*                                         Evaluation Board
*
* Filename      : bsp_usart.h
* Version       : V1.00
* Programmer(s) : wangfei
* data          : 2013-09-01
* e-mail        : wfmartin@hotmail.com
*                
*********************************************************************************************************
*/

#ifndef BSP_UART4_H
#define BSP_UART4_H

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*function prototypes------------------------------------*/

#define RX4_BUFLEN 128							//接收数据缓冲区大小
#define TX4_BUFLEN 128              


extern unsigned char U4_RxBuf[RX4_BUFLEN+1];					//接收数据缓冲区
extern unsigned int U4_RxBufWp;             							//接收缓存区写指针
extern unsigned int U4_RxBufRp;             							//接收缓存区读指针

extern unsigned char U4_TxBuf[TX4_BUFLEN+1];	    //发送数据缓冲区
extern unsigned int U4_TxBufWp;             		      //发送缓存区写指针
extern unsigned int U4_TxBufRp;             		      //发送缓存区读指针



void Bsp_UART4_Init(void);
void UART4_Puts(char * str);
void UART4_Putc(unsigned char c);
void u4_printf(char* fmt,...);
void USART4_PutsNum(char * str,unsigned int Num);

#endif /* BSP_USART3_H */

