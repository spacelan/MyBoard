#include "sys.h"
#include "usart.h"
#include "time.h"
#include "led.h"
#include "i2c.h"
#include "flash.h"
#include "inv_mpu.h"
#include "storage.h"

int main(void)
{
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz 
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MyTime_Init();	    	 //延时函数初始化	 
	MyUSART_Init(115200);
	MyI2C_Init();
	MyLED_Config();
//	while(mpu_init());
	MyStorage_Init();
	
	while(1)
	{
		uint8_t data[64];
//		uint8_t size = MyUSART_GetRxBufSize();
//		if(size)
		{
//			uint16_t halfWord = 0xabcd;
//			MyFlash_Write(0x08008000,&halfWord,1);
//			halfWord = 0;
//			MyFlash_Read(0x08008000,&halfWord,1);
//			MyUSART_Transmit((void *)(&halfWord),2);
			

			short accel[3] = {0x1234,0x5678,0x9abc};
			short a[3];
//			MyUSART_Receive((void*)accel,size);
			MyStorage_Write(accel,STORAGE_DATA_TYPE_ACCEL_BIAS);
			MyStorage_Program();
			MyStorage_Read(a,STORAGE_DATA_TYPE_ACCEL_BIAS);
//			MyUSART_Transmit((void*)a,6);
		}
		Delay_ms(500);
		MyLED_Toggle();
	}
}

