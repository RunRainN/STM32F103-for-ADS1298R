#ifndef _FINGERPRINT_MODULE_H_
#define _FINGERPRINT_MODULE_H_

#include "sysinc.h"


typedef struct
{		  
	uint16_t HW_GPIOx;
	uint16_t GPIO_Pin_x;
	int HW_UARTx;
	int bound;

} GPIOZWC_FINGER;

extern unsigned int PageID;

void fingerprint_init(void);
uint8_t is_wak_finger(void);
u8 SFG_getimage(void);
u8 SFG_empty(void);
u8 SFG_identify(void);                     //自动验证指纹  录图像+生成特征+搜索
u8 SFG_deletchar(unsigned int pageID);     //删除指纹
u8 SFG_enroll(void);	                     //自动注册模板 返回存储ID = 录图像+合并生成模板+存储模板
u8 SFG_fastsearch(void);                   //搜索指纹返回指纹ID
u8 SFG_genchar(void);                      //生成特征并存储

#endif


