# BearPi-HM_Nano开发板WiFi编程开发——Wifi连接热点


本示例将演示如何在BearPi-HM_Nano开发板上编写一个Wifi连接热点业务程序

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## Wifi API分析
本案例主要使用了以下几个API完成Wifi联网
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


## EnableWifi()
```c
WifiErrorCode EnableWifi (void )
```
**描述：**

启用STA模式

## AddDeviceConfig()
```c
WifiErrorCode AddDeviceConfig (const WifiDeviceConfig * config, int * result )
```
**描述：**

添加用于配置连接到热点信息，此函数生成一个networkId

**参数：**

|名字|描述|
|:--|:------| 
| config | 表示要连接的热点信息.  |
| result | 表示生成的networkId。每个networkId匹配一个热点配置  |

## ConnectTo()
```c
WifiErrorCode ConnectTo (int networkId)
```
**描述：**

连接到指定networkId的热点

**参数：**

|名字|描述|
|:--|:------| 
| networkId | 表示与目标热点匹配的网络id.  |




## netifapi_netif_find()
```c
struct netif *netifapi_netif_find(const char *name);
```
**描述：**

获取netif用于IP操作

## dhcp_start()

```c
err_t dhcp_start(n)
```

**描述：**

启动DHCP, 获取IP


## 软件设计

**主要代码分析**

完成Wifi热点的连接需要以下几步

1. 通过 `RegisterWifiEvent` 接口向系统注册扫描状态监听函数，用于接收扫描状态通知，如扫描动作是否完成等
    
* `OnWifiConnectionChangedHandler` 用于绑定连接状态监听函数，该回调函数有两个参数 `state` 和 `info` ；

    * state表示扫描状态，取值为0和1，1表示热点连接成功；

    * info表示Wi-Fi连接信息，包含以下参数；


        |名字|描述|
        |:--|:------| 
        | ssid [WIFI_MAX_SSID_LEN] | 连接的热点名称.  |
        | bssid [WIFI_MAC_LEN] | MAC地址.  |
        | rssi | 接收信号强度(RSSI).  |
        | connState | Wifi连接状态.  |
        | disconnectedReason | Wi-Fi断开的原因.  |




2. 调用 `EnableWifi` 接口，使能 Wifi。
3. 调用 `AddDeviceConfig` 接口，配置连接的热点信息。
4. 调用 `ConnectTo` 接口，连接到指定networkId的热点。
5. 调用 `WaitConnectResult` 接口等待，该函数中会有15s的时间去轮询连接成功标志位 `g_ConnectSuccess`，当`g_ConnectSuccess` 为 1 时退出等待。
6. 调用 `netifapi_netif_find` 接口，获取 netif 用于 IP 操作
7. 调用 `dhcp_start` 接口，启动 DHCP, 获取 IP

```c
static BOOL WifiSTATask(void)
{
    WifiScanInfo *info = NULL;
    unsigned int size = WIFI_SCAN_HOTSPOT_LIMIT;
    static struct netif *g_lwip_netif = NULL;
    WifiDeviceConfig select_ap_config = {0};

    osDelay(200);
    printf("<--System Init-->\r\n");

    //初始化WIFI
    WiFiInit();

    //使能WIFI
    if (EnableWifi() != WIFI_SUCCESS)
    {
        printf("EnableWifi failed, error = %d\r\n", error);
        return -1;
    }

    //判断WIFI是否激活
    if (IsWifiActive() == 0)
    {
        printf("Wifi station is not actived.\r\n");
        return -1;
    }

    //分配空间，保存WiFi信息
    info = malloc(sizeof(WifiScanInfo) * WIFI_SCAN_HOTSPOT_LIMIT);
    if (info == NULL)
    {
        return -1;
    }

    //轮询查找WiFi列表
    do{
        //重置标志位
        ssid_count = 0;
        g_staScanSuccess = 0;

        //开始扫描
        Scan();

        //等待扫描结果
        WaitSacnResult();

        //获取扫描列表
        error = GetScanInfoList(info, &size);

    }while(g_staScanSuccess != 1);

    //打印WiFi列表
    printf("********************\r\n");
    for(uint8_t i = 0; i < ssid_count; i++)
    {
        printf("no:%03d, ssid:%-30s, rssi:%5d\r\n", i+1, info[i].ssid, info[i].rssi/100);
    }
    printf("********************\r\n");

    
    //连接指定的WiFi热点
    for(uint8_t i = 0; i < ssid_count; i++)
    {
        if (strcmp(SELECT_WIFI_SSID, info[i].ssid) == 0)
        {
            int result;

            printf("Select:%3d wireless, Waiting...\r\n", i+1);

            //拷贝要连接的热点信息
            strcpy(select_ap_config.ssid, info[i].ssid);
            strcpy(select_ap_config.preSharedKey, SELECT_WIFI_PASSWORD);
            select_ap_config.securityType = SELECT_WIFI_SECURITYTYPE;

            if (AddDeviceConfig(&select_ap_config, &result) == WIFI_SUCCESS)
            {
                if (ConnectTo(result) == WIFI_SUCCESS && WaitConnectResult() == 1)
                {
                    printf("WiFi connect succeed!\r\n");
                    g_lwip_netif = netifapi_netif_find(SELECT_WLAN_PORT);
                    break;
                }
            }
        }

        if(i == ssid_count-1)
        {
            printf("ERROR: No wifi as expected\r\n");
            while(1) osDelay(100);
        }
    }

    //启动DHCP
    if (g_lwip_netif)
    {
        dhcp_start(g_lwip_netif);
        printf("begain to dhcp\r\n");
    }


    //等待DHCP
    for(;;)
    {
        if(dhcp_is_bound(g_lwip_netif) == ERR_OK)
        {
            printf("<-- DHCP state:OK -->\r\n");

            //打印获取到的IP信息
            netifapi_netif_common(g_lwip_netif, dhcp_clients_info_show, NULL);
            break;
        }

        printf("<-- DHCP state:Inprogress -->\r\n");
        osDelay(100);
    }

    //执行其他操作
    for(;;)
    {
        osDelay(100);
    }

}
```

## 编译调试
### 修改对接热点的账号密码
修改`wifi_sta_connect.c`第51行和52行的热点账号密码
```c
#define SELECT_WIFI_SSID "BearPi"
#define SELECT_WIFI_PASSWORD "0987654321"
```
### 修改 BUILD.gn 文件

修改 `applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `wifi_sta_connect` 参与编译。
```r
#"D1_iot_wifi_sta:wifi_sta",
"D2_iot_wifi_sta_connect:wifi_sta_connect",        
#"D3_iot_udp_client:udp_client",
#"D4_iot_tcp_server:tcp_server",
#"D5_iot_mqtt:iot_mqtt",        
#"D6_iot_cloud_oc:oc_mqtt",
#"D7_iot_cloud_onenet:onenet_mqtt",
```  
    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，会打印连接到的Wifi热点信息。
```
<--System Init-->

<--Wifi Init-->

register wifi event succeed!

+NOTICE:SCANFINISH
WaitSacnResult:wait success[1]s


Select:  2 wireless, Waiting...

+NOTICE:CONNECTED
callback function for wifi connect

WaitConnectResult:wait success[1]s
WiFi connect succeed!

begain to dhcp

<-- DHCP state:Inprogress -->

<-- DHCP state:OK -->

server :
	server_id : 192.168.0.1
	mask : 255.255.255.0, 1
	gw : 192.168.0.1
	T0 : 7200
	T1 : 3600
	T2 : 6300
clients <1> :
	mac_idx mac             addr            state   lease   tries   rto     
	0       801131801388    192.168.0.151   10      0       1       4       

```

