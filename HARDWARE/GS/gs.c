#include "gs.h"

//��ʼ��ADC															   
void  GS_Init(void)
{    
  Adc_Init();

}	


  
// ��ò��ԭʼ�Ҷ�ADֵ
u16 Get_GS_Value(void)
{
	return Get_Adc_Average(ADC_Channel_0, 10);// 10��ȡƽ��
}
   


