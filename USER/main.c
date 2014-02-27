#include "sys.h"
#include "usart.h"
#include "time.h"
#include "led.h"
#include "i2c.h"
#include "inv_mpu.h"

int main(void)
{
	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz 
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	MyTime_Init();	    	 //��ʱ������ʼ��	 
	MyUSART_Init(9600);
	MyI2c_Init();
	MyLED_Config();
	MyLED(ON);
	while(mpu_init());
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

