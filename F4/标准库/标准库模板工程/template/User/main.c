#include "sys.h"
#include "delay.h"

#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_usart3.h"
#include "bsp_uart4.h"
#include "bsp_uart5.h"
#include "bsp_usart6.h"
#include "bsp_uart8.h"
#include "bsp_led.h"

int main(void)
{
    delay_init(180);    // 初始化延时函数
    Bsp_Switch_Init();  // 初始化LED端口
    Bsp_USART1_Init();
    Bsp_USART2_Init();
    Bsp_USART3_Init();
    Bsp_UART4_Init();
    Bsp_UART5_Init();
    Bsp_USART6_Init();
    Bsp_UART8_Init();
    /**下面是通过直接操作库函数的方式实现IO控制**/
    while (1)
    {
        U1_printf("u1 send....\n");
        U2_printf("u2 send....\n");
        U3_printf("u3 send....\n");
        u4_printf("u4 send....\n");
        U5_printf("u5 send....\n");
        U6_printf("u6 send....\n");
        U8_printf("u8 send....\n");
        LED_Run = ON;                       
        Seat1_Display = ON;                 
        Seat2_Display = ON;                 
        Luggage_Signa = ON;                 
        Sound_Signal = ON;                  
        Other = ON;                         
        LED1 = ON;                        
        LED2 = ON;                        
        delay_ms(100);                     
        LED_Run = OFF;                      
        Luggage_Signa = OFF;                
        Sound_Signal = OFF;                 
        Seat1_Display = OFF;                
        Seat2_Display = OFF;                
        Other = OFF;                        
        LED1 = OFF;                         
        LED2 = OFF;                         
        delay_ms(100);                     
    }
}
