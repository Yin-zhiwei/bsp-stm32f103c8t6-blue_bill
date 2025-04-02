/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-21     RT-Thread    first version
 */

#if 1
#include <rtthread.h>
#include "board.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

/**************** 硬件相关配置 ****************/
#define LED_PIN       GPIO_PIN_13  // PC13
#define LED_GPIO_PORT GPIOC       // 使用 GPIOC

/*************** 线程配置 *******************/
#define THREAD_PRIORITY       25
#define THREAD_STACK_SIZE     512
#define THREAD_TIMESLICE      5

static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
volatile char aaa[20] = "线程创建成功";

/************** 硬件初始化函数 ***************/
static void led_hw_init(void)
{
    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能 GPIOC 时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // 配置 PC13 为推挽输出模式，最大速度 50MHz
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;        // 无上下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速模式（50MHz）
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    // 设置初始电平为高（LED 关闭）
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
}

/************** LED控制函数 ****************/
static void led_on(void)
{
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // 使用HAL库函数置高电平
}

/************** 线程入口函数 ****************/
static void thread1_entry(void *parameter)
{
    led_hw_init();

    while (1)
    {
        led_on();
        rt_thread_mdelay(500);
    }
}

static void thread2_entry(void *parameter)
{
    rt_hw_console_output(aaa);

    while (1)
    {

    }
}

/*************** 主函数 ********************/
int main(void)
{
    // 创建线程
    tid1 = rt_thread_create("led",
                            thread1_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY,
                            THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
    {
        rt_thread_startup(tid1);
    }
    else
    {
        return RT_ERROR;
    }

    tid2 = rt_thread_create("Init",
                            thread2_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY,
                            THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
    {
        rt_thread_startup(tid2);
    }
    else
    {
        return RT_ERROR;
    }

    return RT_EOK;
}
#endif

#if 0
#include <rtthread.h>
#include "board.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

/**************** 硬件相关配置 ****************/
/* 以下地址以STM32F1系列为例，需根据实际芯片调整 */
#define RCC_APB2ENR   (*(volatile unsigned long *)0x40021018)
#define GPIOC_CRH     (*(volatile unsigned long *)0x40011004) // GPIOC的高寄存器
#define GPIOC_ODR     (*(volatile unsigned long *)0x4001100C)

#define LED_PIN       13  // PC13

/*************** 线程配置 *******************/
#define THREAD_PRIORITY       25
#define THREAD_STACK_SIZE     512
#define THREAD_TIMESLICE      5

static rt_thread_t tid1 = RT_NULL;

/************** 硬件初始化函数 ***************/
static void led_hw_init(void)
{
    // 使能GPIOC时钟（BIT4）
    RCC_APB2ENR |= (1 << 4);

    // 配置PC13为推挽输出模式，最大速度50MHz
    // CNF[1:0] = 00 (通用推挽输出)
    // MODE[1:0] = 11 (输出模式，最大速度50MHz)
    // 注意：PC13在CRH寄存器中，偏移量为 (13 - 8) * 4 = 20
    GPIOC_CRH &= ~(0x0F << (4 * (LED_PIN - 8))); // 清除原有配置
    GPIOC_CRH |=  (0x03 << (4 * (LED_PIN - 8))); // 设置新配置
}

/************** LED控制函数 ****************/
static void led_toggle(void)
{
    GPIOC_ODR ^= (1 << LED_PIN); // 使用异或操作翻转电平
}

/************** 线程入口函数 ****************/
static void thread1_entry(void *parameter)
{
    led_hw_init();

    while (1)
    {
        led_toggle();
        rt_thread_mdelay(500);
    }
}

/*************** 主函数 ********************/
int main(void)
{
    // 创建线程
    tid1 = rt_thread_create("led",
                        thread1_entry,
                        RT_NULL,
                        THREAD_STACK_SIZE,
                        THREAD_PRIORITY,
                        THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
    {
        rt_thread_startup(tid1);
    }
    else {
        LOG_E("线程创建失败!");
    }

    return RT_EOK;
}
#endif
