/**
  ******************************************************************************
  * @file    systick.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中SysTick的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */
#ifndef __CH_LIB_SYSTICK_H__
#define __CH_LIB_SYSTICK_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "misc.h"
#include <stdint.h>
#include <stdbool.h>

void SYSTICK_DelayInit(void);
void SYSTICK_Init(int timeInUs);
void SYSTICK_Cmd(bool NewState);
void SYSTICK_ITConfig(bool NewState);
void SYSTICK_DelayUs(int us);
void SYSTICK_DelayMs(int ms);
int  SYSTICK_GetVal(void);

#endif
