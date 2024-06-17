# 项目创建

1. 添加预编译宏, 解决波浪线报错

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
               
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE",
                "STM32L431xx",   // 这两个是预编译宏, 比较关键, 波浪线报错
                "USE_HAL_DRIVER"
            ],
            "cStandard": "c17",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "gcc-arm",
            "compilerPath": "D:/env/mingw64/bin/gcc.exe"
        }
    ],
    "version": 4
}
```

2. 解决gpio波浪线报错

```c
/* USER CODE BEGIN 0 */
/* 添加两个头文件防止报错 */
#include "main.h"
#include "stm32l4xx_hal.h"
```

# 工程基本信息

| 外设   | 配置              | 参数                  |
| ------ | ----------------- | --------------------- |
| 时钟   | HSI               | 80MHz                 |
| 定时器 | timer16           | 1ms中断(软件定时器用) |
| Uart2  | PA2(Tx),PA3(Rx)   | 9600                  |
| Uart3  | PC10(Tx),PC11(Rx) | 9600                  |

# 软件定时器

软件定时器数量默认5

开放接口,新增定时器开机时间戳 单位ms.

时间戳类型uint64_t, 理论永久.

``` c
uint64_t get_millis(void);
void software_timer_init(TIM_HandleTypeDef *htimx);
soft_timer_t software_timer_create(char *name, uint32_t period_ms, TimerCallback callback);
void software_timer_open(soft_timer_t timerx);
void software_timer_close(soft_timer_t timerx);

// 演示示例
void soft_timer_demo(void);
```

# 格式化输出

移植

`u2printf.c`

``` c
#define BUF_SIZE 128            /// 缓冲区大小
#define SEND_MAX_DELAY 1000     /// 发送最大延时
#define HUARTx huart2           /// 串口句柄, 移植直接修改即可 huart1,huart2,huart3...
```

# 

