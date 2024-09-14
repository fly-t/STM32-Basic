#include "usart.h"
#include "cmsis_os.h"

unsigned long getRunTimeCounterValue(void) { return osKernelSysTick(); }

void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName)
{ /* 当检测到任务堆栈溢出时调用此钩子函数 */
    UNUSED(xTask);
    U1_printf("task:%s overflow\n", pcTaskName);
}
