/**
  ******************************************************************************
  * @file    nvic.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中NVIC的底层编程（依附于官方底层库的二次封装）
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
