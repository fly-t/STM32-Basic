/**
 * @file sys.h
 * @brief 基础的系统组件
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-07-06 10:24
 *
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-07-06 10:24 <td>1.0     <td>wangh     <td>内容
 * </table>
 */

#ifndef __SYS_H
#define __SYS_H
#include "stm32f1xx.h"

#define NEED_IMPLEMENT        \
    while (1)                 \
    {                         \
        __asm__ volatile(""); \
    }

void sys_init(uint8_t sys_clk);
void delay_us(uint32_t us);
void delay_ms(uint16_t ms);
#endif /*  __SYS_H */
