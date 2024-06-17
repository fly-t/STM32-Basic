/**
 * @file soft_tim.c
 * @brief 软件定时器
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-06-13 18:18
 * 
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-06-13 18:18 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#include "soft_tim.h"
#include "tim.h"
#include <string.h>

#define MAX_TIMERS 5 /// 默认定时器数量5


struct soft_timer timers[MAX_TIMERS];

volatile uint32_t millis = 0;

/**
 * @brief Get the millis second
 * @return * uint32_t ms of timer running
 */
uint64_t get_millis(void)
{
    return millis;
}

/**
 * @brief 打开硬件定时器中断,开始计时.
 * @param  htimx            htim1, him2...(use CubeMx config timer)
 * @return * void 
 */
void software_timer_start(TIM_HandleTypeDef *htimx)
{
    HAL_TIM_Base_Start_IT(htimx);
}

/**
 * @brief 打开定时器中断, 并初始化定时器数组
 * @param  htimx            htimx
 * @return * void
 */
void software_timer_init(TIM_HandleTypeDef *htimx)
{
    software_timer_start(htimx);

    for (int i = 0; i < MAX_TIMERS; i++)
    {
        timers[i].active = false;
    }
}

/**
 * @brief update all timer have actived, and callback
 * @return * void 
 */
void software_timer_update(void)
{
    for (int i = 0; i < MAX_TIMERS; i++)
    {
        if (timers[i].active)
        {
            timers[i].elapsed_ms += 1;
            if (timers[i].elapsed_ms >= timers[i].period_ms)
            {
                timers[i].elapsed_ms = 0;
                timers[i].callback();
            }
        }
    }
}

/**
 * @brief 创建新的定时器, 并绑定回调函数
 * @param  name             定时器名称
 * @param  period_ms        定时器触发周期
 * @param  callback         周期触发回调函数
 * @return * soft_timer_t            错误返回ST_NULL, 否则返回成功的定时器句柄
 */
soft_timer_t software_timer_create(char *name, uint32_t period_ms, TimerCallback callback)
{
    for (int i = 0; i < MAX_TIMERS; i++)
    {
        if (!timers[i].active)
        {
            strcpy(timers[i].name, name);
            timers[i].period_ms = period_ms;
            timers[i].elapsed_ms = 0;
            timers[i].callback = callback;
            timers[i].active = true;
            return &timers[i];
        }
    }
    return ST_NULL;
}


/**
 * @brief 关闭定时器
 * @param  timerx           定时器句柄
 * @return * void
 */
void software_timer_close(soft_timer_t timerx)
{
    timerx->active = 0;
}

/**
 * @brief 打开定时器
 * @param  timerx           定时器句柄
 * @return * void
 */
void software_timer_open(soft_timer_t timerx)
{
    timerx->active = 1;
}

/**
 * @brief stm32 定时器中断处理函数:周期结束回调函数，在定时器更新事件中调用
 * @brief 这里移植需要修改
 * @param  htim             
 * @return * void
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM16)
    {
        millis++;
        software_timer_update();
    }
}



void task_demo(void)
{
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
}

/**
 * @brief 使用示例
 * @return * void 
 */
void soft_timer_demo(void)
{
    /* 初始化定时器 */
    software_timer_init(&htim16);

    soft_timer_t timer1 = software_timer_create("Timer1", 200, task_demo);
}
