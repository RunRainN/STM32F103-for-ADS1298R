/**
  ******************************************************************************
  * @file    i2c.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中IIC的底层编程
  ******************************************************************************
  */

#ifndef __CH_LIB_IIC_H__
#define __CH_LIB_IIC_H__
														
#ifdef __cplusplus
 extern "C" {
#endif
	
#include "sysinc.h"

//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=8<<24;}  //PB14
#define SDA_OUT() {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=3<<24;}  //PB14
//#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}  //PB11
//#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}  //PB11

//IO操作函数	 
#define IIC_SCL    PBout(13) //SCL
#define IIC_SDA    PBout(14) //SDA	 
#define READ_SDA   PBin(14)  //输入SDA 
//#define IIC_SCL    PBout(10) //SCL
//#define IIC_SDA    PBout(11) //SDA	 
//#define READ_SDA   PBin(11)  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

#endif
