/**
 * @file queue.c
 * @brief 消息队列实现
 * @author Tengfei Zhang (izhangtengfei@163.com)
 * @version 1.0
 * @date 2024-06-16 23:07
 * 
 * @copyright Copyright (c) 2024  Tengfei Zhang All rights reserved
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2024-06-16 23:07 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "queue.h"

/**
 * @brief 检查队列是否为空
 * @param  q                队列句柄
 * @return true
 * @return false
 */
bool isEmpty(Queue_t q)
{
    return q->size == 0;
}

/**
 * @brief 检查队列是否已满
 * @param  q                队列句柄
 * @return true
 * @return false
 */
bool isFull(Queue_t q)
{
    return q->size == MAX_SIZE;
}

/**
 * @brief 入队
 * @param  q                队列句柄
 * @param  msg              入队消息
 * @return * void
 */
void enqueue(Queue_t q, msg_t msg)
{
    if (isFull(q))
    {
        printf("Queue is full!\n");
        return;
    }
    q->tail = (q->tail + 1) % MAX_SIZE;
    q->data[q->tail] = msg;
    q->size++;
}

/**
 * @brief 出队
 * @param  q                队列句柄
 * @return * msg_t          出队消息
 */
msg_t dequeue(Queue_t q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty!\n");
        return NULL; // 返回NULL表示队列为空
    }
    msg_t msg = q->data[q->head];
    q->head = (q->head + 1) % MAX_SIZE;
    q->size--;
    return msg;
}

/**
 * @brief 获取队列头部元素
 * @param  q                队列句柄
 * @return * msg_t          队列头部元素
 */
msg_t qFront(Queue_t q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty!\n");
        return NULL; // 返回NULL表示队列为空
    }
    return q->data[q->head];
}

/**
 * @brief 初始化队列和成员函数
 * @param  q                队列句柄
 * @return * void
 */
void queue_init(Queue_t q)
{
    /* 初始化队列 */
    q->head = 0;
    q->tail = -1;
    q->size = 0;

    /* 初始化成员函数 */
    q->isEmpty = isEmpty;
    q->isFull = isFull;
    q->enqueue = enqueue;
    q->dequeue = dequeue;
    q->qFront = qFront;
}

// 主函数测试队列操作
void queue_demo()
{
    struct Queue qInstance;
    Queue_t q = &qInstance;
    queue_init(q);

    struct msg msg1 = {0x01, 0x02, 0x03, 0x04, 0x05, {0x06, 0x07, 0x08, 0x09}, 0x0A, 0x0B, 0x0C};
    struct msg msg2 = {0x11, 0x12, 0x13, 0x14, 0x15, {0x16, 0x17, 0x18, 0x19}, 0x1A, 0x1B, 0x1C};

    q->enqueue(q, &msg1);
    q->enqueue(q, &msg2);

    msg_t frontMsg = q->qFront(q);
    if (frontMsg != NULL)
    {
        printf("head message header is %d\n", frontMsg->header1);
    }

    q->dequeue(q);
    msg_t dequeuedMsg = q->dequeue(q);
    if (dequeuedMsg != NULL)
    {
        printf("Dequeued message command is %d\n", dequeuedMsg->command);
    }
}
