# 标准库模板创建

## 1. 下载官方标注库文件

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-27-24.png)

## 2. 创建keil工程

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-28-18.png)

 - `project -> new_uVisionProject`
 - create_project name

## 3. 复制所需库文件

### 3.1 添加启动文件



将固件库目录中的启动文件添加到项目中

``` bash
D:\donwload\固件库\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm
```

将所有文件复制到新建工程目录中的Stratup文件夹中(文件名字随意)

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-34-59.png)

完成后工程结构如下

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-36-21.png)


### 3.2 添加stm32寄存器(片上外设)描述文件和系统时钟配置文件



src:

``` bash
D:\donwload\固件库\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x
```
dest:

``` bash
template(工程目录)/startup/
```
![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-41-45.png)

`hd.s`

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-23-03-31.png)

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-45-38.png)

### 3.3 添加stm32内核的寄存器描述

将src目录下的所有文件复制到dest目录下

`core_cm3.h`: 内核寄存器描述文件
`core_cm3.c`: 内核配置文件


src:

``` bash
D:\donwload\固件库\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\CoreSupport
```

dest:

``` bash
template(工程目录)/startup/
```

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-51-06.png)


## 4. 将目录中的文件添加到工程

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-57-52.png)

添加完成后工程结构如下

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-21-58-08.png)

## 5. 添加用户文件夹

添加文件夹,并添加到工程中

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-02-08.png)

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-01-23.png)

在`User`文件夹中添加`main.c`文件

`main.c`

``` c
#include "stm32f10x.h"                  // Device header


int main(void){

	return 0;
}

```

## 6. 添加includePath

将user目录和startup目录添加到includePath中

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-07-10.png)


7. 编译

寄存器版本即可开发

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-15-15.png)

## 7. 添加内核和外设库文件



将src目录下的`src`目录和`inc`目录所有文件复制到dest目录下

<font color='red'> 别忘记在工程中新建`Libraries`文件夹和`添加incPath` </font> 


src:

``` bash
D:\donwload\固件库\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\STM32F10x_StdPeriph_Driver
```

dest:
``` bash
template(工程目录)/Libraries/
```

> `misc.c`和 `misc.h`为内核库文件
> 其他为外设库文件


![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-24-36.png)

## 8. 添加库函数头文件包含文件

添加库函数头文件包含文件`stm32f10x_conf.h`, 该文件用于控制库文件的头文件包含(配置是否启用指定的外设库)

`stm32f10x_it.h` `stm32f10x_it.c`用来存放中断函数

将该三个文件添加到工程`User`目录下

src:

``` bash
D:\donwload\固件库\STM32F10x_StdPeriph_Lib_V3.5.0\Project\STM32F10x_StdPeriph_Template
```

dest:

``` bash
template(工程目录)/User/
```

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-33-39.png)

### 8.1 添加宏定义
<font color='red'> 添加宏定义`USE_STDPERIPH_DRIVER` </font>

<font color='red'> 添加宏定义`USE_STDPERIPH_DRIVER`</font>

<font color='red'> 添加宏定义`USE_STDPERIPH_DRIVER` </font>


![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-39-58.png)

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-22-40-27.png)


## 点灯

``` c
#include "stm32f10x.h"                  // Device header

int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	return 0;
}

```



![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-22-23-05-00.png)

# clean

`clean.bat`

该脚本用于清除项目构建过程出现的文件,确保项目大小最小.


# F4的移植参考F1的移植过程

需要注意点:
    1. 添加内核(core)启动文件时需要把cm****相关的文件都添加进来.

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-24-17-38-36.png)

## 复制完工程后编译报错

0. 添加宏定义

``` c
USE_STDPERIPH_DRIVER,STM32F427_437xx
```

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-24-17-23-36.png)

1. 删除多余文件

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-24-17-19-42.png)

2. 编译报错

> …\USER\stm32f4xx.h(11581): warning: #47-D: incompatible redefinition of macro “DBGMCU_APB2_FZ_DBG_TIM1_STOP” (declared at line 11574)

双击进入报错文件`stm32fxx.h`报错行,发现果然存在相同的宏定义

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-24-17-23-00.png)

3. 复制template目录下的`main.c`和`main.h`到工程目录user中.

因为其他文件依赖了main.h.

要不然编译报错:

> .\Objects\Project.axf: Error: L6218E: Undefined symbol TimingDelay_Decrement (referred from stm32f4xx_it.o).

4. 根据实际的晶振配置时钟

默认是25M的时钟, 配置为8M的时钟需要修改

根据cubeMx的时钟配置修改

![](https://raw.githubusercontent.com/fly-t/images/main/blog/create_notes-2024-05-24-18-40-11.png)

在编译宏中添加`HSE_VALUE=80000000`宏定义(具体值根据硬件设置)

`system_stm32f4xx.c`

|  参数    |   值  |
| ------------- | ------------- |
|  PLL_M   |   /4   |
|  PLL_N   |   /180   |
|  PLL_P   |   /2   |