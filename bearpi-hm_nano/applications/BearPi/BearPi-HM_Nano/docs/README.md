## docs 资料包目录结构

| 目录名 | 描述   |
| ---- | ------ | 
| board   | [BearPi-HM_Nano开发板原理图](/applications/BearPi/BearPi-HM_Nano/docs/board)硬件资料、[视频课程配套PPT](/applications/BearPi/BearPi-HM_Nano/docs/board/课程配套PPT)  | 
| figures  | 资料图库   |

## 资料导航

| No | 类别 | 路径  |
| ---- | ---- |  ------------------------------------------------------------ |
| 1    | 开发板硬件资料 | [applications/BearPi/BearPi-HM_Nano/docs/board](/applications/BearPi/BearPi-HM_Nano/docs/board) |
| 2    | 快速上手教程 |  [applications/BearPi/BearPi-HM_Nano/docs/quick-start/](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/BearPi-HM_Nano%E5%8D%81%E5%88%86%E9%92%9F%E4%B8%8A%E6%89%8B.md) |
| 3    | 案例代码列表 |  [applications/BearPi/BearPi-HM_Nano/sample/](/applications/BearPi/BearPi-HM_Nano/sample/README.md) |
| 4    | 视频学习地址 |  [B站](https://www.bilibili.com/video/BV1tv411b7SA?p=1) |
| 5    | 视频课程PPT |  [applications/BearPi/BearPi-HM_Nano/docs/board/课程配套PPT](/applications/BearPi/BearPi-HM_Nano/docs/board/%E8%AF%BE%E7%A8%8B%E9%85%8D%E5%A5%97PPT) |
| 6    | 常见问题 | [ISSUES](https://gitee.com/bearpi/bearpi-hm_nano/issues) |

## 一、BearPi-HM Nano 开发板介绍

小熊派-HarmonyOS·季[（BearPi-HM Nano）](https://item.taobao.com/item.htm?id=633296694816)是一款由小熊派专为HarmonyOS系统打造的HarmonyOS开发板。

* 采用IoTCluB的E53接口标准，可接入所有的[E53案例扩展板](https://shop336827451.taobao.com/category-1488778768.htm)。
* 主控为WiFi SOC Hi3861，160MHz主频，SRAM 352KB、ROM 288KB、2M Flash。
* 板载NFC Forum Type 2 Tag芯片及天线，可实现HarmonyOS“碰一碰”功能。
* 一根TypeC USB线，即可实现供电、下载、调试等多种功能。


## 二、快速上手（十分钟上手）

如果您想快速的体验一下HarmonyOS的源码`[获取]`、`[编译]`、`[烧录]`过程，强烈建议您学习以下教程，这能让您在环境安装环节省下不少时间。

1、视频教程（B站）


* [开发环境搭建(简单)—十分钟快速上手](https://www.bilibili.com/video/BV1tv411b7SA?p=2)

2、文档（Gitee）
* [VMware 镜像版本：十分钟上手体验](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/BearPi-HM_Nano十分钟上手.md)

## 三、手把手教程系列

如果您想学习HarmonyOS系统的环境搭建，并想了解整个从0到1的过程，建议您跟着我们一步一步的学习。
需要告诉您的是，HarmonyOS系统的环境搭建所涉及的领域及组件会比较多，您需要严格按照我们的教程执行每一步，否则可能会出现不能预知的错误。

1、视频系列（B站）[ 对应PPT地址 ](/applications/BearPi/BearPi-HM_Nano/docs/board/课程配套PPT)
* [P1. BearPi-HM Nano开发板介绍](https://www.bilibili.com/video/BV1tv411b7SA?p=1)
* [P2. 开发环境搭建(复杂)—编译环境搭建](https://www.bilibili.com/video/BV1tv411b7SA?p=3)
* [P3. 开发环境搭建(复杂)—源码获取](https://www.bilibili.com/video/BV1tv411b7SA?p=4)
* [P4. 开发环境搭建(复杂)—在Windows上打开源码](https://www.bilibili.com/video/BV1tv411b7SA?p=5)
* [P5. HarmonyOS快速入门：Hello_World](https://www.bilibili.com/video/BV1tv411b7SA?p=6)
* [P6. HarmonyOS快速入门：点亮LED](https://www.bilibili.com/video/BV1tv411b7SA?p=7)
* [P7. Harmony编译构建介绍](https://www.bilibili.com/video/BV1tv411b7SA?p=8)
* [P8. HarmonyOS CMSIS接口简介](https://www.bilibili.com/video/BV1tv411b7SA?p=9)
* [P9. HarmonyOS内核开发—任务管理（上）](https://www.bilibili.com/video/BV1tv411b7SA?p=10)
* [P10. HarmonyOS内核开发—任务管理（下）](https://www.bilibili.com/video/BV1tv411b7SA?p=11)
* [P11. HarmonyOS内核开发—软件定时器](https://www.bilibili.com/video/BV1tv411b7SA?p=12)
* [P12. HarmonyOS内核开发—信号量](https://www.bilibili.com/video/BV1tv411b7SA?p=13)
* [P13. HarmonyOS内核开发—事件管理](https://www.bilibili.com/video/BV1tv411b7SA?p=14)
* [P14. HarmonyOS内核开发—互斥锁](https://www.bilibili.com/video/BV1tv411b7SA?p=15)
* [P15. HarmonyOS内核开发—消息队列](https://www.bilibili.com/video/BV1tv411b7SA?p=16)
* [P16. HarmonyOS驱动子系统开发—GPIO](https://www.bilibili.com/video/BV1tv411b7SA?p=17)
* [P17. HarmonyOS驱动子系统开发—GPIO中断](https://www.bilibili.com/video/BV1tv411b7SA?p=19)
* [P18. HarmonyOS驱动子系统开发—PWM](https://www.bilibili.com/video/BV1tv411b7SA?p=19)
* [P19. HarmonyOS驱动子系统开发—ADC](https://www.bilibili.com/video/BV1tv411b7SA?p=20)
* [P20. HarmonyOS驱动子系统开发—I2C](https://www.bilibili.com/video/BV1tv411b7SA?p=21)
* [P21. HarmomyOS驱动子系统开发—UART](https://www.bilibili.com/video/BV1tv411b7SA?p=22)
* [P22. HarmonyOS无线联网开发—WiFi AP热点](https://www.bilibili.com/video/BV1tv411b7SA?p=23)
* [P23. HarmonyOS无线联网开发—WiFi STA联网](https://www.bilibili.com/video/BV1tv411b7SA?p=24)
* [P24. HarmonyOS网络应用开发—UDP客户端](https://www.bilibili.com/video/BV1tv411b7SA?p=25)
* [P25. HarmonyOS网络应用开发—TCP服务端](https://www.bilibili.com/video/BV1tv411b7SA?p=26)
* [P26. HarmonyOS网络应用开发—TCP客户端](https://www.bilibili.com/video/BV1tv411b7SA?p=27)
* [P27. HarmonyOS网络应用开发—UDP服务端](https://www.bilibili.com/video/BV1tv411b7SA?p=28)
* [P28. HarmonyOS网络应用开发—MQTT客户端](https://www.bilibili.com/video/BV1tv411b7SA?p=29)
* [P29. HarmonyOS网络应用开发—对接华为IoT平台](https://www.bilibili.com/video/BV1tv411b7SA?p=30)
* [P30. HarmonyOS网络应用开发—对接OneNET平台](https://www.bilibili.com/video/BV1tv411b7SA?p=31)
* [更多: 陆续上传中...](https://www.bilibili.com/video/BV1tv411b7SA)

2、文档系列（Gitee）
-   [BearPi-HM_Nano 开发板介绍](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/BearPi-HM_Nano开发板介绍.md)
-   [BearPi-HM_Nano 开发搭建环境](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/BearPi-HM_Nano开发搭建环境.md)
-   [BearPi-HM_Nano 开发板源码获取](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/源码获取.md)
-   [BearPi-HM_Nano 开发板如何烧录程序](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/BearPi-HM_Nano开发板如何烧录程序.md)
-   [BearPi-HM_Nano 开发第一个示例程序](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/BearPi-HM_Nano开发板第一个示例程序.md)
-   [BearPi-HM_Nano 案例开发](/applications/BearPi/BearPi-HM_Nano/sample/README.md)
-   [常见问题](/applications/BearPi/BearPi-HM_Nano/docs/quick-start/常见问题.md)


## 四、BearPi-HM_Nano 案例开发

BearPi-HM Nano提供多个案例，案例以A、B、C、D进行不同类别进行分级，方便初学者由浅入深逐步学习。您拿到工程后经过简单的编程和下载即可看到实验现象。下面依次对A/B/C/D类进行介绍：

* `A1 - A99`：内核类
* `B1 - B99`：基础外设类
* `C1 - C99`：E53传感器类
* `D1 - D99`：物联网类

例程列表如下所示：

| 编号 | 类别   | 例程名           | 说明                                                         |
| ---- | ------ | ---------------- | ------------------------------------------------------------ |
| A1   | 内核   | thread           |   [任务交替打印](/applications/BearPi/BearPi-HM_Nano/sample/A1_kernal_thread/README.md)  |
| A2   | 内核   | timer            |  [定时器  ](/applications/BearPi/BearPi-HM_Nano/sample/A2_kernel_timer/README.md)                                                      |
| A3   | 内核   | event            |   [事件](/applications/BearPi/BearPi-HM_Nano/sample/A3_kernel_event/README.md)|
| A4   | 内核   | mutex            |   [互斥锁](/applications/BearPi/BearPi-HM_Nano/sample/A4_kernel_mutex/README.md)|
| A5   | 内核   | semp             |   [信号量](/applications/BearPi/BearPi-HM_Nano/sample/A5_kernel_semaphore/README.md)|
| A6   | 内核   | message           |    [消息队列](/applications/BearPi/BearPi-HM_Nano/sample/A6_kernel_message/README.md)|
| B1   | 基础   | led_blink        |   [红色 LED 不间断烁](/applications/BearPi/BearPi-HM_Nano/sample/B1_basic_led_blink/README.md)|
| B2   | 基础   | button           |   [按键控制LED灯亮灭](/applications/BearPi/BearPi-HM_Nano/sample/B2_basic_button/README.md)|
| B3   | 基础   | pwm_led          |   [红色 LED 呼吸灯](/applications/BearPi/BearPi-HM_Nano/sample/B3_basic_pwm_led/README.md)|
| B4   | 基础   | adc_mq2          |   [ADC读取电压](/applications/BearPi/BearPi-HM_Nano/sample/B4_basic_adc/README.md)|
| B5   | 基础   | i2c_bh1750       |   [I2C读取NFC标签](/applications/BearPi/BearPi-HM_Nano/sample/B5_basic_i2c_nfc/README.md)|
| B6   | 基础   | basic_uart       |   [UART自发自收](/applications/BearPi/BearPi-HM_Nano/sample/B6_basic_uart/README.md)|
| C1   | E53传感器   | e53_sf1_example        |       [驱动烟雾传感器 MQ2](/applications/BearPi/BearPi-HM_Nano/sample/C1_e53_sf1_mq2/README.md)|
| C2   | E53传感器   | e53_ia1_example              |   [驱动温湿度传感器 SHT30](/applications/BearPi/BearPi-HM_Nano/sample/C2_e53_ia1_temp_humi_pls/README.md)|
| C3   | E53传感器   | e53_sc1_example             |   [驱动光强传感器 BH1750](/applications/BearPi/BearPi-HM_Nano/sample/C3_e53_sc1_pls/README.md)|
| C4   | E53传感器   | e53_sc2_example        |   [驱动 6 轴陀螺仪 MPU6050](/applications/BearPi/BearPi-HM_Nano/sample/C4_e53_sc2_axis/README.md)|
| C5   | E53传感器   | e53_is1_example              |   [驱动人体红外传感器](/applications/BearPi/BearPi-HM_Nano/sample/C5_e53_is1_infrared/README.md)|
| D1   | 物联网 | iot_wifi_ap        |   [Wifi热点创建](/applications/BearPi/BearPi-HM_Nano/sample/D1_iot_wifi_ap/README.md)|
| D2   | 物联网 | iot_wifi_sta_connect    |   [Wifi联网](/applications/BearPi/BearPi-HM_Nano/sample/D2_iot_wifi_sta_connect/README.md)|
| D3   | 物联网 | udp_client       |   [使用 Socket 实现 UDP 客户端](/applications/BearPi/BearPi-HM_Nano/sample/D3_iot_udp_client/README.md)|
| D4   | 物联网 | tcp_server       |   [使用 Socket 实现 TCP 服务端](/applications/BearPi/BearPi-HM_Nano/sample/D4_iot_tcp_server/README.md)|
| D5   | 物联网 | iot_mqtt             |   [使用 Paho-MQTT 软件包实现 MQTT 协议通信](/applications/BearPi/BearPi-HM_Nano/sample/D5_iot_mqtt/README.md)|
| D6   | 物联网 | iot_cloud_oc_sample     |  [接入华为IoT 云平台](/applications/BearPi/BearPi-HM_Nano/sample/D6_iot_cloud_oc/README.md)|
| D7   | 物联网 | iot_cloud_onenet_sample         |   [接入中国移动 OneNET 云平台](/applications/BearPi/BearPi-HM_Nano/sample/D7_iot_cloud_onenet/README.md)|
| D8   | 物联网 | iot_cloud_oc_smoke         |   [基于华为IoT平台的智慧烟感案例](/applications/BearPi/BearPi-HM_Nano/sample/D8_iot_cloud_oc_smoke/README.md)|  
| D9   | 物联网 | iot_cloud_oc_light         |   [基于华为IoT平台的智慧路灯案例](/applications/BearPi/BearPi-HM_Nano/sample/D9_iot_cloud_oc_light/README.md)|    
| D10   | 物联网 | iot_cloud_oc_manhole_cover         |   [基于华为IoT平台的智慧井盖案例](/applications/BearPi/BearPi-HM_Nano/sample/D10_iot_cloud_oc_manhole_cover/README.md)|  
| D11   | 物联网 | iot_cloud_oc_infrared         |   [基于华为IoT平台的智慧人体感应案例](/applications/BearPi/BearPi-HM_Nano/sample/D11_iot_cloud_oc_infrared/README.md)|  
| D12   | 物联网 | iot_cloud_oc_agriculture         |   [基于华为IoT平台的智慧农业案例](/applications/BearPi/BearPi-HM_Nano/sample/D12_iot_cloud_oc_agriculture/README.md)| 
| D13   | 物联网 | iot_cloud_oc_gps         |   [基于华为IoT平台的智慧物流案例](/applications/BearPi/BearPi-HM_Nano/sample/D13_iot_cloud_oc_gps/README.md)|   
||||



## 五、源码目录简介

小熊派的源码目录延续OpenHarmony官方目录结构，以下是源码目录的说明：

<a name="table3815144702820"></a>
<table><thead align="left"><tr id="row198162047192810"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p690319291299"><a name="p690319291299"></a><a name="p690319291299"></a>目录名</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p5903122962918"><a name="p5903122962918"></a><a name="p5903122962918"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row1981674719280"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p69031429162912"><a name="p69031429162912"></a><a name="p69031429162912"></a>applications</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p090352912914"><a name="p090352912914"></a><a name="p090352912914"></a>BearPi-HM_Nano应用程序样例</p>
</td>
</tr>
<tr id="row5816747132817"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p99031129112918"><a name="p99031129112918"></a><a name="p99031129112918"></a>base</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p790472962914"><a name="p790472962914"></a><a name="p790472962914"></a>基础软件服务子系统集&amp;硬件服务子系统集</p>
</td>
</tr>
<tr id="row1134218692910"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p4904112910295"><a name="p4904112910295"></a><a name="p4904112910295"></a>build</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1090482942911"><a name="p1090482942911"></a><a name="p1090482942911"></a>组件化编译、构建和配置脚本</p>
</td>
</tr>
<tr id="row1841618902919"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1390462902910"><a name="p1390462902910"></a><a name="p1390462902910"></a>domains</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1390432914296"><a name="p1390432914296"></a><a name="p1390432914296"></a>增强软件服务子系统集</p>
</td>
</tr>
<tr id="row841620912298"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p119041629182919"><a name="p119041629182919"></a><a name="p119041629182919"></a>drivers</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p9904629132911"><a name="p9904629132911"></a><a name="p9904629132911"></a>驱动子系统</p>
</td>
</tr>
<tr id="row164164992915"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p79042298298"><a name="p79042298298"></a><a name="p79042298298"></a>foundation</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p18904132922915"><a name="p18904132922915"></a><a name="p18904132922915"></a>系统基础能力子系统集</p>
</td>
</tr>
<tr id="row1441610922915"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p490402916299"><a name="p490402916299"></a><a name="p490402916299"></a>kernel</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1904112932912"><a name="p1904112932912"></a><a name="p1904112932912"></a>内核子系统</p>
</td>
</tr>
<tr id="row194175972917"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1904132912910"><a name="p1904132912910"></a><a name="p1904132912910"></a>prebuilts</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p390492919296"><a name="p390492919296"></a><a name="p390492919296"></a>编译器及工具链子系统</p>
</td>
</tr>
<tr id="row841718942913"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p12904929202919"><a name="p12904929202919"></a><a name="p12904929202919"></a>test</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p4904152912297"><a name="p4904152912297"></a><a name="p4904152912297"></a>测试子系统</p>
</td>
</tr>
<tr id="row24175915294"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p13904162992916"><a name="p13904162992916"></a><a name="p13904162992916"></a>third_party</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p6904829112917"><a name="p6904829112917"></a><a name="p6904829112917"></a>开源第三方组件</p>
</td>
</tr>
<tr id="row334210652914"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1390442918299"><a name="p1390442918299"></a><a name="p1390442918299"></a>utils</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p690412296297"><a name="p690412296297"></a><a name="p690412296297"></a>常用的工具集</p>
</td>
</tr>
<tr id="row73421664298"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p7905172920292"><a name="p7905172920292"></a><a name="p7905172920292"></a>vendor</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p290510290293"><a name="p290510290293"></a><a name="p290510290293"></a>厂商提供的软件</p>
</td>
</tr>
<tr id="row734319617292"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p09056291290"><a name="p09056291290"></a><a name="p09056291290"></a>build.py</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1790542912290"><a name="p1790542912290"></a><a name="p1790542912290"></a>编译脚本文件</p>
</td>
</tr>
</tbody>
</table>

## 六、开发板图片预览[（淘宝链接）](https://item.taobao.com/item.htm?id=633296694816)

[![](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano_Info.png)](https://item.taobao.com/item.htm?id=633296694816)


## 七、联系我们



![](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/bearpi_club_wechat.jpg)

