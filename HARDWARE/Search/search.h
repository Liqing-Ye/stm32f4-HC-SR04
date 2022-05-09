#ifndef _SEARCH_H
#define _SEARCH_H
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//定时器初始化函数
//定时器生成PWM
////////////////////////////////////////////////////////////////////////////////// 	

#define BLACK 1
#define WHITE 0  //红外模块上的LED灯亮，检测到非黑线区域
#define LL_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)
#define LM_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)
#define MM_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)
#define MR_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) //三路循迹用不上PD4
#define RR_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5) //三路循迹用不上PD5

void Search_Init(void); //初始化
void Run(void);   //判断赛道
void ControlSpeed(void); // 控制电机速度
#endif

