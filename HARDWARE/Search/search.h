#ifndef _SEARCH_H
#define _SEARCH_H
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//��ʱ����ʼ������
//��ʱ������PWM
////////////////////////////////////////////////////////////////////////////////// 	

#define BLACK 1
#define WHITE 0  //����ģ���ϵ�LED��������⵽�Ǻ�������
#define LL_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)
#define LM_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)
#define MM_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)
#define MR_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) //��·ѭ���ò���PD4
#define RR_IN          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5) //��·ѭ���ò���PD5

void Search_Init(void); //��ʼ��
void Run(void);   //�ж�����
void ControlSpeed(void); // ���Ƶ���ٶ�
#endif

