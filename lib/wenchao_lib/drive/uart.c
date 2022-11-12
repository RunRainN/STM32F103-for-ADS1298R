/**
  ******************************************************************************
  * @file    uart.c
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.22
  * @note    �˳���ΪARM��uart�ĵײ��̣������ڹٷ��ײ��Ķ��η�װ��
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
 * @brief  ���ڿ��ٳ�ʼ������
 * @code
 *      ��ʼ��UART2: 9600-0-8-1,�����ȼ�preepri=2,��Ӧ���ȼ�subpri=2,ʹ���ж�ITsta=ENABLE
 *      UART_QuickInit(HW_UART2, 9600, 2, 2, ENABLE);
 * @endcode
 * @param[in]   instance ģ���
 *              @arg HW_UART1 1�˿�
 *              @arg HW_UART2 2�˿�
 *              @arg HW_UART3 3�˿�
 * @param[in]   bound   ������: 9600,115200....
 * @param[in]   preepri ��ռ���ȼ���Ĭ��group2����ѡֵ0,1,2,3
 * @param[in]   subpri  ��Ӧ���ȼ���Ĭ��group2����ѡֵ0,1,2,3
 * @param[in]   ITsta   ʹ��/ʧ���жϣ���ѡֵENABLE��DISABLE
 * @retval      UART��ʼ�������1��ʼ����ȷ��0��ʼ��ʧ��
 */
uint8_t UART_QuickInit(int instance, int bound, int preepri, int subpri,  FunctionalState ITsta)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
		
		switch(instance)
    {
        case HW_UART1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
						USART_DeInit(USART1);                                   //��λ����1
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;               //USART1_TX   PA.9
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //�����������
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��PA9  
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //USART1_RX	  PA.10
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��PA10

						NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
						NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=preepri ;//��ռ���ȼ�3
						NVIC_InitStructure.NVIC_IRQChannelSubPriority = subpri;		    //�����ȼ�3
						NVIC_InitStructure.NVIC_IRQChannelCmd = ITsta;			          //IRQͨ��ʹ��
						NVIC_Init(&NVIC_InitStructure);	                              //����ָ���Ĳ�����ʼ��VIC�Ĵ���						

						USART_InitStructure.USART_BaudRate = bound;                		//һ������Ϊ9600;
						USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ֳ�Ϊ8λ���ݸ�ʽ
						USART_InitStructure.USART_StopBits = USART_StopBits_1;        //һ��ֹͣλ
						USART_InitStructure.USART_Parity = USART_Parity_No;           //����żУ��λ
						USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
						USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

						USART_Init(USART1, &USART_InitStructure);                     //��ʼ������
						USART_ITConfig(USART1, USART_IT_RXNE, ITsta);                 //�����ж�
						USART_Cmd(USART1, ENABLE);                                    //ʹ�ܴ��� 				
				
        case HW_UART2:
            RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
						USART_DeInit(USART2);                                   //��λ����1
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;               //USART1_TX   PA.9
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //�����������
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��PA9  
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;              //USART1_RX	  PA.10
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
						GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��PA10

						NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
						NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=preepri ;//��ռ���ȼ�3
						NVIC_InitStructure.NVIC_IRQChannelSubPriority = subpri;		  //�����ȼ�3
						NVIC_InitStructure.NVIC_IRQChannelCmd = ITsta;			    //IRQͨ��ʹ��
						NVIC_Init(&NVIC_InitStructure);	                        //����ָ���Ĳ�����ʼ��VIC�Ĵ���						

						USART_InitStructure.USART_BaudRate = bound;              //һ������Ϊ9600;
						USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
						USART_InitStructure.USART_StopBits = USART_StopBits_1;     //һ��ֹͣλ
						USART_InitStructure.USART_Parity = USART_Parity_No;        //����żУ��λ
						USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
						USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

						USART_Init(USART2, &USART_InitStructure);                     //��ʼ������
						USART_ITConfig(USART2, USART_IT_RXNE, ITsta);                //�����ж�
						USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 				 //�����趨������ʼ
            break;
        case HW_UART3:
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
						RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
						USART_DeInit(USART3);                                   //��λ����1
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;               //USART1_TX   PA.9
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //�����������
						GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��PA9  
							
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;              //USART1_RX	  PA.10
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //��������
						GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��PA10

						NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
						NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=preepri ;//��ռ���ȼ�3
						NVIC_InitStructure.NVIC_IRQChannelSubPriority = subpri;		  //�����ȼ�3
						NVIC_InitStructure.NVIC_IRQChannelCmd = ITsta;			    //IRQͨ��ʹ��
						NVIC_Init(&NVIC_InitStructure);	                        //����ָ���Ĳ�����ʼ��VIC�Ĵ���						

						USART_InitStructure.USART_BaudRate = bound;              //һ������Ϊ9600;
						USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
						USART_InitStructure.USART_StopBits = USART_StopBits_1;     //һ��ֹͣλ
						USART_InitStructure.USART_Parity = USART_Parity_No;        //����żУ��λ
						USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
						USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

						USART_Init(USART3, &USART_InitStructure);                     //��ʼ������
						USART_ITConfig(USART3, USART_IT_RXNE, ITsta);                //�����ж�
						USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 				 //�����趨������ʼ
            break;
        
        default:
						return 0;					
    }
		return 1;
}

/**
 * @brief  ���ڶ��ֽڳ���
 * @code
 *      // ��UART2��unit16_t ch;
 *      UART_ReadByte(HW_UART2, &ch);
 * @endcode
 * @param[in]   instance ģ���
 *              @arg HW_UART1 1�˿�
 *              @arg HW_UART2 2�˿�
 *              @arg HW_UART3 3�˿�
 * @retval      UART�������1����ȷ��0��ʧ��
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
 * @brief  ����д�ֽڳ���
 * @code
 *      // дUART2��unit16_t ch=ox7a;
 *      UART_WriteByte(HW_UART2, ch);
 * @endcode
 * @param[in]   instance ģ���
 *              @arg HW_UART1 1�˿�
 *              @arg HW_UART2 2�˿�
 *              @arg HW_UART3 3�˿�
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
 * @brief  ϵͳ�����жϺ������û�����ʹ�ã�ֻ������ļ���ͷ��ע�ắ�����ɡ�
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
 * @brief  ϵͳ�����жϺ������û�����ʹ�ã�ֻ������ļ���ͷ��ע�ắ�����ɡ�
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
 * @brief  ϵͳ�����жϺ������û�����ʹ�ã�ֻ������ļ���ͷ��ע�ắ�����ɡ�
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







