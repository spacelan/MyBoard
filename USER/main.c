#include "sys.h"
#include "usart.h"
#include "time.h"
#include "led.h"
#include "i2c.h"
	
int main(void)
{
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	MyTime_Init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MyUSART_Init(9600);
	MyLED_Config();
	MyLED(ON);
	MyI2c_Init();
	while(1)
	{
		
		u8 byte[64];
		u8 size = MyUSART_GetRxBufSize();
		if(size)
		{
			while(MyI2c_Read(0x68,0x75,byte) == false) ;
			MyUSART_Receive(&byte[1],size);
			MyUSART_Transmit(byte,size + 1);
		}
		Delay_ms(500);
		MyLED_Toggle();
	}
}

