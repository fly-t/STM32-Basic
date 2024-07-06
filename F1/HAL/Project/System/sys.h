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
