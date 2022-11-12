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

//IO方向设置
#define DHT11_IO_IN()  {GPIO_QuickInit( gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ, GPIO_Mode_IPU); }
#define DHT11_IO_OUT() {GPIO_QuickInit( gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ, GPIO_Mode_Out_PP); }
////IO操作函数											   
#define	DHT11_DQ_OUT(x)  GPIO_Writebit(gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ, x )
#define	DHT11_DQ_IN  		 GPIO_ReadBit(gpiozwc_DHT11.HW_GPIOx_DQ, gpiozwc_DHT11.GPIO_Pin_x_DQ)


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif















