/**
  ******************************************************************************
  * @file    i2c.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    �˳���ΪARM��IIC�ĵײ���
  ******************************************************************************
  */

#ifndef __CH_LIB_IIC_H__
#define __CH_LIB_IIC_H__
														
#ifdef __cplusplus
 extern "C" {
#endif
	
#include "sysinc.h"

//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=8<<24;}  //PB14
#define SDA_OUT() {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=3<<24;}  //PB14
//#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}  //PB11
//#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}  //PB11

//IO��������	 
#define IIC_SCL    PBout(13) //SCL
#define IIC_SDA    PBout(14) //SDA	 
#define READ_SDA   PBin(14)  //����SDA 
//#define IIC_SCL    PBout(10) //SCL
//#define IIC_SDA    PBout(11) //SDA	 
//#define READ_SDA   PBin(11)  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

#endif
