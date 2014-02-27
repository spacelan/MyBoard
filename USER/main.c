#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "myled.h"

//Mini STM32开发板范例代码1
//跑马灯实验		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//实验现象：
// DS0 ,DS1闪烁，时间间隔为300ms.
//详细的实验现象以及硬件连接请查看《STM32不完全手册》3.2按键输入实验
	
int main(void)
{
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MyUSART_Init(9600);
	MyLED_Config();
	MyLED(ON);
	while(1)
	{
		u8 byte[2];
		byte[0] = 0xaa;
		if(MyUSART_GetRxBufSize() >= 1)
		{
			MyUSART_Receive(byte,1);
			MyUSART_Transmit(byte,1);
		}
		delay_ms(500);
		MyLED_Toggle();
	}
}

