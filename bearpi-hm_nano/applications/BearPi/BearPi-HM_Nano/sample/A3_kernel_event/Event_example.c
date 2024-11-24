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

#define FLAGS_MSK1 0x00000001U

osEventFlagsId_t evt_id; // event flags id

/***** 发送事件 *****/
void Thread_EventSender(void *argument)
{
  (void)argument;
  while (1)
  {
    osEventFlagsSet(evt_id, FLAGS_MSK1);

    //suspend thread
    osThreadYield();

    osDelay(100);
  }
}

/***** 接收事件 *****/
void Thread_EventReceiver(void *argument)
{
  (void)argument;
  uint32_t flags;

  while (1)
  {
    flags = osEventFlagsWait(evt_id, FLAGS_MSK1, osFlagsWaitAny, osWaitForever);
    printf("Receive Flags is %d\n", flags);
  }
}

/***** 创建事件 *****/
static void Event_example(void)
{
  evt_id = osEventFlagsNew(NULL);
  if (evt_id == NULL)
  {
    printf("Falied to create EventFlags!\n");
  }

  osThreadAttr_t attr;

  attr.attr_bits = 0U;
  attr.cb_mem = NULL;
  attr.cb_size = 0U;
  attr.stack_mem = NULL;
  attr.stack_size = 1024 * 4;
  attr.priority = 25;

  attr.name = "Thread_EventSender";
  if (osThreadNew(Thread_EventSender, NULL, &attr) == NULL)
  {
    printf("Falied to create Thread_EventSender!\n");
  }
  attr.name = "Thread_EventReceiver";
  if (osThreadNew(Thread_EventReceiver, NULL, &attr) == NULL)
  {
    printf("Falied to create Thread_EventReceiver!\n");
  }
}

APP_FEATURE_INIT(Event_example);
