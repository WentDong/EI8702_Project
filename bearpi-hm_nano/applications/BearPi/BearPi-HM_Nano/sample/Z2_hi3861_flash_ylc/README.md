# hi3861基础外设开发——内部flash读写（基于BearPi-HM_Nano开发板）
本示例将演示如何进行hi3861内部flash数据读写

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)

## FLASH API分析
本示例主要使用了以下API完成内部flash数据读写
## FlashRead()
```c
unsigned int FlashRead(const unsigned int flashOffset, const unsigned int size, unsigned char *ramData)
```
**描述：**

读取flash数据。
**参数：**

|名字|描述|
|:--|:------| 
| flashOffset | flash偏移地址  |
| size |要读取的字节数|
| ramData |存放待读取数据的缓存指针|

## FlashWrite()
```c
unsigned int FlashWrite(const unsigned int flashOffset, unsigned int size,
                        const unsigned char *ramData, unsigned char doErase)
```
**描述：**
将数据写入flash


**参数：**

|名字|描述|
|:--|:------| 
| flashOffset | flash偏移地址  |
| size |待写入字节数|
| ramData |待写入数据缓存指针|
| doErase |表示是否执行擦除|



## 硬件设计
无

## 软件设计

无

## 编译调试

### 修改 BUILD.gn 文件


修改 `applications\BearPi\BearPi-HM_Nano\sample` 路径下 BUILD.gn 文件，指定 `flash_example` 参与编译。

```r
#"Zx_Developer:zx_develop_sample"  ##不参与构建，为开发者贡献演示结构，其中Zx为 Z1，Z2...Z100
#"Z1_hi3861_uart_ylc:uart_hi3861",
"Z2_hi3861_flash_ylc:flash_example",
```   


### 运行结果

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手可以看到从flash读到了数据。

```c
内部闪存读写测试 Hello, BearPi!
```

