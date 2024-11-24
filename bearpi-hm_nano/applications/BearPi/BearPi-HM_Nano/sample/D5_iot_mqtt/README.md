# BearPi-HM_Nano开发板WiFi编程开发——MQTT协议开发
本示例将演示如何在BearPi-HM_Nano开发板上使用MQTT协议

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)


## 编译调试

### 下载MQTT消息代理工具Mosquitto

点击[下载](https://mosquitto.org/download/)Mosquitto 工具

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/消息代理.png "消息代理")

下载后双击安装包，安装工具，安装完毕后，打开电脑设备管理器，在“服务”中开启mosquitto服务。
![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/启动mosquitto服务.png "启动mosquitto服务")

修改安装路径下的mosquitto.conf文件
修改515行附近代码
![](../../docs/figures/D5_iot_mqtt/%E6%B7%BB%E5%8A%A0allow.png "添加allow")
修改216行附近代码，其中`192.168.0.173`为自己的电脑的IP地址
![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/添加listener.png "添加listener")

### 下载Eclipse Paho MQTT 工具
点击[下载](https://repo.eclipse.org/content/repositories/paho-releases/org/eclipse/paho/org.eclipse.paho.ui.app/1.1.1/)Eclipse Paho MQTT 工具


![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/下载客户端.png "下载客户端")

解压缩后，双击paho.exe，打开后的Eclipse Paho UI开始界面，点击上图中的 十字图标，就能新建一个MQTT的客户端的连接，如下图所示

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/新建客户端.png "新建客户端")

输入正确的MQTT服务端的连接地址，比如，本例中的连接地址是tcp://localhost:1883,然后点击“连接”按钮，这个时候，如果MQTT服务端没有设置密码（默认情况是没有密码的）的话，这个时候，我们就能看到连接得到状态是“已连接”，如下图所示：
![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/填写客户端信息.png "填写客户端信息")


这个时候我们就能订阅消息了。选择“订阅”下方的绿色十字图标，就可以输入订阅的主题（topic）的名字，比如我们设置主题名称为“pubtopic”，并点击 “订阅”按钮，如下图所示
![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/订阅.png "订阅")

### 修改对接IP
将代码中对接的IP修改为电脑在命令行窗口里输入 `ipconfig` 查询的电脑的本地IP

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/查询对接IP.png "查询对接IP")

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/修改对接IP.png "修改对接I")



### 修改 BUILD.gn 文件

修改 `applications\sample\BearPi\BearPi-HM_Nano`路径下 BUILD.gn 文件，指定 `iot_mqtt` 参与编译。

```r
#"D1_iot_wifi_sta:wifi_sta",
#"D2_iot_wifi_sta_connect:wifi_sta_connect",       
#"D3_iot_udp_client:udp_client",
#"D4_iot_tcp_server:tcp_server",
"D5_iot_mqtt:iot_mqtt",        
#"D6_iot_cloud_oc:oc_mqtt",
#"D7_iot_cloud_onenet:onenet_mqtt",
```

示例代码编译烧录代码后，按下开发板的RESET按键，Eclipse Paho MQTT 工具上会接收到开发板发布的消息。

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/接收消息.png "订阅")


往开发板发送一条消息主题为“substopic”，内容为“Hello HarmoayOS!”的MQTT消息。然后点击“发布”按钮，这个时候，我们就能看到消息已经发送成功。

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/发布消息.png "发布消息")

且开发板的串口上也打印出接收消息成功的信息。

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/D5_iot_mqtt/接收消息成功.png "接收消息成功")

