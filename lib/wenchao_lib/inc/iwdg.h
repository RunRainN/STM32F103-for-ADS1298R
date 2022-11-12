/**
  ******************************************************************************
  * @file    iwdg.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    �˳���ΪARM��IWDG�ĵײ��̣������ڹٷ��ײ���װ��
  ******************************************************************************
  */

#ifndef __CH_LIB_IWDG_H__
#define __CH_LIB_IWDG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_iwdg.h"
//13104 0
/* API functions */
void IWDG_QuickInit(int timeInMs);
void IWDG_ENABLE(void);
void IWDG_FEED(void);

#endif



