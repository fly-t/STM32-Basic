/**
 * @file soft_tim.c
 * @brief 软件定时器(嵌入式链表版本)
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-07-25 22:31
 *
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-06-13 18:18 <td>1.0     <td> Tengfei    <td> 数组维护定时器
 * <tr><td>2024-07-25 22:31 <td>2.0     <td> Tengfei    <td> 链表维护定时器,不用预先开辟内存.
 * </table>
 */
#include "soft_tim.h"
#include "tim.h"
#include <string.h>

/* 移植:硬件定时器选择 */
#define USING_TIMERx htim7

// 软件定时器链表头
static KLIST_HEAD(soft_tim_llist);

void software_timer_start(void);
void software_timer_create(soft_timer_t timer, char *name, uint32_t period_ms, TimerCallback callback);
void software_timer_open(soft_timer_t timerx);
void software_timer_close(soft_timer_t timerx);
void software_timer_update(void);

struct Softim soft_tim = {
    .id_counter = 0,
    .create = software_timer_create,
    .close = software_timer_close,
    .open = software_timer_open,
    .start_hd = software_timer_start,
};

/**
 * @brief stm32 定时器中断处理函数:周期结束回调函数，在定时器更新事件中调用
 * @brief 这里移植需要修改
 * @param  htim
 * @return * void
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == USING_TIMERx.Instance)
    {
        software_timer_update();
    }
}

/**
 * @brief 打开硬件定时器中断,开始计时.
 * @return * void
 */
void software_timer_start(void)
{
    HAL_TIM_Base_Start_IT(&USING_TIMERx);
}

/**
 * @brief 每1ms进中断一次, 检查时间是否到达, 到达则调用回调函数,复位时间
 * @return * void
 */
void software_timer_update(void)
{
    soft_timer_t timer;
    list_for_each_entry(timer, &soft_tim_llist, self)
    {
        timer->elapsed_ms += 1;
        if (timer->elapsed_ms >= timer->period_ms)
        {
            timer->callback();
            timer->elapsed_ms = 0;
        }
    }
}

/**
 * @brief 创建新的定时器, 并绑定回调函数
 * @param  soft_timer_t     定时器句柄
 * @param  name             定时器名称,最长8个字符
 * @param  period_ms        定时器触发周期
 * @param  callback         周期触发回调函数
 * @return * void
 */
void software_timer_create(soft_timer_t timer, char *name, uint32_t period_ms, TimerCallback callback)
{
    strncpy(timer->name, name, sizeof(timer->name));
    timer->period_ms = period_ms;
    timer->elapsed_ms = 0;
    timer->callback = callback;
    timer->id = soft_tim.id_counter++;

    LINK_INIT(&(timer->self));
}

/**
 * @brief 关闭定时器, 将定时器移除链表
 * @param  timerx           定时器指针
 * @return * void
 */
void software_timer_close(soft_timer_t timer)
{
    list_del(&timer->self);
}

/**
 * @brief 打开定时器, 将定时器添加到链表
 * @param  timerx           定时器指针
 * @return * void
 */
void software_timer_open(soft_timer_t timer)
{
    list_add_tail(&timer->self, &soft_tim_llist);
}

void task_demo(void)
{
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
}

void task_demo2(void)
{
    HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
}

void soft_timer_demo(void)
{
    static struct soft_timer timer1, timer2;
    soft_tim.create(&timer1, "Timer1", 100, task_demo);
    soft_tim.create(&timer2, "Timer2", 1000, task_demo2);
    soft_tim.open(&timer1);
    soft_tim.open(&timer2);
    soft_tim.start_hd();
}
