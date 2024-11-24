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

#include "wifi_device.h"
#include "lwip/netifapi.h"
#include "lwip/api_shell.h"
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include "lwip/sockets.h"
#include "wifi_connect.h"

#define _PROT_ 8888

//在sock_fd 进行监听，在 new_fd 接收新的链接
int sock_fd;

int addr_length;
static const char *send_data = "Hello! I'm BearPi-HM_Nano UDP Client!\r\n";

static void UDPClientTask(void)
{
    //服务器的地址信息
    struct sockaddr_in send_addr;
    socklen_t addr_length = sizeof(send_addr);
    char recvBuf[512];

    //连接Wifi
    WifiConnect("TP-LINK_65A8", "0987654321");

    //创建socket
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("create socket failed!\r\n");
        exit(1);
    }

    //初始化预连接的服务端地址
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(_PROT_);
    send_addr.sin_addr.s_addr = inet_addr("192.168.0.175");
    addr_length = sizeof(send_addr);

    //总计发送 count 次数据
    while (1)
    {
        bzero(recvBuf, sizeof(recvBuf));

        //发送数据到服务远端
        sendto(sock_fd, send_data, strlen(send_data), 0, (struct sockaddr *)&send_addr, addr_length);

        //线程休眠一段时间
        sleep(10);

        //接收服务端返回的字符串
        recvfrom(sock_fd, recvBuf, sizeof(recvBuf), 0, (struct sockaddr *)&send_addr, &addr_length);
        printf("%s:%d=>%s\n", inet_ntoa(send_addr.sin_addr), ntohs(send_addr.sin_port), recvBuf);
    }

    //关闭这个 socket
    closesocket(sock_fd);
}

static void UDPClientDemo(void)
{
    osThreadAttr_t attr;

    attr.name = "UDPClientTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = osPriorityNormal;

    if (osThreadNew((osThreadFunc_t)UDPClientTask, NULL, &attr) == NULL)
    {
        printf("[UDPClientDemo] Falied to create UDPClientTask!\n");
    }
}

APP_FEATURE_INIT(UDPClientDemo);
