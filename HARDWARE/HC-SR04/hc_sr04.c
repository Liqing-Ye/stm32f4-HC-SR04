#include "hc_sr04.h"

float Distance;//s32 Distance;

// HCSR04_GPIO_Init() ������ʵ���߼���
//1��ʹ�� IO ��ʱ�ӣ���ʼ�� IO ��Ϊ���롣
//2��ʹ�� SYSCFG ʱ�ӣ����� IO �����ж��ߵ�ӳ���ϵ��
//3����ʼ�������жϣ����ô��������ȡ�
//4�������жϷ��飨NVIC������ʹ���жϡ�
//5����д�жϷ�������
void HCSR04_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure; 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ�� SYSCFG ʱ�ӣ��ⲿ�ж�
	
	// GPIO PD1 ����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;// PD1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //���빦��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);  //��ʼ��IO��
	
	// GPIO PD0 ������ͨ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ�������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);  //��ʼ��IO��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1); // ���� GPIO ���ж��ߵ�ӳ���ϵ: ���ж��� 1 �� GPIOD ӳ������,��GPIOD.1 �� EXTI1 �ж�������
	
	//�ⲿ�ж�����
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; //�ж�
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising; //�����ش���
	EXTI_Init(&EXTI_InitStructure);
	
	//�����жϷ��飨NVIC������ʹ���ж�
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn; //ʹ���ⲿ�ж�ͨ�� 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ� 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //��Ӧ���ȼ� 2
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI1_IRQHandler(void)
{
	delay_us(10);
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET) //�ж��ж���1�ϵ��ж��Ƿ�������־λ�Ƿ���λ��
	{
		TIM_SetCounter(TIM4,0); 
		TIM_Cmd(TIM4,ENABLE);
		while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1));  //�ȴ�PD1�͵�ƽ	
		TIM_Cmd(TIM4,DISABLE);
		
		Distance=(TIM_GetCounter(TIM4)*340)/200.0;
		printf("Distance:%f cm\r\n",Distance); 
		
		EXTI_ClearITPendingBit(EXTI_Line1); // ����ж���1���жϱ�־λ
	}
}

void HCSR04_Start(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_0);   //��Trig����Ϊ�ߵ�ƽ
	delay_us(12);               //��������10us����������������ģ�鹤��
	GPIO_ResetBits(GPIOD,GPIO_Pin_0); 
}

