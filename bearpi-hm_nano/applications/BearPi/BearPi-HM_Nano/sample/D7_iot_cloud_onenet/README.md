# BearPi-HM_Nano开发板WiFi编程开发——MQTT连接OneNet
本示例将演示如何在BearPi-HM_Nano开发板上使用MQTT协议连接OneNet，使用的是E53_IA1 智慧农业扩展板与 BearPi-HM_Nano 开发板。

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/E53_IA1安装.png "E53_IA1安装")
# OneNET API

## 初始化

### OneNET 初始化

> int onenet_mqtt_init(void);

OneNET 初始化函数，需要在使用 OneNET 功能前调用。

| **参数**  | **描述**  |
| :-----   | :-----    |
|无         | 无       |
| **返回**  | **描述**  |
|0         | 成功                |
|-1        | 获得设备信息失败      |
|-2        | mqtt 客户端初始化失败 |

### 设置命令响应函数

> void onenet_set_cmd_rsp_cb(void(*cmd_rsp_cb)(uint8_t *recv_data, size_t recv_size, uint8_t **resp_data, size_t *resp_size));

设置命令响应回调函数。

| **参数**    | **描述**    |
| :-----	 | :-----  	   |
|recv_data   | 接收到的数据  |
|recv_size   | 数据的长度    |
|resp_data   | 响应数据      |
|resp_size   | 响应数据的长度 |
| **返回**    | **描述**     |
|无           | 无          |

## 数据上传

### mqtt 上传数据到指定主题

> int onenet_mqtt_publish(const char *topic, const uint8_t *msg, size_t len);

利用 mqtt 向指定 topic 发送消息。

| **参数**  | **描述**    	|
| :-----   | :-----  	  |
|topic     | 主题       	|
|msg       | 要上传的数据   |
|len       | 数据长度      |
| **返回**  | **描述**     |
|0         | 上传成功 	   |
|-1        | 上传失败 	   |

### mqtt 上传字符串到 OneNET

> int onenet_mqtt_upload_string(const char *ds_name, const char *str);

利用 mqtt 向 OneNET 平台发送字符串数据。

| **参数**   | **描述**    	|
| :-----   	| :-----  	   |
|ds_name    | 数据流名称    |
|str        | 要上传的字符串 |
| **返回**   | **描述**  	|
|0       	| 上传成功 		|
|-5      	| 内存不足 		|

### mqtt 上传数字到 OneNET

> int onenet_mqtt_upload_digit(const char *ds_name, const double digit);

利用 mqtt 向 OneNET 平台发送数字数据。

| **参数**   | **描述**    |
| :-----   	| :-----  	  |
|ds_name    | 数据流名称   |
|digit      | 要上传的数字  |
| **返回**   | **描述**    |
|0       	| 上传成功 	   |
|-5      	| 内存不足 	   |

### mqtt 上传二进制文件到 OneNET

> int onenet_mqtt_upload_bin(const char *ds_name, const uint8_t *bin, size_t len);

利用 mqtt 向 OneNET 平台发送二进制文件。会动态申请内存来保存二进制文件，使用前请确保有足够的内存。

| **参数**   | **描述**     |
| :-----   	| :-----  	  |
|ds_name    | 数据流名称    |
|bin		| 二进制文件	   |
|len		| 二进制文件大小 |
| **返回**   | **描述**     |
|0       	| 上传成功      |
|-1      	| 上传失败      |

### mqtt 通过路径上传二进制文件到 OneNET

> int onenet_mqtt_upload_bin_by_path(const char *ds_name, const char *bin_path);

利用 mqtt 向 OneNET 平台发送二进制文件。

| **参数**   | **描述**     |
| :-----   	| :-----  	  |
|ds_name    | 数据流名称    |
|bin_path   | 二进制文件路径 |
| **返回**   | **描述**     |
|0       	| 上传成功      |
|-1      	| 上传失败      |



## 软件设计



### OneNET 初始化

在 ENV 里面已经配置好了连接云平台需要的各种信息，直接调用`onenet_mqtt_init`函数进行初始化即可，设备会自动连接 OneNET 平台。

### 推送数据

当需要上传数据时，可以按照数据类型选择对应的 API 来上传数据。代码示例如下： 

```c
char str[] = { "hello world" };

/* 获得温度值 */
temp = get_temperature_value();
/* 将温度值上传到 temperature 数据流 */
onenet_mqtt_upload_digit("temperature",temp);

/* 将hello world上传到 string 数据流 */
onenet_mqtt_upload_string("string",str);
```

除了支持上传数字和字符串外，软件包还支持上传二进制文件。

可以通过`onenet_mqtt_upload_bin`或`onenet_mqtt_upload_bin_by_path`来上传二进制文件。代码示例如下

```c
uint8_t buf[] = {0x01, 0x02, 0x03};

/* 将根目录下的1.bin文件上传到 bin 数据流 */
onenet_mqtt_upload_bin_by_path("bin", "/1.bin");
/* 将 buf 中的数据上传到 bin 数据流 */
onenet_mqtt_upload_bin(("bin", buf, 3);
```


### 命令接收

OneNET 支持下发命令，命令是用户自定义的。用户需要自己实现命令响应回调函数，然后利用`onenet_set_cmd_rsp_cb`将回调函数装载上。当设备收到平台下发的命令后，会调用用户实现的命令响应回调函数，等待回调函数执行完成后，将回调函数返回的响应内容再发给云平台。保存响应的内存必须是动态申请出来的，在发送完响应后，程序会自动释放申请的内存。代码示例如下： 

```c
static void onenet_cmd_rsp_cb(uint8_t *recv_data, size_t recv_size,uint8_t **resp_data,
size_t *resp_size)
{
  /* 申请内存 */

  /* 解析命令 */
  
  /* 执行动作 */
  
  /* 返回响应 */
  
}

int main()
{
    /* 用户代码 */
	
    onenet_mqtt_init();

    onenet_set_cmd_rsp_cb(onenet_cmd_rsp_cb);
    
    /* 用户代码 */
   
}
```

### 信息获取

#### 数据流信息获取

用户可以通过`onenet_http_get_datastream`来获取数据流的信息，包括数据流 id，数据流最后更新时间，数据流单位，数据流当前值等等，获取的数据流信息会保存在传入的 datastream 结构体指针所指向的结构体中。代码示例如下

```{.c}
struct rt_onenet_ds_info ds_temp;

/* 获取到 temperature 数据流的信息后保存到 ds_temp 结构体中 */
onenet_http_get_datastream("temperature",ds_temp);
```

#### 数据点信息获取

数据点信息可以通过以下 3 个 API 来获取

> cJSON *onenet_get_dp_by_limit(char *ds_name, size_t limit);
> 
> cJSON *onenet_get_dp_by_start_end(char *ds_name, uint32_t start, uint32_t end, size_t limit);
> 
> cJSON *onenet_get_dp_by_start_duration(char *ds_name, uint32_t start, size_t duration, size_t limit);

这三个 API 返回的都是 cJSON 格式的数据点信息，区别只是查询的方法不一样，下面通过示例来讲解如何使用这 3 个 API。

```{.c}
/* 获取 temperature 数据流的最后10个数据点信息 */
dp = onenet_get_dp_by_limit("temperature",10);

/* 获取 temperature 数据流2018年7月19日14点50分0秒到2018年7月19日14点55分20秒的前10个
数据点信息 */
/* 第二、三个参数是Unix时间戳 */
dp = onenet_get_dp_by_start_end("temperature",1531983000，1531983320，10);

/* 获取 temperature 数据流2018年7月19日14点50分0秒往后50秒内的前10个数据点信息 */
/* 第二个参数是Unix时间戳 */
dp = onenet_get_dp_by_start_end("temperature",1531983000，50，10);
```

## 注意事项

- 设置命令响应回调函数之前必须要先调用`onenet_mqtt_init`函数，在初始化函数里会将回调函数指向NULL。
- 命令响应回调函数里存放响应内容的 buffer 必须是 malloc 出来的，在发送完响应内容后，程序会将这个 buffer 释放掉。

## 编译调试


### 登录

设备接入 OneNET 云之前，需要在平台注册用户账号，OneNET 云平台地址：<https://open.iot.10086.cn>

通过左边栏产品导航进入 **多协议接入**

![onenet](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/多协议接入.png)

### 创建产品

点击右上角的 添加产品，在弹出页面中按照提示填写产品的基本信息，进行产品创建；请您按照提示尽可能完整、全面地填写相应内容，这样更方便您后期对产品进行管理接入协议选择 `MQTT` 协议，如下图所示：

![onenet](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/添加产品.png)

![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/产品配置.png)



#### 创建设备

点击产品列表中产品信息，进入产品详情

![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/产品列表.png)
![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/产品详情.png)

点击左侧 **设备列表**，进入设备列表，点击右侧 **添加设备**

![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/添加设备.png)
编辑设备名称 与 设备描述，点击 **添加**，完成添加设备

- 其中，设备名称为用户自定义设备唯一识别码，该产品下唯一

![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/添加设备信息.png)

![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/完成添加设备.png)

#### 添加设备API KEY

点击设备右侧的详情，进入设备详情页面，点击 添加APIKey，输入自定义的APIKey完成添加。
![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/添加APIKEY.png)
![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/点击添加APIKEY.png)
![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/输入APIKEY.png)



### 修改代码中设备信息

### 修改案例代码
修改 `applications\BearPi\BearPi-HM_Nano\sample\D7_iot_cloud_onenet`路径下 `iot_cloud_onenet_sample.c` 文件，

其中`ONENET_INFO_PROID`和`ONENET_MASTER_APIKEY`修改为产品的产品ID和Master-APIkey
```C
#define ONENET_INFO_PROID "383575"
#define ONENET_MASTER_APIKEY "GNQeLPioqBVpndus2KABmdOVZZI="
```
![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/查看产品对接信息.png)

`ONENET_INFO_DEVID`修改为设备ID;`ONENET_INFO_AUTH`修改为鉴权信息;`ONENET_INFO_APIKEY`修改为APIKey。
```C
#define ONENET_INFO_DEVID "648900765"
#define ONENET_INFO_AUTH "2020123456789"
#define ONENET_INFO_APIKEY "JHr7UCOXy2tbHkHqWTSwIlU3NzQ="
```
![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/查看设备对接信息.png)

`Wifi_SSID`修改为Wifi热点名称;`Wifi_PASSWORD`修改为Wifi热点密码。
```c
#define Wifi_SSID "TP-LINK_65A8"
#define Wifi_PASSWORD "0987654321"
```

### 修改 BUILD.gn 文件

修改 `applications\BearPi\BearPi-HM_Nano\sample`ifi路径下 BUILD.gn 文件，指定 `onenet_mqtt` 参与编译。

```r
#"D1_iot_wifi_sta:wifi_sta",
#"D2_iot_wifi_sta_connect:wifi_sta_connect",       
#"D3_iot_udp_client:udp_client",
#"D4_iot_tcp_server:tcp_server",
#"D5_iot_mqtt:iot_mqtt",        
#"D6_iot_cloud_oc:oc_mqtt",
"D7_iot_cloud_onenet:onenet_mqtt",
```

    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，会打印温湿度及光照强度信息。

```c
=======================================

***********IoT_OneNET_example**********

=======================================

******************************Lux Value is  40.83

******************************Humidity is  54.76

******************************Temperature is  24.43

=======================================

***********IoT_OneNET_example**********

=======================================

******************************Lux Value is  41.67

******************************Humidity is  54.77

******************************Temperature is  24.43
```
点击平台设备右侧的数据流，查看上报上来的数据。

![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/点击数据流.png)


![onenet_create_product](/applications/BearPi/BearPi-HM_Nano/docs/figures/D7_iot_cloud_onenet/查看数据流.png)



