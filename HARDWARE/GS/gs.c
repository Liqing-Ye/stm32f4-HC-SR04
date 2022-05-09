#include "gs.h"

//初始化ADC															   
void  GS_Init(void)
{    
  Adc_Init();

}	


  
// 获得测得原始灰度AD值
u16 Get_GS_Value(void)
{
	return Get_Adc_Average(ADC_Channel_0, 10);// 10次取平均
}
   


