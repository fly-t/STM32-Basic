/**
 * @file soft_tim.h
 * @brief 软件定时器, 使用一个硬件定时器
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-06-13 18:16
 * 
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-06-13 18:16 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#ifndef __SOFT_TIM_H__
#define __SOFT_TIM_H__

#include <stdbool.h>
#include "stm32F1xx.h"
#include "klist.h"

typedef void (*TimerCallback)(void);

struct soft_timer
{
    link_t self;            /// 链表
    uint8_t id;             /// 定时器ID
    char name[8];           /// 定时器名称
    uint32_t period_ms;     ///  周期ms
    uint32_t elapsed_ms;    ///  已用ms
    TimerCallback callback; /// 回调函数
};

typedef struct soft_timer *soft_timer_t;


/**
 * @brief 创建新的定时器, 并绑定回调函数
 * @param  soft_timer_t     定时器句柄
 * @param  name             定时器名称,最长8个字符
 * @param  period_ms        定时器触发周期
 * @param  callback         周期触发回调函数
 * @return * void
 */
void software_timer_create(soft_timer_t timer, char *name, uint32_t period_ms, TimerCallback callback);

/**
 * @brief 打开定时器, 将定时器添加到链表
 * @param  timerx           定时器指针
 * @return * void
 */
void software_timer_open(soft_timer_t timerx);

/**
 * @brief 关闭定时器, 将定时器移除链表
 * @param  timerx           定时器指针
 * @return * void
 */
void software_timer_close(soft_timer_t timerx);

/**
 * @brief 每1ms进中断一次, 检查时间是否到达, 到达则调用回调函数,复位时间
 * @return * void
 */
void software_timer_update(void);

/**
 * @brief 测试用例
 * @return * void
 */
void soft_timer_demo(void);

#endif /* __SOFT_TIM_H__ */

