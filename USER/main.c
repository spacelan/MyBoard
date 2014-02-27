#include "sys.h"
#include "usart.h"
#include "time.h"
#include "led.h"
	
int main(void)
{
	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	MyTime_Init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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

