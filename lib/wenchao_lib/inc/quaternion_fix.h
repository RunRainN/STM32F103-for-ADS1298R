/**
  ******************************************************************************
  * @file    quaternion_fix.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.9.27
  * @note    此程序为ARM的应用编程
  ******************************************************************************
  */
#ifndef __CH_LIB_QUATERNION_FIX_H__
#define __CH_LIB_QUATERNION_FIX_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sysinc.h"


#define Kp 100.0f                        
#define Ki 0.002f                
#define halfT 0.005f                //周期的一半

//API
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);

#endif

