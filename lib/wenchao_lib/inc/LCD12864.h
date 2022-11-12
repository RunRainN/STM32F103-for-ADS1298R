#ifndef _LCD12864_H_
#define _LCD12864_H_

#include "sysinc.h"

#define RS_H GPIO_SetBits(GPIOB,GPIO_Pin_7) //RS=1   4PIN
#define RS_L GPIO_ResetBits(GPIOB,GPIO_Pin_7) //RS=0

#define RW_H GPIO_SetBits(GPIOB,GPIO_Pin_8) //RW=1    5PIN
#define RW_L GPIO_ResetBits(GPIOB,GPIO_Pin_8);  //RW = 0

#define EN_H GPIO_SetBits(GPIOB,GPIO_Pin_9);    //EN = 1   6PIN
#define EN_L GPIO_ResetBits(GPIOB,GPIO_Pin_9);  //EN = 0

void SendCMD(unsigned char dat);
void SendDat(unsigned char dat);
void initlcm(void);
void display(unsigned char x_add,unsigned char *ptr);
void LCD12864_show(unsigned char y, unsigned char x, unsigned char *puts);
void LCD12864_clear(void);

#endif

