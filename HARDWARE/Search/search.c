#include "search.h"

void Search_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5; //PD1,PD2,PD3,PD4,PD5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //输入功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOD,&GPIO_InitStructure);  //初始化PA1

}
void Run(void)
{
		if(LL_IN == WHITE && LM_IN == BLACK && MM_IN == WHITE){ // 直行
			  TIM_SetCompare1(TIM4,50);// 速度计算公式  (x/65535)*100% = 占全速的百分比（占空比）
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,50); 
        TIM_SetCompare4(TIM4,0); //右轮
		}
    else if (LL_IN == BLACK && LM_IN == BLACK && MM_IN == WHITE) {  //左小转
        TIM_SetCompare1(TIM4,15);
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,50);
        TIM_SetCompare4(TIM4,0);
    }
    else if(LL_IN == WHITE && LM_IN == BLACK && MM_IN == BLACK) { //右小转
        TIM_SetCompare1(TIM4,50);
        TIM_SetCompare2(TIM4,0); //300 
        TIM_SetCompare3(TIM4,15); 
        TIM_SetCompare4(TIM4,0); //180
    }
		else if(LL_IN == BLACK && LM_IN == WHITE && MM_IN == WHITE) { //左大转
        TIM_SetCompare1(TIM4,14);
        TIM_SetCompare2(TIM4,0); //60
        TIM_SetCompare3(TIM4,50); 
        TIM_SetCompare4(TIM4,0); //300
    }
		else if(LL_IN == WHITE && LM_IN == WHITE && MM_IN == BLACK) { //右大转
        TIM_SetCompare1(TIM4,50);
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,14); 
        TIM_SetCompare4(TIM4,0);
    }
    else { //异常 停
        TIM_SetCompare1(TIM4,0);
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,0);
        TIM_SetCompare4(TIM4,0);
    }
		
//测试电机：
//	TIM_SetCompare1(TIM4,65535);
//	TIM_SetCompare2(TIM4,0); 
//	TIM_SetCompare3(TIM4,65535);
//	TIM_SetCompare4(TIM4,0);
}

void ControlSpeed(void) { // 速度缓慢增加的调速函数（未完成）
    u16 led0pwmval=0;
    u8 dir=1;
    if(dir)led0pwmval++;//dir==1 led0pwmval递增
    else led0pwmval--;	//dir==0 led0pwmval递减
    if(led0pwmval>1000) {
        dir=0;//led0pwmval到达1000后，方向为递减
        //TIM_SetCompare1(TIM4,10000);
    }
    if(led0pwmval==0) {
        dir=1;	//led0pwmval递减到0后，方向改为递增
        //TIM_SetCompare1(TIM4,40000);
    }
    TIM_SetCompare1(TIM4,led0pwmval); //修改比较值，修改占空比
    TIM_SetCompare3(TIM4,led0pwmval); //修改比较值，修改占空比
    delay_ms(10);
}
