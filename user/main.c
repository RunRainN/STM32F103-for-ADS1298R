#include "sysinc.h"
#include "data.h"
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Ӳ����ʼ��������������ѯ��ʽ��ȡADS1298R����
  * @details        : ϵͳʱ�ӡ�GPIO��SPI��ADS1298R��NVIC��UART��ʼ��
  * @author         : RunRain CQU-BME-219 QQ:1121192423
  * @date           : 2022/11/11
  * @version        : V1.0
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * PC13����LED��Ӳ����ʼ���ɹ�������ADS1298R��ʼ��ʧ����˸
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2022/11/11
  *         ���ߣ�RunRain
  *         �޸ģ�
  * @endverbatim
  ******************************************************************************
  */
	
//u8 USART1_RX_BUF[100];     //���ջ���,���100���ֽ�.
//u16 USART1_RX_STA=0;       //����״̬���
//u8 USART1_TX_BUF[100];     //���ͻ���,���100���ֽ�.

u8 ADS1298R_Values[27];   /* �洢ԭʼ���ݣ�״̬�ֹ�3���ֽڣ�8��ͨ����3���ֽ�*/
int32_t ch_data[8];   /* 8��ͨ����int32���� */
u8 tx_buf[18];		/* ���ڷ��ͻ�������8��ͨ����2���ֽڣ�������־2���ֽ� */

//void uart1(uint16_t Res)
//{		
//			if((USART1_RX_STA&0x8000)==0)//����δ���
//		{
//			if(USART1_RX_STA&0x4000)//���յ���0X0D
//			{
//				if(Res!=0X0A)USART1_RX_STA=0;//���մ���,���¿�ʼ
//				else 
//				{
//					USART1_RX_STA|=0x8000;	//��������� 
//				}
//			}
//			else //��û�յ�0X0D
//			{	
//				if(Res==0X0D)USART1_RX_STA|=0x4000;
//				else
//					{
//						USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res;
//						USART1_RX_STA++;
//						if(USART1_RX_STA>99)USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
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
		uart_send_data(tx_buf, 0x0B);//ch1��ch2��ch4
	}
}

