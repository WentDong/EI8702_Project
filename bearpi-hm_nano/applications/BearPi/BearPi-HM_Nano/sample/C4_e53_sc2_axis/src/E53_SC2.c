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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "cmsis_os2.h"
#include "E53_SC2.h"
#include "wifiiot_errno.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_i2c.h"
#include "wifiiot_i2c_ex.h"


/***************************************************************
* 函数名称: E53_SC2_IO_Init
* 说    明: E53_SC2_GPIO初始化
* 参    数: 无
* 返 回 值: 无
***************************************************************/
static void E53_SC2_IO_Init(void)
{
    GpioInit();
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_7, WIFI_IOT_IO_FUNC_GPIO_7_GPIO);//设置GPIO_7的复用功能为普通GPIO
    GpioSetDir(WIFI_IOT_IO_NAME_GPIO_7, WIFI_IOT_GPIO_DIR_OUT);//设置GPIO_7为输出模式
    
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_8, WIFI_IOT_IO_FUNC_GPIO_8_GPIO);//设置GPIO_8的复用功能为普通GPIO
    GpioSetDir(WIFI_IOT_IO_NAME_GPIO_8, WIFI_IOT_GPIO_DIR_OUT);//设置GPIO_8为输出模式

    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_0, WIFI_IOT_IO_FUNC_GPIO_0_I2C1_SDA);   // GPIO_0复用为I2C1_SDA
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_1, WIFI_IOT_IO_FUNC_GPIO_1_I2C1_SCL);   // GPIO_1复用为I2C1_SCL
    I2cInit(WIFI_IOT_I2C_IDX_1, 400000); /* baudrate: 400kbps */
    I2cSetBaudrate(WIFI_IOT_I2C_IDX_1, 400000);
    
}
/***************************************************************
  * 函数功能: 通过I2C写入一个值到指定寄存器内
  * 输入参数: Addr：I2C设备地址
  *           Reg：目标寄存器
  *           Value：值
  * 返 回 值: 无
  * 说    明: 无
  **************************************************************/
void I2C_MPU6050_WriteData( uint8_t Reg, uint8_t Value)
{
  
    WifiIotI2cData mpu6050_i2c_data = { 0 };
    uint8_t send_data[2] = { Reg,Value };
    mpu6050_i2c_data.sendBuf = send_data;
    mpu6050_i2c_data.sendLen = 2;
    I2cWrite(WIFI_IOT_I2C_IDX_1,(MPU6050_SLAVE_ADDRESS<<1)|0x00,&mpu6050_i2c_data); 

}
/***************************************************************
  * 函数功能: 通过I2C写入一段数据到指定寄存器内
  * 输入参数: Addr：I2C设备地址
  *           Reg：目标寄存器
  *           RegSize：寄存器尺寸(8位或者16位)
  *           pBuffer：缓冲区指针
  *           Length：缓冲区长度
  * 返 回 值: HAL_StatusTypeDef：操作结果
  * 说    明: 在循环调用是需加一定延时时间
  **************************************************************/
uint8_t I2C_MPU6050_WriteBuffer(uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
 
    uint32_t status = 0;
    WifiIotI2cData mpu6050_i2c_data = {0};
    uint8_t send_data[256] = {0};

    send_data[0] = Reg;
    for (int j = 0; j < Length; j++)
    {
        send_data[j+1] = pBuffer[j];
    }
    mpu6050_i2c_data.sendBuf = send_data;
    mpu6050_i2c_data.sendLen = Length+1;

    status = I2cWrite(WIFI_IOT_I2C_IDX_1, (MPU6050_SLAVE_ADDRESS<<1)|0x00, &mpu6050_i2c_data);
    if (status != 0)
    {
        printf("===== Error: I2C write status1 = 0x%x! =====\r\n", status);
        return status;
    }
  
    return 0;
}
/***************************************************************
  * 函数功能: 通过I2C读取一个指定寄存器内容
  * 输入参数: Addr：I2C设备地址
  *           Reg：目标寄存器
  * 返 回 值: uint8_t：寄存器内容
  * 说    明: 无
  **************************************************************/
uint8_t I2C_MPU6050_ReadData(uint8_t Reg)
{
    uint8_t value = 0;
    uint32_t status = 0;
    WifiIotI2cData mpu6050_i2c_data = {0};
    uint8_t  buffer[1] = {Reg};
    mpu6050_i2c_data.sendBuf = buffer;
    mpu6050_i2c_data.sendLen = 1;
    mpu6050_i2c_data.receiveBuf = &value;
    mpu6050_i2c_data.receiveLen = 1;
    status = I2cWriteread(WIFI_IOT_I2C_IDX_1, (MPU6050_SLAVE_ADDRESS<<1)|0x00, &mpu6050_i2c_data);
    if (status != 0)
    {
        printf("===== Error: I2C write status = 0x%x! =====\r\n", status);
        return status;
    }
    return value;
}

/***************************************************************
  * 函数功能: 通过I2C读取一段寄存器内容存放到指定的缓冲区内
  * 输入参数: Addr：I2C设备地址
  *           Reg：目标寄存器
  *           RegSize：寄存器尺寸(8位或者16位)
  *           pBuffer：缓冲区指针
  *           Length：缓冲区长度
  * 返 回 值: HAL_StatusTypeDef：操作结果
  * 说    明: 无
  **************************************************************/
uint8_t I2C_MPU6050_ReadBuffer(uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
  
    uint32_t status = 0;
    WifiIotI2cData mpu6050_i2c_data = {0};
    uint8_t  buffer[1] = {Reg};
    mpu6050_i2c_data.sendBuf = buffer;
    mpu6050_i2c_data.sendLen = 1;
    mpu6050_i2c_data.receiveBuf = pBuffer;
    mpu6050_i2c_data.receiveLen = Length;
    status = I2cWriteread(WIFI_IOT_I2C_IDX_1, (MPU6050_SLAVE_ADDRESS<<1)|0x00, &mpu6050_i2c_data);
    if (status != 0)
    {
        printf("===== Error: I2C write status = 0x%x! =====\r\n", status);
        return status;
    }
    return 0;  
}
/***************************************************************
  * 函数功能: 写数据到MPU6050寄存器
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  ***************************************************************/
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat)
{
  I2C_MPU6050_WriteData(reg_add,reg_dat);
}

/***************************************************************
  * 函数功能: 从MPU6050寄存器读取数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
***************************************************************/ 
void MPU6050_ReadData(uint8_t reg_add,unsigned char *Read,uint8_t num)
{
  I2C_MPU6050_ReadBuffer(reg_add,Read,num);
}

/***************************************************************
  * 函数功能: 读取MPU6050的加速度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
***************************************************************/ 
void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

/***************************************************************
  * 函数功能: 读取MPU6050的角速度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
 ***************************************************************/ 
void MPU6050ReadGyro(short *gyroData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

/***************************************************************
  * 函数功能: 读取MPU6050的原始温度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  ***************************************************************/
void MPU6050ReadTemp(short *tempData)
{
	  uint8_t buf[2];
    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
    *tempData = (buf[0] << 8) | buf[1];
}

/***************************************************************
  * 函数功能: 读取MPU6050的温度数据，转化成摄氏度
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  **************************************************************/ 
void MPU6050_ReturnTemp(short*Temperature)
{
	short temp3;
	uint8_t buf[2];
	
	MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
	temp3= (buf[0] << 8) | buf[1];
	*Temperature=(((double) (temp3 + 13200)) / 280)-13;
}

/***************************************************************
  * 函数功能: 自由落体中断
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  **************************************************************/
void Free_Fall_Interrupt(void)          //自由落体中断
{
    MPU6050_WriteReg(MPU6050_RA_FF_THR,0x01);             //自由落体阈值
    MPU6050_WriteReg(MPU6050_RA_FF_DUR,0x01);             //自由落体检测时间20ms 单位1ms 寄存器0X20
}
void Motion_Interrupt(void)             //运动中断
{
    MPU6050_WriteReg(MPU6050_RA_MOT_THR,0x03);            //运动阈值
    MPU6050_WriteReg(MPU6050_RA_MOT_DUR,0x14);            //检测时间20ms 单位1ms 寄存器0X20
}
void Zero_Motion_Interrupt(void)        //静止中断
{
    MPU6050_WriteReg(MPU6050_RA_ZRMOT_THR,0x20);          //静止阈值
    MPU6050_WriteReg(MPU6050_RA_ZRMOT_DUR,0x20);          //静止检测时间20ms 单位1ms 寄存器0X20
}

/***************************************************************
  * 函数功能: 初始化MPU6050芯片
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  ***************************************************************/ 
void MPU6050_Init(void)
{
  int i=0,j=0;
  //在初始化之前要延时一段时间，若没有延时，则断电后再上电数据可能会出错
  for(i=0;i<1000;i++)
  {
    for(j=0;j<1000;j++)
    {
      ;
    }
  }
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1,0X80);       //复位MPU6050
	usleep(20000);
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1,0X00);       //唤醒MPU6050
	MPU6050_WriteReg(MPU6050_RA_INT_ENABLE,0X00);       //关闭所有中断
	MPU6050_WriteReg(MPU6050_RA_USER_CTRL,0X00);        //I2C主模式关闭
	MPU6050_WriteReg(MPU6050_RA_FIFO_EN,0X00);          //关闭FIFO
	MPU6050_WriteReg(MPU6050_RA_INT_PIN_CFG,0X80);      //中断的逻辑电平模式,设置为0，中断信号为高电；设置为1，中断信号为低电平时。
	Motion_Interrupt();           					    //运动中断
	MPU6050_WriteReg(MPU6050_RA_CONFIG,0x04);           //配置外部引脚采样和DLPF数字低通滤波器
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG,0x1C);     //加速度传感器量程和高通滤波器配置
	MPU6050_WriteReg(MPU6050_RA_INT_PIN_CFG,0X1C);      //INT引脚低电平平时
	MPU6050_WriteReg(MPU6050_RA_INT_ENABLE,0x40);       //中断使能寄存器
}

/***************************************************************
  * 函数功能: 读取MPU6050的ID
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  ***************************************************************/ 
uint8_t MPU6050ReadID(void)
{
	unsigned char Re = 0;
	MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //读器件地址
	if(Re != 0x68)
	{
		printf("MPU6050 dectected error!\r\n");
		return 0;
	}
	else
	{
		return 1;
	}
}
/***************************************************************
* 函数名称: Init_E53_SC2
* 说    明: 初始化Init_E53_SC2
* 参    数: 无
* 返 回 值: 无
***************************************************************/
void E53_SC2_Init(void)
{
    E53_SC2_IO_Init();
    MPU6050_Init();
    osDelay(100);
}
/***************************************************************
* 函数名称: E53_SC2_Read_Data
* 说    明: 读取数据
* 参    数: 无
* 返 回 值: 无
***************************************************************/
void E53_SC2_Read_Data(void)
{
	short  Accel[3];
	short  Temp;
	if (MPU6050ReadID() == 0)
	{	
	  while(1);
  }
  MPU6050ReadAcc(Accel);			
  MPU6050_ReturnTemp(&Temp);
  E53_SC2_Data.Temperature = Temp;
  E53_SC2_Data.Accel[0] = Accel[0];
  E53_SC2_Data.Accel[1] = Accel[1];
  E53_SC2_Data.Accel[2] = Accel[2];
  usleep(50000);
}
/***************************************************************
* 函数名称: LED_D1_StatusSet
* 说    明: LED_D1状态设置
* 参    数: status,ENUM枚举的数据
*									OFF,关
*									ON,开
* 返 回 值: 无
***************************************************************/
void LED_D1_StatusSet(E53_SC2_Status_ENUM status)
{
	if(status == ON)
		GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_7, 1);//设置GPIO_7输出高电平点亮灯
	if(status == OFF)
		GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_7, 0);//设置GPIO_7输出低电平关闭灯
}

/***************************************************************
* 函数名称: LED_D2_StatusSet
* 说    明: LED_D2状态设置
* 参    数: status,ENUM枚举的数据
*									OFF,关
*									ON,开
* 返 回 值: 无
***************************************************************/
void LED_D2_StatusSet(E53_SC2_Status_ENUM status)
{
	if(status == ON)
		GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_8, 1);//设置GPIO_8输出高电平点亮灯
	if(status == OFF)
		GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_8, 0);//设置GPIO_8输出低电平关闭灯
}
