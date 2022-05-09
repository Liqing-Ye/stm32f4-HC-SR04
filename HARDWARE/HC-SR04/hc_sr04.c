#include "hc_sr04.h"

float Distance;//s32 Distance;

// HCSR04_GPIO_Init() 函数的实现逻辑：
//1）使能 IO 口时钟，初始化 IO 口为输入。
//2）使能 SYSCFG 时钟，设置 IO 口与中断线的映射关系。
//3）初始化线上中断，设置触发条件等。
//4）配置中断分组（NVIC），并使能中断。
//5）编写中断服务函数。
void HCSR04_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure; 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能 SYSCFG 时钟，外部中断
	
	// GPIO PD1 输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;// PD1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //输入功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure);  //初始化IO口
	
	// GPIO PD0 推挽普通输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure);  //初始化IO口
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1); // 配置 GPIO 与中断线的映射关系: 将中断线 1 与 GPIOD 映射起来,即GPIOD.1 与 EXTI1 中断线连接
	
	//外部中断配置
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; //中断
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising; //上升沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	//配置中断分组（NVIC），并使能中断
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn; //使能外部中断通道 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //使能外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //响应优先级 2
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI1_IRQHandler(void)
{
	delay_us(10);
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET) //判断中断线1上的中断是否发生（标志位是否置位）
	{
		TIM_SetCounter(TIM4,0); 
		TIM_Cmd(TIM4,ENABLE);
		while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1));  //等待PD1低电平	
		TIM_Cmd(TIM4,DISABLE);
		
		Distance=(TIM_GetCounter(TIM4)*340)/200.0;
		printf("Distance:%f cm\r\n",Distance); 
		
		EXTI_ClearITPendingBit(EXTI_Line1); // 清除中断线1的中断标志位
	}
}

void HCSR04_Start(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_0);   //将Trig设置为高电平
	delay_us(12);               //持续大于10us触发，触发超声波模块工作
	GPIO_ResetBits(GPIOD,GPIO_Pin_0); 
}

