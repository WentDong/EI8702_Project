# BearPi-HM_Nano开发板基础外设开发——GPIO输出
本示例将演示如何在BearPi-HM_Nano开发板上使用GPIO输出功能去点亮LED灯。

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)

## GPIO API分析
本案例主要使用了以下几个API完成GPIO输出功能
## GpioInit()
```c
unsigned int GpioInit (void )
```
 **描述：**

初始化GPIO外设
## IoSetFunc()
```c
unsigned int IoSetFunc (WifiIotIoName id, unsigned char val )
```
**描述：**

设置GPIO引脚复用功能

**参数：**

|名字|描述|
|:--|:------| 
| id | 表示GPIO引脚号.  |
| val | 表示GPIO复用功能 |

## GpioSetDir()
```c
unsigned int GpioSetDir (WifiIotGpioIdx id, WifiIotGpioDir dir )
```
**描述：**

设置GPIO输出方向

**参数：**

|名字|描述|
|:--|:------| 
| id | 表示GPIO引脚号.  |
| dir | 表示GPIO输出方向.  |


## 硬件设计
本案例将使用板载的LED来验证GPIO的输出功能，在BearPi-HM_Nano开发板上LED的连接电路图如下图所示，LED的控制引脚与主控芯片的GPIO_2连接，所以需要编写软件去控制GPIO_2输出高低电平实现LED灯的亮灭。

![LED灯电路](/applications/BearPi/BearPi-HM_Nano/docs/figures/B1_basic_led_blink/LED灯电路.png )

## 软件设计

**主要代码分析**

LedTask()为LED灯测试主任务，该任务先调用 GpioInit()初始化GPIO，因为LED灯的控制引脚接在GPIO_2上，所以通过调用IoSetFunc()和GpioSetDir()将GPIO_2设置为普通GPIO的输出模式。最后在死循环里面间隔 1s 输出GPIO_2的高低电平，实现LED灯闪烁的现象
```c
static void LedTask(void)
{
    GpioInit();//初始化GPIO
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_2, WIFI_IOT_IO_FUNC_GPIO_2_GPIO);//设置GPIO_2的复用功能为普通GPIO
    GpioSetDir(WIFI_IOT_IO_NAME_GPIO_2, WIFI_IOT_GPIO_DIR_OUT);//设置GPIO_2为输出模式
    
    while (1) 
        {
            GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_2, 1);//设置GPIO_2输出高电平点亮LED灯
            usleep(1000000);//延时1s
            GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_2, 0);//设置GPIO_2输出低电平熄灭LED灯
            usleep(1000000);//延时1s
        }
}
```

## 编译调试

### 修改 BUILD.gn 文件

修改`applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `led_example` 参与编译。

```r
"B1_basic_led_blink:led_example",
#"B2_basic_button:button_example",
#"B3_basic_pwm_led:pwm_example",
#"B4_basic_adc:adc_example",
#"B5_basic_i2c_nfc:i2c_example",
#"B6_basic_uart:uart_example",
```   
    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，开发板的LED灯开始闪烁


