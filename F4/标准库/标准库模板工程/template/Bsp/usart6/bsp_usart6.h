#ifndef BSP_UART6_H
#define BSP_UART6_H


#include "stm32f4xx.h"


#define RX6_BUFLEN 128							//接收数据缓冲区大小
#define TX6_BUFLEN 128              



void Bsp_USART6_Init(void);
void U6_Puts(uint8_t * str);
void U6_Putc(uint8_t c);
void U6_PutsNum(uint8_t * str,uint32_t Num);
void U6_printf(char* fmt,...);
#endif /* BSP_USART3_H */

