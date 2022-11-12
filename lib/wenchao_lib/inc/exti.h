/**
  ******************************************************************************
  * @file    exti.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    此程序为ARM中EXTI的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */
#ifndef __CH_LIB_EXTI_H__
#define __CH_LIB_EXTI_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "gpio.h"
#include "nvic.h"
#include "stm32f10x_exti.h"
#include "uart.h"


/** @defgroup GPIO_Pin_sources   */

#define EXTI_Pin_0        GPIO_PinSource0          
#define EXTI_Pin_1        GPIO_PinSource1          
#define EXTI_Pin_2        GPIO_PinSource2          
#define EXTI_Pin_3        GPIO_PinSource3          
#define EXTI_Pin_4        GPIO_PinSource4          
#define EXTI_Pin_5        GPIO_PinSource5          
#define EXTI_Pin_6        GPIO_PinSource6          
#define EXTI_Pin_7        GPIO_PinSource7          
#define EXTI_Pin_8        GPIO_PinSource8          
#define EXTI_Pin_9        GPIO_PinSource9          
#define EXTI_Pin_10       GPIO_PinSource10          
#define EXTI_Pin_11       GPIO_PinSource11          
#define EXTI_Pin_12       GPIO_PinSource12         
#define EXTI_Pin_13       GPIO_PinSource13         
#define EXTI_Pin_14       GPIO_PinSource14         
#define EXTI_Pin_15       GPIO_PinSource15         
 
/* EXTI端口定义 */
#define HW_EXTIA          GPIO_PortSourceGPIOA  
#define HW_EXTIB          GPIO_PortSourceGPIOB  
#define HW_EXTIC          GPIO_PortSourceGPIOC  
#define HW_EXTID          GPIO_PortSourceGPIOD  
#define HW_EXTIE          GPIO_PortSourceGPIOE  

typedef void (*GPIO_CallBackType)(void);

/* API functions */
void EXTI_QuickInit(int instance, int EXTI_Pin_x,int preepri, int subpri);
void EXTI_IRQcmd(int instance, int EXTI_Pin_x,FunctionalState ITsta);
void EXTI_CallbackInstall(int EXTI_Pin_x, GPIO_CallBackType AppCBFun);



#endif

