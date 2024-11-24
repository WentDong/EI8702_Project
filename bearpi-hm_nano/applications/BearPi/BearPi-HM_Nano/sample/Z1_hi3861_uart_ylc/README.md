# hi3861基础外设开发——UART数据读写（基于BearPi-HM_Nano开发板）
本示例将展示一种好用的串口收发逻辑

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## 注意点
本例使用的uart1，其txd脚也就是芯片的18脚为硬件配置字，上电时必须低电平，所以必须等烧录成功并完成重启之后再连接串口模块。
## UART API分析
本示例主要使用了以下API完成UART数据读写
## hi_uart_init()
```c
hi_u32 hi_uart_init(hi_uart_idx id, const hi_uart_attribute *param, const hi_uart_extra_attr *extra_attr)
```
 **描述：**

配置一个UART设备。
**参数：**

|名字|描述|
|:--|:------| 
| id | UART端口号.  |
| param |表示基本UART属性|
| extraAttr |表示扩展UART属性|

## hi_uart_write()
```c
hi_s32 hi_uart_write(hi_uart_idx id, const hi_u8 *data, hi_u32 data_len)
```
 **描述：**
将数据写入UART设备


**参数：**

|名字|描述|
|:--|:------| 
| id | UART端口号.  |
| data |表示指向要写入数据的起始地址的指针|
| dataLen |表示读取数据的长度|

## hi_uart_read_timeout()
```c
hi_s32 hi_uart_read_timeout(hi_uart_idx id, hi_u8 *data, hi_u32 len, hi_u32 timeout_ms)
```
 **描述：**

从UART设备读取数据。


**参数：**

|名字|描述|
|:--|:------| 
| id | UART端口号.  |
| data |表示指向要读取数据的起始地址的指针|
| dataLen |表示读取数据的长度|
| timeout_ms |表示读取数据的超时时间|



## 硬件设计
本案例将用 BearPi-HM_Nano 开发板 E53 接口的 UART 作为测试，如原理图所示 E53 接口第 18 和 19 脚分别为 TXD 和 RXD ，连接了主控芯片的 GPIO_6 和 GPIO_5 ，所以在编写软件的时候需要将 GPIO_6 和 GPIO_5 分别复用为 TXD 和 RXD 。

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/B6_basic_uart/E53接口电路.png "E53接口电路")

## 软件设计

**主要代码分析**

这部分代码为UART初始化的代码，首先要在 `hi_uart_attribute` 结构体这配置波特率、数据位、停止位、奇偶检验位，然后通过 `hi_uart_init()` 函数对串口1进行配置。

```c
    hi_uart_attribute uart_attr = {
        .baud_rate = 115200,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0,
    };

    //Initialize uart driver
    ret = hi_uart_init(HI_UART_IDX_1, &uart_attr, NULL);
    if (ret != HI_ERR_SUCCESS)
    {
        printf("Failed to init uart! Err code = %d\n", ret);
        return;
    }
```
这部分的代码为接收线程，阻塞在uart1_recv进行串口接收，接收到数据之后调用处理函数进行处理
```c
    while (1)
    {
        //阻塞等待串口1数据
        rxlen=uart1_recv(uart_buff_ptr, UART_BUFF_SIZE);        
        //处理数据
        uart1_rxproc(uart_buff_ptr,rxlen);
        osDelay(2);
    }
```
这是串口接收函数，没有接收到数据时在while中死循环阻塞，收到数据且断帧达到UART_TIMEOUT_MS后返回接收长度
```c
uint16_t uart1_recv(uint8_t *buf,uint16_t len)
{
    uint16_t rxlen=0;
    uint16_t ret=0;
    while(len-rxlen>0){
        ret=hi_uart_read_timeout(HI_UART_IDX_1, buf+rxlen, len-rxlen,UART_TIMEOUT_MS);
        if(ret==0&&rxlen!=0){
            return rxlen;
        }
        else{
            rxlen+=ret;
        }
    }
    return rxlen;
}
```


## 编译调试

### 修改 BUILD.gn 文件


修改 `applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `uart_hi3861` 参与编译。

```r
#"D12_iot_cloud_oc_agriculture:cloud_oc_agriculture",
#"D13_iot_cloud_oc_gps:cloud_oc_gps",

#"Zx_Developer:zx_develop_sample"  ##不参与构建，为开发者贡献演示结构，其中Zx为 Z1，Z2...Z100
"Z1_hi3861_uart_ylc:uart_hi3861",
```   


### 运行结果

示例代码编译烧录代码后，按下开发板的RESET按键， `将开发板上E53接口的UART_TX、UART_RX和GND用杜邦线接到TTL转USB模块（自备）` 通过串口助手查看数据，串口1实现接收回显。

