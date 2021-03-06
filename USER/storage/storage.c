#include "storage.h"
#include "flash.h"

#define MY_STORAGE_DATA_NUM 7
#define MY_STORAGE_DATA_LENGTH 24 //字节
#define MY_STORAGE_ADDR_OFFSET 0x0800FC00

uint8_t dataBuf[MY_STORAGE_DATA_LENGTH];
uint8_t StorageDataLength[24];
uint32_t currentAddress;
//将24字节的数据循环存放在1024字节的块中
//初始化时要找到数据在块中的哪个位置。。。。
//若找不到。。。擦出快，数据从0开始
void MyStorage_Init()
{
	uint32_t addr;
	uint16_t temp;
	for(addr=0;addr<1024-MY_STORAGE_DATA_LENGTH;addr+=2)
	{
		temp = MyFlash_ReadHalfWord(MY_STORAGE_ADDR_OFFSET + addr);
		if(temp == 0xabcd)
			break;
	}
	if(addr >= 1024-MY_STORAGE_DATA_LENGTH)
	{
		FLASH_Unlock();
		FLASH_ErasePage(MY_STORAGE_ADDR_OFFSET);
		currentAddress = MY_STORAGE_ADDR_OFFSET;
		FLASH_ProgramHalfWord(currentAddress + STORAGE_DATA_TYPE_HEAD,0xabcd);
		FLASH_Lock();
	}
	else
	{
		currentAddress = MY_STORAGE_ADDR_OFFSET + addr;
	}
	MyFlash_Read(currentAddress,(uint16_t*)dataBuf,MY_STORAGE_DATA_LENGTH /2);
	
	StorageDataLength[STORAGE_DATA_TYPE_HEAD] = 2;
	StorageDataLength[STORAGE_DATA_TYPE_ACCEL_BIAS] = 6;
	StorageDataLength[STORAGE_DATA_TYPE_GYRO_BIAS] = 6;
	StorageDataLength[STORAGE_DATA_TYPE_MOTOR_BASE] = 4;
	StorageDataLength[STORAGE_DATA_TYPE_P] = 2;
	StorageDataLength[STORAGE_DATA_TYPE_I] = 2;
	StorageDataLength[STORAGE_DATA_TYPE_D] = 2;
}

//将数据写入RAM
void MyStorage_Write(void *data,uint8_t type)
{
	uint32_t addr;
	for(addr=0;addr<StorageDataLength[type];addr+=2)
		*(uint16_t*)((uint8_t*)dataBuf + type + addr) = *(uint16_t*)((uint8_t*)data + addr);
}
//从RAM读取数据
void MyStorage_Read(void *data,uint8_t type)
{
	uint32_t addr;
	for(addr=0;addr<StorageDataLength[type];addr+=2)
		*(uint16_t*)((uint8_t*)data + addr) = *(uint16_t*)((uint8_t*)dataBuf + type + addr);
}
//将RAM中数据写入flash，在多个区块中循环写入，减少flash刷写次数，增加了的复杂度。。。。
void MyStorage_Program()
{
	uint32_t addr;
	FLASH_Unlock();
	if(1024 - (currentAddress - MY_STORAGE_ADDR_OFFSET + MY_STORAGE_DATA_LENGTH) >= MY_STORAGE_DATA_LENGTH)
	{
		for(addr=0;addr<MY_STORAGE_DATA_LENGTH;addr+=4)
			FLASH_ProgramWord(currentAddress + addr,0);
		currentAddress += MY_STORAGE_DATA_LENGTH;
	}
	else
	{
		FLASH_ErasePage(MY_STORAGE_ADDR_OFFSET);
		currentAddress = MY_STORAGE_ADDR_OFFSET;
	}
	MyFlash_Write(currentAddress,(uint16_t*)dataBuf,MY_STORAGE_DATA_LENGTH / 2);
	FLASH_Lock();
}
