/**
  ******************************************************************************
  * @file    uart.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    �˳���ΪARM��uart�ĵײ��̣������ڹٷ��ײ��Ķ��η�װ��
  ******************************************************************************
  */
#ifndef __CH_LIB_UART_H__
#define __CH_LIB_UART_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stdio.h"	
#include "nvic.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "gpio.h"

//���ͻ���
#define UART_SendLR(instan)  UART_WriteByte(instan,0X0D);\
											       UART_WriteByte(instan,0X0A)


/* UART ģ��� */
#define HW_UART1  (0x01U)
#define HW_UART2  (0x02U)
#define HW_UART3  (0x03U)

typedef void (*UART_CallBackType)(uint16_t Res);

/* API functions */
uint8_t UART_QuickInit(int instance, int bound, int preepri, int subpri,  FunctionalState ITsta);
uint8_t UART_ReadByte(uint32_t instance, uint16_t *ch);
void UART_WriteByte(uint32_t instance, uint16_t ch);
void UART_SendString(uint32_t instance, u8 *ch);
void UART_CallbackInstall(uint32_t instance, UART_CallBackType AppCBFun);

#endif

