#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "hc_sr04.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
    delay_init(180);  //��ʼ����ʱ���� 
    USART1_init(9600);//��ʼ�����ڲ�����Ϊ9600
	
    TIM4_Init(9998,7199); //��ʱ����ʼ��
    HCSR04_GPIO_Init(); //��������������ʼ��
	
    while(1)
    {
			u8 i=0;
			while(i<10){
				delay_ms(100); // �������������ڽ�����60ms���ϣ��Է�ֹ�����źŶԻ����źŵ�Ӱ��
				i++;
			}
			
        HCSR04_Start(); // ʹ�ܳ��������������������һ��
    }
}

