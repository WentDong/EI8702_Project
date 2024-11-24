# BearPi-HM_Nano开发板HarmonyOS内核编程开发——信号量
本示例将演示如何在BearPi-HM_Nano开发板上使用cmsis 2.0 接口通过信号量同时从不同的线程访问共享资源

![BearPi-HM_Nano](/applications/BearPi/BearPi-HM_Nano/docs/figures/00_public/BearPi-HM_Nano.png)
## Semaphore API分析

## osSemaphoreNew()

```c
osSemaphoreId_t osSemaphoreNew(uint32_t max_count,uint32_t initial_count,const osSemaphoreAttr_t *attr)
```
**描述：**

函数osMessageQueueNew创建并初始化一个消息队列对象。该函数返回消息队列对象标识符，如果出现错误则返回NULL，可以在RTOS启动(调用 osKernelStart)之前安全地调用该函数，也可以在内核初始化 (调用 osKernelInitialize)之前调用该函数。
> **注意** :不能在中断服务调用该函数


**参数：**

|名字|描述|
|:--|:------| 
| max_count |可用令牌的最大数量.  |
| initial_count |可用令牌的初始数量.  |
| attr |信号量的属性;空:默认值.  |

## osSemaphoreRelease()

```c
osStatus_t osSemaphoreRelease(osSemaphoreId_t semaphore_id)
```
**描述：**
函数osSemaphoreRelease释放由参数semaphore_id指定的信号量对象的标记

> **注意** :该函数可以在中断服务例程调用


**参数：**

|名字|描述|
|:--|:------| 
| semaphore_id | 由osSemaphoreNew获得的信号量ID.  |


## osSemaphoreAcquire()

```c
osStatus_t osSemaphoreAcquire(osSemaphoreId_t semaphore_id,uint32_t timeout)	
```
**描述：**
阻塞函数osSemaphoreAcquire一直等待，直到由参数semaphore_id指定的信号量对象的标记可用为止。如果一个令牌可用，该函数立即返回并递减令牌计数。

> **注意** :如果参数timeout设置为0，可以从中断服务例程调用。


**参数：**

|名字|描述|
|:--|:------| 
| semaphore_id | 由osSemaphoreNew获得的信号量ID.  |
| timeout | 超时值.  |


## 软件设计

**主要代码分析**

在Semaphore_example函数中，通过osSemaphoreNew()函数创建了sem1信号量，Thread_Semaphore1()函数中通过osSemaphoreRelease()函数释放两个信号量，Thread_Semaphore2()和Thread_Semaphore3()函数中，先开始阻塞等待sem1信号量。只有当Thread_Semaphore1()函数中增加两次信号量，Thread_Semaphore2()和Thread_Semaphore3()才能继续同步运行。若Thread_Semaphore1()函数中只增加一次信号量，那Thread_Semaphore2()和Thread_Semaphore3()只能轮流执行。
```c
void Thread_Semaphore1(void)
{
    while(1)
	{
		osSemaphoreRelease(sem1);  //释放两次sem1信号量，使得Thread_Semaphore2和Thread_Semaphore3能同步执行
        osSemaphoreRelease(sem1);  //此处若只释放一次信号量，则Thread_Semaphore2和Thread_Semaphore3会交替运行。
        printf("Thread_Semaphore1 Release  Semap \n");
        osDelay(100);
	}

}
void Thread_Semaphore2(void)
{    
    while(1)
	{
		osSemaphoreAcquire(sem1,osWaitForever);//申请sem1信号量
        printf("Thread_Semaphore2 get Semap \n");
        osDelay(1);
	}
}

void Thread_Semaphore3(void)
{    
    while(1)
	{
		osSemaphoreAcquire(sem1,osWaitForever);//等待sem1信号量
        printf("Thread_Semaphore3 get Semap \n");
        osDelay(1);
	}
}

void Semaphore_example (void)
{ 
    osThreadAttr_t attr;  

    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 1024*4;
    attr.priority = 24;
    
    attr.name = "Thread_Semaphore1";
    if (osThreadNew((osThreadFunc_t)Thread_Semaphore1, NULL, &attr) == NULL) 
    {
        printf("Falied to create Thread_Semaphore1!\n");
    }
    attr.name = "Thread_Semaphore2";
    if (osThreadNew((osThreadFunc_t)Thread_Semaphore2, NULL, &attr) == NULL) 
    {
        printf("Falied to create Thread_Semaphore2!\n");
    }
    attr.name = "Thread_Semaphore3";
    if (osThreadNew((osThreadFunc_t)Thread_Semaphore3, NULL, &attr) == NULL) 
    {
        printf("Falied to create Thread_Semaphore3!\n");
    }
    sem1=osSemaphoreNew(4, 0, NULL);  
    if (sem1 == NULL) 
    {
        printf("Falied to create Semaphore1!\n");
    }
}
```

## 编译调试

### 修改 BUILD.gn 文件

修改 `applications\BearPi\BearPi-HM_Nano\sample`路径下 BUILD.gn 文件，指定 `semp_example` 参与编译。

```r
#"A1_kernal_thread:thread_example",
#"A2_kernel_timer:timer_example",
#"A3_kernel_event:event_example",
#"A4_kernel_mutex:mutex_example",
"A5_kernel_semaphore:semaphore_example",
#"A6_kernel_message:message_example",
```
    


### 运行结果<a name="section18115713118"></a>

示例代码编译烧录代码后，按下开发板的RESET按键，通过串口助手查看日志，Thread_Semaphore1一次释放两个信号量，Thread_Semaphore2和Thread_Semaphore3同步执行。
```
Thread_Semaphore1 Release  Semap 
Thread_Semaphore2 get Semap 
Thread_Semaphore3 get Semap 
Thread_Semaphore1 Release  Semap 
Thread_Semaphore2 get Semap 
Thread_Semaphore3 get Semap 
Thread_Semaphore1 Release  Semap 
Thread_Semaphore2 get Semap 
Thread_Semaphore3 get Semap 
```
