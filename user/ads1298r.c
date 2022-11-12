/**
  ******************************************************************************
  * @file           : ads1298r.c
  * @brief          : ADS1298R驱动源文件
  * @details        : 包含ADS1298R初始化、发送指令、读写寄存器、获取各通道采样数据
  * @author         : RunRain CQU-BME-219 QQ:1121192423
  * @date           : 2022/11/10
  * @version        : V1.0
  * @copyright      : Copyright (C) 
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  * @verbatim
  * 修改历史:    
  *      1. 日期：2022/11/10
  *         作者：RunRain
  *         修改：
  * @endverbatim
  ******************************************************************************
  */

#include "sysinc.h"


typedef struct 
{
    u8 id;            /* ID控制寄存器 */
    u8 config1;				/* 配置寄存器 */
    u8 config2;				/* 配置寄存器 */
		u8 config3;				/* 配置寄存器 */
    u8 loff;          /* 导联脱落控制 */
    u8 ch1set;        /* 通道一设置 */
    u8 ch2set;        /* 通道二设置 */
		u8 ch3set;        /* 通道三设置 */
    u8 ch4set;        /* 通道四设置 */
		u8 ch5set;        /* 通道五设置 */
    u8 ch6set;        /* 通道六设置 */
		u8 ch7set;        /* 通道七设置 */
    u8 ch8set;        /* 通道八设置 */
    u8 rld_sensp;     /* 右腿驱动 */
		u8 rld_sensn;     /* 右腿驱动 */
    u8 loff_sensp;    /* 导联脱落检测 */
		u8 loff_sensn;    /* 导联脱落检测 */
		u8 loff_flip;     /* 导联脱落翻转 */
    u8 loff_statp;    /* 导联脱落状态 */
		u8 loff_statn;    /* 导联脱落状态 */
		u8 gpio;          /* GPIO控制 */
    u8 pace;          /* 起搏 */
    u8 resp;          /* 呼吸 */
		u8 config4;				/* 配置寄存器 */
    u8 wct1;					/* 威尔逊中心端子和增强导联控制 */
		u8 wct2;					/* 威尔逊中心端子控制 */
}ADS1298R_Regs;



/* ads1298R寄存器初始化值 */
static ADS1298R_Regs ADS1298R_regs = {
                                0xD2,   /* 固定地址0xD2 */
                                0x86,   /* 高分辨率模式，500sps采样率 */
																0x10,		/* 测试信号未使用 */
																0xDC,		/* 2.4V基准电压，内部RLDREF信号 */
																0x02,		/* 导联脱落频率不使用 */
																0x00,		/* CH1 正常电极，6倍增益 */
																0x00,		/* CH2 正常电极，6倍增益 */
																0x00,		/* CH3 正常电极，6倍增益 */
																0x10,		/* CH4 正常电极，1倍增益 */
																0x00,		/* CH5 正常电极，6倍增益 */
																0x00,		/* CH6 正常电极，6倍增益 */
																0x00,		/* CH7 正常电极，6倍增益 */
																0x00,		/* CH8 正常电极，6倍增益 */
                                0x00,   /* 未使用 */
                                0x00,   /* 未使用 */
	                              0x00,   /* 未使用 */
                                0x00,   /* 未使用 */
	                              0x00,   /* 未使用 */
                                0x00,   /* 未使用 */
	                              0x00,   /* 未使用 */
                                0x00,   /* GPIO全输出 */
																0x00,		/* 未使用 */
                                0xF6,   /* 呼吸配置 内部呼吸 */
                                0x00,   /* 内部呼吸64kHz调制频率，导联脱落比较器禁用 */
																0x00,		/* 未使用 */
																0x00,		/* 未使用 */
                                };

																

/** @brief 初始化ADS1298R
  * @details 500SPS，6倍增益，初始化失败则会一直检测ADS1298R，直到初始化成功
	* @param[in] 无		
  * @retval 无
  */
void ADS1298R_Init(void)
{
    u8 id;
    
    ADS1298R_GPIOInit();
    
    ADS1298R_CS = 1;
    
    ADS1298R_RESET = 0;   /* 硬件复位 */
    ADS1298R_START = 0;
    SYSTICK_DelayMs(1000);
    ADS1298R_RESET = 1;
    SYSTICK_DelayMs(100); 
    
	  ads1298R_SendCmd(_SDATAC);    /* 软件复位，并停止连续读状态 */
    SYSTICK_DelayMs(100);
    ads1298R_SendCmd(_RESET);
    SYSTICK_DelayMs(1000);
    ads1298R_SendCmd(_SDATAC);
    SYSTICK_DelayMs(100);
    
    do
    {
			id = ADS1298R_RWReg(0, 0x00, 0x00);		/* 识别芯片型号，ADS1298R为0xD2 */
			SYSTICK_DelayMs(1000);
			PCout(13) = ~PCout(13);
		}while(id != ADS1298R_regs.id);
    
    /* 写入配置 */
    ADS1298R_RWRegs(1, 0x00, 26, (u8 *)&ADS1298R_regs) ;
    SYSTICK_DelayMs(10) ;
    
    ads1298R_SendCmd(_RDATAC) ; /* 启动连续模式 */
    SYSTICK_DelayMs(10) ;		
    ads1298R_SendCmd(_START) ;	/* 发送开始数据转换（等效于拉高START引脚） */	
    SYSTICK_DelayMs(10) ;	
}



/** @brief 初始化与ADS1298R控制信号相连的GPIO
  * @details 初始化与CS、START、RESET、DRDY相连的GPIO
  * @param[in] 无
  * @retval 无
  */
void ADS1298R_GPIOInit(void)
{
    GPIO_InitTypeDef 	GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	 
	
    /* CS、START、RESET */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   /* 推挽输出 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    /* DRDY，待机时高电平，采集时低电平有效 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   /* 上拉输入*/
    GPIO_Init(GPIOA, &GPIO_InitStructure) ;		
}   



/** @brief ADS1298R发送指令
  * @details 发送单字节指令
  * @param[in] cmd为操作码
  * @retval 无
  */
u8 ads1298R_SendCmd(u8 cmd)
{
  u8 rx = 0;
    
	ADS1298R_CS = 0;    /* 选中设备 */   
	SYSTICK_DelayUs(100) ;
	
	rx = SPI_ReadWriteByte(SPI1, cmd);
	
  SYSTICK_DelayUs(100) ;
	ADS1298R_CS =1;      /* 释放设备 */
    
  return rx;
}



/** @brief ADS1298R读写单个寄存器
  * @details 返回值为读寄存器读到的值，写寄存器返回0
  * @param[in] rw=1写，rw=0读，reg为寄存器地址，
  * 写寄存器data为写入的值，读寄存器data设为0x00
  * @retval 无
  */
u8 ADS1298R_RWReg(u8 rw, u8 reg, u8 data)
{
	u8 rx = 0;
    
	ADS1298R_CS = 0;    /* 选中设备 */
	SYSTICK_DelayUs(1);
  
	if(rw) SPI_ReadWriteByte(SPI1, _WREG|reg);		/* 发送写指令 */
	else SPI_ReadWriteByte(SPI1, _RREG|reg);		/* 发送读指令 */
	
	SPI_ReadWriteByte(SPI1, 0x00);	/* 只读写一个数据 */
    
	rx = SPI_ReadWriteByte(SPI1, data);
    
	SYSTICK_DelayUs(1);
	ADS1298R_CS = 1;    /* 释放设备 */
    
	return rx;
}



/** @brief ADS1298R从指定寄存器开始读写一定数量的寄存器
  * @details 主要用在初始化ADS1298R批量写寄存器
  * @param[in] rw=1写，rw=0读，reg为寄存器地址，size为读写寄存器的个数，
  * ch为读写寄存器指针，函数调用时赋为读写数组的首地址
  * @retval 无
  */
void ADS1298R_RWRegs(u8 rw, u8 reg, u8 size, u8 *ch)
{
    u8 i;

    ADS1298R_CS = 0;    /* 选中设备 */	
    SYSTICK_DelayUs(100);

		if(rw)	/* 写寄存器 */
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
		else	/* 读寄存器 */
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



/** @brief 获取转换后的ad原始数据,轮询方式读取
  * @details 原始数据：数据位数为 24 个状态位 + 每个通道 24 位 × 8 个通道 = 216 位（27字节）
  * @param[in] buf为存储原始数据数组的指针，数组大小应不小于27Bytes
  * [2:0]为状态字，[5:3]为通道一结果，[8:6]为通道二结果，其他通道各三字节依次往后排。
  * @retval NONE
  */
void ADS1298R_GetValues(u8 *buf)
{
    u8 i;
    
    while(ADS1298R_DRDY);   /* 等待转换结束 */
    
    ADS1298R_CS = 0;

    for(i=0; i<27; i++)        /* 读取转换结果 */
    {	
        *buf++ = SPI_ReadWriteByte(SPI1, 0x00);	
    }

    ADS1298R_CS = 1;
} 
