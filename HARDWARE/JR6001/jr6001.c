#include "jr6001.h"

void JR6001_Init(void){
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //GPIOC1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//���빦��
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
//	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PC1 for BUSY
	
	USART1_init(9600);//��ʼ�����ڲ�����Ϊ9600
}

void JR6001_Voice(u16 Data){ // ���������ļ���Data.mp3�� 
//	while(BUSY){
//		delay_ms(10);
//	}
	//printf("A8:02/00001*mp3"); /
	printf("A8:02/%05d*mp3",Data); // ��A8:02/�� ����Flash����ĸ���
	delay_ms(100);
}

void JR6001_VolumeSetting(u16 setting){
	printf("AF:%02d",setting); 
}


