#ifndef BSP_UART2_H
#define BSP_UART2_H


#include "stm32f4xx.h"


#define RX2_BUFLEN 128							//接收数据缓冲区大小
#define TX2_BUFLEN 128              



void Bsp_USART2_Init(void);
void U2_Puts(uint8_t * str);
void U2_Putc(uint8_t c);
void U2_PutsNum(uint8_t * str,uint32_t Num);
void U2_printf(char* fmt,...);
#endif /* BSP_USART3_H */

