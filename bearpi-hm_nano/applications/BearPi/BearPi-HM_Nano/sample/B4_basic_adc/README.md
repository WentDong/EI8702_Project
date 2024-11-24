# BearPi-HM_Nano开发板基础外设开发——ADC采样
本示例将演示如何在BearPi-HM_Nano开发板上通过按下按键改变GPIO口的电压，并使用ADC读取GPIO的电压值，

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## ADC API分析
本案例主要使用了以下API完成ADC采样的功能
## AdcRead()
```c
unsigned int AdcRead (WifiIotAdcChannelIndex channel, unsigned short * data, WifiIotAdcEquModelSel equModel, WifiIotAdcCurBais curBais, unsigned short rstCnt )
```
 **描述：**

根据输入参数从指定的ADC通道读取一段采样数据


**参数：**

|名字|描述|
|:--|:------| 
| channel | 表示ADC通道.  |
| data |表示指向存储读取数据的地址的指针 |
| equModel | 表示平均算法的次数 |
| curBais | 表示模拟功率控制模式 |
| rstCnt | 指示从重置到转换开始的时间计数。一次计数等于334纳秒。值的范围必须从0到0xFF|



## 硬件设计
本案例将使用板载用户按键F1来模拟GPIO口电压的变化。通过查看芯片手册可知GPIO_11对应的是 ADC Channel 5 ,所以需要编写软件去读取ADC Channel 5的电压,程序设计时先将GPIO_11上拉，使GPIO_11的电压一直处于高电平，当按键按下时GPIO_11接地，此时GPIO_11的电压变为 0 V。

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/B4_basic_adc/按键电路.png "按键电路")

## 软件设计

**主要代码分析**
 
该函数通过使用AdcRead()函数来读取 `ADC_CHANNEL_5` 的数值存储在data中， `WIFI_IOT_ADC_EQU_MODEL_8` 表示8次平均算法模式，`WIFI_IOT_ADC_CUR_BAIS_DEFAULT` 表示默认的自动识别模式，最后通过 `data * 1.8 * 4 / 4096.0` 计算出实际的电压值。
```c
static float GetVoltage(void)
{
    unsigned int ret;
    unsigned short data;

    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_5, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_DEFAULT, 0xff);
    if (ret != WIFI_IOT_SUCCESS) 
    {
        printf("ADC Read Fail\n");            
    }
    return (float)data * 1.8 * 4 / 4096.0;  /* data * 1.8 * 4 / 4096.0: Convert code into voltage */
}
```



## 编译调试

### 修改 BUILD.gn 文件


修改`applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `adc_example` 参与编译。

```r
#"B1_basic_led_blink:led_example",
#"B2_basic_button:button_example",
#"B3_basic_pwm_led:pwm_example",
"B4_basic_adc:adc_example",
#"B5_basic_i2c_nfc:i2c_example",
#"B6_basic_uart:uart_example",
```   

    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，当F1按键未按下时采集到的电压为3.3V左右，当按键按下时，电压变为0.2V左右。
```c
=======================================
*************ADC_example***********
=======================================
vlt:3.371V
=======================================
*************ADC_example***********
=======================================
vlt:3.371V
=======================================
*************ADC_example***********
=======================================
vlt:3.373V
=======================================
*************ADC_example***********
=======================================
vlt:0.248V
=======================================
*************ADC_example***********
=======================================
vlt:0.244V
```

