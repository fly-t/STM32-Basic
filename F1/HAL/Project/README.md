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