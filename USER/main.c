#include "sys.h"
#include "usart.h"
#include "time.h"
#include "led.h"
#include "i2c.h"
#include "inv_mpu.h"

void Jump2App(uint32_t addr)
{
	uint32_t reset = *(uint32_t*)(addr+4);
	uint32_t msp = *(uint32_t*)(addr);

	__set_MSP(msp);
	( (void(*)(void)) (reset) )();
}
 
int main(void)
{
//	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz // ！！已经在启动代码中执行！！
	SCB->VTOR = FLASH_BASE | 0x8000; /* Vector Table Relocation in Internal FLASH. */
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	MyTime_Init();	    	 //延时函数初始化	 
	MyUSART_Init(115200);
	MyI2C_Init();
	MyLED_Config();
	MyLED_Toggle();
//	Jump2App(0x08008000);
	while(1)
	{
		Delay_ms(100);
		MyLED_Toggle();
	}
}

