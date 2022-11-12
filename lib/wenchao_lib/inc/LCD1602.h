/**
  ******************************************************************************
  * @file    LCD1602.c
  * @author  张文超 
	* @qq      269426626
  * @version V1.2
  * @note    1602--四根数据线驱动模式
  ******************************************************************************
  */
	
#ifndef _LCD1602_H_
#define _LCD1602_H_

#include "sysinc.h"

typedef struct
{		  
	uint16_t HW_GPIOx_RS;
	uint16_t GPIO_Pin_x_RS;
	uint16_t HW_GPIOx_RW;
	uint16_t GPIO_Pin_x_RW;
	uint16_t HW_GPIOx_EN;
	uint16_t GPIO_Pin_x_EN;
	
	uint16_t HW_GPIOx_DB4;
	uint16_t GPIO_Pin_x_DB4;
	uint16_t HW_GPIOx_DB5;
	uint16_t GPIO_Pin_x_DB5;
	uint16_t HW_GPIOx_DB6;
	uint16_t GPIO_Pin_x_DB6;
	uint16_t HW_GPIOx_DB7;
	uint16_t GPIO_Pin_x_DB7;

} GPIOZWC_1602;

//用户仅仅需要修改以下引脚参数就可以了---任意引脚皆可

static GPIOZWC_1602 gpiozwc_1602 = {
	HW_GPIOB, GPIO_Pin_11,      //RS
	HW_GPIOB, GPIO_Pin_10,      //RW
	HW_GPIOB, GPIO_Pin_1,      //EN
	HW_GPIOA, GPIO_Pin_4,				//DB4
	HW_GPIOA, GPIO_Pin_3,				//DB5
	HW_GPIOA, GPIO_Pin_2,				//DB6
	HW_GPIOA, GPIO_Pin_1				//DB7
};
 
#define	LCD_RS_Set()	GPIO_Writebit(gpiozwc_1602.HW_GPIOx_RS, gpiozwc_1602.GPIO_Pin_x_RS, 1 )
#define	LCD_RS_Clr()	GPIO_Writebit(gpiozwc_1602.HW_GPIOx_RS, gpiozwc_1602.GPIO_Pin_x_RS, 0 )
 
#define	LCD_RW_Set()	GPIO_Writebit(gpiozwc_1602.HW_GPIOx_RW, gpiozwc_1602.GPIO_Pin_x_RW, 1 )
#define	LCD_RW_Clr()	GPIO_Writebit(gpiozwc_1602.HW_GPIOx_RW, gpiozwc_1602.GPIO_Pin_x_RW, 0 )
 
#define	LCD_EN_Set()	GPIO_Writebit(gpiozwc_1602.HW_GPIOx_EN, gpiozwc_1602.GPIO_Pin_x_EN, 1 )
#define	LCD_EN_Clr()	GPIO_Writebit(gpiozwc_1602.HW_GPIOx_EN, gpiozwc_1602.GPIO_Pin_x_EN, 0 )
 
#define	DATAOUT(x)	  { GPIO_Writebit(gpiozwc_1602.HW_GPIOx_DB4, gpiozwc_1602.GPIO_Pin_x_DB4, x & 0x10 );\
												GPIO_Writebit(gpiozwc_1602.HW_GPIOx_DB5, gpiozwc_1602.GPIO_Pin_x_DB5, x & 0x20 );\
												GPIO_Writebit(gpiozwc_1602.HW_GPIOx_DB6, gpiozwc_1602.GPIO_Pin_x_DB6, x & 0x40 );\
												GPIO_Writebit(gpiozwc_1602.HW_GPIOx_DB7, gpiozwc_1602.GPIO_Pin_x_DB7, x & 0x80 );\
											}
 	

void LCD1602_Init(void);
 
void LCD1602_Wait_Ready(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void LCD1602_ClearScreen(void);
void LCD1602_Set_Cursor(u8 x, u8 y);
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);

#endif
