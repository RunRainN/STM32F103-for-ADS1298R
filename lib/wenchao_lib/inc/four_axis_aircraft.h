/**
  ******************************************************************************
  * @file    four_axis_aircraft.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.10.4
  * @note    此程序四轴应用层编程
  ******************************************************************************
  */
#ifndef __CH_FOUR_AXIS_AIRCRAFT_H__
#define __CH_FOUR_AXIS_AIRCRAFT_H__

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{		
	  short south_north_fly;
	  short east_west_fly;
}DIRECTION_FLY;


#include "sysinc.h"

/*******nrf2401接收发送定义*******/
#define  LOW_POWER     			      		0x00
#define  POWER_VAL           					0x01
#define  ATTITUDE      					      0x02
#define  PITCH_PID   		  			      0x03
#define  ROLL_PID           	 				0x04
#define  REAL_ATTITUDE            		0x05

#define  ACCELERATOR                  0X0A
#define  START_REAL_ATTITUDE      		0x0B
#define  GET_POWER_VAL           	  	0x0C
#define  GET_PITCH_PID   					    0x0D
#define  GET_ROLL_PID         	 		  0x0E
#define  UPDATE_OUT_P									0X0F
#define  UPDATE_OUT_I									0X10
#define  UPDATE_OUT_D									0X11
#define  UPDATE_IN_P									0X12
#define  UPDATE_IN_I									0X13
#define  UPDATE_IN_D									0X14
#define  EAST_FLY											0x15
#define  WEST_FLY											0x16
#define  SOUTH_FLY										0x17
#define  NORTH_FLY										0x18
#define  HOVER_FLY										0x19
#define  NIGHT_LIGHT									0x1A

//API
void hover_flying(DIRECTION_FLY *dire_fly);
void east_flying(DIRECTION_FLY *dire_fly);
void west_flying(DIRECTION_FLY *dire_fly);
void south_flying(DIRECTION_FLY *dire_fly);
void north_flying(DIRECTION_FLY *dire_fly);
void update_out_p(void);
void update_out_i(void);
void update_out_d(void);
void update_in_p(void);
void update_in_i(void);
void update_in_d(void);
#endif
