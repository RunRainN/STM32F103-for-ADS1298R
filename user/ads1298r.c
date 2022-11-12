/**
  ******************************************************************************
  * @file           : ads1298r.c
  * @brief          : ADS1298R����Դ�ļ�
  * @details        : ����ADS1298R��ʼ��������ָ���д�Ĵ�������ȡ��ͨ����������
  * @author         : RunRain CQU-BME-219 QQ:1121192423
  * @date           : 2022/11/10
  * @version        : V1.0
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  * @verbatim
  * �޸���ʷ:    
  *      1. ���ڣ�2022/11/10
  *         ���ߣ�RunRain
  *         �޸ģ�
  * @endverbatim
  ******************************************************************************
  */

#include "sysinc.h"


typedef struct 
{
    u8 id;            /* ID���ƼĴ��� */
    u8 config1;				/* ���üĴ��� */
    u8 config2;				/* ���üĴ��� */
		u8 config3;				/* ���üĴ��� */
    u8 loff;          /* ����������� */
    u8 ch1set;        /* ͨ��һ���� */
    u8 ch2set;        /* ͨ�������� */
		u8 ch3set;        /* ͨ�������� */
    u8 ch4set;        /* ͨ�������� */
		u8 ch5set;        /* ͨ�������� */
    u8 ch6set;        /* ͨ�������� */
		u8 ch7set;        /* ͨ�������� */
    u8 ch8set;        /* ͨ�������� */
    u8 rld_sensp;     /* �������� */
		u8 rld_sensn;     /* �������� */
    u8 loff_sensp;    /* ���������� */
		u8 loff_sensn;    /* ���������� */
		u8 loff_flip;     /* �������䷭ת */
    u8 loff_statp;    /* ��������״̬ */
		u8 loff_statn;    /* ��������״̬ */
		u8 gpio;          /* GPIO���� */
    u8 pace;          /* �� */
    u8 resp;          /* ���� */
		u8 config4;				/* ���üĴ��� */
    u8 wct1;					/* ����ѷ���Ķ��Ӻ���ǿ�������� */
		u8 wct2;					/* ����ѷ���Ķ��ӿ��� */
}ADS1298R_Regs;



/* ads1298R�Ĵ�����ʼ��ֵ */
static ADS1298R_Regs ADS1298R_regs = {
                                0xD2,   /* �̶���ַ0xD2 */
                                0x86,   /* �߷ֱ���ģʽ��500sps������ */
																0x10,		/* �����ź�δʹ�� */
																0xDC,		/* 2.4V��׼��ѹ���ڲ�RLDREF�ź� */
																0x02,		/* ��������Ƶ�ʲ�ʹ�� */
																0x00,		/* CH1 �����缫��6������ */
																0x00,		/* CH2 �����缫��6������ */
																0x00,		/* CH3 �����缫��6������ */
																0x10,		/* CH4 �����缫��1������ */
																0x00,		/* CH5 �����缫��6������ */
																0x00,		/* CH6 �����缫��6������ */
																0x00,		/* CH7 �����缫��6������ */
																0x00,		/* CH8 �����缫��6������ */
                                0x00,   /* δʹ�� */
                                0x00,   /* δʹ�� */
	                              0x00,   /* δʹ�� */
                                0x00,   /* δʹ�� */
	                              0x00,   /* δʹ�� */
                                0x00,   /* δʹ�� */
	                              0x00,   /* δʹ�� */
                                0x00,   /* GPIOȫ��� */
																0x00,		/* δʹ�� */
                                0xF6,   /* �������� �ڲ����� */
                                0x00,   /* �ڲ�����64kHz����Ƶ�ʣ���������Ƚ������� */
																0x00,		/* δʹ�� */
																0x00,		/* δʹ�� */
                                };

																

/** @brief ��ʼ��ADS1298R
  * @details 500SPS��6�����棬��ʼ��ʧ�����һֱ���ADS1298R��ֱ����ʼ���ɹ�
	* @param[in] ��		
  * @retval ��
  */
void ADS1298R_Init(void)
{
    u8 id;
    
    ADS1298R_GPIOInit();
    
    ADS1298R_CS = 1;
    
    ADS1298R_RESET = 0;   /* Ӳ����λ */
    ADS1298R_START = 0;
    SYSTICK_DelayMs(1000);
    ADS1298R_RESET = 1;
    SYSTICK_DelayMs(100); 
    
	  ads1298R_SendCmd(_SDATAC);    /* �����λ����ֹͣ������״̬ */
    SYSTICK_DelayMs(100);
    ads1298R_SendCmd(_RESET);
    SYSTICK_DelayMs(1000);
    ads1298R_SendCmd(_SDATAC);
    SYSTICK_DelayMs(100);
    
    do
    {
			id = ADS1298R_RWReg(0, 0x00, 0x00);		/* ʶ��оƬ�ͺţ�ADS1298RΪ0xD2 */
			SYSTICK_DelayMs(1000);
			PCout(13) = ~PCout(13);
		}while(id != ADS1298R_regs.id);
    
    /* д������ */
    ADS1298R_RWRegs(1, 0x00, 26, (u8 *)&ADS1298R_regs) ;
    SYSTICK_DelayMs(10) ;
    
    ads1298R_SendCmd(_RDATAC) ; /* ��������ģʽ */
    SYSTICK_DelayMs(10) ;		
    ads1298R_SendCmd(_START) ;	/* ���Ϳ�ʼ����ת������Ч������START���ţ� */	
    SYSTICK_DelayMs(10) ;	
}



/** @brief ��ʼ����ADS1298R�����ź�������GPIO
  * @details ��ʼ����CS��START��RESET��DRDY������GPIO
  * @param[in] ��
  * @retval ��
  */
void ADS1298R_GPIOInit(void)
{
    GPIO_InitTypeDef 	GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	 
	
    /* CS��START��RESET */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   /* ������� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    /* DRDY������ʱ�ߵ�ƽ���ɼ�ʱ�͵�ƽ��Ч */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   /* ��������*/
    GPIO_Init(GPIOA, &GPIO_InitStructure) ;		
}   



/** @brief ADS1298R����ָ��
  * @details ���͵��ֽ�ָ��
  * @param[in] cmdΪ������
  * @retval ��
  */
u8 ads1298R_SendCmd(u8 cmd)
{
  u8 rx = 0;
    
	ADS1298R_CS = 0;    /* ѡ���豸 */   
	SYSTICK_DelayUs(100) ;
	
	rx = SPI_ReadWriteByte(SPI1, cmd);
	
  SYSTICK_DelayUs(100) ;
	ADS1298R_CS =1;      /* �ͷ��豸 */
    
  return rx;
}



/** @brief ADS1298R��д�����Ĵ���
  * @details ����ֵΪ���Ĵ���������ֵ��д�Ĵ�������0
  * @param[in] rw=1д��rw=0����regΪ�Ĵ�����ַ��
  * д�Ĵ���dataΪд���ֵ�����Ĵ���data��Ϊ0x00
  * @retval ��
  */
u8 ADS1298R_RWReg(u8 rw, u8 reg, u8 data)
{
	u8 rx = 0;
    
	ADS1298R_CS = 0;    /* ѡ���豸 */
	SYSTICK_DelayUs(1);
  
	if(rw) SPI_ReadWriteByte(SPI1, _WREG|reg);		/* ����дָ�� */
	else SPI_ReadWriteByte(SPI1, _RREG|reg);		/* ���Ͷ�ָ�� */
	
	SPI_ReadWriteByte(SPI1, 0x00);	/* ֻ��дһ������ */
    
	rx = SPI_ReadWriteByte(SPI1, data);
    
	SYSTICK_DelayUs(1);
	ADS1298R_CS = 1;    /* �ͷ��豸 */
    
	return rx;
}



/** @brief ADS1298R��ָ���Ĵ�����ʼ��дһ�������ļĴ���
  * @details ��Ҫ���ڳ�ʼ��ADS1298R����д�Ĵ���
  * @param[in] rw=1д��rw=0����regΪ�Ĵ�����ַ��sizeΪ��д�Ĵ����ĸ�����
  * chΪ��д�Ĵ���ָ�룬��������ʱ��Ϊ��д������׵�ַ
  * @retval ��
  */
void ADS1298R_RWRegs(u8 rw, u8 reg, u8 size, u8 *ch)
{
    u8 i;

    ADS1298R_CS = 0;    /* ѡ���豸 */	
    SYSTICK_DelayUs(100);

		if(rw)	/* д�Ĵ��� */
		{
			SPI_ReadWriteByte(SPI1, _WREG|reg);
			SYSTICK_DelayUs(100);
			SPI_ReadWriteByte(SPI1, size - 1);
			SYSTICK_DelayUs(100);
			for(i=0; i<size; i++)
			{
					SPI_ReadWriteByte(SPI1, *ch++);
					SYSTICK_DelayUs(100);				
			}
	  }
		else	/* ���Ĵ��� */
		{
			SPI_ReadWriteByte(SPI1, _RREG|reg);
			SYSTICK_DelayUs(100);
			SPI_ReadWriteByte(SPI1, size - 1);
			SYSTICK_DelayUs(100);
			for(i=0; i<size; i++)
			{
				*ch++ = SPI_ReadWriteByte(SPI1, 0x00);
				SYSTICK_DelayUs(100);
			}
		}
    ADS1298R_CS = 1;
}



/** @brief ��ȡת�����adԭʼ����,��ѯ��ʽ��ȡ
  * @details ԭʼ���ݣ�����λ��Ϊ 24 ��״̬λ + ÿ��ͨ�� 24 λ �� 8 ��ͨ�� = 216 λ��27�ֽڣ�
  * @param[in] bufΪ�洢ԭʼ���������ָ�룬�����СӦ��С��27Bytes
  * [2:0]Ϊ״̬�֣�[5:3]Ϊͨ��һ�����[8:6]Ϊͨ�������������ͨ�������ֽ����������š�
  * @retval NONE
  */
void ADS1298R_GetValues(u8 *buf)
{
    u8 i;
    
    while(ADS1298R_DRDY);   /* �ȴ�ת������ */
    
    ADS1298R_CS = 0;

    for(i=0; i<27; i++)        /* ��ȡת����� */
    {	
        *buf++ = SPI_ReadWriteByte(SPI1, 0x00);	
    }

    ADS1298R_CS = 1;
} 
