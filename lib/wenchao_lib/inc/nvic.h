/**
  ******************************************************************************
  * @file    nvic.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    �˳���ΪARM��NVIC�ĵײ��̣������ڹٷ��ײ��Ķ��η�װ��
  ******************************************************************************
  */

#ifndef __CH_LIB_NVIC_H__
#define __CH_LIB_NVIC_H__
														
#ifdef __cplusplus
 extern "C" {
#endif
	
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void NVIC_init(void);

#endif
