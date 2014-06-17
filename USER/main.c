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
//	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz // �����Ѿ�������������ִ�У���
	SCB->VTOR = FLASH_BASE | 0x8000; /* Vector Table Relocation in Internal FLASH. */
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	MyTime_Init();	    	 //��ʱ������ʼ��	 
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

