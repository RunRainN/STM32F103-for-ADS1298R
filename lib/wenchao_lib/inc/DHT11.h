#ifndef __DHT11_H
#define __DHT11_H 
#include "sysinc.h"

typedef struct
{		  
	uint16_t HW_GPIOx_DQ;
	uint16_t GPIO_Pin_x_DQ;
} GPIOZWC_DHT11;

static GPIOZWC_DHT11 gpiozwc_DHT11 = {
	HW_GPIOA, GPIO_Pin_12
};

//IO��������
#define DHT11_IO_IN()  {GPIO_QuickInit( gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ, GPIO_Mode_IPU); }
#define DHT11_IO_OUT() {GPIO_QuickInit( gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ, GPIO_Mode_Out_PP); }
////IO��������											   
#define	DHT11_DQ_OUT(x)  GPIO_Writebit(gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ, x )
#define	DHT11_DQ_IN  		 GPIO_ReadBit(gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ)


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif















