/**
  ******************************************************************************
  * @file    systick.c
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    �˳���ΪARM��SysTick�ĵײ��̣������ڹٷ��ײ��Ķ��η�װ��
  ******************************************************************************
  */
#include "systick.h"

static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������


 /**
 * @brief  			��ʼ��SysTick
 * @code
 *   			 			//SysTick�趨ת�ж�����10000us(10ms)
 *   						SYSTICK_Init(10000);
 * @endcode
 * @param[in]  	timeInUs ʱ�䣬��λ΢��
 * @retval 			None
 */
void SYSTICK_Init(int timeInUs)
{
    /* Set clock source = core clock */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);																	//ѡ���ⲿʱ��  HCLK/8
		fac_us=SystemCoreClock/8000000;																												//Ϊϵͳʱ�ӵ�1/8     fac_us /= 1000000;
    fac_ms = fac_us * 1000;
    /* every 100ms in a int */
    SysTick->LOAD = fac_us * timeInUs;
}
/**
 * @brief  	����SysTick ֮�����Ӧ�ú���DelayMs DelayUs
 * @code
 *      		SYSTICK_DelayInit();
 *      		SYSTICK_DelayMs(20);
 * @endcode
 * @retval 	None
 */
void SYSTICK_DelayInit(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);														//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;																									//Ϊϵͳʱ�ӵ�1/8  
	fac_ms=(u16)fac_us*1000;																												//��ucos��,����ÿ��ms��Ҫ��systickʱ����   
	SYSTICK_Cmd(true);
  SYSTICK_ITConfig(false);
}

 /**
 * @brief  			ʹ�ܻ�ʧ��SysTick
 * @code
 *   						//ʹ��
 *   						SYSTICK_Cmd(true);
 * @endcode
 * @param[in]  	NewState 
 *              @arg true ʹ��
 *              @arg false ʧ��
 * @retval 			None
 */
void SYSTICK_Cmd(bool NewState)
{
	(true == NewState)?(SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk):(SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk);
}

/**
 * @brief 	 		����SysTick�ж�
 * @code
 *      				//����
 *      				SYSTICK_ITConfig(true);
 * @endcode
 * @param[in]  	NewState ״̬
 *              @arg true  ʹ��
 *              @arg false ʧ��
 * @retval 			None
 */
void SYSTICK_ITConfig(bool NewState)
{
	(true == NewState)?(SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk):(SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk);
}

/**
 * @brief 		΢���ʱ
 * @code
 *      			//��ʱ100us
 *     				SYSTICK_DelayUs(100);
 * @endcode
 * @retval 		None
 */
void SYSTICK_DelayUs(int nus)
{
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 																											//ʱ�����	  		 
	SysTick->VAL=0x00;        																											//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          															//��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));																							//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      																	//�رռ�����
	SysTick->VAL =0X00;       																											//��ռ�����	 
}


/**
 * @brief 		���뼶��ʱ
 * @code
 *      			//��ʱ100ms
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
 * @brief		 ���System tick timer��ǰֵ
 * @retval 	 ����System tick timer��ǰֵ
 */
int  SYSTICK_GetVal(void)
{
	return SysTick->VAL ;
}
