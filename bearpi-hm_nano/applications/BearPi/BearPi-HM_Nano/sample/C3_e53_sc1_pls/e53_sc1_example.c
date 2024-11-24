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
#include "E53_SC1.h"

#define TASK_STACK_SIZE 1024 * 8
#define TASK_PRIO 25

static void Example_Task(void)
{
    float Lux;
    E53_SC1_Init();

    while (1)
    {
        printf("=======================================\r\n");
        printf("*************E53_SC1_example***********\r\n");
        printf("=======================================\r\n");
        Lux = E53_SC1_Read_Data();
        printf("Lux data:%.2f\r\n", Lux);
        if (Lux < 20)
        {
            Light_StatusSet(ON);
        }
        else
        {
            Light_StatusSet(OFF);
        }
        usleep(1000000);
    }
}

static void ExampleEntry(void)
{
    osThreadAttr_t attr;

    attr.name = "Example_Task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TASK_STACK_SIZE;
    attr.priority = TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)Example_Task, NULL, &attr) == NULL)
    {
        printf("Falied to create Example_Task!\n");
    }
}

APP_FEATURE_INIT(ExampleEntry);