#ifndef __WS2811_H
#define __WS2811_H	

#include <stm32f10x.h>

#include "sysinc.h"


//#define   Time_D	   400
 
#define nWs 6		// �ж��ٿ�WS2811����


//B-R-G
#define   White        0xFFFFFF  // ��ɫ
#define   Black        0x000000  // ��ɫ ��������
#define   Blue         0xFF0000  // ��ɫ
#define   Red          0x00FF00  // ��ɫ
#define   Green        0x0000FF  // ��ɫ
#define   Gray         0x22ee22


extern void WS_GPIO_Init(int instance, int GPIO_Pin_x);//WS2811�˿ڳ�ʼ��

extern unsigned long WsDat_RUN[nWs];
extern unsigned long WsDat[nWs];

extern void WS_Set_Date(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned char len,unsigned long dat); //
extern void WS_SetAll(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN);	 //���������ֽ�

/*******/
//�ƴ����Ʒ���
extern unsigned long WS_SET_ColorToColor(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color0, unsigned long color1,unsigned int speed) ;//��ɫ����

extern void WS_Set_Color(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color);                                      //��ʼ���Դ�����	
extern void RUN_LED(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color,unsigned int speed,unsigned char temp); //�����
	
#endif

