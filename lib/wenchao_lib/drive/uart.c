/**
  ******************************************************************************
  * @file    uart.c
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    此程序为ARM中uart的底层编程（依附于官方底层库的二次封装）
  ******************************************************************************
  */

#include "uart.h"
#include "gpio.h"
#include "nvic.h"


static UART_CallBackType UART_CallBackTable[4] = {NULL};


int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  
{ 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}


 /**
 * @brief  串口快速初始化程序
 * @code
 *      初始化UART2: 9600-0-8-1,主优先级preepri=2,响应优先级subpri=2,使能中断ITsta=ENABLE
 *      UART_QuickInit(HW_UART2, 9600, 2, 2, ENABLE);
 * @endcode
 * @param[in]   instance 模块号
 *              @arg HW_UART1 1端口
 *              @arg HW_UART2 2端口
 *              @arg HW_UART3 3端口
 * @param[in]   bound   波特率: 9600,115200....
 * @param[in]   preepri 抢占优先级，默认group2，可选值0,1,2,3
 * @param[in]   subpri  响应优先级，默认group2，可选值0,1,2,3
 * @param[in]   ITsta   使能/失能中断，可选值ENABLE，DISABLE
 * @retval      UART初始化结果，1初始化正确，0初始化失败
 */
uint8_t UART_QuickInit(int instance, int bound, int preepri, int subpri,  FunctionalState ITsta)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
		
		switch(instance)
    {
        case HW_UART1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
						USART_DeInit(USART1);                                   //复位串口1
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;               //USART1_TX   PA.9
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //复用推挽输出
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化PA9  
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //USART1_RX	  PA.10
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化PA10

						NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
						NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=preepri ;//抢占优先级3
						NVIC_InitStructure.NVIC_IRQChannelSubPriority = subpri;		    //子优先级3
						NVIC_InitStructure.NVIC_IRQChannelCmd = ITsta;			          //IRQ通道使能
						NVIC_Init(&NVIC_InitStructure);	                              //根据指定的参数初始化VIC寄存器						

						USART_InitStructure.USART_BaudRate = bound;                		//一般设置为9600;
						USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //字长为8位数据格式
						USART_InitStructure.USART_StopBits = USART_StopBits_1;        //一个停止位
						USART_InitStructure.USART_Parity = USART_Parity_No;           //无奇偶校验位
						USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
						USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

						USART_Init(USART1, &USART_InitStructure);                     //初始化串口
						USART_ITConfig(USART1, USART_IT_RXNE, ITsta);                 //开启中断
						USART_Cmd(USART1, ENABLE);                                    //使能串口 				
				
        case HW_UART2:
            RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
						USART_DeInit(USART2);                                   //复位串口1
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;               //USART1_TX   PA.9
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //复用推挽输出
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化PA9  
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;              //USART1_RX	  PA.10
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化PA10

						NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
						NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=preepri ;//抢占优先级3
						NVIC_InitStructure.NVIC_IRQChannelSubPriority = subpri;		  //子优先级3
						NVIC_InitStructure.NVIC_IRQChannelCmd = ITsta;			    //IRQ通道使能
						NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器						

						USART_InitStructure.USART_BaudRate = bound;              //一般设置为9600;
						USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
						USART_InitStructure.USART_StopBits = USART_StopBits_1;     //一个停止位
						USART_InitStructure.USART_Parity = USART_Parity_No;        //无奇偶校验位
						USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
						USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

						USART_Init(USART2, &USART_InitStructure);                     //初始化串口
						USART_ITConfig(USART2, USART_IT_RXNE, ITsta);                //开启中断
						USART_Cmd(USART2, ENABLE);                    //使能串口 				 //根据设定参数初始
            break;
        case HW_UART3:
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
						RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
						USART_DeInit(USART3);                                   //复位串口1
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;               //USART1_TX   PA.9
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //复用推挽输出
						GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化PA9  
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;              //USART1_RX	  PA.10
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //浮空输入
						GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化PA10

						NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
						NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=preepri ;//抢占优先级3
						NVIC_InitStructure.NVIC_IRQChannelSubPriority = subpri;		  //子优先级3
						NVIC_InitStructure.NVIC_IRQChannelCmd = ITsta;			    //IRQ通道使能
						NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器						

						USART_InitStructure.USART_BaudRate = bound;              //一般设置为9600;
						USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
						USART_InitStructure.USART_StopBits = USART_StopBits_1;     //一个停止位
						USART_InitStructure.USART_Parity = USART_Parity_No;        //无奇偶校验位
						USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
						USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

						USART_Init(USART3, &USART_InitStructure);                     //初始化串口
						USART_ITConfig(USART3, USART_IT_RXNE, ITsta);                //开启中断
						USART_Cmd(USART3, ENABLE);                    //使能串口 				 //根据设定参数初始
            break;
        
        default:
						return 0;					
    }
		return 1;
}

/**
 * @brief  串口读字节程序
 * @code
 *      // 读UART2，unit16_t ch;
 *      UART_ReadByte(HW_UART2, &ch);
 * @endcode
 * @param[in]   instance 模块号
 *              @arg HW_UART1 1端口
 *              @arg HW_UART2 2端口
 *              @arg HW_UART3 3端口
 * @retval      UART读结果，1读正确，0读失败
 */
uint8_t UART_ReadByte(uint32_t instance, uint16_t *ch)
{
	switch(instance)
	{
		case HW_UART1:
				*ch = (uint16_t)(USART1->DR & (uint16_t)0x01FF);
				break;
		case HW_UART2:
			  *ch = (uint16_t)(USART2->DR & (uint16_t)0x01FF);
				break;
		case HW_UART3:
				*ch = (uint16_t)(USART3->DR & (uint16_t)0x01FF);
				break;	
		default:
				return 0;
	}
	return 1;
}

/**
 * @brief  串口写字节程序
 * @code
 *      // 写UART2，unit16_t ch=ox7a;
 *      UART_WriteByte(HW_UART2, ch);
 * @endcode
 * @param[in]   instance 模块号
 *              @arg HW_UART1 1端口
 *              @arg HW_UART2 2端口
 *              @arg HW_UART3 3端口
 */
void UART_WriteByte(uint32_t instance, uint16_t ch)
{
	switch(instance)
	{
		case HW_UART1:
				USART1->DR = (ch & (uint16_t)0x01FF);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
				break;
		case HW_UART2:
        USART2->DR = (ch & (uint16_t)0x01FF);
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}
				break;
		case HW_UART3:
				 USART3->DR = (ch & (uint16_t)0x01FF);
				 while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){}
				break;	
	}
}


void UART_CallbackInstall(uint32_t instance, UART_CallBackType AppCBFun)
{
    /* init moudle */
    if(AppCBFun != NULL)
    {
        UART_CallBackTable[instance] = AppCBFun;
    }
}
/**
 * @brief  系统接收中断函数，用户不必使用，只需更改文件开头的注册函数即可。
 */
void USART1_IRQHandler(void)                
{		
	  uint16_t Res;
	  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
		{
				 UART_ReadByte(HW_UART1, &Res); 
			   if(UART_CallBackTable[HW_UART1] != NULL)UART_CallBackTable[HW_UART1](Res);
		} 
} 


/**
 * @brief  系统接收中断函数，用户不必使用，只需更改文件开头的注册函数即可。
 */
void USART2_IRQHandler(void)                
{
		uint16_t Res;
	  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
		{  	 	  
			 UART_ReadByte(HW_UART2, &Res); 
			 if(UART_CallBackTable[HW_UART2] != NULL)UART_CallBackTable[HW_UART2](Res);
		} 
} 


/**
 * @brief  系统接收中断函数，用户不必使用，只需更改文件开头的注册函数即可。
 */
void USART3_IRQHandler(void)                
{
		uint16_t Res;
	  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  
		{
  	 	  UART_ReadByte(HW_UART3, &Res); 
			  if(UART_CallBackTable[HW_UART3] != NULL)UART_CallBackTable[HW_UART3](Res);
		} 
} 

void UART_SendString(uint32_t instance, u8 *ch){
	while(*ch){
		uint16_t cht = *ch++;
		UART_WriteByte(instance, cht); 
	}
}







