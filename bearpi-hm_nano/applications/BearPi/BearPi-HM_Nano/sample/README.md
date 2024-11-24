# BearPi-HM_Nano案例开发

BearPi-HM_Nano 提供的例程多达 30个，每个例程都有非常详细的注释，代码风格统一，按照基本例程到高级例程的方式编排，方便初学者由浅入深逐步学习。开发者拿到工程后经过简单的编译和下载即可看到实验现象。

这些例程包括四个类别：内核类、基本外设类、驱动类、物联网类。不仅包括了硬件资源的应用，更是提供了丰富的物联网领域的应用示例，帮助物联网开发者更好更快地进行开发。

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
| Z1   | 开发者贡献例程 | hi3861_uart         |   [Hi3861串口收发（带超时功能）@游乐场](/applications/BearPi/BearPi-HM_Nano/sample/Z1_hi3861_uart_ylc/README.md)|   
| Z2   | 开发者贡献例程 | hi3861_flash         |   [Hi3861内部Flash读写 @游乐场](/applications/BearPi/BearPi-HM_Nano/sample/Z2_hi3861_flash_ylc/README.md)|   
||||
