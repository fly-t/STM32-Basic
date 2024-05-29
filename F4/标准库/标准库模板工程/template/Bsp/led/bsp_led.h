#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define ON 0
#define OFF 1

/* 开关量信号定义 */
#define LED_Run PFout(12)

#define Seat1_Display PEout(2)
#define Seat2_Display PBout(7)
#define Sound_Signal PBout(6)
#define Luggage_Signa PEout(3)
#define LED1 PEout(4)
#define LED2 PEout(5)
#define Other PEout(6)

void Bsp_Switch_Init(void); // 初始化
#endif
