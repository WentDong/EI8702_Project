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

#include "lwip/sockets.h"
#include "wifi_connect.h"

#define _PROT_ 8888
#define TCP_BACKLOG 10

//在sock_fd 进行监听，在 new_fd 接收新的链接
int sock_fd, new_fd;

char recvbuf[512];
char *buf = "Hello! I'm BearPi-HM_Nano TCP Server!";

static void TCPServerTask(void)
{
	//服务端地址信息
	struct sockaddr_in server_sock;

	//客户端地址信息
	struct sockaddr_in client_sock;
	int sin_size;

	struct sockaddr_in *cli_addr;

	//连接Wifi
	WifiConnect("TP-LINK_65A8", "0987654321");

	//创建socket
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket is error\r\n");
		exit(1);
	}

	bzero(&server_sock, sizeof(server_sock));
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(_PROT_);

	//调用bind函数绑定socket和地址
	if (bind(sock_fd, (struct sockaddr *)&server_sock, sizeof(struct sockaddr)) == -1)
	{
		perror("bind is error\r\n");
		exit(1);
	}

	//调用listen函数监听(指定port监听)
	if (listen(sock_fd, TCP_BACKLOG) == -1)
	{
		perror("listen is error\r\n");
		exit(1);
	}

	printf("start accept\n");

	//调用accept函数从队列中
	while (1)
	{
		sin_size = sizeof(struct sockaddr_in);

		if ((new_fd = accept(sock_fd, (struct sockaddr *)&client_sock, (socklen_t *)&sin_size)) == -1)
		{
			perror("accept");
			continue;
		}

		cli_addr = malloc(sizeof(struct sockaddr));

		printf("accept addr\r\n");

		if (cli_addr != NULL)
		{
			memcpy(cli_addr, &client_sock, sizeof(struct sockaddr));
		}

		//处理目标
		ssize_t ret;

		while (1)
		{
			if ((ret = recv(new_fd, recvbuf, sizeof(recvbuf), 0)) == -1)
			{
				printf("recv error \r\n");
			}
			printf("recv :%s\r\n", recvbuf);
			sleep(2);
			if ((ret = send(new_fd, buf, strlen(buf) + 1, 0)) == -1)
			{
				perror("send : ");
			}

			sleep(2);
		}

		close(new_fd);
	}
}

static void TCPServerDemo(void)
{
	osThreadAttr_t attr;

	attr.name = "TCPServerTask";
	attr.attr_bits = 0U;
	attr.cb_mem = NULL;
	attr.cb_size = 0U;
	attr.stack_mem = NULL;
	attr.stack_size = 10240;
	attr.priority = osPriorityNormal;

	if (osThreadNew((osThreadFunc_t)TCPServerTask, NULL, &attr) == NULL)
	{
		printf("[TCPServerDemo] Falied to create TCPServerTask!\n");
	}
}

APP_FEATURE_INIT(TCPServerDemo);
