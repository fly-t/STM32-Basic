/**
 * @file sys.c
 * @brief 基础的系统组件
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-07-06 09:57
 * 
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-07-06 09:57 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#include "sys.h"

static uint32_t fac_us = 0; // us延时倍乘数


/**
 * @brief 记录systick,72Mhz-> 72个puse = 1us.
 * @param  sys_clk          My Param doc
 * @return * void 
 */
void delay_init(uint8_t sys_clk)
{
    
    fac_us = sys_clk;
}

/**
 * @brief us延时
 * @param  us               value
 * @return * void 
 */
void delay_us(uint32_t us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD; // LOAD的值
    ticks = us * fac_us;       // 需要的节拍数
    told = SysTick->VAL;        // 刚进入时的计数器值
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow; // 这里注意一下SYSTICK是一个递减的计数器就可以了.
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break; // 时间超过/等于要延迟的时间,则退出.
        }
    };
}

/**
 * @brief ms延时
 * @param  ms               value
 * @return * void
 */
void delay_ms(uint16_t ms)
{
    uint32_t i;
    for (i = 0; i < ms; i++)
        delay_us(1000);
}


/**
 * @brief 系统组件初始化
 * @param  sys_clk          My Param doc
 * @return * void 
 */
void sys_init(uint8_t sys_clk)
{
    delay_init(sys_clk);
}
