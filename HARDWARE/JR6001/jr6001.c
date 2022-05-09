#include "jr6001.h"

void JR6001_Init(void){
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //GPIOC1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入功能
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
//	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PC1 for BUSY
	
	USART1_init(9600);//初始化串口波特率为9600
}

void JR6001_Voice(u16 Data){ // 播放语音文件“Data.mp3” 
//	while(BUSY){
//		delay_ms(10);
//	}
	//printf("A8:02/00001*mp3"); /
	printf("A8:02/%05d*mp3",Data); // “A8:02/” 播放Flash里面的歌曲
	delay_ms(100);
}

void JR6001_VolumeSetting(u16 setting){
	printf("AF:%02d",setting); 
}


