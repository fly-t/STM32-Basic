#include <stdarg.h>
#include <stdio.h>
#include "bsp_uart.h"
#include "cmsis_os.h"

extern osSemaphoreId BinarySem_U1_RxHandle;

uBuf u_buf_g[UCNT];

void bsp_uart_init(void)
{
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)&u_buf_g[U1].RxBuf, RX_BUFLEN); /// DMA 接收开启
    __HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);                                  /// 关闭DMA过半中断
}

/**
 * @brief uart接收回调函数, DMA中断接收完成触发二值信号量
 * @param  huart            My Param doc
 * @param  Size             My Param doc
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART1) { osSemaphoreRelease(BinarySem_U1_RxHandle); }
}

void U1_Putc(uint8_t *str)
{
    while (*str) {
        HAL_UART_Transmit(&huart1, (uint8_t *)str++, 1, HAL_MAX_DELAY);
        while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
    }
}
/**
 * @brief uart1 输出 num 个 uint8_t
 * @param  str              输出的数据
 * @return * void
 */
void U1_PutsNum(uint8_t *str, uint32_t Num)
{
    if (Num > 0) {
        // 启动 DMA 传输
        if (HAL_UART_Transmit_IT(&huart1, str, Num) == HAL_OK) {
            // 等待 传输完成
            while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET) {
                // 这里可以添加一个超时机制，避免死等
            }
        } else {
            // 错误处理，可能需要重试或其他操作
        }
    }
}

/**
 * @brief uart1 格式化输出
 * @param  fmt              格式串
 * @param  ...
 * @return * void
 */
void U1_printf(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char *)u_buf_g[U1].TxBuf, fmt, ap);
    va_end(ap);
    U1_Putc(u_buf_g[U1].TxBuf);
}
