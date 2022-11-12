/**
  ******************************************************************************
  * @file    hmc5883.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.10.1
  * @note    �˳���ΪARM��Ӧ�ñ��
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
		float hmc_level_angle;      //����Ϊ��ȣ���ƫ��Ϊ����ƫ��Ϊ�������˽Ƕ�Ϊˮƽ���ýǶ�
		
	  float hmc_nlevel_x;
	  float hmc_nlevel_y;
	  float hmc_nlevel_angle;
} HMC_DATE;

#include "sysinc.h"


#define HMC_SlaveAddress  0x3c

/*HMC5883�Ĵ�����ַ*/
#define	HMC_REGA  		0X00         	//���üĴ���A��Ĭ��ֵ0x10����������ģʽ������Ҫ�Ķ���
#define	HMC_REGB  		0X01					//���üĴ���B����Ҫ�������棬����Ҫ�Ķ���
#define	HMC_MODE  		0X02					//ģʽ�Ĵ����� һ����Ҫ�ֶ�����Ϊ0X00����������ģʽ
#define	HMC_XOUT_H  	0x03					//���ݱ���ȫ����ȡһ�飬���ݲŻ����
#define	HMC_XOUT_L  	0x04
#define	HMC_ZOUT_H  	0x05
#define	HMC_ZOUT_L  	0x06
#define	HMC_YOUT_H  	0x07
#define	HMC_YOUT_L  	0x08
#define	HMC_STATUS  	0x09					//״̬�Ĵ�����7~2λ��reserve 1λ����������λ�����������ݶ�����ȡ�������������λ����
#define	HMC_IDENA   	0x0A														//0λ�����ݾ���λ��������ȫ�����¾�������λ
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







