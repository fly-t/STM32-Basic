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



struct Softim
{
    uint8_t id_counter; /// 定时器ID计数
    /* 定时器创建 */
    void (*create)(soft_timer_t timer, char *name, uint32_t period_ms, TimerCallback callback);
    /* 定时器打开 */
    void (*open)(soft_timer_t timerx);  
    /* 定时器关闭 */
    void (*close)(soft_timer_t timerx);
    /* 硬件定时器启动 */
    void (*start_hd)(void);
};
typedef struct Softim *Softim_t;
extern struct Softim soft_tim;


/**
 * @brief 测试用例
 * @return * void
 */
void soft_timer_demo(void);

#endif /* __SOFT_TIM_H__ */

