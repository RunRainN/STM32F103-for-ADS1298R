/**
  ******************************************************************************
  * @file    hmc5883+mpu6050+kalman.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.10.2
  * @note    此程序为ARM中应用编程
  ******************************************************************************
  */
#ifndef __CH_HMC5883_MPU6050_KALMAN_H__
#define __CH_HMC5883_MPU6050_KALMAN_H__

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{		
	  float pitch;
		float roll;
		float yaw;
}FLYING_ANGLE;


#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "sysinc.h"

	 
//API
void Nine_Axis_Get(MPU_DATE *ag,HMC_DATE *p);
void Six_Axis_Get(MPU_DATE *ag);
void Sthree_Axis_Get(HMC_DATE *p);
void Get_kalman_Pitch(KALMAN_SAME_PARAMETER *kalman,MPU_DATE *ag,FLYING_ANGLE *fly);
void Get_kalman_Roll(KALMAN_SAME_PARAMETER *kalman,MPU_DATE *ag,FLYING_ANGLE *fly);
void Get_kalman_Yaw(KALMAN_SAME_PARAMETER *kalman,MPU_DATE *ag, HMC_DATE *p,FLYING_ANGLE *fly);
void Get_firstcomp_Yaw(FIRST_COMPLEMENTARY_PARAMETER *first_comp,MPU_DATE *ag, HMC_DATE *p,FLYING_ANGLE *fly);
void HMC5883_NLevel_Angle(FLYING_ANGLE *fly,HMC_DATE *p);
void HMC5883_Level_Fix(HMC_DATE *p,FLYING_ANGLE *fly);
#endif

