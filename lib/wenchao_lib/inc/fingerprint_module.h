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
u8 SFG_identify(void);                     //�Զ���ָ֤��  ¼ͼ��+��������+����
u8 SFG_deletchar(unsigned int pageID);     //ɾ��ָ��
u8 SFG_enroll(void);	                     //�Զ�ע��ģ�� ���ش洢ID = ¼ͼ��+�ϲ�����ģ��+�洢ģ��
u8 SFG_fastsearch(void);                   //����ָ�Ʒ���ָ��ID
u8 SFG_genchar(void);                      //�����������洢

#endif


