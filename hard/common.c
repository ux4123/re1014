#include "common.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "stdarg.h"
#include "string.h"

u8 USART1_TX_BUF[200];
u8 USART3_TX_BUF[100];

void mpu_exit_int(u8 PreempPriority,u8 SubPriority)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;	
//////*************************************************************
	//*************************************************************	
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);    
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);
    //*************************************************************
//////*************************************************************	   	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
//////*************************************************************	
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);		
//////*************************************************************	
	NVIC_InitStructure.NVIC_IRQChannel =EXTI3_IRQn;			
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreempPriority;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;					
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					
    NVIC_Init(&NVIC_InitStructure);  	   
}
void u1_printf(char* fmt, ...)  
{  
	u16 i, j; 
	va_list ap; 
	va_start(ap, fmt);
	vsprintf((char*)USART1_TX_BUF, fmt, ap);
	va_end(ap);
	i = strlen((const char*)USART1_TX_BUF); 		
	for(j = 0 ; j < i ; j++)							
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
		USART_SendData(USART1, USART1_TX_BUF[j]); 
	} 
}
void u3_printf(char* fmt, ...)  
{  
	u16 i, j; 
	va_list ap; 
	va_start(ap, fmt);
	vsprintf((char*)USART3_TX_BUF, fmt, ap);
	va_end(ap);
	i = strlen((const char*)USART3_TX_BUF); 		
	for(j = 0 ; j < i ; j++)							
	{
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) ;
		USART_SendData(USART3, USART3_TX_BUF[j]); 
	} 
}

////void EXTI9_5_IRQHandler(void)
////{
////	float pitch,roll,yaw;
////  //  if(EXTI_GetFlagStatus(EXTI_Line15)!=RESET)
////    {
////////     while((mpu_dmp_get_data(&pitch,&roll,&yaw))!=0) 
////////		{
////////			u3_printf("error is \r\n");
////////			delay_ms(500);
////////		}
////		 u3_printf("sda\r\n");
//////		MPU_Get_Gyroscope(gx,gy,gz);


////        EXTI_ClearITPendingBit(EXTI_Line5);
////    }


////}











