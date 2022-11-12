/**
  ******************************************************************************
  * @file    iwdg.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中IWDG的底层编程（依附于官方底层库封装）
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



