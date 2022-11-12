/**
  ******************************************************************************
  * @file    ssd1306.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中的1306底层应用编程
  ******************************************************************************
  */

#ifndef __CH_LIB_SSD1306_H__
#define __CH_LIB_SSD1306_H__

#ifdef __cplusplus
 extern "C" {
#endif

#define	BRIGHTNESS  	0xCF 
#define X_MAX_WIDTH 	128
#define Y_MAX_WIDTH 	64

#define IIC_SSD1306_SlaveAddress  0x78
#define IIC_SSD1306_WRITEDAT      0x40
#define IIC_SSD1306_WRITECMD      0x00

#include "sysinc.h"

//API
void OLED_Init(void);
void OLED_WrDat(u8 dat);
void OLED_WrCmd(u8 cmd);
void OLED_Set_Pos(u8 x,u8 y);
void OLED_Fill(u8 blean);
void OLED_CLS(void);
void OLED_P6x8Str(u8 x, u8 y,u8 ch[]);
void OLED_P8x16Str(u8 x, u8 y,u8 ch[]);
void OLED_P16x16Ch(u8 x, u8 y, u8 N);
void Draw_BMP(u8 x0, u8 y0, u8 x1, u8 y1,u8 BMP[]);
void OLED_ON(void);
void OLED_OFF(void);

void OLED_P6x8Str_Num(u8 x, u8 y,u8 ch[],u8 ch2,float num);
#endif

