/**
  ******************************************************************************
  * @file    common_filter.c
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.10.16
  * @note    �˳���ΪARM�е�Ӧ�ñ��
  ******************************************************************************
  */
#ifndef __CH_LIB_COMMON_FILTER_H__
#define __CH_LIB_COMMON_FILTER_H__
														
#ifdef __cplusplus
 extern "C" {
#endif

	 
typedef struct
{		  
	float k; 
	float num;
}FIRST_ORDER_PARAMETER;


#include "sysinc.h"

void First_Order_parameter_init(FIRST_ORDER_PARAMETER *p,float ki);
void First_Order_filter(FIRST_ORDER_PARAMETER *p, float number);

#endif
