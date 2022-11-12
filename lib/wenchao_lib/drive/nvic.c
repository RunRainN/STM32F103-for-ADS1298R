/**
  ******************************************************************************
  * @file    nvic.c
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中NVIC的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */
#include "nvic.h"


/**
 * @brief   设置NVIC中断分组2:2位抢占优先级，2位响应优先级

 */
void NVIC_init(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
