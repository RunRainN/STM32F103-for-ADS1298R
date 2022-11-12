/**
  ******************************************************************************
  * @file    complemen_filter.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.9.26
  * @note    此程序为ARM中的应用编程
  ******************************************************************************
  */
#ifndef __CH_LIB_COMPLEMEN_FILTER_H__
#define __CH_LIB_COMPLEMEN_FILTER_H__

#ifdef __cplusplus
 extern "C" {
#endif



typedef struct
{		  
float K1; 
float T;
float angle1;
}FIRST_COMPLEMENTARY_PARAMETER;
 

typedef struct
{		  
	float T;
	float K2; 
	float x1;
	float x2;
	float y1;
	float angle2;
}TWO_COMPLEMENTARY_PARAMETER;
 
#include "sysinc.h"

void First_complementary_parameter_init(FIRST_COMPLEMENTARY_PARAMETER *p, float Time);
void First_order_complementary_filter(FIRST_COMPLEMENTARY_PARAMETER *p, float angle_m, float gyro_m);

void Two_complementary_parameter_init(TWO_COMPLEMENTARY_PARAMETER *p, float Time);
void Two_order_complementary_filter(TWO_COMPLEMENTARY_PARAMETER *p, float angle_m, float gyro_m);	 
	 
#endif

