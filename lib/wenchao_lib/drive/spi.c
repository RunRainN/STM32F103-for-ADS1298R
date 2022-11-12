/**
  ******************************************************************************
  * @file    spi.c
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.09.03
  * @note    �˳���ΪARM��spi�ĵײ��̣������ڹٷ��ײ��Ķ��η�װ��
  ******************************************************************************
  */

#include "sysinc.h"




 /**
 * @brief    		SPI���ٳ�ʼ������
 * @code
 *      				// ��ʼ��Spi1,���е�ƽΪ�ߣ��ڶ�����Ϊ�Ͳɼ��źţ�������Ԥ��ƵֵΪ64��NSS�ź����������
 *       				SPI_QuickInit(Spi1, CPOL_HIGH_CPHA_0, SPI_BaudRatePrescaler_64, SPI_NSS_Soft);
 * @endcode
 * @param[in]   frameFormat ģ���
 *              @arg CPOL_HIGH_CPHA_1 	���Ըߣ���λ��
 *              @arg CPOL_HIGH_CPHA_2 	���Ըߣ���λ��
 *              @arg CPOL_LOW_CPHA_1 		���Եͣ���λ��
 *              @arg CPOL_LOW_CPHA_2 		���Եͣ���λ��
 * @param[in]   SPI_BaudRatePrescaler_x ��������Ԥ��Ƶֵ��x�Ŀ�ѡֵΪ2,4,8,16,32.....256
 * @param[in]   SPI_NSS_mode: NSS�źŹ���ģʽ
 *              @arg SPI_NSS_Soft				�������
 *              @arg SPI_NSS_Hard 			Ӳ������
 * @return			����0����ʼ������    1����ʼ����ȷ
 */
uint32_t SPI_QuickInit(uint32_t Spix, int frameFormat, uint32_t SPI_BaudRatePrescaler_x, int SPI_NSS_mode)
{
		
	  GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;
	
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   	  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	                         	//����SPI����ģʽ:����Ϊ��SPI
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                 	  //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
		SPI_InitStructure.SPI_NSS = SPI_NSS_mode;																//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_x;	  	//���岨����Ԥ��Ƶ��ֵ:������Ԥ��Ƶֵ
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;											//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
		SPI_InitStructure.SPI_CRCPolynomial = 7;																//CRCֵ����Ķ���ʽ
		switch(frameFormat)
		{
			case CPOL_HIGH_CPHA_1:   
				   SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	
	         SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	
			     break;
			case CPOL_HIGH_CPHA_2:   
				   SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	
	         SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	
			     break;
			case CPOL_LOW_CPHA_1:
				   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low ;	
	         SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	
			     break;
			case CPOL_LOW_CPHA_2:
				   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	
	         SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	
			     break;
			default :		break ;
		}
	
		 switch(Spix)
		{
			case Spi1:   
								RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );     
								RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1,  ENABLE );       
								GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(GPIOA, &GPIO_InitStructure);
			
								GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_13;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
								GPIO_Init(GPIOB, &GPIO_InitStructure);
								GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_3 | GPIO_Pin_7 | GPIO_Pin_13);
			
			          SPI_Init(SPI1, &SPI_InitStructure);
								SPI_Cmd(SPI1, ENABLE); 
								break;
			case Spi2:   
								RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );     
								RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );     
								GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(GPIOB, &GPIO_InitStructure);
			
                GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_4;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
								GPIO_Init(GPIOB, &GPIO_InitStructure);
			
								GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_12| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			
			          SPI_Init(SPI2, &SPI_InitStructure);
								SPI_Cmd(SPI2, ENABLE); 
								break;
			case Spi3:   
								RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );      
								RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI3 ,  ENABLE );     
								GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
								GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_Init(GPIOB, &GPIO_InitStructure);
			          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
								GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
								GPIO_Init(GPIOA, &GPIO_InitStructure);
								GPIO_SetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
								GPIO_SetBits(GPIOA,GPIO_Pin_14 | GPIO_Pin_15 );
			
			          SPI_Init(SPI3, &SPI_InitStructure);
								SPI_Cmd(SPI3, ENABLE); 
							  SPI_ReadWriteByte(SPI3 , 0xff);															//��������		 
								break;		
			default :		
								return 0;
		}		
		return 1;
}



 /**
 * @brief    		SPI���ô����ٶ�
 * @code
 *      				// ��ʼ��SPI1,������Ԥ��ƵֵΪ64
 *       				SPI_SetSpeed(SPI1,SPI_BaudRatePrescaler_64);
 * @endcode
 * @param[in]   SPIx : SPIģ��ѡ�񣬿�ѡֵ��SPI1��SPI2��SPI3
 * @param[in]   SPI_BaudRatePrescaler ��������Ԥ��Ƶֵ��x�Ŀ�ѡֵΪ2,4,8,16,32.....256
 */
void SPI_SetSpeed(SPI_TypeDef *SPIx ,u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPIx->CR1&=0XFFC7;
	SPIx->CR1|=SPI_BaudRatePrescaler;	
	SPI_Cmd(SPIx,ENABLE); 
} 


 /**
 * @brief    		SPI��дһ���ֽ�
 * @code
 *      				// ��ʼ��SPI1,д���Ϊa=0x13;
 *       				SPI_ReadWriteByte(SPI1 ,a);
 * @endcode
 * @param[in]   SPIx : SPIģ��ѡ�񣬿�ѡֵ��SPI1��SPI2��SPI3
 * @param[in]   TxData:Ҫд����ֽ�
 * @return			����ֵ:��ȡ�����ֽ�
 */
u8 SPI_ReadWriteByte(SPI_TypeDef *SPIx ,u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPIx, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPIx); //����ͨ��SPIx������յ�����					    
}



