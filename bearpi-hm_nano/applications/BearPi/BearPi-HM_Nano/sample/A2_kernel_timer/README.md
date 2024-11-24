# BearPi-HM_Nano开发板HarmonyOS内核编程开发——定时器
本示例将演示如何在BearPi-HM_Nano开发板上使用cmsis 2.0 接口进行定时器开发

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## Timer API分析


## osTimerNew()

```c
osTimerId_t osTimerNew	(osTimerFunc_t func,osTimerType_t type,void *argument,const osTimerAttr_t *attr)
```
**描述：**

函数osTimerNew创建一个一次性或周期性计时器，并将其与一个带参数的回调函数相关联。计时器在osTimerStart启动之前一直处于停止状态。可以在RTOS启动(调用 osKernelStart)之前安全地调用该函数，但不能在内核初始化 (调用 osKernelInitialize)之前调用该函数。
> **注意** :不能在中断服务调用该函数


**参数：**

|名字|描述|
|:--|:------| 
| func | 函数指针指向回调函数.  |
| type | 定时器类型，osTimerOnce表示单次定时器，osTimerPeriodic周期表示周期性定时器.  |
| argument |定时器回调函数的参数|
| attr |计时器属性|

## osTimerStart()

```c
osStatus_t osTimerStart	(osTimerId_t timer_id,uint32_t ticks)
```
**描述：**

函数osTimerStart启动或重新启动指定参数timer_id的计时器。参数ticks指定计时器的计数值。

> **注意** :不能在中断服务调用该函数


**参数：**

|名字|描述|
|:--|:------| 
| timer_id | 由osTimerNew获得的计时器ID.  |
| ticks | 时间滴答计时器的值.  |

## 软件设计

## 软件设计

**主要代码分析**

在Timer_example函数中，通过osTimerNew()函数创建了回调函数为Timer1_Callback的定时器1，并通过osTimerStart()函数将该定时器设置为100个tick,因为hi3861默认10ms为一个tick,所以100个tick正好为1S钟，1S计时到后会触发Timer1_Callback()函数并打印日志。定时器2也同理为3S触发Timer2_Callback()函数并打印日志.

```c
void Timer_example (void) {
    osTimerId_t id1, id2;                         // timer id
    uint32_t    timerDelay;                       // timer value
    osStatus_t  status;                           // function return status

    // Create periodic timer
    exec1 = 1U;
    id1 = osTimerNew(Timer1_Callback, osTimerPeriodic, &exec1, NULL);
    if (id1 != NULL)  {
        timerDelay = 100U;                            // Hi3861 1U=10ms,100U=1S
        status = osTimerStart(id1, timerDelay);       // start timer
        if (status != osOK) {
        // Timer could not be started
        }
    }

    // Create periodic timer
    exec2 = 1U;
    id2 = osTimerNew(Timer2_Callback, osTimerPeriodic, &exec2, NULL);
    if (id2 != NULL)  {
        timerDelay = 300U;                            // Hi3861 1U=10ms,300U=3S
        status = osTimerStart(id2, timerDelay);       // start timer
        if (status != osOK) {
        // Timer could not be started
        }
    }
  
}

```

## 编译调试

### 修改 BUILD.gn 文件

修改 `applications\BearPi\BearPi-HM_Nano\sample`路径下 BUILD.gn 文件，指定 `timer_example` 参与编译。

```r
#"A1_kernal_thread:thread_example",
"A2_kernel_timer:timer_example",
#"A3_kernel_event:event_example",
#"A4_kernel_mutex:mutex_example",
#"A5_kernel_semaphore:semaphore_example",
#"A6_kernel_message:message_example",
```
    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，Timer1_Callback会1S打印一次数据，Timer2_Callback会3S打印一次数据。
```
This is BearPi Harmony Timer1_Callback!
This is BearPi Harmony Timer1_Callback!
This is BearPi Harmony Timer1_Callback!
This is BearPi Harmony Timer2_Callback!
This is BearPi Harmony Timer1_Callback!
This is BearPi Harmony Timer1_Callback!
This is BearPi Harmony Timer1_Callback!
This is BearPi Harmony Timer2_Callback!
```
