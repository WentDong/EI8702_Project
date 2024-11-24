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
 */
#ifndef __Flower_H__
#define __Flower_H__

/***************************************************************
* 名		称: Flower_Status_ENUM
* 说    明：枚举状态结构体
***************************************************************/
typedef enum
{
	CLOSE = 0,
	OPEN
} Flower_Status_ENUM;

/* Flower传感器数据类型定义 ------------------------------------------------------------*/
typedef struct
{
	float    Lux;				//光照强度
	float    Smo;				//土壤湿度
	float    Humidity;        	//湿度
	float    Temperature;     	//温度
} Flower_Data_TypeDef;

extern Flower_Data_TypeDef Flower_Data;

/* 寄存器宏定义 --------------------------------------------------------------------*/
#define SHT30_Addr 0x44
#define BH1750_Addr 0x23

void Flower_Init(void);
void Flower_Read_Data(void);
void LED_Light_StatusSet(Flower_Status_ENUM status);
void Motor_Flower_StatusSet(Flower_Status_ENUM status);
void Motor_Fan_StatusSet(Flower_Status_ENUM status);


#endif /* __Flower_H__ */

