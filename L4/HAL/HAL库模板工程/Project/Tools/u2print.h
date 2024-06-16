/**
 * @file u2print.h
 * @brief usb<-->ttl 串口打印/接收
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-06-16 23:07
 * 
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-06-16 23:07 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#ifndef __U2PRINT_H__
#define __U2PRINT_H__

#include "stm32L4xx.h"
#include <stdbool.h>

void u2_printf(char *format, ...);
void u2_send_byte(uint8_t byte);
void u2_send_n(uint8_t *arr, uint16_t n);

void u2_demo(void);
#endif /* __U2PRINT_H__ */
