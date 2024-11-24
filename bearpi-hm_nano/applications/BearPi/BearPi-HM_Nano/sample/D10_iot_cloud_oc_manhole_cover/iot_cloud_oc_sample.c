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
#include <stdlib.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"

#include "wifi_connect.h"
#include <queue.h>
#include <oc_mqtt_al.h>
#include <oc_mqtt_profile.h>
#include "E53_SC2.h"
#include <dtls_al.h>
#include <mqtt_al.h>

#define CONFIG_WIFI_SSID          "BearPi"                            //修改为自己的WiFi 热点账号

#define CONFIG_WIFI_PWD           "0987654321"                        //修改为自己的WiFi 热点密码

// #define CONFIG_APP_SERVERIP       "121.36.42.100"                       //基础版平台对接地址

#define CONFIG_APP_SERVERIP       "117.78.5.125"                       //标准版平台对接地址

#define CONFIG_APP_SERVERPORT     "1883"

#define CONFIG_APP_DEVICEID       "601ceda104feea02d7069720_2143565789"       //替换为注册设备后生成的deviceid

#define CONFIG_APP_DEVICEPWD      "123456789"                                   //替换为注册设备后生成的密钥

#define CONFIG_APP_LIFETIME       60     ///< seconds

#define CONFIG_QUEUE_TIMEOUT      (5*1000)

#define MSGQUEUE_OBJECTS 16 // number of Message Queue Objects

typedef enum
{
    en_msg_cmd = 0,
    en_msg_report,
}en_msg_type_t;

typedef struct
{
    char *request_id;
    char *payload;
} cmd_t;


typedef struct
{
    int temp;
    int acce_x;
    int acce_y;
    int acce_z;
} report_t;

typedef struct
{
    en_msg_type_t msg_type;
    union
    {
        report_t report;
    } msg;
} app_msg_t;

typedef struct
{
    queue_t                     *app_msg;
    int                          connected;

}app_cb_t;
static app_cb_t  g_app_cb;

int X = 0,Y = 0,Z = 0, Cover_Status = 0;
E53_SC2_Data_TypeDef E53_SC2_Data;


static void deal_report_msg(report_t *report)
{
    oc_mqtt_profile_service_t service;
    oc_mqtt_profile_kv_t temperature;
    oc_mqtt_profile_kv_t Accel_x;
    oc_mqtt_profile_kv_t Accel_y;
    oc_mqtt_profile_kv_t Accel_z;
    oc_mqtt_profile_kv_t status;

    if(g_app_cb.connected != 1){
        return;
    }

    service.event_time = NULL;
    service.service_id = "Manhole_Cover";
    service.service_property = &temperature;
    service.nxt = NULL;
    
    temperature.key = "Temperature";
    temperature.value = &report->temp;
    temperature.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    temperature.nxt = &Accel_x;

    Accel_x.key = "Accel_x";
    Accel_x.value = &report->acce_x;
    Accel_x.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    Accel_x.nxt = &Accel_y;

    Accel_y.key = "Accel_y";
    Accel_y.value = &report->acce_y;
    Accel_y.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    Accel_y.nxt = &Accel_z;

    Accel_z.key = "Accel_z";
    Accel_z.value = &report->acce_z;
    Accel_z.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    Accel_z.nxt = &status;

    status.key = "Cover_Status";
    status.value = Cover_Status ? "Tilt" : "Level";
    status.type = EN_OC_MQTT_PROFILE_VALUE_STRING;
    status.nxt = NULL;

    oc_mqtt_profile_propertyreport(NULL,&service);
    return;
}

static int task_main_entry(void)
{
    app_msg_t *app_msg;
    uint32_t ret ;
    
    WifiConnect(CONFIG_WIFI_SSID, CONFIG_WIFI_PWD);
    dtls_al_init();
    mqtt_al_init();
    oc_mqtt_init();
    
    g_app_cb.app_msg = queue_create("queue_rcvmsg",10,1);
    if(NULL ==  g_app_cb.app_msg){
        printf("Create receive msg queue failed");
        
    }
    oc_mqtt_profile_connect_t  connect_para;
    (void) memset( &connect_para, 0, sizeof(connect_para));

    connect_para.boostrap =      0;
    connect_para.device_id =     CONFIG_APP_DEVICEID;
    connect_para.device_passwd = CONFIG_APP_DEVICEPWD;
    connect_para.server_addr =   CONFIG_APP_SERVERIP;
    connect_para.server_port =   CONFIG_APP_SERVERPORT;
    connect_para.life_time =     CONFIG_APP_LIFETIME;
    connect_para.rcvfunc =       NULL;
    connect_para.security.type = EN_DTLS_AL_SECURITY_TYPE_NONE;
    ret = oc_mqtt_profile_connect(&connect_para);
    if((ret == (int)en_oc_mqtt_err_ok)){
        g_app_cb.connected = 1;
        printf("oc_mqtt_profile_connect succed!\r\n");
    }
    else
    {
        printf("oc_mqtt_profile_connect faild!\r\n");
    }
    

    while (1)
    {
        app_msg = NULL;
        (void)queue_pop(g_app_cb.app_msg,(void **)&app_msg,0xFFFFFFFF);
        if (NULL != app_msg)
        {
            switch (app_msg->msg_type)
            {
            case en_msg_report:
                deal_report_msg(&app_msg->msg.report);
                break;
            default:
                break;
            }
            free(app_msg);
        }
    }
    return 0;
}


static int task_sensor_entry(void)
{
    app_msg_t *app_msg;
    float Lux;
    E53_SC2_Init();
    while (1)
    {
        E53_SC2_Read_Data();
        printf("\r\n******************************Temperature      is  %d\r\n", (int)E53_SC2_Data.Temperature);
        printf("\r\n******************************Accel[0]         is  %d\r\n", (int)E53_SC2_Data.Accel[0]);
        printf("\r\n******************************Accel[1]         is  %d\r\n", (int)E53_SC2_Data.Accel[1]);
        printf("\r\n******************************Accel[2]         is  %d\r\n", (int)E53_SC2_Data.Accel[2]);
        if( X == 0 && Y == 0 && Z == 0)
        {
            X = (int)E53_SC2_Data.Accel[0];
            Y = (int)E53_SC2_Data.Accel[1];
            Z = (int)E53_SC2_Data.Accel[2];
        }
        else
        {
            if(X+100<E53_SC2_Data.Accel[0]||X-100>E53_SC2_Data.Accel[0]||Y+100<E53_SC2_Data.Accel[1]||Y-100>E53_SC2_Data.Accel[1]||Z+100<E53_SC2_Data.Accel[2]||Z-100>E53_SC2_Data.Accel[2])
            {
                LED_D1_StatusSet(OFF);
                LED_D2_StatusSet(ON);
                Cover_Status = 1;
            }
            else
            {
                LED_D1_StatusSet(ON);
                LED_D2_StatusSet(OFF);
                Cover_Status = 0;
            }
        }

        app_msg = malloc(sizeof(app_msg_t));       

        if (NULL != app_msg)
        {
            app_msg->msg_type = en_msg_report;
            app_msg->msg.report.temp = (int)E53_SC2_Data.Temperature;
            app_msg->msg.report.acce_x = (int)E53_SC2_Data.Accel[0];
            app_msg->msg.report.acce_y = (int)E53_SC2_Data.Accel[1];
            app_msg->msg.report.acce_z = (int)E53_SC2_Data.Accel[2];

            if(0 != queue_push(g_app_cb.app_msg,app_msg,CONFIG_QUEUE_TIMEOUT)){
                free(app_msg);
            }
        }
        sleep(3);
    }
    return 0;
}

static void OC_Demo(void)
{
    osThreadAttr_t attr;

    attr.name = "task_main_entry";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = 24;

    if (osThreadNew((osThreadFunc_t)task_main_entry, NULL, &attr) == NULL)
    {
        printf("Falied to create task_main_entry!\n");
    }
    attr.stack_size = 4096;
    attr.priority = 25;
    attr.name = "task_sensor_entry";
    if (osThreadNew((osThreadFunc_t)task_sensor_entry, NULL, &attr) == NULL)
    {
        printf("Falied to create task_sensor_entry!\n");
    }
}

APP_FEATURE_INIT(OC_Demo);