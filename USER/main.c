#include "sys.h"
#include "usart.h"
#include "time.h"
#include "led.h"
	
int main(void)
{
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	MyTime_Init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MyUSART_Init(9600);
	MyLED_Config();
	MyLED(ON);
	while(1)
	{
		u8 byte[64];
		u8 size = MyUSART_GetRxBufSize();
		if(size)
		{
			MyUSART_Receive(byte,size);
			MyUSART_Transmit(byte,size);
		}
		Delay_ms(100);
		MyLED_Toggle();
	}
}

