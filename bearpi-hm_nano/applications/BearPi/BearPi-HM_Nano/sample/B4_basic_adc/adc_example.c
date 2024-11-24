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
#include <math.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_errno.h"
#include "wifiiot_adc.h"

#define ADC_TASK_STACK_SIZE 1024 * 8
#define ADC_TASK_PRIO 24

/***** 获取电压值函数 *****/
static float GetVoltage(void)
{
    unsigned int ret;
    unsigned short data;

    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_5, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_DEFAULT, 0xff);
    if (ret != WIFI_IOT_SUCCESS)
    {
        printf("ADC Read Fail\n");
    }

    return (float)data * 1.8 * 4 / 4096.0;
}

static void ADCTask(void)
{
    float voltage;

    //上拉，让按键未按下时GPIO_11保持高电平状态
    IoSetPull(WIFI_IOT_IO_NAME_GPIO_11, WIFI_IOT_IO_PULL_UP);
    while (1)
    {
        printf("=======================================\r\n");
        printf("***************ADC_example*************\r\n");
        printf("=======================================\r\n");

        //获取电压值
        voltage = GetVoltage();
        printf("vlt:%.3fV\n", voltage);

        //延时1s
        usleep(1000000);
    }
}

static void ADCExampleEntry(void)
{
    osThreadAttr_t attr;

    attr.name = "ADCTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = ADC_TASK_STACK_SIZE;
    attr.priority = ADC_TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)ADCTask, NULL, &attr) == NULL)
    {
        printf("[ADCExample] Falied to create ADCTask!\n");
    }
}

APP_FEATURE_INIT(ADCExampleEntry);