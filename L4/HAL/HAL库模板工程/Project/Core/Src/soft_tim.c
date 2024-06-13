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
#include "stm32L4xx.h"
#include <stdbool.h>
#include <string.h>

#define MAX_TIMERS 5

typedef void (*TimerCallback)(void);

typedef struct
{
    char name[8];
    uint32_t period_ms;     ///  周期ms
    uint32_t elapsed_ms;    ///  已用ms
    TimerCallback callback;
    bool active;
} Soft_TIM_HandleTypeDef;

Soft_TIM_HandleTypeDef timers[MAX_TIMERS];

volatile uint32_t millis = 0;

void software_tim16_init(void)
{
    HAL_TIM_Base_Start_IT(&htim16);
}

void software_timer_init(void)
{
    for (int i = 0; i < MAX_TIMERS; i++)
    {
        timers[i].active = false;
    }
}

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

int software_timer_create(char *name, uint32_t period_ms, TimerCallback callback)
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
            return i;
        }
    }
    return -1;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = millis;
    while ((millis - start) < ms)
        ;
}

void task1(void)
{
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);    
}


// 周期结束回调函数，在定时器更新事件中调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM16)
    {
        millis++;
        software_timer_update();
    }
}
int test(void)
{

    software_tim16_init();
    software_timer_init();

    software_timer_create("Timer1", 100, task1);
    //create_timer("Timer2", 1000, task2);

}