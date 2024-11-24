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


//number of Message Queue Objects
#define MSGQUEUE_OBJECTS 16

typedef struct
{
  //object data type
  char *Buf;
  
  uint8_t Idx;
} MSGQUEUE_OBJ_t;



//message queue id
osMessageQueueId_t mid_MsgQueue;   

void Thread_MsgQueue1(void *argument)
{
  (void)argument;
  MSGQUEUE_OBJ_t msg;
  //do some work...
  msg.Buf = "Hello BearPi-HM_Nano!";
  msg.Idx = 0U;
  while (1)
  {
    osMessageQueuePut(mid_MsgQueue, &msg, 0U, 0U);

    //suspend thread
    osThreadYield();
    osDelay(100);
  }
}

void Thread_MsgQueue2(void *argument)
{
  (void)argument;
  osStatus_t status;
  MSGQUEUE_OBJ_t msg;
  while (1)
  {
    //Insert thread code here...

    //wait for message
    status = osMessageQueueGet(mid_MsgQueue, &msg, NULL, osWaitForever);
    if (status == osOK)
    {
       printf("Message Queue Get msg:%d-%s\n", msg.Idx,msg.Buf);
    }
  }
}

static void Message_example(void)
{

  mid_MsgQueue = osMessageQueueNew(MSGQUEUE_OBJECTS, sizeof(MSGQUEUE_OBJ_t), NULL);
  if (mid_MsgQueue == NULL)
  {
    printf("Falied to create Message Queue!\n");
  }

  osThreadAttr_t attr;

  attr.attr_bits = 0U;
  attr.cb_mem = NULL;
  attr.cb_size = 0U;
  attr.stack_mem = NULL;
  attr.stack_size = 1024 * 10;
  attr.priority = 25;

  attr.name = "Thread_MsgQueue1";
  if (osThreadNew(Thread_MsgQueue1, NULL, &attr) == NULL)
  {
    printf("Falied to create Thread_MsgQueue1!\n");
  }
  attr.name = "Thread_MsgQueue2";
  if (osThreadNew(Thread_MsgQueue2, NULL, &attr) == NULL)
  {
    printf("Falied to create Thread_MsgQueue2!\n");
  }
}

APP_FEATURE_INIT(Message_example);
