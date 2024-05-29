#ifndef BSP_UART1_H
#define BSP_UART1_H


#include "stm32f4xx.h"


#define RX1_BUFLEN 128							//接收数据缓冲区大小
#define TX1_BUFLEN 128              



void Bsp_USART1_Init(void);
void U1_Puts(char * str);
void U1_Putc(unsigned char c);
void U1_PutsNum(char * str,unsigned int Num);
void U1_printf(char* fmt,...);
#endif /* BSP_USART3_H */

