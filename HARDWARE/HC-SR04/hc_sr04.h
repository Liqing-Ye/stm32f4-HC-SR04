#ifndef _HCSR04_H
#define _HCSR04_H
#include "sys.h"
#include "delay.h"
#include "usart.h"

//������������HC-SR04
//Trig PD0 ʹ��ģ��
//Echo PD1 �ɲ��񷵻ؾ�����Ϣ

void HCSR04_GPIO_Init(void); // ��ʼ��IO
void HCSR04_Start(void); // ʹ�ܴ�����(���Ծ���һ��)
#endif
