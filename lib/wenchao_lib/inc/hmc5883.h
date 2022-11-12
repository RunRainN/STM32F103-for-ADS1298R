/**
  ******************************************************************************
  * @file    hmc5883.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.10.1
  * @note    此程序为ARM中应用编程
  ******************************************************************************
  */
#ifndef __CH_HMC5883_H__
#define __CH_HMC5883_H__

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{		
    short hmc_date_x;
    short hmc_date_z;
    short hmc_date_y;
	
		short hmc_offset_x;
		short hmc_offset_y;
		short hmc_offset_z;
	
		float hmc_level_lastangle;
		float hmc_level_angle;      //北方为零度，北偏东为正，偏西为负，另：此角度为水平放置角度
		
	  float hmc_nlevel_x;
	  float hmc_nlevel_y;
	  float hmc_nlevel_angle;
} HMC_DATE;

#include "sysinc.h"


#define HMC_SlaveAddress  0x3c

/*HMC5883寄存器地址*/
#define	HMC_REGA  		0X00         	//配置寄存器A：默认值0x10，正常测量模式，不需要改动它
#define	HMC_REGB  		0X01					//配置寄存器B：主要配置增益，不需要改动它
#define	HMC_MODE  		0X02					//模式寄存器： 一般需要手动配置为0X00，连续测量模式
#define	HMC_XOUT_H  	0x03					//数据必须全部读取一遍，数据才会更新
#define	HMC_XOUT_L  	0x04
#define	HMC_ZOUT_H  	0x05
#define	HMC_ZOUT_L  	0x06
#define	HMC_YOUT_H  	0x07
#define	HMC_YOUT_L  	0x08
#define	HMC_STATUS  	0x09					//状态寄存器：7~2位：reserve 1位：数据锁存位，当六个数据都被读取后清除，否则置位锁存
#define	HMC_IDENA   	0x0A														//0位：数据就绪位，当数据全部更新就绪后置位
#define	HMC_IDENB   	0x0B
#define	HMC_IDENC   	0x0C

//API
void HMC5883_Init(void);
void HMC5883_offset(HMC_DATE *p);
void HMC5883_ByteWrite(uint8_t REG_Address,uint8_t REG_data);
u8   HMC5883_ByteRead_Single(uint8_t REG_Address);
void HMC5883_GetDate(HMC_DATE *p);
void HMC5883_GetLevel_Angle(HMC_DATE *p);

#endif







