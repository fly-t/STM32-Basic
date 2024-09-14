# rtos 开启堆栈监测

https://xie.infoq.cn/article/d3f7d46aa262b2118a544f250

# 溢出不是很离谱的情况可以进入钩子函数

太离谱了程序直接跑不动, option1 更轻量化

``` c
void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName)
{ /* 当检测到任务堆栈溢出时调用此钩子函数 */
    U1_printf("task:%s overflow\n", pcTaskName);
}
```

