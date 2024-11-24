# BearPi-HM_Nano开发板传感器驱动开发——E53_IA1读取温度 、湿度、光照强度
本示例将演示如何在BearPi-HM_Nano开发板上使用E53_IA1读取温度 、湿度、光照强度，当温度 、湿度超标时开启电机通风，当光照强度过低时，开启补光灯补光。

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## E53_IA1 API分析
本案例主要使用了以下API完成温度 、湿度、光照强度读取
## E53_IA1_Init()
```C
void E53_IA1_Init(void)
```
 **描述：**

初始化E53_IA1

## E53_IA1_Read_Data()
```C
void E53_IA1_Read_Data(void)
```
 **描述：**
读取温度 、湿度、光照强度
## Light_StatusSet()
```C
void Light_StatusSet(E53_IA1_Status_ENUM status)
```
 **描述：**

控制补光灯开关
**参数：**

|名字|描述|
|:--|:------| 
| status | ON开，OFF关闭.  |

## Motor_StatusSet()
```C
void Motor_StatusSet(E53_IA1_Status_ENUM status)
```
 **描述：**

控制电机开关

**参数：**

|名字|描述|
|:--|:------| 
| status | ON开，OFF关闭.  |

## 硬件设计
本案例将用到 E53_IA1 智慧农业扩展板与 BearPi-HM_Nano 开发板，其中E53_IA1扩展板接口原理图如下，温湿度传感器sht30和光照强度传感器BH1750都是通过I2C来驱动，电机和补光灯分别通过GPIO_8和GPIO_14来控制。
![](/applications/BearPi/BearPi-HM_Nano/docs/figures/C2_e53_ia1_temp_humi_pls/E53_IA1接口.png "E53_IA1接口")

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/C2_e53_ia1_temp_humi_pls/E53接口电路.png "E53接口电路")

E53_IA1 智慧农业扩展板与 BearPi-HM_Nano 开发板安装如下图所示

![](/applications/BearPi/BearPi-HM_Nano/docs/figures/C2_e53_ia1_temp_humi_pls/E53_IA1安装.png "E53_IA1安装")

## 软件设计

**主要代码分析**


首先调用 `E53_IA1_Init()` 函数初始化E53_IA1所接的引脚的功能，然后循环调用 `E53_IA1_Read_Data()` 函数读取温度 、湿度、光照强度并通过串口打印出来，当光照强度过低时，开启补光灯补光，当温度 、湿度超标时开启电机通风。

```C
static void Example_Task(void)
{
    E53_IA1_Init();

    while(1)
    {
        printf("\r\n=======================================\r\n");
        printf("\r\n***********I2C_BH1750_example**********\r\n");
        printf("\r\n=======================================\r\n");

        E53_IA1_Read_Data();

        printf("\r\n******************************Lux Value is  %.2f\r\n", E53_IA1_Data.Lux);
		printf("\r\n******************************Humidity is  %.2f\r\n", E53_IA1_Data.Humidity);
		printf("\r\n******************************Temperature is  %.2f\r\n", E53_IA1_Data.Temperature);

        if( E53_IA1_Data.Lux < 20 )
        {
            Light_StatusSet(ON);
        }
        else
        {
            Light_StatusSet(OFF);
        }
        
        if( (E53_IA1_Data.Humidity > 70) | (E53_IA1_Data.Temperature > 35) )
        {
            Motor_StatusSet(ON);
        }
        else
        {
            Motor_StatusSet(OFF);
        }

        usleep(1000000);
    }
}
```



## 编译调试

### 修改 BUILD.gn 文件
修改`applications\BearPi\BearPi-HM_Nano\sample`路径下 BUILD.gn 文件，指定 `e53_ia1_example` 参与编译。
```r
#"C1_e53_sf1_mq2:e53_sf1_example",
"C2_e53_ia1_temp_humi_pls:e53_ia1_example",
#"C3_e53_sc1_pls:e53_sc1_example",
#"C4_e53_sc2_axis:e53_sc2_example",
#"C5_e53_is1_infrared:e53_is1_example",
```

    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，会打印温湿度及光照强度信息。用手遮住扩展板，补光灯会自动开启，控制温度或者湿度超标，电机会自动开启。
```c
=======================================

*************E53_IA1_example***********

=======================================

******************************Lux Value is  53.33

******************************Humidity is  44.10

******************************Temperature is  28.13
=======================================

*************E53_IA1_example***********

=======================================

******************************Lux Value is  53.33

******************************Humidity is  44.10

******************************Temperature is  28.13
```

