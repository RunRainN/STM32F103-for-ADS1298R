#ifndef DS1302_H
#define DS1302_H

#include "sysinc.h"


typedef struct
{		  
	uint16_t SCK_HW_GPIOx;
	uint16_t SCK_GPIO_Pin_x;
	uint16_t IO_HW_GPIOx;
	uint16_t IO_GPIO_Pin_x;
	uint16_t RST_HW_GPIOx;
	uint16_t RST_GPIO_Pin_x;
} GPIOZWC_DS1302;

#define IO_i_MODE GPIO_QuickInit(gpiozwc_ds1302.IO_HW_GPIOx, gpiozwc_ds1302.IO_GPIO_Pin_x , GPIO_Mode_IPU);
#define IO_o_MODE GPIO_QuickInit(gpiozwc_ds1302.IO_HW_GPIOx, gpiozwc_ds1302.IO_GPIO_Pin_x , GPIO_Mode_Out_PP);

#define ds1302_sec_add			  0x80		 
#define ds1302_min_add			  0x82		 
#define ds1302_hr_add			    0x84		 
#define ds1302_date_add			  0x86		 
#define ds1302_month_add		  0x88	 
#define ds1302_day_add			  0x8a		 
#define ds1302_year_add			  0x8c	 
#define ds1302_control_add		0x8e		 
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

void ds1302_init(void);
void ds1302_write_byte(unsigned char addr, unsigned char d);
unsigned char ds1302_read_byte(unsigned char addr);
// ds1302_write_time(19, 9, 22, 4,16,05,55);
void ds1302_write_time(unsigned char year,unsigned char month,unsigned char day,unsigned char week,unsigned char hour,unsigned char min,unsigned char sec);
void ds1302_read_data(unsigned char dat[7]);

#endif
