/**
  ******************************************************************************
  * @file           : ads1298r.h
  * @brief          : ADS1298R驱动头文件
  * @details        : 包含ADS1298R的操作码和寄存器地址
  * @author         : RunRain CQU-BME-219 QQ:1121192423
  * @date           : 2022/11/10
  * @version        : V1.0
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2022/11/10
  *         作者：RunRain
  *         修改：添加ADS1298R的操作码和寄存器地址
  * @endverbatim
  ******************************************************************************
  */

#ifndef __ADS1298R_H
#define __ADS1298R_H	  

#include "sysinc.h"

//操作码
#define _WAKEUP 	0x02 // Wake-up from standby mode
#define _STANDBY 	0x04 // Enter Standby mode
#define _RESET 		0x06 // Reset the device registers to default
#define _START 		0x08 // Start and restart (synchronize) conversions
#define _STOP 		0x0A // Stop conversion
#define _RDATAC 	0x10 // Enable Read Data Continuous mode (default mode at power-up)
#define _SDATAC 	0x11 // Stop Read Data Continuous mode
#define _RDATA 		0x12 // Read data by command; supports multiple read back
#define _RREG 		0x20 // Read register, last 5 bits for register address
#define _WREG 		0x40 // Write register, last 5 bits for register address

//寄存器地址
#define ID 0x00
#define CONFIG1 0x01
#define CONFIG2 0x02
#define CONFIG3 0x03
#define LOFF 0x04
#define CH1SET 0x05
#define CH2SET 0x06
#define CH3SET 0x07
#define CH4SET 0x08
#define CH5SET 0x09
#define CH6SET 0x0A
#define CH7SET 0x0B
#define CH8SET 0x0C
#define RLD_SENSP 0x0D
#define RLD_SENSN 0x0E
#define LOFF_SENSP 0x0F
#define LOFF_SENSN 0x10
#define LOFF_FLIP 0x11
#define LOFF_STATP 0x12
#define LOFF_STATN 0x13
#define GPIO 0x14
#define PACE 0x15
#define RESP 0x16
#define CONFIG4 0x17
#define WCT1 0x18
#define WCT2 0x19

#define ADS1298R_CS        PAout(1)
#define ADS1298R_START     PAout(2)
#define ADS1298R_RESET     PAout(3)
#define ADS1298R_DRDY      PAin(4)

void ADS1298R_Init(void);
void ADS1298R_GetValues(u8 *buf);
void ADS1298R_GPIOInit(void);
u8 ads1298R_SendCmd(u8 cmd);
u8 ADS1298R_RWReg(u8 rw, u8 reg, u8 data);
void ADS1298R_RWRegs(u8 rw, u8 reg, u8 size, u8 *ch);
  
#endif



