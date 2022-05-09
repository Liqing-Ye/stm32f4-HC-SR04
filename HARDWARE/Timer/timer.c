#include "timer.h"

void TIM4_Init(u16 arr,u16 psc) // TIM4 rewrite
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; //定时器参数初始化
	
	//初始化定时器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4时钟使能 
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //输入捕获会用到
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器4
}
