# BearPi-HM_Nano开发板第一个示例程序<a name="ZH-CN_TOPIC_0000001053183925"></a>

本示例将演示如何编写简单业务，输出“Hello World”。

## 修改源码<a name="section9360141181414"></a>

bugfix和新增业务两种情况，涉及源码修改。下面以新增业务举例，向开发者介绍如何进行源码修改。

1.  <a name="li5479332115116"></a>确定目录结构。

    开发者编写业务时，务必先在./applications/BearPi/BearPi-HM_Nano/sample路径下新建一个目录（或一套目录结构），用于存放业务源码文件。

    例如：在app下新增业务my\_first\_app，其中hello\_world.c为业务代码，BUILD.gn为编译脚本，具体规划目录结构如下：

    ```
    .
    └── applications        
        └── BearPi
            └── BearPi-HM_Nano
                └── sample
                    │── my_first_app
                    │  │── hello_world.c
                    │  └── BUILD.gn
                    └── BUILD.gn
    ```

2.  编写业务代码。

    在hello\_world.c中新建业务入口函数HelloWorld，并实现业务逻辑。并在代码最下方，使用OpenHarmony启动恢复模块接口SYS\_RUN\(\)启动业务。（SYS\_RUN定义在ohos\_init.h文件中）

    ```
    #include "ohos_init.h"
    #include "ohos_types.h"
    #include <stdio.h>
    
    void HelloWorld(void)
    {
        printf("[DEMO] Hello world.\n");
    }
    SYS_RUN(HelloWorld);
    ```

3.  编写用于将业务构建成静态库的BUILD.gn文件。

    如[步骤1](#li5479332115116)所述，BUILD.gn文件由三部分内容（目标、源文件、头文件路径）构成，需由开发者完成填写。以my\_first\_app为例，需要创建./applications/BearPi/BearPi-HM_Nano/sample/my\_first\_app/BUILD.gn，并完如下配置。

    ```
    static_library("myapp") {
        sources = [
            "hello_world.c"
        ]
        include_dirs = [
            "//utils/native/liteos/include"
        ]
    }
    ```

    -   static\_library中指定业务模块的编译结果，为静态库文件libmyapp.a，开发者根据实际情况完成填写。
    -   sources中指定静态库.a所依赖的.c文件及其路径，若路径中包含"//"则表示绝对路径（此处为代码根路径），若不包含"//"则表示相对路径。
    -   include\_dirs中指定source所需要依赖的.h文件路径。

4.  编写模块BUILD.gn文件，指定需参与构建的特性模块。

    配置`./applications/BearPi/BearPi-HM_Nano/sample/BUILD.gn`文件，在features字段中增加索引`"my_first_app:myapp"`，使目标模块参与编译。并屏蔽其他模块。

    ```
        #"D1_iot_wifi_scan:wifi_scan",
        #"D2_iot_wifi_connect:wifi_connect",        
        #"D3_iot_udp_client:udp_client",
        #"D4_iot_tcp_server:tcp_server",
        #"D5_iot_mqtt:iot_mqtt",        
        #"D6_iot_cloud_oc:oc_mqtt",
        #"D7_iot_cloud_onenet:onenet_mqtt",
        
        "my_first_app:myapp"
    ```

    -   my\_first\_app是相对路径，指向`./applications/BearPi/BearPi-HM_Nano/sample/my_first_app/BUILD.gn`。
    -   myapp是目标，指向 `./applications/BearPi/BearPi-HM_Nano/sample/my_first_app/BUILD.gn` 中的static\_library\("myapp"\)。


## 运行结果<a name="section18115713118"></a>

示例代码编译、烧录、运行、调测后，会显示如下结果：

```
ready to OS start
FileSystem mount ok.
wifi init success!
[DEMO] Hello world.
```

## 下一步学习<a name="section9712145420182"></a>

恭喜，您已完成BearPi-HM_Nano开发板快速上手,可以进行[BearPi-HM_Nano案例开发](/applications/BearPi/BearPi-HM_Nano/sample/README.md)了。