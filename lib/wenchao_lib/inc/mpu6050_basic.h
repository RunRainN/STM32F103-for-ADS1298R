/**
  ******************************************************************************
  * @file    mpu6050_basic.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.9.11
  * @note    此程序为ARM的底层编程
  ******************************************************************************
  */
#ifndef __CH_LIB_MPU6050_BASIC_H__
#define __CH_LIB_MPU6050_BASIC_H__

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{		
    short acc[3];							//x,y,z
    short gyr[3];
    short tmp;
		

    short acc_offset[3];		 //零漂
    short gyr_offset[3];
    short tmp_offset;
	
    float acc_gain[3];			 //比例 
    float gyr_gain[3];
    float tmp_gain;
	
		float angle_acc_x;
		float angle_acc_y;
		float angle_acc_z;
	
		float w_gyr_x;
		float w_gyr_y;
		float w_gyr_z;
} ACGY;

//typedef struct ACGY    MPU_DATE ;																		


#include "sysinc.h"



//寄存器
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG_				0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据


//API
u8 MPU6050_Check(void);
void MPU6050_ByteWrite(uint8_t REG_Address,uint8_t REG_data);
uint8_t MPU6050_ByteRead(uint8_t REG_Address);

void MPU6050_Init(void);

void MPU6050_Offset(ACGY *ag);
void MPU6050_GetData(ACGY *ag);
void MPU6050_Acc_Angle(ACGY *ag);
void MPU6050_Gyr_W(ACGY *ag);

#endif

