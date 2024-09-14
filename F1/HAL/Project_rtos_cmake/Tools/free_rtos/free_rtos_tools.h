#ifndef __TOOLS_H__
#define __TOOLS_H__
// 定义一个缓冲区，用于存储任务列表信息
char g_taskListBuffer[1024];

/* 获取任务的剩余栈空间 */
#define GET_TASK_FREE_STACK(HANDLE)                                                                \
    do {                                                                                           \
        uint32_t freeStack = uxTaskGetStackHighWaterMark(HANDLE);                                  \
        U1_printf("%s free stack: %u words\n", pcTaskGetName((HANDLE)), freeStack);                \
    } while (0)

/* 获取所有任务的运行时间 */
#define GET_CUR_TASK_CPU_TIME()                                                                    \
    do {                                                                                           \
        vTaskGetRunTimeStats(g_taskListBuffer);                                                    \
        U1_printf("======== Task Runtime ========\n\n%s", g_taskListBuffer);                       \
    } while (0)

/* 获取所有任务的状态 */
#define GET_ALL_TASK_STATS()                                                                       \
    do {                                                                                           \
        vTaskList(g_taskListBuffer);                                                               \
        U1_printf("======== Task List ========\n\n%s", g_taskListBuffer);                          \
    } while (0)

#endif /* __TOOLS_H__ */
