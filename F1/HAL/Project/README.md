# 软件定时器

使用链表维护软件定时器.

<font color='red'> 移植要点 </font>

1. 编译选项中添加`--gnu`

使用gnu扩展选项, 否则typeof无法使用.

![](https://raw.githubusercontent.com/fly-t/images/main/blog/README-2024-07-25-22-51-39.png)

2. 修改`soft_time.c`中的硬件定时器

``` c
// 根据所使用的硬件定时器选择.
#define USING_TIMERx htim7
```

3. 测试用例

``` c
#include "soft_tim.h"
#include "klist.h"  // 依赖链表

void soft_timer_demo(void)
{
    static struct soft_timer timer1, timer2,timer3;
    soft_tim.create(&timer1, "Timer1", 100, task_demo);
    soft_tim.create(&timer2, "Timer2", 1000, task_demo2);
    soft_tim.create(&timer3, "Timer3", 1500, task_demo3);
    soft_tim.close(&timer2);
    soft_tim.close(&timer3);
    soft_tim.start_hd();
}
```