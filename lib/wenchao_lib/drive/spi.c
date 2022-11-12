/**
  ******************************************************************************
  * @file    spi.c
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.09.03
  * @note    此程序为ARM中spi的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */

#include "sysinc.h"




 /**
 * @brief    		SPI快速初始化程序
 * @code
 *      				// 初始化Spi1,空闲电平为高，第二边沿为低采集信号，波特率预分频值为64，NSS信号由软件管理
 *       				SPI_QuickInit(Spi1, CPOL_HIGH_CPHA_0, SPI_BaudRatePrescaler_64, SPI_NSS_Soft);
 * @endcode
 * @param[in]   frameFormat 模块号
 *              @arg CPOL_HIGH_CPHA_1 	极性高，相位低
 *              @arg CPOL_HIGH_CPHA_2 	极性高，相位高
 *              @arg CPOL_LOW_CPHA_1 		极性低，相位低
 *              @arg CPOL_LOW_CPHA_2 		极性低，相位高
 * @param[in]   SPI_BaudRatePrescaler_x ：波特率预分频值，x的可选值为2,4,8,16,32.....256
 * @param[in]   SPI_NSS_mode: NSS信号管理模式
 *              @arg SPI_NSS_Soft				软件管理
 *              @arg SPI_NSS_Hard 			硬件管理
 * @return			返回0：初始化错误    1：初始化正确
 */
uint32_t SPI_QuickInit(uint32_t Spix, int frameFormat, uint32_t SPI_BaudRatePrescaler_x, int SPI_NSS_mode)
{
		
	  GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;
	
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   	  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	                         	//设置SPI工作模式:设置为主SPI
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                 	  //设置SPI的数据大小:SPI发送接收8位帧结构
		SPI_InitStructure.SPI_NSS = SPI_NSS_mode;																//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_x;	  	//定义波特率预分频的值:波特率预分频值
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;											//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
		SPI_InitStructure.SPI_CRCPolynomial = 7;																//CRC值计算的多项式
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
							  SPI_ReadWriteByte(SPI3 , 0xff);															//启动传输		 
								break;		
			default :		
								return 0;
		}		
		return 1;
}



 /**
 * @brief    		SPI设置传输速度
 * @code
 *      				// 初始化SPI1,波特率预分频值为64
 *       				SPI_SetSpeed(SPI1,SPI_BaudRatePrescaler_64);
 * @endcode
 * @param[in]   SPIx : SPI模块选择，可选值有SPI1，SPI2，SPI3
 * @param[in]   SPI_BaudRatePrescaler ：波特率预分频值，x的可选值为2,4,8,16,32.....256
 */
void SPI_SetSpeed(SPI_TypeDef *SPIx ,u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPIx->CR1&=0XFFC7;
	SPIx->CR1|=SPI_BaudRatePrescaler;	
	SPI_Cmd(SPIx,ENABLE); 
} 


 /**
 * @brief    		SPI读写一个字节
 * @code
 *      				// 初始化SPI1,写入的为a=0x13;
 *       				SPI_ReadWriteByte(SPI1 ,a);
 * @endcode
 * @param[in]   SPIx : SPI模块选择，可选值有SPI1，SPI2，SPI3
 * @param[in]   TxData:要写入的字节
 * @return			返回值:读取到的字节
 */
u8 SPI_ReadWriteByte(SPI_TypeDef *SPIx ,u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPIx, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPIx); //返回通过SPIx最近接收的数据					    
}



