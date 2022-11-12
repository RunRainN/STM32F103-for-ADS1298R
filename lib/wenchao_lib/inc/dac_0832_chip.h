/**
  ******************************************************************************
  * @file    DAC_0832_CHIP.H
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.10.24
  * @note    此程序为ARM中的应用编程
  ******************************************************************************
  */
#ifndef __CH_LIB_DAC_0832_CHIP_H__
#define __CH_LIB_DAC_0832_CHIP_H__
														
#ifdef __cplusplus
 extern "C" {
#endif

#define  DAC0832_v_TO_date  51.2 

#include "sysinc.h"

void Chip_0832_Port_Init(void);
void Write_0832_Date(u8 date);
void Write_0832_V(float V);
	 
#endif
