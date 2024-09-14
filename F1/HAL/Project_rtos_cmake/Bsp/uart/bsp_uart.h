#ifndef __BSP_UART_H__
#define __BSP_UART_H__
#include <stdint.h>
#include "usart.h"

#define TX_BUFLEN 1024
#define RX_BUFLEN 13 /// 接收缓冲区大小

typedef struct {
    uint8_t TxBuf[TX_BUFLEN];
    uint8_t RxBuf[RX_BUFLEN];
} uBuf;
typedef uBuf *uBuf_t;

/* 串口索引 */
typedef enum {
    U1,
    UCNT // 数量
} uart_index_t;

extern uBuf u_buf_g[UCNT];

void bsp_uart_init(void);

void U1_printf(char *fmt, ...);
void U1_PutsNum(uint8_t *str, uint32_t Num);

#endif /* __BSP_UART_H__ */
