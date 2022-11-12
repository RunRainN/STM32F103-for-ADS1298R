/**
  ******************************************************************************
  * @file    sysinc.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    此程序为头文件合集
  ******************************************************************************
  */
#ifndef __CH_LIB_SYSINC_H__
#define __CH_LIB_SYSINC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#define    T_ANGLE           57.32484076
#define    DEG_TO_RAD        0.0174532925199
#define    MPU_DATE          ACGY	 

//自己写的头文件
#include "uart.h"
#include "gpio.h"
#include "nvic.h"
#include "systick.h"
#include "exti.h"
#include "iwdg.h"
#include "spi.h"
#include "nrf2401.h"
#include "timer.h"
#include "adc.h"
#include "i2c.h"
#include "mpu6050_basic.h"
#include "kalman.h"
#include "my_math.h"
#include "complemen_filter.h"
#include "quaternion_fix.h"
#include "hmc5883.h"
#include "hmc5883+mpu6050+kalman.h"
#include "pid.h"
#include "four_axis_aircraft.h"
#include "iic_ssd1306.h"
#include "common_filter.h"
#include "dac_0832_chip.h"
#include "four_axis_remote_control.h"
#include "LCD12864.h"
#include "matrix_keyboard.h"
#include "fingerprint_module.h"
#include "flash_S.h"
#include "DS1302.h"
#include "ads1298r.h"


//官方头文件
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_can.h"
#include "stm32f10x_cec.h"
#include "stm32f10x_crc.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_dbgmcu.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_iwdg.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_sdio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_wwdg.h"


#endif
