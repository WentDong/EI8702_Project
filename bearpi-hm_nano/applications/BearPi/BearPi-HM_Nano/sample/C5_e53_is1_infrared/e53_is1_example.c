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
#include "E53_IS1.h"

#define TASK_STACK_SIZE 1024 * 8
#define TASK_PRIO 25
#define FLAGS_MSK1 0x00000001U

osEventFlagsId_t evt_id;

static void Beep_Alarm(char *arg)
{
    (void)arg;
    osEventFlagsSet(evt_id, FLAGS_MSK1);
}

static void Example_Task(void)
{
    E53_IS1_Init();
    E53_IS1_Read_Data(Beep_Alarm);
    while (1)
    {
        osEventFlagsWait(evt_id, FLAGS_MSK1, osFlagsWaitAny, osWaitForever);
        Beep_StatusSet(ON);
        osDelay(300);
        Beep_StatusSet(OFF);
    }
}

static void ExampleEntry(void)
{
    evt_id = osEventFlagsNew(NULL);
    if (evt_id == NULL)
    {
        printf("Falied to create EventFlags!\n");
    }
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