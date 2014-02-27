#include "sys.h"
#include "usart.h"
#include "time.h"
#include "led.h"
#include "i2c.h"
	
int main(void)
{
	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	MyTime_Init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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

