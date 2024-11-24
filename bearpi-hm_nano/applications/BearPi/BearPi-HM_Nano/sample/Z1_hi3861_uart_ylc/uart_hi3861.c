/*
 * Copyright (c) 2020 Nanjing Xiaoxiongpai Intelligent Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Date : 2022-04-29
 * Author : ylc
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "hi_uart.h"
#include "hi_io.h"

#define UART_BUFF_SIZE 1024     //接收缓冲大小
#define UART_TIMEOUT_MS 20      //接收超时时间

//向外提供的发送接口
void uart1_send(uint8_t *buf,uint16_t len)
{
    hi_uart_write(HI_UART_IDX_1, (unsigned char *)buf, len);
}
//接收处理函数
void uart1_rxproc(uint8_t *buf,uint16_t len)
{
    uart1_send((unsigned char *)buf, len);
    printf("Uart1 read data len:%d\r\n", len);
}


//串口接收，无数据时阻塞，有数据时收完一帧或者收到最大值返回
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

void uart_recv_task(void)
{
    uint8_t uart_buff[UART_BUFF_SIZE] = {0};
    uint8_t *uart_buff_ptr = uart_buff;
    uint32_t ret;
    uint16_t rxlen;

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
    printf("UART Test Start\n");

    while (1)
    {
        //阻塞等待串口1数据
        rxlen=uart1_recv(uart_buff_ptr, UART_BUFF_SIZE);        
        //处理数据
        uart1_rxproc(uart_buff_ptr,rxlen);
        osDelay(2);
    }
}

static void UART_ExampleEntry(void)
{

    osThreadAttr_t attr;

    attr.name = "UART_Task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 2048;
    attr.priority = 15;

    if (osThreadNew((osThreadFunc_t)uart_recv_task, NULL, &attr) == NULL)
    {
        printf("[Uart Example2] Falied to create UART_Task!\n");
    }
}

APP_FEATURE_INIT(UART_ExampleEntry);