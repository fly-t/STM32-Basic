/**
 * @file u2print.c
 * @brief 
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-06-16 23:06
 * 
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-06-16 23:06 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "u2print.h"
#include "usart.h"

#define BUF_SIZE 128            /// 缓冲区大小
#define SEND_MAX_DELAY 1000     /// 发送最大延时
#define HUARTx huart2           /// 串口句柄, 移植直接修改即可 huart1,huart2,huart3...

/**
 * @brief 格式化输出字符串,printf 函数的替代品
 * @param  format           格式
 * @param  ...              
 * @return * void 
 */
void u2_printf(char *format, ...)
{
    char buffer[BUF_SIZE]; // 缓冲区大小
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    HAL_UART_Transmit(&HUARTx, (uint8_t *)buffer, strlen(buffer), SEND_MAX_DELAY);
}

/**
 * @brief 发送一个字节
 * @param  byte             My Param doc
 * @return * void 
 */
void u2_send_byte(uint8_t byte)
{
    HAL_UART_Transmit(&HUARTx, &byte, 1, SEND_MAX_DELAY);
}

/**
 * @brief 发送n个字节
 * @param  arr              字节数组
 * @param  n                数量
 * @return * void
 */
void u2_send_n(uint8_t *arr, uint16_t n)
{
    while (n)
    {
        n--;
        u2_send_byte(*arr++);
    }
}

void u2_demo(void){
    u2_printf("u2_printf\r\n");
    
    u2_send_byte(0x1a);

    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    u2_send_n(data, 4);
}