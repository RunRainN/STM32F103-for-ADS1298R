//================================================================================
//STM32F103         多功能通讯控制演示模块
//================================================================================
//FLASH_S.C/H       片内FLASH读写函数                          BY SAGAHDS 20190306
//================================================================================
#ifndef __FLASH_S_H
#define __FLASH_S_H
//================================================================================
//BY SAGAHDS 20190306
extern unsigned char FLASH_RDBUFF[256];     	//FLASH读缓存
extern unsigned char FLASH_WRBUFF[256];     	//FLASH写缓存
extern unsigned char FLASH_FLAG;     					//FLASH标志位

#define FLASH_FLAG_ENABLE 0x01 	//置1安装了FLASH
//================================================================================
void FLASH_Configuration(unsigned char Enable);					//初始化
unsigned int FLASH_ReadINT(unsigned long address);	//在指定地址读出int
void FLASH_ReadMoreINT(unsigned long startAddress, unsigned int *readData, unsigned int countToRead);			//在指定地址读出数据到指定位置
void FLASH_ReadMoreCHAR(unsigned int startAddress, unsigned char *readData, unsigned int countToRead);		//在指定地址读出数据到指定位置
void FLASH_WriteMoreCHAR(unsigned int startAddress, unsigned char *writeData, unsigned int countToWrite);	//在指定地址写入数据从指定位置
//================================================================================
#endif
//================================================================================

