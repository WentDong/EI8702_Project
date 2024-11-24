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
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"

#include "onenet.h"
#include "wifi_connect.h"
#include "E53_IA1.h"

#define ONENET_INFO_PROID "383575"
#define ONENET_MASTER_APIKEY "GNQeLPioqBVpndus2KABmdOVZZI="

#define ONENET_INFO_DEVID "648900765"
#define ONENET_INFO_AUTH "2020123456789"
#define ONENET_INFO_APIKEY "JHr7UCOXy2tbHkHqWTSwIlU3NzQ="

#define Wifi_SSID "TP-LINK_65A8"
#define Wifi_PASSWORD "0987654321"

//extern int rand(void);
E53_IA1_Data_TypeDef E53_IA1_Data;

void onenet_cmd_rsp_cb(uint8_t *recv_data, size_t recv_size, uint8_t **resp_data, size_t *resp_size)
{

    printf("recv data is %.*s\n", recv_size, recv_data);

    *resp_data = NULL;
    *resp_size = 0;
}

void MQTT_Report_Task(void)
{

    WifiConnect(Wifi_SSID, Wifi_PASSWORD);
    device_info_init(ONENET_INFO_DEVID, ONENET_INFO_PROID, ONENET_INFO_AUTH, ONENET_INFO_APIKEY, ONENET_MASTER_APIKEY);
    onenet_mqtt_init();
    onenet_set_cmd_rsp_cb(onenet_cmd_rsp_cb);
    while (1)
    {

        onenet_mqtt_upload_digit("Temperature", (int)E53_IA1_Data.Temperature);
        onenet_mqtt_upload_digit("Humidity", (int)E53_IA1_Data.Humidity);
        onenet_mqtt_upload_digit("Luminance", (int)E53_IA1_Data.Lux);

        sleep(1);
    }
}
static void Sensor_Read_Task(void)
{
    E53_IA1_Init();

    while (1)
    {
        printf("\r\n=======================================\r\n");
        printf("\r\n***********IoT_OneNET_example**********\r\n");
        printf("\r\n=======================================\r\n");

        E53_IA1_Read_Data();

        printf("\r\n******************************Lux Value is  %.2f\r\n", E53_IA1_Data.Lux);
        printf("\r\n******************************Humidity is  %.2f\r\n", E53_IA1_Data.Humidity);
        printf("\r\n******************************Temperature is  %.2f\r\n", E53_IA1_Data.Temperature);

        sleep(2);
    }
}
static void MQTT_Demo(void)
{
    osThreadAttr_t attr;

    attr.name = "MQTT_Report_Task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = osPriorityNormal;

    if (osThreadNew((osThreadFunc_t)MQTT_Report_Task, NULL, &attr) == NULL)
    {
        printf("Falied to create MQTT_Report_Task!\n");
    }

    attr.name = "Sensor_Read_Task";
    if (osThreadNew((osThreadFunc_t)Sensor_Read_Task, NULL, &attr) == NULL)
    {
        printf("Falied to create Sensor_Read_Task!\n");
    }
}

APP_FEATURE_INIT(MQTT_Demo);