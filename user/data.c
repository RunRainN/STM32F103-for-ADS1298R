#include "data.h"
/**
  ******************************************************************************
  * @file           : data.c
  * @brief          : 解析数据
  * @details        : 包含int24补码转int32补码、转换成电压值、串口发送
  * @author         : RunRain CQU-BME-219 QQ:1121192423
  * @date           : 2022/11/11
  * @version        : V1.0
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2022/11/11
  *         作者：RunRain
  *         修改：
  * @endverbatim
  ******************************************************************************
  */


//每个通道int24补码转成int32补码
void convert_data(u8 *source, int32_t *res)
{
	u8 i,j=0;
	for(i=3; i<27; i+=3)//通道1~通道8
	{
		if((source[i]&0x80)==0x80)res[j++] = ((int32_t)source[i]<<16 | (int32_t)source[i+1]<<8 | (int32_t)source[i+2]) | 0xFF000000;
		else res[j++] = (int32_t)source[i]<<16 | (int32_t)source[i+1]<<8 | (int32_t)source[i+2];
	}
}


//转换成电压值
void pack_data(int32_t *data, u8 *buf)
{
	u8 i;
	float LSB = 2400.0/8388607;	//2^23-1 = 8388607
	int16_t volt;
	for(i=0; i<8; i++)
	{
		volt = LSB*data[i]*10;//分辨率0.1mV
		buf[i*2] = volt>>8;
		buf[i*2+1] = volt;
	}
}


//串口发送选择通道的电压值
//例如：ch=0b00001011=0x0B代表通道1、通道2、通道4
void uart_send_data(u8 *tx_buf, u8 ch)
{
	u8 i,j=0x01;
	for(i=0; i<8; i++)//判断通道1~通道8选择情况
	{
		if((ch&j)==j)
		{
			UART_WriteByte(HW_UART1, tx_buf[i*2]);//每个通道2个字节
			UART_WriteByte(HW_UART1, tx_buf[i*2+1]);
		}
		j<<=1;
	}
	UART_WriteByte(HW_UART1, 0x0D);
	UART_WriteByte(HW_UART1, 0x0A);
}
