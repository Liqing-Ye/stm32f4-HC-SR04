#include "search.h"

void Search_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5; //PD1,PD2,PD3,PD4,PD5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //���빦��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOD,&GPIO_InitStructure);  //��ʼ��PA1

}
void Run(void)
{
		if(LL_IN == WHITE && LM_IN == BLACK && MM_IN == WHITE){ // ֱ��
			  TIM_SetCompare1(TIM4,50);// �ٶȼ��㹫ʽ  (x/65535)*100% = ռȫ�ٵİٷֱȣ�ռ�ձȣ�
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,50); 
        TIM_SetCompare4(TIM4,0); //����
		}
    else if (LL_IN == BLACK && LM_IN == BLACK && MM_IN == WHITE) {  //��Сת
        TIM_SetCompare1(TIM4,15);
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,50);
        TIM_SetCompare4(TIM4,0);
    }
    else if(LL_IN == WHITE && LM_IN == BLACK && MM_IN == BLACK) { //��Сת
        TIM_SetCompare1(TIM4,50);
        TIM_SetCompare2(TIM4,0); //300 
        TIM_SetCompare3(TIM4,15); 
        TIM_SetCompare4(TIM4,0); //180
    }
		else if(LL_IN == BLACK && LM_IN == WHITE && MM_IN == WHITE) { //���ת
        TIM_SetCompare1(TIM4,14);
        TIM_SetCompare2(TIM4,0); //60
        TIM_SetCompare3(TIM4,50); 
        TIM_SetCompare4(TIM4,0); //300
    }
		else if(LL_IN == WHITE && LM_IN == WHITE && MM_IN == BLACK) { //�Ҵ�ת
        TIM_SetCompare1(TIM4,50);
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,14); 
        TIM_SetCompare4(TIM4,0);
    }
    else { //�쳣 ͣ
        TIM_SetCompare1(TIM4,0);
        TIM_SetCompare2(TIM4,0); 
        TIM_SetCompare3(TIM4,0);
        TIM_SetCompare4(TIM4,0);
    }
		
//���Ե����
//	TIM_SetCompare1(TIM4,65535);
//	TIM_SetCompare2(TIM4,0); 
//	TIM_SetCompare3(TIM4,65535);
//	TIM_SetCompare4(TIM4,0);
}

void ControlSpeed(void) { // �ٶȻ������ӵĵ��ٺ�����δ��ɣ�
    u16 led0pwmval=0;
    u8 dir=1;
    if(dir)led0pwmval++;//dir==1 led0pwmval����
    else led0pwmval--;	//dir==0 led0pwmval�ݼ�
    if(led0pwmval>1000) {
        dir=0;//led0pwmval����1000�󣬷���Ϊ�ݼ�
        //TIM_SetCompare1(TIM4,10000);
    }
    if(led0pwmval==0) {
        dir=1;	//led0pwmval�ݼ���0�󣬷����Ϊ����
        //TIM_SetCompare1(TIM4,40000);
    }
    TIM_SetCompare1(TIM4,led0pwmval); //�޸ıȽ�ֵ���޸�ռ�ձ�
    TIM_SetCompare3(TIM4,led0pwmval); //�޸ıȽ�ֵ���޸�ռ�ձ�
    delay_ms(10);
}
