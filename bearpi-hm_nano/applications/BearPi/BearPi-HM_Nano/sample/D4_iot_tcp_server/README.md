# BearPi-HM_Nano开发板WiFi编程开发——TCP服务器
本示例将演示如何在BearPi-HM_Nano开发板上使用socket编程创建TCP服务端，接收客户端消息并回复固定消息。

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## socket API分析
本案例主要使用了以下几个API完socket编程实验
## socket()

```c
sock_fd = socket(AF_INET, SOCK_STREAM, 0)) //AF_INT:ipv4, SOCK_STREAM:tcp协议
```
**描述：**

在网络编程中所需要进行的第一件事情就是创建一个socket，无论是客户端还是服务器端，都需要创建一个socket，该函数返回socket文件描述符，类似于文件描述符。socket是一个结构体，被创建在内核中。
## bind()
```c
bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))
```
**描述：**

把一个本地协议地址和套接口绑定，比如把本机的2222端口绑定到套接口。注意：为什么在[使用 Socket 实现 UDP 客户端](/applications/BearPi/BearPi-HM_Nano/sample/D3_iot_udp_client/README.md)教程中的客户端不需要调用bind函数？这是因为如果没有调用bind函数绑定一个端口的话，当调用connect函数时，内核会为该套接口临时选定一个端口，因此可以不用绑定。而服务器之所以需要绑定的原因就是，所以客户端都需要知道服务器使用的哪个端口，所以需要提前绑定


## listen()
```c
int listen(int s, int backlog)
```
**描述：**

当socket创建后，它通常被默认为是主动套接口，也就是说是默认为要马上调用connect函数的，而作为服务器是需要被动接受的，所以需要调用linsten函数将主动套接口转换成被动套接口。调用linsten函数后，内核将从该套接口接收连接请求。



## accept()
```c
int accept(s, addr, addrlen)    
```
**描述：**

此函数返回已经握手完成的连接的套接口。注意：此处的套接口不同于服务器开始创建的监听套接口，此套接口是已经完成连接的套接口，监听套接口只是用来监听。

## recv()
```c
int recv( SOCKET s, char *buf, int  len, int flags)   
```
**描述：**

recv函数用来从TCP连接的另一端接收数据

## send()
```c
int send( SOCKET s,char *buf,int len,int flags )
```
**描述：**
send函数用来向TCP连接的另一端发送数据。




## 软件设计

**主要代码分析**

完成Wifi热点的连接后还需要以下几步

1. 通过 `socket` 接口创建一个socket,`AF_INT`表示ipv4,`SOCK_STREAM`表示使用tcp协议
2. 调用 `bind` 接口绑定socket和地址。
3. 调用 `listen` 接口监听(指定port监听),通知操作系统区接受来自客户端链接请求,第二个参数：指定队列长度
4. 调用`accept`接口从队列中获得一个客户端的请求链接
5. 调用 `recv` 接口接收客户端发来的数据
6. 调用 `send` 接口向客户端回复固定的数据

```c
static void TCPServerTask(void)
{
	/* 服务端地址信息 */
	struct sockaddr_in server_sock;
	/* 客户端地址信息 */
	struct sockaddr_in client_sock;
	int sin_size;

	struct sockaddr_in *cli_addr;
    /* 连接Wifi */
    WifiConnect("TP-LINK_65A8","0987654321");


    /**
    * 1.创建socket
    * AF_INET:ipv4
    * SOCK_STRAM:tcp协议
    */
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket is error\r\n");
		exit(1);
	}

	bzero(&server_sock,sizeof(server_sock));
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(_PROT_);

	/*2.调用bind函数绑定socket和地址*/
	if(bind(sock_fd, (struct sockaddr *)&server_sock, sizeof(struct sockaddr)) == -1)
	{
		perror("bind is error\r\n");
		exit(1);
	}

	/**
 	* 3:调用listen函数监听(指定port监听)
	* 通知操作系统区接受来自客户端链接请求
	* 第二个参数：指定队列长度
	*/
	if(listen(sock_fd, TCP_BACKLOG) == -1)
	{
		perror("listen is error\r\n");
		exit(1);
	}

	printf("start accept\n");

    /**
    * 4：调用accept函数从队列中
    * 获得一个客户端的请求链接
    */
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);

		if((new_fd = accept(sock_fd, (struct sockaddr *)&client_sock, (socklen_t *)&sin_size)) == -1)
		{
			perror("accept");
			continue;
		}

		cli_addr = malloc(sizeof(struct sockaddr));

		printf("accept addr\r\n");

		if(cli_addr != NULL)
		{
			memcpy(cli_addr, &client_sock, sizeof(struct sockaddr));
		}

		//处理目标
		ssize_t ret;		

		while(1)
		{
			if((ret = recv(new_fd, recvbuf, sizeof(recvbuf), 0)) == -1)
			{
				printf("recv error \r\n");				
			}
			printf("recv :%s\r\n",recvbuf);
			sleep(2);
			if((ret = send(new_fd, buf, strlen(buf) + 1, 0)) == -1)
			{
				perror("send : ");
			}

			sleep(2);
		}	

		close(new_fd);

	}
}
```

## 编译调试

### 修改 BUILD.gn 文件

修改 `applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `tcp_server` 参与编译。
```r
#"D1_iot_wifi_sta:wifi_sta",
#"D2_iot_wifi_sta_connect:wifi_sta_connect",      
#"D3_iot_udp_client:udp_client",
"D4_iot_tcp_server:tcp_server",
#"D5_iot_mqtt:iot_mqtt",        
#"D6_iot_cloud_oc:oc_mqtt",
#"D7_iot_cloud_onenet:onenet_mqtt",
```   


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，会打印模块的本地IP，如本例程中的 `192.1668.0.164` ,并开始准备获取客户端的请求链接
```
g_connected: 1
netifapi_dhcp_start: 0
server :
        server_id : 192.168.0.1
        mask : 255.255.255.0, 1
        gw : 192.168.0.1
        T0 : 7200
        T1 : 3600
        T2 : 6300
clients <1> :
        mac_idx mac             addr            state   lease   tries   rto     
        0       181131a48f7a    192.168.0.164   10      0       1       2       
netifapi_netif_common: 0
start accept
```
使用 Socket tool 创建客户端用于测试。

![创建TCP_Clien](/applications/BearPi/BearPi-HM_Nano/docs/figures/D4_iot_tcp_server/创建TCP_Clien.png)

在创建客户端后点击“连接”，在数据发送窗口输入要发送的数据，点击发送后服务端会回复固定消息，且开发板收到消息后会通过日志打印出来。

```
start accept
accept addr
recv :Hello! BearPi-HM_nano TCP Server!
```

![TCP发送数据](/applications/BearPi/BearPi-HM_Nano/docs/figures/D4_iot_tcp_server/TCP发送数据.png)