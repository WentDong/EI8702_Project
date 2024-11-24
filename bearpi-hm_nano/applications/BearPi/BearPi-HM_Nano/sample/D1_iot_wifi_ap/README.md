# BearPi-HM_Nano开发板WiFi编程开发——Wifi AP 热点


本示例将演示如何在BearPi-HM_Nano开发板上编写一个创建Wifi热点程序

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## Wifi API分析
本案例主要使用了以下几个API完成Wifi热点创建

依赖文件：

foundation\communication\interfaces\kits\wifi_lite\wifiservice\wifi_device.h
foundation\communication\interfaces\kits\wifi_lite\wifiservice\wifi_hotspot.h
## RegisterWifiEvent()
```c
WifiErrorCode RegisterWifiEvent (WifiEvent * event)
```
 **描述：**
为指定的Wi-Fi事件注册回调函数。当WifiEvent中定义的Wi-Fi事件发生时，将调用已注册的回调函数
**参数：**

|名字|描述|
|:--|:------| 
| event | 表示要注册回调的事件.  |


## EnableHotspot()
```c
WifiErrorCode EnableHotspot (void )
```
**描述：**

启用Wifi热点模式

## SetHotspotConfig()
```c
WifiErrorCode SetHotspotConfig(const HotspotConfig* config)
```
**描述：**

设置指定的热点配置

## IsHotspotActive()
```c
int IsHotspotActive(void);
```
**描述：**
检查AP热点模式是否启用

## GetStationList()
```c
WifiErrorCode GetStationList(StationInfo* result, unsigned int* size)
```
**描述：**

获取连接到该热点的一系列STA

**参数：**

|名字|描述|
|:--|:------| 
| result | 表示连接到该热点的STA列表.  |
| size | 表示连接到该热点的STA数量  |






## 软件设计

**主要代码分析**

完成Wifi热点的扫描需要以下几步

1. 通过 `RegisterWifiEvent` 接口向系统注册热点状态改变事件、STA站点加入事件、STA站点退出事件
    
    * `OnHotspotStateChangedHandler` 用于绑定热点状态改变事件，该回调函数有一个参数 `state` ；

        * state表示是否开启AP模式，取值为0和1，0表示已启用Wifi AP模式，1表示已禁用Wifi AP模式；

    * `OnHotspotStaLeaveHandler` 用于绑定STA站点退出事件,当有STA站点退出，该回调函数会打印出退出站点的MAC地址；
    * `OnHotspotStaJoinHandler` 用于绑定STA站点加入事件，当有新的STA站点加入时，该回调函数会创建 `HotspotStaJoinTask`，在该任务中会调用 `GetStationList` 函数获取当前接入到该AP的所有STA站点信息，并打印出每个STA站点的MAC地址；
2. 调用 `SetHotspotConfig` 接口，设置指定的热点配置；
3. 调用 `EnableHotspot` 接口，使能 Wifi AP 模式；
4. 调用 `IsHotspotActive` 接口，检查AP热点模式是否启用；
5. 调用 `netifapi_netif_set_addr` 函数设置网卡信息；
6. 调用 `netifapi_dhcps_start` 函数启动dhcp服务；
    
```c
static BOOL WifiAPTask(void)
{
    //延时2S便于查看日志
    osDelay(200);

    //注册wifi事件的回调函数
    g_wifiEventHandler.OnHotspotStaJoin = OnHotspotStaJoinHandler;
    g_wifiEventHandler.OnHotspotStaLeave = OnHotspotStaLeaveHandler;
    g_wifiEventHandler.OnHotspotStateChanged = OnHotspotStateChangedHandler;
    error = RegisterWifiEvent(&g_wifiEventHandler);
    if (error != WIFI_SUCCESS)
    {
        printf("RegisterWifiEvent failed, error = %d.\r\n",error);
        return -1;
    }
    printf("RegisterWifiEvent succeed!\r\n");
    //设置指定的热点配置
    HotspotConfig config = {0};

    strcpy(config.ssid, AP_SSID);
    strcpy(config.preSharedKey, AP_PSK);
    config.securityType = WIFI_SEC_TYPE_PSK;
    config.band = HOTSPOT_BAND_TYPE_2G;
    config.channelNum = 7;

    error = SetHotspotConfig(&config);
    if (error != WIFI_SUCCESS)
    {
        printf("SetHotspotConfig failed, error = %d.\r\n", error);
        return -1;
    }
    printf("SetHotspotConfig succeed!\r\n");

    //启动wifi热点模式
    error = EnableHotspot(); 
    if (error != WIFI_SUCCESS)
    {
        printf("EnableHotspot failed, error = %d.\r\n", error);
        return -1;
    }
    printf("EnableHotspot succeed!\r\n");

    //检查热点模式是否使能
    if (IsHotspotActive() == WIFI_HOTSPOT_NOT_ACTIVE)
    {
        printf("Wifi station is not actived.\r\n");
        return -1;
    }
    printf("Wifi station is actived!\r\n");

    //启动dhcp
    g_lwip_netif = netifapi_netif_find("ap0");
    if (g_lwip_netif) 
    {
        ip4_addr_t bp_gw;
        ip4_addr_t bp_ipaddr;
        ip4_addr_t bp_netmask;

        IP4_ADDR(&bp_gw, 192, 168, 1, 1);           /* input your gateway for example: 192.168.1.1 */
        IP4_ADDR(&bp_ipaddr, 192, 168, 1, 1);       /* input your IP for example: 192.168.1.1 */
        IP4_ADDR(&bp_netmask, 255, 255, 255, 0);    /* input your netmask for example: 255.255.255.0 */

        err_t ret = netifapi_netif_set_addr(g_lwip_netif, &bp_ipaddr, &bp_netmask, &bp_gw);
        if(ret != ERR_OK)
        {
            printf("netifapi_netif_set_addr failed, error = %d.\r\n", ret);
            return -1;
        }
        printf("netifapi_netif_set_addr succeed!\r\n");

        ret = netifapi_dhcps_start(g_lwip_netif, 0, 0);
        if(ret != ERR_OK)
        { 
            printf("netifapi_dhcp_start failed, error = %d.\r\n", ret);
            return -1;
        }
        printf("netifapi_dhcps_start succeed!\r\n");

    }

    /****************以下为UDP服务器代码***************/
	//在sock_fd 进行监听
    int sock_fd;
    //服务端地址信息
	struct sockaddr_in server_sock;

    //创建socket
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket is error.\r\n");
		return -1;
	}

	bzero(&server_sock, sizeof(server_sock));
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(8888);

	//调用bind函数绑定socket和地址
	if (bind(sock_fd, (struct sockaddr *)&server_sock, sizeof(struct sockaddr)) == -1)
	{
		perror("bind is error.\r\n");
		return -1;
	}

    int ret;
    char recvBuf[512] = {0};
    //客户端地址信息
    struct sockaddr_in client_addr;
    int size_client_addr= sizeof(struct sockaddr_in);
    while (1)
    {
        
        printf("Waiting to receive data...\r\n");
        memset(recvBuf, 0, sizeof(recvBuf));
        ret = recvfrom(sock_fd, recvBuf, sizeof(recvBuf), 0, (struct sockaddr*)&client_addr,(socklen_t*)&size_client_addr);
        if(ret < 0)
        {
            printf("UDP server receive failed!\r\n");
            return -1;
        }
        printf("receive %d bytes of data from ipaddr = %s, port = %d.\r\n", ret, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("data is %s\r\n",recvBuf);
        ret = sendto(sock_fd, recvBuf, strlen(recvBuf), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
        if (ret < 0)
        {
            printf("UDP server send failed!\r\n");
            return -1;
        }
    }
    /*********************END********************/
}
```

## 编译调试

### 修改 BUILD.gn 文件

修改 `applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `wifi_ap` 参与编译。
```r
"D1_iot_wifi_ap:wifi_ap",
#"D2_iot_wifi_sta_connect:wifi_sta_connect",        
#"D3_iot_udp_client:udp_client",
#"D4_iot_tcp_server:tcp_server",
#"D5_iot_mqtt:iot_mqtt",        
#"D6_iot_cloud_oc:oc_mqtt",
#"D7_iot_cloud_onenet:onenet_mqtt",
```    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，使用手机去连接该热点，会打印出一下信息。
```
RegisterWifiEvent succeed!

SetHotspotConfig succeed!

HotspotStateChanged:state is 1.

EnableHotspot succeed!

Wifi station is actived!

+NOTICE:STA CONNECTED
New Sta Join
HotspotSta[0]: macAddress=EC:5C:68:5B:2D:3D.

netifapi_netif_set_addr succeed!

netifapi_dhcps_start succeed!

Waiting to receive data...
```


