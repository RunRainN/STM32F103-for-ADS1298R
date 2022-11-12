/**
  ******************************************************************************
  * @file    adc.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.9.10
  * @note    此程序为ARM中ADC1的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */
#ifndef __CH_LIB_ADC_H__
#define __CH_LIB_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sysinc.h"

/* ADC规则通道 端口定义 */
#define ADC_CH0   0       // PA0
#define ADC_CH1   1  			// PA1
#define ADC_CH2   2  			// PA2
#define ADC_CH3   3  			// PA3
#define ADC_CH4   4  			// PA4
#define ADC_CH5   5  			// PA5
#define ADC_CH6   6  			// PA6
#define ADC_CH7   7  			// PA7
#define ADC_CH8   8  			// PB0
#define ADC_CH9   9  			// PB1
#define ADC_CH10  10   		// PC0
#define ADC_CH11  11   		// PC1
#define ADC_CH12  12   		// PC2
#define ADC_CH13  13   		// PC3
#define ADC_CH14  14   		// PC4
#define ADC_CH15  15   		// PC5


//ADC1 API
void ADC_init(u8 ADC_CHx);
u16 Get_Adc(u8 ADC_CHx);
u16 Get_Adc_Average(u8 ADC_CHx,u8 times);
void adc_5ch_dma(void);

#endif
