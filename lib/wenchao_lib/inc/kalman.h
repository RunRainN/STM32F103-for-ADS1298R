/**
  ******************************************************************************
  * @file    kalman.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.9.25
  * @note    �˳���Ϊ�ײ�Ӧ�ó���KALMAN
  ******************************************************************************
  */
#ifndef __CH_LIB_KALMAN_H__
#define __CH_LIB_KALMAN_H__

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{		  
	float A;
	float H; 						//����
	float Q;
	float R;						//����ֵ
	float P00;					//�м�p
	float P10;					//p
	float T;						//����
	float Kg;						//Kg
	float angle_10;			//�Ƕ�Ԥ��
	float angle_00;			//���ŽǶ�
} KALMAN_SAME_PARAMETER;

typedef struct
{		  
	float T;          	//����
	float angle;				//�Ƕ�
	float angle_dot;		//���ٶ�
	float P[2][2];			//�м�P
	float Pdot[4];			//�м����
	float Q_angle;			//�Ƕ�Qֵ
	float	Q_gyro; 			
	float R_angle;
	float C_0; 
	float q_bias;				//���ٶȶ�̬ƫ��
	float angle_err;
	float PCt_0;
	float PCt_1;
	float E;
	float K_0;
	float K_1;
	float t_0;
	float t_1;
} KALMAN_DIFFERENT_PARAMETER;

	 
	 
#include "sysinc.h"



//API

void kalman_same_parameter_init(KALMAN_SAME_PARAMETER *p,float Time);
void Kalman_Same_Q_Filter(KALMAN_SAME_PARAMETER *p,float angle_m, float gyro_m);

void kalman_different_parameter_init(KALMAN_DIFFERENT_PARAMETER *p,float Time);
void Kalman_Different_Q_Filter(KALMAN_DIFFERENT_PARAMETER *p,float angle_m, float gyro_m);

#endif

