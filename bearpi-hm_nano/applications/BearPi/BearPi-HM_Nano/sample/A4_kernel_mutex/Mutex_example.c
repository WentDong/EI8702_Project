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

osMutexId_t mutex_id;

void HighPrioThread(void)
{
  // wait 1s until start actual work
  osDelay(100U);

  while (1)
  {
    // try to acquire mutex
    osMutexAcquire(mutex_id, osWaitForever);

    printf("HighPrioThread is runing.\r\n");
    osDelay(300U);
    osMutexRelease(mutex_id);
  }
}

void MidPrioThread(void)
{
  // wait 1s until start actual work
  osDelay(100U);

  while (1)
  {
    printf("MidPrioThread is runing.\r\n");
    osDelay(100);
  }
}

void LowPrioThread(void)
{
  while (1)
  {
    osMutexAcquire(mutex_id, osWaitForever);
    printf("LowPrioThread is runing.\r\n");

    // block mutex for 3s
    osDelay(300U);
    osMutexRelease(mutex_id);
  }
}

void Mutex_example(void)
{
  osThreadAttr_t attr;

  attr.attr_bits = 0U;
  attr.cb_mem = NULL;
  attr.cb_size = 0U;
  attr.stack_mem = NULL;
  attr.stack_size = 1024 * 4;

  attr.name = "HighPrioThread";
  attr.priority = 26;
  if (osThreadNew((osThreadFunc_t)HighPrioThread, NULL, &attr) == NULL)
  {
    printf("Falied to create HighPrioThread!\n");
  }
  attr.name = "MidPrioThread";
  attr.priority = 25;
  if (osThreadNew((osThreadFunc_t)MidPrioThread, NULL, &attr) == NULL)
  {
    printf("Falied to create MidPrioThread!\n");
  }
  attr.name = "LowPrioThread";
  attr.priority = 24;
  if (osThreadNew((osThreadFunc_t)LowPrioThread, NULL, &attr) == NULL)
  {
    printf("Falied to create LowPrioThread!\n");
  }
  mutex_id = osMutexNew(NULL);
  if (mutex_id == NULL)
  {
    printf("Falied to create Mutex!\n");
  }
}
APP_FEATURE_INIT(Mutex_example);
