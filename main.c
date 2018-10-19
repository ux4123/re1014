#include "stm32f10x.h"
#include "mpu6050.h"
#include "common.h"
#include "inv_mpu.h"
#include "dianji.h"

/*
#define usartDebug 0
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  delay_init();
	dianji_init();
	myUsart_init();
#if usartDebug
	int i=0;	



#else
#if 1
	MPU_Init();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	while(mpu_dmp_init())
 	{
		u3_printf("lll\r\n");
		delay_ms(200);
	}  
	u3_printf("iic\r\n");
	mpu_exit_int(0,0);
	u3_printf("iic\r\n");
#endif	
	STBY(1);
#if 1
	TIM_SetCompare1(TIM3,130);
	TIM_SetCompare4(TIM3,110);

	AIN1(1);AIN2(0);
	BIN1(1);BIN2(0);
#endif
#endif	
	while(1)
	{
#if usartDebug
		for(i=0;i<100;i++)
		{
			delay_ms(10);
			u3_printf("%d\r\n",-i/3+10);
		}
#endif
//		USART_SendData(USART3,0XFF);
//		u3_printf("ssss%d\r\n",a);

	}
}
*/
int main(void)
{
	int i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
  delay_init();
	myUsart_init();
//**************************************************************    MPU6050
	MPU_Init();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	while(mpu_dmp_init())
 	{
//		u3_printf("lll\r\n");
//		u1_printf("iic\r\n");	
		delay_ms(200);
	}  
//	u3_printf("iic\r\n");
//	u1_printf("iic\r\n");	
	mpu_exit_int(2,2);
//**************************************************************
//	u3_printf("iic\r\n");	
//	u1_printf("iic\r\n");	
/****************************************************************/  //dianji
	dianji_init();
	STBY(1);
/****************************************************************/
	TIM_SetCompare1(TIM3,100);
	TIM_SetCompare4(TIM3,100);


	AIN1(1);AIN2(0);
	BIN1(1);BIN2(0);
	
	while(1)
	{
//		u1_printf("iic\r\n");	
//		u3_printf("iic\r\n");	
		
	}
}
