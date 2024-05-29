#ifndef BSP_UART5_H
#define BSP_UART5_H


#include "stm32f4xx.h"


#define RX5_BUFLEN 128							//接收数据缓冲区大小
#define TX5_BUFLEN 128              



void Bsp_UART5_Init(void);
void U5_Puts(char * str);
void U5_Putc(unsigned char c);
void U5_PutsNum(char * str,unsigned int Num);
void U5_printf(char* fmt,...);
#endif /* BSP_USART5_H */

