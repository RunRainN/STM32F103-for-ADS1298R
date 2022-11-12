#ifndef _MAXTRIC_KEYBOARD_H_
#define _MAXTRIC_KEYBOARD_H_

#include "sysinc.h"

typedef struct
{		  
	uint16_t HW_GPIOx;
	uint16_t GPIO_Pin_x;

} GPIOZWC_MAXTRIC;

u8 get_maxtric_keybord_value(void);

#endif

