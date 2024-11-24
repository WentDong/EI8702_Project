# BearPi-HM_Nano开发板HarmonyOS内核编程开发——消息队列
本示例将演示如何在BearPi-HM_Nano开发板上使用cmsis 2.0 接口通过消息队列进行线程之间交换消息

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## MessageQueue API分析



## osMessageQueueNew()

```c
osMessageQueueId_t osMessageQueueNew(uint32_t msg_count,uint32_t msg_size,const osMessageQueueAttr_t *attr)
```
**描述：**

函数osMessageQueueNew创建并初始化一个消息队列对象。该函数返回消息队列对象标识符，如果出现错误则返回NULL，可以在RTOS启动(调用 osKernelStart)之前安全地调用该函数，也可以在内核初始化 (调用 osKernelInitialize)之前调用该函数。
> **注意** :不能在中断服务调用该函数


**参数：**

|名字|描述|
|:--|:------| 
| msg_count |队列中的最大消息数.  |
| msg_size |最大消息大小(以字节为单位).  |
| attr |消息队列属性;空:默认值.  |

## osMessageQueuePut()

```c
osStatus_t osMessageQueuePut(osMessageQueueId_t mq_id,const void *msg_ptr,uint8_t msg_prio,uint32_t timeout)	
```
**描述：**
函数osMessageQueuePut将msg_ptr指向的消息放入参数mq_id指定的消息队列中。

> **注意** :如果参数timeout设置为0，可以从中断服务例程调用


**参数：**

|名字|描述|
|:--|:------| 
| mq_id | 由osMessageQueueNew获得的消息队列ID.  |
| msg_ptr | 要发送的消息.  |
| msg_prio | 指优先级.  |
| timeout | 超时值.  |

## osMessageQueueGet()

```c
osStatus_t osMessageQueueGet(osMessageQueueId_t mq_id,void *msg_ptr,uint8_t *msg_prio,uint32_t 	timeout)
```
**描述：**
函数osMessageQueueGet从参数mq_id指定的消息队列中检索消息，并将其保存到参数msg_ptr所指向的缓冲区中。

> **注意** :如果参数timeout设置为0，可以从中断服务例程调用。


**参数：**

|名字|描述|
|:--|:------| 
| mq_id | 由osMessageQueueNew获得的消息队列ID.  |
| msg_ptr | 指针指向队列中获取消息的缓冲区指针.  |
| msg_prio | 指优先级.  |
| timeout | 超时值.  |

## 软件设计

## 软件设计

**主要代码分析**

在Message_example函数中，通过osMessageQueueNew()函数创建了消息队列ID，Thread_MsgQueue1()函数中通过osMessageQueuePut()函数向消息队列中发送消息。在Thread_MsgQueue2()函数中通过osMessageQueueGet()函数读取消息队列中的消息比打印出来。

```c

void Thread_MsgQueue1 (void *argument) 
{
  (void)argument; 

  msg.Buf = "Hello BearPi-HM_Nano!";                                         // do some work...
  msg.Idx    = 0U;
  while (1)
  {
    osMessageQueuePut(mid_MsgQueue, &msg, 0U, 0U);
    osThreadYield();                                            // suspend thread   
    osDelay(100);
  }
}
 
void Thread_MsgQueue2 (void *argument) 
{
  (void)argument;
  osStatus_t status;

  while (1) {
    // Insert thread code here...
    status = osMessageQueueGet(mid_MsgQueue, &msg, NULL, 0U);   // wait for message
    if (status == osOK) {
      printf("Message Queue Get msg:%s\n",msg.Buf);
    }
  }
}

static void Message_example (void) {
 
  mid_MsgQueue = osMessageQueueNew(MSGQUEUE_OBJECTS, 100, NULL);
  if (mid_MsgQueue == NULL) {
    printf("Falied to create Message Queue!\n");
  } 
  osThreadAttr_t attr;
  
  attr.attr_bits = 0U;
  attr.cb_mem = NULL;
  attr.cb_size = 0U;
  attr.stack_mem = NULL;
  attr.stack_size = 1024*10;
  attr.priority = 25;

  attr.name = "Thread_MsgQueue1";
  if (osThreadNew(Thread_MsgQueue1, NULL, &attr) == NULL) {
      printf("Falied to create Thread_MsgQueue1!\n");
  }
  attr.name = "Thread_MsgQueue2";
  if (osThreadNew(Thread_MsgQueue2, NULL, &attr) == NULL) {
      printf("Falied to create Thread_MsgQueue2!\n");
  }
}

```

## 编译调试

### 修改 BUILD.gn 文件

修改 `applications\BearPi\BearPi-HM_Nano\sample`路径下 BUILD.gn 文件，指定 `message_example` 参与编译。

```r
#"A1_kernal_thread:thread_example",
#"A2_kernel_timer:timer_example",
#"A3_kernel_event:event_example",
#"A4_kernel_mutex:mutex_example",
#"A5_kernel_semaphore:semaphore_example",
"A6_kernel_message:message_example",
```
    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，会打印从消息队列中获取的消息。
```c
Message Queue Get msg:Hello BearPi-HM_Nano!
Message Queue Get msg:Hello BearPi-HM_Nano!
Message Queue Get msg:Hello BearPi-HM_Nano!
Message Queue Get msg:Hello BearPi-HM_Nano!
Message Queue Get msg:Hello BearPi-HM_Nano!
```
