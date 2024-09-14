# UART

## 概要
1. 阻塞(不推荐)
2. 中断
3. dma
4. 空闲中断

使用HAL的方式下还是推荐DMA+空闲中断. 

使用其他配置方式对cpu的占用比较高.

>  - 使用阻塞发送实现是最简单的, 但是也是性能开销最大的. 极度不推荐.
>  - 使用中断接收收发数据频繁的情况下,对cpu的占用也是比较高的负担(收发频率较高不推荐)
>  - 使用dma模式极大程度减轻了cpu负担, 但但是数据长度固定(推荐数据长度固定的场景)
>  - dma+空闲中断, 减轻cpu负担的情况下还可以接收不定长数据(但是时效性还是定长的速度快).

## 配置模式

normal: 一次触发进中断一次,需要手动开启接中断.(推荐)
circular: 自动触发下次(有点问题,有时候处理不好会出现数据丢失的情况)

![](https://raw.githubusercontent.com/fly-t/images/main/blog/README-2024-06-26-14-30-24.png)

<font color='red'> 以下代码均采用`normal`模式进行</font>
<font color='red'> 以下代码均采用`normal`模式进行</font>
<font color='red'> 以下代码均采用`normal`模式进行</font>

### 中断模式, 阻塞模式, dma模式
``` c
/* 中断和dma要数量匹配 */
uint8_t rec_buf[13];

/* dma it 回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 复位DMA中断接收(mormal模式) */
    if (HAL_UART_Receive_DMA(&huart4, rec_buf, sizeof(rec_buf)) != HAL_OK)
    {
        Error_Handler();
    }
    /* 判断串口 */
    if (huart == &huart4)
    {
        /* dma发送(该模式下发送会触发  发送中断) */
        HAL_UART_Transmit_DMA(&huart4, rec_buf, sizeof(rec_buf));
        /* 中断发送(该模式下发送会触发  发送中断)*/
        HAL_UART_Transmit_IT(&huart4, rec_buf, sizeof(rec_buf));
        /* 阻塞发送(不会 进入到发送中断) */
        HAL_UART_Transmit(&huart4, rec_buf, sizeof(rec_buf),HAL_MAX_DELAY);
    }
}

int main(){

    /* 复位DMA中断进入接收状态(mormal模式) */
    /* 下列两种模式需要配置 接收的数据长度 触发中断 */
    HAL_UART_Receive_DMA(&huart4, rec_buf, sizeof(rec_buf));
    // HAL_UART_Receive_IT(&huart4, rec_buf, sizeof(rec_buf));
    
    while(1){

    }
}
```


# 空闲中断模式


``` c
/* dma传输过半会触发回调函数,记得关闭 */
uint8_t rec_buf[13];

/* idel中断接收回调 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    HAL_UART_Transmit_DMA(&huart4, rec_buf, Size);
    
    HAL_UARTEx_ReceiveToIdle_DMA(&huart4, rec_buf, sizeof(rec_buf));
    /* 关闭dma接收过半中断 */
	__HAL_DMA_DISABLE_IT(&hdma_uart4_rx, DMA_IT_HT);
}


int main(){

    /* 复位DMA中断进入接收状态(mormal模式) */
    HAL_UARTEx_ReceiveToIdle_DMA(&huart4, rec_buf, sizeof(rec_buf));
    __HAL_DMA_DISABLE_IT(&hdma_uart4_rx, DMA_IT_HT);
    while(1){
        
    }
}
```

测试结果,间隔1ms发送没有任何问题.

![](https://raw.githubusercontent.com/fly-t/images/main/blog/README-2024-06-26-15-50-27.png)
