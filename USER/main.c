#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "myled.h"

//Mini STM32�����巶������1
//�����ʵ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//ʵ������
// DS0 ,DS1��˸��ʱ����Ϊ300ms.
//��ϸ��ʵ�������Լ�Ӳ��������鿴��STM32����ȫ�ֲᡷ3.2��������ʵ��
	
int main(void)
{
	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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

