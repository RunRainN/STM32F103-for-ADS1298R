/**
  ******************************************************************************
  * @file    kalman.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.9.25
  * @note    此程序为底层应用程序KALMAN
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
	float H; 						//参数
	float Q;
	float R;						//置信值
	float P00;					//中间p
	float P10;					//p
	float T;						//周期
	float Kg;						//Kg
	float angle_10;			//角度预测
	float angle_00;			//最优角度
} KALMAN_SAME_PARAMETER;

typedef struct
{		  
	float T;          	//周期
	float angle;				//角度
	float angle_dot;		//角速度
	float P[2][2];			//中间P
	float Pdot[4];			//中间参量
	float Q_angle;			//角度Q值
	float	Q_gyro; 			
	float R_angle;
	float C_0; 
	float q_bias;				//角速度动态偏离
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

