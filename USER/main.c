#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "hc_sr04.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
    delay_init(180);  //初始化延时函数 
    USART1_init(9600);//初始化串口波特率为9600
	
    TIM4_Init(9998,7199); //定时器初始化
    HCSR04_GPIO_Init(); //超声波传感器初始化
	
    while(1)
    {
			u8 i=0;
			while(i<10){
				delay_ms(100); // 超声波工作周期建议在60ms以上，以防止发射信号对回响信号的影响
				i++;
			}
			
        HCSR04_Start(); // 使能超声波传感器，测算距离一次
    }
}

