/**
 * @file queue.h
 * @brief 消息队列
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-06-16 22:41
 * 
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-06-16 22:41 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "stm32L4xx.h"
#include <stdbool.h>

#define MAX_SIZE 5

struct msg
{
    uint8_t header1;
    uint8_t header2;
    uint8_t length;
    uint8_t command;
    uint8_t reg;
    uint8_t data[4];
    uint8_t check;
    uint8_t tail1;
    uint8_t tail2;
};

typedef struct msg *msg_t;

struct Queue
{
    msg_t data[MAX_SIZE];
    int head; // 队列头指针
    int tail; // 队列尾指针
    int size; // 当前队列大小

    // 成员函数指针
    bool (*isFull)(struct Queue *q);
    bool (*isEmpty)(struct Queue *q);
    void (*enqueue)(struct Queue *q, msg_t msg);
    msg_t (*dequeue)(struct Queue *q);
    msg_t (*qFront)(struct Queue *q);
};

typedef struct Queue *Queue_t;

void queue_init(Queue_t q);
void queue_demo(void);

#endif /* __QUEUE_H__ */
