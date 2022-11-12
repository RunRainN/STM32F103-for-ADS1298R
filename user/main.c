#include "sysinc.h"
#include "data.h"
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 硬件初始化，主函数以轮询方式读取ADS1298R数据
  * @details        : 系统时钟、GPIO、SPI、ADS1298R、NVIC、UART初始化
  * @author         : RunRain CQU-BME-219 QQ:1121192423
  * @date           : 2022/11/11
  * @version        : V1.0
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * PC13控制LED，硬件初始化成功常亮，ADS1298R初始化失败闪烁
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2022/11/11
  *         作者：RunRain
  *         修改：
  * @endverbatim
  ******************************************************************************
  */
	
//u8 USART1_RX_BUF[100];     //接收缓冲,最大100个字节.
//u16 USART1_RX_STA=0;       //接收状态标记
//u8 USART1_TX_BUF[100];     //发送缓冲,最大100个字节.

u8 ADS1298R_Values[27];   /* 存储原始数据：状态字共3个字节，8个通道各3个字节*/
int32_t ch_data[8];   /* 8个通道的int32补码 */
u8 tx_buf[18];		/* 串口发送缓冲区：8个通道各2个字节，结束标志2个字节 */

//void uart1(uint16_t Res)
//{		
//			if((USART1_RX_STA&0x8000)==0)//接收未完成
//		{
//			if(USART1_RX_STA&0x4000)//接收到了0X0D
//			{
//				if(Res!=0X0A)USART1_RX_STA=0;//接收错误,重新开始
//				else 
//				{
//					USART1_RX_STA|=0x8000;	//接收完成了 
//				}
//			}
//			else //还没收到0X0D
//			{	
//				if(Res==0X0D)USART1_RX_STA|=0x4000;
//				else
//					{
//						USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res;
//						USART1_RX_STA++;
//						if(USART1_RX_STA>99)USART1_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
//			}
//		}  
//}


int main(void)
{
	SYSTICK_DelayInit();
	GPIO_QuickInit(HW_GPIOC, GPIO_Pin_13, GPIO_Mode_Out_PP);
	SPI_QuickInit(Spi1, CPOL_LOW_CPHA_2, SPI_BaudRatePrescaler_256, SPI_NSS_Soft);
	ADS1298R_Init();
	NVIC_init();
	UART_QuickInit(HW_UART1, 115200, 2, 2, ENABLE);
	//UART_CallbackInstall(HW_UART1, uart1);
	PCout(13) = 0;
	while(1)
	{	
		ADS1298R_GetValues(ADS1298R_Values);
		convert_data(ADS1298R_Values, ch_data);
		pack_data(ch_data, tx_buf);
		uart_send_data(tx_buf, 0x0B);//ch1、ch2、ch4
	}
}

