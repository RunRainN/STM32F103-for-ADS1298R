#ifndef __WS2811_H
#define __WS2811_H	

#include <stm32f10x.h>

#include "sysinc.h"


//#define   Time_D	   400
 
#define nWs 6		// 有多少颗WS2811级联


//B-R-G
#define   White        0xFFFFFF  // 白色
#define   Black        0x000000  // 黑色 （不亮）
#define   Blue         0xFF0000  // 蓝色
#define   Red          0x00FF00  // 红色
#define   Green        0x0000FF  // 绿色
#define   Gray         0x22ee22


extern void WS_GPIO_Init(int instance, int GPIO_Pin_x);//WS2811端口初始化

extern unsigned long WsDat_RUN[nWs];
extern unsigned long WsDat[nWs];

extern void WS_Set_Date(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned char len,unsigned long dat); //
extern void WS_SetAll(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN);	 //发送所有字节

/*******/
//灯带控制方案
extern unsigned long WS_SET_ColorToColor(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color0, unsigned long color1,unsigned int speed) ;//颜色渐变

extern void WS_Set_Color(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color);                                      //初始化显存数组	
extern void RUN_LED(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color,unsigned int speed,unsigned char temp); //跑马灯
	
#endif

