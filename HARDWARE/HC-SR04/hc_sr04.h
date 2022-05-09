#ifndef _HCSR04_H
#define _HCSR04_H
#include "sys.h"
#include "delay.h"
#include "usart.h"

//超声波传感器HC-SR04
//Trig PD0 使能模块
//Echo PD1 可捕获返回距离信息

void HCSR04_GPIO_Init(void); // 初始化IO
void HCSR04_Start(void); // 使能传感器(测试距离一次)
#endif
