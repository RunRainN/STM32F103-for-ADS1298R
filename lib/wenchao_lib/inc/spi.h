/**
  ******************************************************************************
  * @file    spi.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    此程序为ARM中spi的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */

#ifndef __CH_LIB_SPI_H__
#define __CH_LIB_SPI_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sysinc.h"
 
/* 模式定义 */
#define CPOL_HIGH_CPHA_1         1 
#define CPOL_HIGH_CPHA_2         2 
#define CPOL_LOW_CPHA_1          3
#define CPOL_LOW_CPHA_2          4 

/* 端口定义 */
#define Spi1         1 
#define Spi2         2 
#define Spi3         3 

/* 引脚定义 */
#define SPI1_NSS         PBout(7)
#define SPI1_CE          PBout(13)

#define SPI2_NSS         PBout(12)
#define SPI2_CE          PBout(4)

#define SPI3_NSS         PAout(14)
#define SPI3_CE          PAout(15)


/* API*/
uint32_t SPI_QuickInit(uint32_t Spix, int frameFormat, uint32_t SPI_BaudRatePrescaler_x, int SPI_NSS_mode);
void SPI_SetSpeed(SPI_TypeDef *SPIx, u8 SPI_BaudRatePrescaler);
u8 SPI_ReadWriteByte(SPI_TypeDef *SPIx ,u8 TxData);

#endif
