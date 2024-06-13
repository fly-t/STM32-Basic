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

