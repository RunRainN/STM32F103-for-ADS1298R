/**
  ******************************************************************************
  * @file    timer.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    此程序为ARM的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */

#ifndef __CH_LIB_TIMER_H__
#define __CH_LIB_TIMER_H__

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{		
	  int pwm1;
		int pwm2;
		int pwm3;
		int pwm4;
}PWM_DUTY;


#include "sysinc.h"							

/* PWM 端口定义*/
#define PWM_CH1  1
#define PWM_CH2  2
#define PWM_CH3  3
#define PWM_CH4  4

/* TIMER 端口定义*/
#define HW_TIMER1          1  
#define HW_TIMER2          2  
#define HW_TIMER3          3  
#define HW_TIMER4          4  

/* 输入捕捉 端口定义*/
#define CAP_CH1  1
#define CAP_CH2  2
#define CAP_CH3  3
#define CAP_CH4  4

/* 定时器中断回调函数原型 */
typedef void (*TIMER_CallBackType)(void);


//timer1~timer4 API

u8 TIM_us_Init(TIM_TypeDef* TIMx, u32 Tim_us, u16 TIM_IT, u16 Subpri,FunctionalState NewState);
u8 TIM_ms_Init(TIM_TypeDef* TIMx, u16 Tim_ms, u16 TIM_IT, u16 Subpri,FunctionalState NewState);
u8 TIM_us_Init_org(TIM_TypeDef* TIMx, u32 Tim_arr, u16 Tim_psc);

void TIM_ITconfig(TIM_TypeDef* TIMx, u16 TIM_IT,u16 Subpri, FunctionalState NewState);
void TIM_cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

//pwm（timer1~timer4）
void TIM_PWM_Init(TIM_TypeDef* TIMx, u8 PWM_CHx, u32 Frequency, FunctionalState NewState);
u8 	TIM_SetCompare(TIM_TypeDef* TIMx, u8 PWM_CHx, u32 PWM_Duty);	

u8 TIM_tim_Init(TIM_TypeDef* TIMx, u32 Tim_us, FunctionalState NewState);
void GPIO_PWM_Init(TIM_TypeDef* TIMx, u8 PWM_CHx);
void TIM_OCInit(TIM_TypeDef* TIMx, u8 PWM_CHx);

//输入捕捉功能timer2~timer5
void TIM_Cap_Init(TIM_TypeDef* TIMx, u8 CAP_CHx, u16 arr,u16 psc, u16 Subpri, u8 N);

u8 TIM_Ctim_Init(TIM_TypeDef* TIMx, u16 arr,u16 psc, u16 Subpri, FunctionalState NewState);
u32 GPIO_Cap_Init(TIM_TypeDef* TIMx, u8 CAP_CHx);

void TIMER_CallbackInstall(u8 HW_TIMERx, TIMER_CallBackType AppCBFun);


#endif
