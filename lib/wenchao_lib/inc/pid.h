/**
  ******************************************************************************
  * @file    cascade_pid.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.10.4
  * @note    �˳���CASCADE_PIDӦ�ò���
  ******************************************************************************
  */
#ifndef __CH_PID_H__
#define __CH_PID_H__

#ifdef __cplusplus
 extern "C" {
#endif

#define PWM_BASE_F    2000

typedef struct
{		
	  short pid_out_p;                       //�⻷����ϵ��
	  float pid_out_i;
	  short pid_out_d;
		short pid_out_err;										//�⻷���
		short pid_out_err_max;								//�⻷�������޶�
		short pid_out_last_err;								//�ϴ�����¼
		short pid_out_integral_err;						//������
		short pid_out_integral_err_max;				//����������޶�		
	  short pid_out_control;
	
		short pid_in_p;												//�ڻ�
	  float pid_in_i;
	  short pid_in_d;
		short pid_in_err;
		short pid_in_err_max;
		short pid_in_last_err;
		short pid_in_integral_err;
		short pid_in_integral_err_max;
	  short pid_in_control;
}PID_CASCADE_DATE;

typedef struct
{		
	  short pid_p;                       
	  float pid_i;
	  short pid_d;
		short pid_err;										
		short pid_err_max;										
		short pid_last_err;								
		short pid_integral_err;						
		short pid_integral_err_max;						
	  short pid_control;	
}PID_DATE;


#include "sysinc.h"

//API
void PID_DATE_Init(PID_DATE *piddate);
void PID_Control(short target_val,short now_val,PID_DATE *piddate);

void PID_CASCADE_DATE_Init(PID_CASCADE_DATE *pid_date);
void PID_Cascade(short target_val,short now_val,PID_CASCADE_DATE *pid_date);
void PID_Out(short target_val,short now_val,PID_CASCADE_DATE *pid_date);
void PID_In(short target_val,short now_val,PID_CASCADE_DATE *pid_date);

#endif
