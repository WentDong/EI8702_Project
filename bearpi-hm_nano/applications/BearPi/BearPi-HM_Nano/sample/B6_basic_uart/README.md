# BearPi-HM_Nano开发板基础外设开发——UART数据读写
本示例将演示如何在BearPi-HM_Nano开发板上使用UART进行数据的收发

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## UART API分析
本示例主要使用了以下API完成UART数据读写
## UartInit()
```c
unsigned int UartInit (WifiIotUartIdx id, const WifiIotUartAttribute * param, const WifiIotUartExtraAttr * extraAttr )
```
 **描述：**

配置一个UART设备。
**参数：**

|名字|描述|
|:--|:------| 
| id | UART端口号.  |
| param |表示基本UART属性|
| extraAttr |表示扩展UART属性|

## UartWrite()
```c
int UartWrite (WifiIotUartIdx id, const unsigned char * data, unsigned int dataLen )
```
 **描述：**
将数据写入UART设备


**参数：**

|名字|描述|
|:--|:------| 
| id | UART端口号.  |
| data |表示指向要写入数据的起始地址的指针|
| dataLen |表示读取数据的长度|

## UartRead()
```c
int UartRead (WifiIotUartIdx id, unsigned char * data, unsigned int dataLen )
```
 **描述：**

从UART设备读取数据。


**参数：**

|名字|描述|
|:--|:------| 
| id | UART端口号.  |
| data |表示指向要读取数据的起始地址的指针|
| dataLen |表示读取数据的长度|




## 硬件设计
本案例将用 BearPi-HM_Nano 开发板 E53 接口的 UART 作为测试，如原理图所示第 18 和 19 脚分别为 TXD 和 RXD ，连接了主控芯片的 GPIO_6 和 GPIO_5 ，所以在编写软件的时候需要将 GPIO_6 和 GPIO_5 分别复用为 TXD 和 RXD 。

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/B6_basic_uart/E53接口电路.png "E53接口电路")

## 软件设计

**主要代码分析**

这部分代码为UART初始化的代码，首先要在 `uart_attr` 结构体这配置波特率、数据位、停止位、奇偶检验位，然后通过 `UartInit()` 函数对串口1进行配置。

```c
WifiIotUartAttribute uart_attr = {
    .baudRate = 9600, /* baud_rate: 9600 */
    .dataBits = 8,      /* data_bits: 8bits */
    .stopBits = 1,
    .parity = 0,
};

/* Initialize uart driver */
ret = UartInit(WIFI_IOT_UART_IDX_1, &uart_attr, NULL);
if (ret != WIFI_IOT_SUCCESS) {
    printf("Failed to init uart! Err code = %d\n", ret);
    return;
}
```
这部分的代码主要实现通过 `UartWrite()` 函数在串口1发送一串数据，然后通过 `UartRead()` 函数将数据都回来，并通过 `debug` 串口打印出来。
```c
UartWrite(WIFI_IOT_UART_IDX_1, (unsigned char *)data, strlen(data));    // 通过串口1发送数据
UartRead(WIFI_IOT_UART_IDX_1,uart_buff_ptr,UART_BUFF_SIZE);             // 通过串口1接收数据
printf("%s",uart_buff_ptr);
```


## 编译调试

### 修改 BUILD.gn 文件


修改 `applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `uart_example` 参与编译。

```r
#"B1_basic_led_blink:led_example",
#"B2_basic_button:button_example",
#"B3_basic_pwm_led:pwm_example",
#"B4_basic_adc:adc_example",
#"B5_basic_i2c_nfc:i2c_example",
"B6_basic_uart:uart_example",
```   


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键， `将开发板上E53接口的UART_TX和UART_RX用杜邦线短接` 通过串口助手查看日志，串口1实现自发自收。
```c
=======================================
*************UART_example**************
=======================================
Uart1 read data:Hello, BearPi!
=======================================
*************UART_example**************
=======================================
Uart1 read data:Hello, BearPi!
```

