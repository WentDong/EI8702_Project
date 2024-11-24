# BearPi-HM Nano 十分钟上手教程<a name="ZH-CN_TOPIC_0000001054781998"></a>

## 一、准备工作<a name="section466851916410"></a>
- 准备一台电脑：
    - 无具体要求，家用即可，Windows系统

## 二、开始下载
- 下载官方提供镜像
    - 下载地址（百度云）：https://pan.baidu.com/s/1T0Tcl3y48C1p5L6y-6HJNg  提取码：eusr
- 下载HiBurn
    - 下载地址（百度云）：https://pan.baidu.com/s/1vSpPWvIhL8wCVGnEOjXS7g?pwd=1234 提取码：1234

- 下载并安装虚拟机VMware Workstation
    - 下载地址：https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html

- 下载并安装MobaXterm工具
    - 下载地址：https://en.softonic.com/download/moba/windows/post-download
    - 或者通过以下下载：https://download.mobatek.net/2312023031823706/MobaXterm_Installer_v23.1.zip

- 下载并安装RaiDrive工具
    - 下载地址：https://forspeed.rbread05.cn/down/newdown/5/28/RaiDrive.rar   
- 下载并安装开发板USB驱动
    - 下载地址：http://www.wch.cn/search?q=ch340g&t=downloads
- 下载并安装VS Code
    - 下载地址：https://code.visualstudio.com
## 三、开始部署环境

1. 解压百度云下载的HarmonyOS`Ubuntu18.4镜像OVF.zip`文件到某个目录。

    ![](figures/Ubuntu18.4镜像目录.png)

2. 打开VMware Workstation工具

    ![](figures/vmware_workstation.png)

3. 选择第1步解压的`Ubuntu18.4镜像OVF`文件夹中，点击` 打开 `

    ![](figures/打开镜像.png)

4. 导入镜像到本地磁盘（选择一个磁盘空间大小≥ 10G的盘），点击`导入`。

    ![](figures/导入镜像.png)

5. 点击`开启此虚拟机`，来开启虚拟机电源

    ![](figures/开启ubuntu虚拟机.png)
    
6. 此时虚拟机进入登录界面，点击`HarmonyOS`

    ![](figures/虚拟机登录页面.png)

7. 输入密码：bearpi，然后点击`登录`

    ![](figures/ubuntu登录.png)

8. 进入桌面后，点击桌面空白处`右键`，点击`打开终端(E)`

    ![](figures/ubuntu打开终端.png)

9. 在终端中输入`ifconfig`，然后点击回车，除`lo`外，另外一个就是你的网卡信息，记录你获取到的IP地址。

    ![](figures/获取虚拟机ip地址.png)

10. 最小化VMware Workstation，回到Windows桌面上。

11. 附加：如果连不上网络（如果主机网络需要拨号，如`校园网络`、`ADSL拨号`等）

    在VMware Workstation中，点击`虚拟机`>> `设置`

    ![](figures/VMWare设置.png)

    然后在网络适配器中，改成`NAT 模式`，点击`确定`

    ![](figures/VMware_net_config.png)

    然后再回复`步骤8`。
    

## 四、在Windows上远程连接服务器

1. 打开`MobaXterm`工具，并依次点击：`Session`，`SSH` 按钮。

    ![](figures/MobaXterm首页.png)

2. 输入连接信息，远程地址，并点击OK

    ![](figures/MobaX地址输入.png)

3. 输入账号：`bearpi`，点击回车

    ![](figures/Mobax_账号输入.png)

4. 输入密码：`bearpi`，注意，输入密码的时候屏幕不会显示，输完之后点击`回车`

    ![](figures/Mobax_密码输入.png)

5. 在弹出的界面上，点击`Yes`保存账号信息，以免下次输入

    ![](figures/Mobax_保存密码.png)

## 五、把ubuntu文件远程映射到Windows上

1. 安装RaiDrive软件
   
    默认安装即可。

2. 切换为中文语言

    ![](figures/RaiDrive_chinese.png)

3. 添加链接信息

    * 取消勾选只读
    * SFTP://______ （这个输入 三.9 获取到的地址）
    * 账户：账号和密码皆为 bearpi   
    * 其他默认
    * 点击`确定`

    ![](figures/RaiDrive_mesg.png)

4. 查看本地映射的ubuntu文件路径

    ![](figures/RaiDrive本地映射.png)


## 六、在ubuntu获取源码（gitee获取方式）

1. 鼠标焦点移到MobaXterm

2. 在MobaXterm中输入：
    ```
    cd /home/bearpi
    ```
    然后回车

3. 在MobaXterm中输入： 
    ```
    mkdir project && cd project
    ```
    然后回车

4. 在MobaXterm中输入：

    ```
    git clone https://gitee.com/bearpi/bearpi-hm_nano.git -b master
    ```

    然后回车，等待1-3分钟（根据不同网速）

    **注：** 若执行失败请参考`第三-11`解决网络问题，并通过ping外网确认ubuntu网络正常。

5. 当屏幕中出现`Successful`意味着代码获取完成


## 七、编译代码（gitee获取方式）

1. 进入项目根目录，在MobaXterm中输入：

    ```
    cd bearpi-hm_nano
    ```

2. 进入后，在MobaXterm中输入：

    ```
    python build.py BearPi-HM_Nano
    ```
    然后回车，等待直到屏幕出现：`BUILD SUCCESS`字样，说明编译成功。

3. 查看编译出的固件位置

    当编译完后，在Windows中可以直接查看到最终编译的固件，具体路径在：

    ![](figures/查看编译输出文件.png)

    *注意，最前面的盘符为`RaiDrive`在你电脑上实际映射的路径。

## 八、连接开发板

1. 通过TypeC数据线，把电脑与BearPi-HM Nano连接。

2. 安装CH340驱动。

    下载地址：http://www.wch.cn/search?q=ch340g&t=downloads

3. 关闭虚拟机捕获USB功能。（有很多开发者都是因为虚拟机捕获了USB设备，导致本机Windows电脑看不到串口）

    ![](figures/关闭虚拟机捕获USB.png)

    如果上面操作不行，直接关闭VMware Workstation，选择挂起，然后再重新插拔USB。

4. 查看开发板的串口

    ![](figures/获取到开发板串口号.png)

## 九、下载程序

1. 在Windows打开Hiburn工具，并点击`Refresh`，在`COM`中选择`第八-4`看到的COM号

    ![](figures/HiBurn主界面.png)

    然后点击`Setting`，并选择 `Com settings`，

2. 在Com settings中设置`Baud`为：`921600`，点击确定    

    ![](figures/HiBurn_Comsettings.png)

3. 点击 Hiburn工具中的`Select file`按钮，在弹出的文件框中，选择`七-2` 中对应的路径，并选中：`Hi3861_wifiiot_app_allinone.bin` 文件。

    ![](figures/HiBurn_打开文件.png)

4. 点击`Auto burn`复选框，然后点击`Connect`

    ![](figures/HiBurn准备下载.png)

    此时`Connect`按钮变成`Disconnect`，等待下载

5. 复位开发板`RESET`按键，开始下载程序

    ![](figures/复位开发板.png)

    ![](figures/Hiburn_下载程序中.png)

6. 直到出现`Execution Successful`字样，程序下载完成。

7. 下载完后，点击`Disconnect`按钮，便于后面调测使用。


## 十、MobaXterm 查看串口打印日志

1. 打开MobaXterm，
   
    1. 点击：`Session`、`Serial`按钮

    2. 设置Seral port为 Hiburn 同一个串口

    3. 设置Speed为 `115200`

    4. 点击`OK`


    ![](figures/Mobax_Serial_选择.png)

2.  如果显示Unable to open...等字样，需要看一下Hiburn的链接状态是否为关闭（九-7）步骤。


3. 复位开发板，此时COM打印出对应日志信息

    ![](figures/COM启动日志.png)
















































