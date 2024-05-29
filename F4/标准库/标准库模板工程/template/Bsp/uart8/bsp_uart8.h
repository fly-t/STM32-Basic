#ifndef BSP_UART8_H
#define BSP_UART8_H


#include "stm32f4xx.h"


#define RX8_BUFLEN 128							//接收数据缓冲区大小
#define TX8_BUFLEN 128              



void Bsp_UART8_Init(void);
void U8_Puts(char * str);
void U8_Putc(unsigned char c);
void U8_PutsNum(char * str,unsigned int Num);
void U8_printf(char* fmt,...);
#endif /* BSP_USART8_H */

