//#include "stm32f4xx.h"
//#include "epaper.h" 
//#include "picture.h"
//#include "epr.h"
//#include "INA226.h"
//#include "delay.h"
//ErrorStatus HSEStartUpStatus;

///* Private function prototypes -----------------------------------------------*/
//void epr_init(void)
//{
//	RCC_Configuration();
//	//GPIO setting
//	GPIO_Configuration();
//	EPD_HW_Init(); //Electronic paper initialization	
//	EPD_SetRAMValue_BaseMap(gImage_22); //Partial refresh background color [5000]
//	}
///************************************************
//************************************************/
///////////////////////main//////////////////////////////////////
//void epr(short Voltage)
//{
//						short tens,ones,Voltage_ones,Voltage_dotones;
//						if((Voltage/10000)%10>=1)
//						{
//							Voltage_ones=9;
//							Voltage_dotones=9;
//						}
//						else{
//							Voltage_ones=(Voltage/1000)%10;
//							Voltage_dotones=(Voltage/100)%10;
//						}
//					  
//						
//						if(Voltage>=10000)
//						{
//							tens=9;
//							ones=9;
//						}
//						else if(Voltage<2000)
//						{
//							tens=0;
//							ones=0;
//						}
//						else{
//							tens=(((Voltage-2000)/80)/10)%10;
//							ones=((Voltage-2000)/80)%10;
//						}
//						
//						
//						EPD_Dis_Part_myself(140,70,Num[ones],         //x-A,y-A,DATA-A
//																			80,40,Num[Voltage_dotones],         //x-B,y-B,DATA-B
//																			140,110,Num[tens],       //x-C,y-C,DATA-C
//																			80,100,Num[Voltage_ones],         //x-D,y-D,DATA-D
//																			80,195,gImage_uncharged,32,64);	//
//						
//				
//////////////////////////////////////////////////////////////////////////	
//			//Clear screen
//			//goto Clear;
////		Clear:
////		EPD_HW_Init(); //Electronic paper initialization
////		EPD_WhiteScreen_White(); //Show all white
////		EPD_DeepSleep();  //Enter deep sleep	

//}
/////////////////////////////////////////////////////////////








///*******************************************************************************
//* Function Name  : RCC_Configuration
//* Description    : Configures the different system clocks.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void RCC_Configuration(void)
//{
// 
//  // Reset RCC clock configuration
//  RCC_DeInit();
// 
//  // Enable external crystal
//  RCC_HSEConfig(RCC_HSE_ON);
//  
//  // Waiting for the external crystal to stabilize
//  HSEStartUpStatus = RCC_WaitForHSEStartUp();
//  if(HSEStartUpStatus == SUCCESS)
//  {
//    // Set the phase-locked loop frequency PLLCLK = 8MHz * 9 = 72 MHz
//    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
//  }
//  else {
//    // Enable internal crystal
//    RCC_HSICmd(ENABLE);
//    // Waiting for the internal crystal to stabilize
//    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

//    // Set the phase-locked loop frequency PLLCLK = 8MHz/2 * 16 = 64 MHz 
//    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
//  }

//    // Enable flash prefetch cache
//  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

//  //Set the code delay, FLASH_Latency_2 is two delay cycles
//  FLASH_SetLatency(FLASH_Latency_2);
//	
//  //Set the system total clock
//  RCC_HCLKConfig(RCC_SYSCLK_Div1); 

//  //Set the high speed device total clock, RCC_HCLK_Div1 is the system clock divided by 1
//  RCC_PCLK2Config(RCC_HCLK_Div1); 

//  //Set the low speed device total clock, RCC_HCLK_Div2 is the system clock divided by 2
//  RCC_PCLK1Config(RCC_HCLK_Div2);
//  
//  //Enable phase-locked loop multiplier
//  RCC_PLLCmd(ENABLE);
//  
//  // Waiting for the frequency of the phase-locked loop to multiply after frequency stabilization
//  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
//  
//  // Select the phase-locked loop clock as the system clock
//  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//  
//  // Waiting for setup to complete
//  while(RCC_GetSYSCLKSource() != 0x08);
//    
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
//            RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,
//            ENABLE);
//						

//}

///*******************************************************************************
//* Function Name  :  GPIO_Configuration
//* Description    : Configures the different system clocks.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void GPIO_Configuration(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;
// 	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);//使能PD、E端口时钟
//	  				     	
//	
//	 //CS-->PD8   SCK-->PD9  SDO--->PD10 (PB7, PB8, PB9)
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;		//Port configuration
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
//	GPIO_Init(GPIOB, &GPIO_InitStructure);	  	
//	
//	
//	
//	 // D/C--->PE15	   RES-->PE14  (PB5, PB6)
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;		//Port configuration
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
//	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				     		
//	
//	// BUSY--->PB4
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//Pull down input
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);				//Initialize GPIO
//	
//	 //LED
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		//Port configuration
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
////	GPIO_Init(GPIOC, &GPIO_InitStructure);
//}

///*******************************************************************************
//* Function Name  : NVIC_Configuration
//* Description    : Configures Vector Table base location.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void NVIC_Configuration(void)
//{ 
//  //NVIC_InitTypeDef NVIC_InitStructure;
//  ;
//}


//#ifdef  DEBUG
///*******************************************************************************
//* Function Name  : assert_failed
//* Description    : Reports the name of the source file and the source line number
//*                  where the assert_param error has occurred.
//* Input          : - file: pointer to the source file name
//*                  - line: assert_param error line source number
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void assert_failed(u8* file, u32 line)
//{ 
//  /* User can add his own implementation to report the file name and line number,
//     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

//  /* Infinite loop */
//  while (1)
//  {
//  }
//}
//#endif






