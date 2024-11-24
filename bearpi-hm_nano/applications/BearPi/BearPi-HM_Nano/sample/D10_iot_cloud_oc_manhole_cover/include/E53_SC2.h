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

#ifndef __E53_SC2_H__
#define __E53_SC2_H__


typedef enum
{
	OFF = 0,
	ON
} E53_SC2_Status_ENUM;

/* E53_SC2传感器数据类型定义 ------------------------------------------------------------*/
typedef struct
{
    short   Temperature;     //温度
    short   Accel[3];
} E53_SC2_Data_TypeDef;

extern E53_SC2_Data_TypeDef E53_SC2_Data;
/* 类型定义 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/
#define MPU6050_GYRO_OUT            0x43  //MPU6050陀螺仪数据寄存器地址
#define MPU6050_ACC_OUT             0x3B  //MPU6050加速度数据寄存器地址
#define MPU6050_SLAVE_ADDRESS       0x68  //MPU6050器件读地址
#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_FF_THR           0x1D
#define MPU6050_RA_FF_DUR           0x1E
#define MPU6050_RA_MOT_THR          0x1F  //运动检测阀值设置寄存器
#define MPU6050_RA_MOT_DUR          0x20  //运动检测时间阀值
#define MPU6050_RA_ZRMOT_THR        0x21
#define MPU6050_RA_ZRMOT_DUR        0x22
#define MPU6050_RA_FIFO_EN          0x23
#define MPU6050_RA_INT_PIN_CFG      0x37   //中断/旁路设置寄存器
#define MPU6050_RA_INT_ENABLE       0x38   //中断使能寄存器
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_USER_CTRL        0x6A
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_WHO_AM_I         0x75

// /* 扩展变量 ------------------------------------------------------------------*/
// /* 函数声明 ------------------------------------------------------------------*/
// void MPU6050ReadTemp(short *tempData);
// void MPU6050ReadGyro(short *gyroData);
// void MPU6050ReadAcc(short *accData);
// void MPU6050_ReturnTemp(short*Temperature);
// void MPU6050_Init(void);
// uint8_t MPU6050ReadID(void);
// void PMU6050_ReadData(uint8_t reg_add,unsigned char*Read,uint8_t num);
// void PMU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat);

// void MPU6050_PWR_MGMT_1_INIT(void);

// void Motion_Interrupt(void);             //运动中断
// void Zero_Motion_Interrupt(void);        //静止中断
// void Free_Fall_Interrupt(void);        //自由落体中断

void E53_SC2_Init(void);
void E53_SC2_Read_Data(void);
void LED_D1_StatusSet(E53_SC2_Status_ENUM status);
void LED_D2_StatusSet(E53_SC2_Status_ENUM status);
// void Init_Light(void);

// void MX_I2C_MPU6050_Init(void);
// void I2C_MPU6050_WriteData( uint8_t Reg, uint8_t Value);
// uint8_t I2C_MPU6050_WriteBuffer( uint8_t Reg, uint8_t *pBuffer, uint16_t Length);
// uint8_t I2C_MPU6050_ReadData(uint8_t Reg);
// uint8_t I2C_MPU6050_ReadBuffer( uint8_t Reg,  uint8_t *pBuffer, uint16_t Length);


#endif 
