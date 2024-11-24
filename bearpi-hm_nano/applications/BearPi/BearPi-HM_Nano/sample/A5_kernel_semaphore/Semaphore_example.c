/*
 * Copyright (c) 2020 Nanjing Xiaoxiongpai Intelligent Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"

osSemaphoreId_t sem1;

void Thread_Semaphore1(void)
{
    while (1)
    {
        //释放两次sem1信号量，使得Thread_Semaphore2和Thread_Semaphore3能同步执行
        osSemaphoreRelease(sem1);

        //此处若只释放一次信号量，则Thread_Semaphore2和Thread_Semaphore3会交替运行。
        osSemaphoreRelease(sem1);

        printf("Thread_Semaphore1 Release  Semap \n");
        osDelay(100);
    }
}
void Thread_Semaphore2(void)
{
    while (1)
    {
        //申请sem1信号量
        osSemaphoreAcquire(sem1, osWaitForever);

        printf("Thread_Semaphore2 get Semap \n");
        osDelay(1);
    }
}

void Thread_Semaphore3(void)
{
    while (1)
    {
        //申请sem1信号量
        osSemaphoreAcquire(sem1, osWaitForever);

        printf("Thread_Semaphore3 get Semap \n");
        osDelay(1);
    }
}

void Semaphore_example(void)
{
    osThreadAttr_t attr;

    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 1024 * 4;
    attr.priority = 24;

    attr.name = "Thread_Semaphore1";
    if (osThreadNew((osThreadFunc_t)Thread_Semaphore1, NULL, &attr) == NULL)
    {
        printf("Falied to create Thread_Semaphore1!\n");
    }
    attr.name = "Thread_Semaphore2";
    if (osThreadNew((osThreadFunc_t)Thread_Semaphore2, NULL, &attr) == NULL)
    {
        printf("Falied to create Thread_Semaphore2!\n");
    }
    attr.name = "Thread_Semaphore3";
    if (osThreadNew((osThreadFunc_t)Thread_Semaphore3, NULL, &attr) == NULL)
    {
        printf("Falied to create Thread_Semaphore3!\n");
    }
    sem1 = osSemaphoreNew(4, 0, NULL);
    if (sem1 == NULL)
    {
        printf("Falied to create Semaphore1!\n");
    }
}
APP_FEATURE_INIT(Semaphore_example);
