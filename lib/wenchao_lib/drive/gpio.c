/**
  ******************************************************************************
  * @file    gpio.c
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中GPIO的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */

	
#include "gpio.h"


/**
 * @param[in]  instance GPIO模块端口号  
 *              @arg HW_GPIOA A端口
 *              @arg HW_GPIOB B端口
 *              @arg HW_GPIOC C端口
 *              @arg HW_GPIOD D端口
 *              @arg HW_GPIOE E端口
 * @param[in]   GPIO_Pin_x x为引脚号
 * @param[in]  Mode 引脚输出模式 
 *              @arg GPIO_Mode_AIN           模拟输入
 *              @arg GPIO_Mode_IN_FLOATING   浮空输入
 *              @arg GPIO_Mode_IPD					 下拉输入
 *              @arg GPIO_Mode_IPU 					 上拉输入
 *              @arg GPIO_Mode_Out_OD				 开漏输出
 *              @arg GPIO_Mode_Out_PP  		   推挽输出
 *              @arg GPIO_Mode_AF_OD				 复用开漏输出
 *              @arg GPIO_Mode_AF_PP 				 复用推挽输出
 */
 
u8 GPIO_QuickInit(int instance, int GPIO_Pin_x, GPIOMode_TypeDef Mode)
{
	 /* config state */
	  GPIO_InitTypeDef  GPIO_InitStructure;
    switch(instance)
    {
        case HW_GPIOA:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;	
						if( GPIO_Pin_x == GPIO_Pin_13  || GPIO_Pin_x == GPIO_Pin_14 || GPIO_Pin_x == GPIO_Pin_15 ){
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
							GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
						}				
						GPIO_InitStructure.GPIO_Mode = Mode; 		
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
						GPIO_Init(GPIOA, &GPIO_InitStructure);					//根据设定参数初始
            break;
				
        case HW_GPIOB:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;	
						if(GPIO_Pin_x == GPIO_Pin_4  || GPIO_Pin_x == GPIO_Pin_3 ){
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
							GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
						}				
						GPIO_InitStructure.GPIO_Mode = Mode; 		
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
						GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始
            break;
        case HW_GPIOC:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				
						GPIO_InitStructure.GPIO_Mode = Mode; 		 
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
						GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始
            break;
        case HW_GPIOD:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				
						GPIO_InitStructure.GPIO_Mode = Mode; 		
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
						GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始
            break;
        case HW_GPIOE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				
						GPIO_InitStructure.GPIO_Mode = Mode; 		 
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
						GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始
            break;
        default:
						return 0;					
    }
		return  1;
}




/**
 * @param[in]  instance GPIO模块端口号  
 *              @arg HW_GPIOA A端口
 *              @arg HW_GPIOB B端口
 *              @arg HW_GPIOC C端口
 *              @arg HW_GPIOD D端口
 *              @arg HW_GPIOE E端口
 * @param[in]   GPIO_Pin_x x为引脚号
 * @param[in]   data 1或0 
 *             
 */
void GPIO_Writebit(int instance, int GPIO_Pin_x, int data)
{
	
	  switch(instance)
    {
        case HW_GPIOA:
              assert_param(IS_GPIO_ALL_PERIPH(GPIOA));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
							assert_param(IS_GPIO_BIT_ACTION(data));  
							if (data != Bit_RESET)
							{
								GPIOA->BSRR = GPIO_Pin_x;
							}
							else
							{
								GPIOA->BRR = GPIO_Pin_x;
							}
							break;
				
        case HW_GPIOB:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOB));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
							assert_param(IS_GPIO_BIT_ACTION(data));  
							if (data != Bit_RESET)
							{
								GPIOB->BSRR = GPIO_Pin_x;
							}
							else
							{
								GPIOB->BRR = GPIO_Pin_x;
							}
							break;
        case HW_GPIOC:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOC));
						assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
							assert_param(IS_GPIO_BIT_ACTION(data));  
							if (data != Bit_RESET)
							{
								GPIOC->BSRR = GPIO_Pin_x;
							}
							else
							{
								GPIOC->BRR = GPIO_Pin_x;
							}
							break;
        case HW_GPIOD:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOD));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
							assert_param(IS_GPIO_BIT_ACTION(data));  
							if (data != Bit_RESET)
							{
								GPIOD->BSRR = GPIO_Pin_x;
							}
							else
							{
								GPIOD->BRR = GPIO_Pin_x;
							}
							break;
        case HW_GPIOE:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOE));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
							assert_param(IS_GPIO_BIT_ACTION(data));  
							if (data != Bit_RESET)
							{
								GPIOE->BSRR = GPIO_Pin_x;
							}
							else
							{
								GPIOE->BRR = GPIO_Pin_x;
							}
							break;
        default:
            break;					
    }
}
 




/**
 * @param[in]  instance GPIO模块端口号  
 *              @arg HW_GPIOA A端口
 *              @arg HW_GPIOB B端口
 *              @arg HW_GPIOC C端口
 *              @arg HW_GPIOD D端口
 *              @arg HW_GPIOE E端口
 * @param[in]   GPIO_Pin_x x为引脚号 * @param[in]   data 1或0 
 *             
 */
uint8_t GPIO_ReadBit(uint32_t instance, uint16_t GPIO_Pin_x)
{
	
  uint8_t bitstatus = 0x00;
	switch(instance)
    {
        case HW_GPIOA:
              /* Check the parameters */
							assert_param(IS_GPIO_ALL_PERIPH(GPIOA));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x)); 
  
							if ((GPIOA->IDR & GPIO_Pin_x) != 0)
							{
									bitstatus = 1;
							}
							else
							{
									bitstatus = 0;
							}
							break;
				
        case HW_GPIOB:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOB));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x)); 
  
							if ((GPIOB->IDR & GPIO_Pin_x) != 0)
							{
									bitstatus = 1;
							}
							else
							{
									bitstatus = 0;
							}
							break;
        case HW_GPIOC:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOC));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x)); 
  
							if ((GPIOC->IDR & GPIO_Pin_x) != 0)
							{
									bitstatus = 1;
							}
							else
							{
									bitstatus = 0;
							}
							break;
        case HW_GPIOD:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOD));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x)); 
  
							if ((GPIOD->IDR & GPIO_Pin_x) != 0)
							{
									bitstatus = 1;
							}
							else
							{
									bitstatus = 0;
							}							
							break;
        case HW_GPIOE:
							assert_param(IS_GPIO_ALL_PERIPH(GPIOE));
							assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x)); 
  
							if ((GPIOE->IDR & GPIO_Pin_x) != 0)
							{
									bitstatus = 1;
							}
							else
							{
									bitstatus = 0;
							}
							break;
        default:
            break;					
    }
		return bitstatus;

}
