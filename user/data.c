#include "data.h"
/**
  ******************************************************************************
  * @file           : data.c
  * @brief          : ��������
  * @details        : ����int24����תint32���롢ת���ɵ�ѹֵ�����ڷ���
  * @author         : RunRain CQU-BME-219 QQ:1121192423
  * @date           : 2022/11/11
  * @version        : V1.0
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2022/11/11
  *         ���ߣ�RunRain
  *         �޸ģ�
  * @endverbatim
  ******************************************************************************
  */


//ÿ��ͨ��int24����ת��int32����
void convert_data(u8 *source, int32_t *res)
{
	u8 i,j=0;
	for(i=3; i<27; i+=3)//ͨ��1~ͨ��8
	{
		if((source[i]&0x80)==0x80)res[j++] = ((int32_t)source[i]<<16 | (int32_t)source[i+1]<<8 | (int32_t)source[i+2]) | 0xFF000000;
		else res[j++] = (int32_t)source[i]<<16 | (int32_t)source[i+1]<<8 | (int32_t)source[i+2];
	}
}


//ת���ɵ�ѹֵ
void pack_data(int32_t *data, u8 *buf)
{
	u8 i;
	float LSB = 2400.0/8388607;	//2^23-1 = 8388607
	int16_t volt;
	for(i=0; i<8; i++)
	{
		volt = LSB*data[i]*10;//�ֱ���0.1mV
		buf[i*2] = volt>>8;
		buf[i*2+1] = volt;
	}
}


//���ڷ���ѡ��ͨ���ĵ�ѹֵ
//���磺ch=0b00001011=0x0B����ͨ��1��ͨ��2��ͨ��4
void uart_send_data(u8 *tx_buf, u8 ch)
{
	u8 i,j=0x01;
	for(i=0; i<8; i++)//�ж�ͨ��1~ͨ��8ѡ�����
	{
		if((ch&j)==j)
		{
			UART_WriteByte(HW_UART1, tx_buf[i*2]);//ÿ��ͨ��2���ֽ�
			UART_WriteByte(HW_UART1, tx_buf[i*2+1]);
		}
		j<<=1;
	}
	UART_WriteByte(HW_UART1, 0x0D);
	UART_WriteByte(HW_UART1, 0x0A);
}
