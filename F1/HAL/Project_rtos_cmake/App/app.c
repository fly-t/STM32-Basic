#include "app.h"
#include "bsp_uart.h"
#include "light.h"
// #include "free_rtos_tools.h"

/* ---------------------- 定时器句柄 ------------------------ */
osTimerId Timer_once_Handle;
osTimerId Timer_loop_Handle;

/* ---------------------- os信号量句柄 ------------------------ */
osSemaphoreId BinarySem_U1_RxHandle;

/* ---------------------- 线程句柄 ------------------------ */
osThreadId Task_U1_RecHandle;

/* ---------------------- 线程入口函数 ------------------------ */
void Task_U1_Rec_entry(void const *argument);

/* ---------------------- 按键回调 ------------------------ */
void Timer_loop_cb(void const *argument);

void Timer_once_cb(void const *argument);
/* ---------------------- report任务执行操作 ------------------------ */

void app_init(void)
{

    /* --------------------- 信号量 ------------------------ */
    osSemaphoreDef(BinarySem_U1_Rx);

    BinarySem_U1_RxHandle = osSemaphoreCreate(osSemaphore(BinarySem_U1_Rx), 1);
    xSemaphoreTake(BinarySem_U1_RxHandle, 0); /// 将信号量初始化为0

    /* --------------------- 任务 ----------------------- */
    osThreadDef(Task_U1_Rec, Task_U1_Rec_entry, osPriorityNormal, 0, 256);

    Task_U1_RecHandle =
        osThreadCreate(osThread(Task_U1_Rec), BinarySem_U1_RxHandle);

    /* --------------------- 定时器 ------------------------ */
    // osTimerDef(Timer_loop, Timer_loop_cb);
    // osTimerDef(Timer_once, Timer_once_cb);
    // Timer_loop_Handle =
    //     osTimerCreate(osTimer(Timer_loop), osTimerPeriodic, NULL);
    // Timer_once_Handle = osTimerCreate(osTimer(Timer_once), osTimerOnce,
    // NULL);

    // osTimerStart(Timer_loop_Handle, 50);
}

void Task_U1_Rec_entry(void const *argument)
{
    for (;;) {
        hello();
        U1_printf("blink\r\n");
        osSemaphoreId binSem_U1_Rx = (osSemaphoreId)argument;
        if (binSem_U1_Rx != NULL) {
            if (osSemaphoreWait(binSem_U1_Rx, 100) == osOK) {
                /* 校验数据 */

                HAL_UARTEx_ReceiveToIdle_DMA(
                    &huart1, (uint8_t *)&u_buf_g[U1].RxBuf, RX_BUFLEN);
                __HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);
            }
        }
        osDelay(50);
    }
}

// void Timer_loop_cb(void const *argument) { UNUSED(argument); }

// void Timer_once_cb(void const *argument) { UNUSED(argument); }
