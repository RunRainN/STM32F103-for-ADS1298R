#ifndef _GSM800C_H_
#define _GSM800C_H_

#include "sysinc.h"
#include "String.h"

#define GSM_UART  HW_UART3
#define GSM_TIMER HW_TIMER2
#define GSM_TIMX TIM2

//static u8 *telnum="AT+CMGS=\"00310039003900310033003800320039003800340034\"";
//static u8 *telnum="AT+CMGS=\"18567056404\"";
static u8 *telnum="AT+CMGS=\"15872656618\"";
static u8 *text="ABC:1345   SDE:789 ";										 
//static u8 *text="4ECA5929665A4E0A54035C4E003100320033004100420043006100620063003A";										 


#define GSM_BUF_MAX 200 	


void GSM800C_init(void);
void Second_Gsm_AT_Command(u8 *b,u8 *a,u8 wait_time);
void Send_Text_Sms(u8 *tel,u8 *txt);
void Set_CH_Text_Mode(void);
void Set_EN_Text_Mode(void);

#endif

