#ifndef BSP_UART3_H
#define BSP_UART3_H


#include "stm32f4xx.h"


#define RX3_BUFLEN 128							//接收数据缓冲区大小
#define TX3_BUFLEN 128              



void Bsp_USART3_Init(void);
void U3_Puts(char * str);
void U3_Putc(uint8_t c);
void U3_PutsNum(char * str,uint32_t Num);
void U3_printf(char* fmt,...);
#endif /* BSP_USART3_H */

