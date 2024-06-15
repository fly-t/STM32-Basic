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

#include "stm32L4xx.h"
#include <stdbool.h>

typedef void (*TimerCallback)(void);

struct soft_timer
{
    char name[8];
    uint32_t period_ms;     ///  周期ms
    uint32_t elapsed_ms;    ///  已用ms
    TimerCallback callback; /// 回调函数
    bool active;            /// 定时器是否打开
};

typedef struct soft_timer *soft_timer_t;

/* null pointer definition(ST:Soft Timer) */
#define ST_NULL 0

void software_timer_init(TIM_HandleTypeDef *htimx);
soft_timer_t software_timer_create(char *name, uint32_t period_ms, TimerCallback callback);
void software_timer_open(soft_timer_t timerx);
void software_timer_close(soft_timer_t timerx);

void soft_timer_demo(void);

#endif /* __SOFT_TIM_H__ */

