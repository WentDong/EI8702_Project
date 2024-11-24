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
#include "wifiiot_flash.h"

//flash地址0x400000 - 0x600000

char *str="内部闪存读写测试 Hello, BearPi!";


void in_flash_read(uint32_t addr,uint8_t *buf,uint16_t len)
{
    FlashRead(addr-0x400000,len,(uint8_t*)buf);
}
void in_flash_write(uint32_t addr,uint8_t *buf,uint16_t len)
{
    //参数1是flash偏移量
    FlashWrite(addr-0x400000,len,(uint8_t*)buf,1);
}

/**************测试flash读写**************/
static void in_flash_test(void)
{
    uint8_t buf[200]={0};
    osDelay(100);
    in_flash_write(0x600000-200,(uint8_t*)str,strlen(str)+1);
    in_flash_read(0x600000-200,(uint8_t*)buf,200);
    printf("%s",buf);
}


APP_FEATURE_INIT(in_flash_test);