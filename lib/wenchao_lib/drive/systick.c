/**
  ******************************************************************************
  * @file    systick.c
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    此程序为ARM中SysTick的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */
#include "systick.h"

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数


 /**
 * @brief  			初始化SysTick
 * @code
 *   			 			//SysTick设定转中断周期10000us(10ms)
 *   						SYSTICK_Init(10000);
 * @endcode
 * @param[in]  	timeInUs 时间，单位微秒
 * @retval 			None
 */
void SYSTICK_Init(int timeInUs)
{
    /* Set clock source = core clock */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);																	//选择外部时钟  HCLK/8
		fac_us=SystemCoreClock/8000000;																												//为系统时钟的1/8     fac_us /= 1000000;
    fac_ms = fac_us * 1000;
    /* every 100ms in a int */
    SysTick->LOAD = fac_us * timeInUs;
}
/**
 * @brief  	配置SysTick 之后可以应用函数DelayMs DelayUs
 * @code
 *      		SYSTICK_DelayInit();
 *      		SYSTICK_DelayMs(20);
 * @endcode
 * @retval 	None
 */
void SYSTICK_DelayInit(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);														//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;																									//为系统时钟的1/8  
	fac_ms=(u16)fac_us*1000;																												//非ucos下,代表每个ms需要的systick时钟数   
	SYSTICK_Cmd(true);
  SYSTICK_ITConfig(false);
}

 /**
 * @brief  			使能或失能SysTick
 * @code
 *   						//使能
 *   						SYSTICK_Cmd(true);
 * @endcode
 * @param[in]  	NewState 
 *              @arg true 使能
 *              @arg false 失能
 * @retval 			None
 */
void SYSTICK_Cmd(bool NewState)
{
	(true == NewState)?(SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk):(SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk);
}

/**
 * @brief 	 		开启SysTick中断
 * @code
 *      				//例子
 *      				SYSTICK_ITConfig(true);
 * @endcode
 * @param[in]  	NewState 状态
 *              @arg true  使能
 *              @arg false 失能
 * @retval 			None
 */
void SYSTICK_ITConfig(bool NewState)
{
	(true == NewState)?(SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk):(SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk);
}

/**
 * @brief 		微妙级延时
 * @code
 *      			//延时100us
 *     				SYSTICK_DelayUs(100);
 * @endcode
 * @retval 		None
 */
void SYSTICK_DelayUs(int nus)
{
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 																											//时间加载	  		 
	SysTick->VAL=0x00;        																											//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          															//开始倒数	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));																							//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      																	//关闭计数器
	SysTick->VAL =0X00;       																											//清空计数器	 
}


/**
 * @brief 		毫秒级延时
 * @code
 *      			//延时100ms
 *      			SYSTICK_DelayMs(100);
 * @endcode
 * @retval 		None
 */
void SYSTICK_DelayMs(int ms)
{
	uint32_t temp;
    uint32_t i;
    SysTick->LOAD = fac_ms;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    for(i = 0; i < ms; i++)
	{
		SysTick->VAL = 0;
		do
		{
			temp = SysTick->CTRL;
		}
    while((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
	}
}


/**
 * @brief		 获得System tick timer当前值
 * @retval 	 返回System tick timer当前值
 */
int  SYSTICK_GetVal(void)
{
	return SysTick->VAL ;
}
