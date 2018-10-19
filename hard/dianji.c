#include "dianji.h"
#if 0
void dianji_init(void)
{
    GPIO_InitTypeDef GPIO_S;
    TIM_TimeBaseInitTypeDef TIM_S;
    TIM_OCInitTypeDef TIM_OS;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_S.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_3;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_S);

    TIM_S.TIM_Prescaler=71;
    TIM_S.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_S.TIM_Period=999;
    TIM_S.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_S.TIM_RepetitionCounter=0;

    TIM_TimeBaseInit(TIM2,&TIM_S);

    TIM_OS.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OS.TIM_OutputState=TIM_OutputState_Enable;
 // TIM_OS.TIM_OutputNState  
    TIM_OS.TIM_Pulse=500;       
    TIM_OS.TIM_OCPolarity=TIM_OCPolarity_High;
 // TIM_OS.TIM_OCNPolarity=
//  TIM_OS.TIM_OCIdleState=TIM_OCIdleState_Reset;
//  TIM_OS.TIM_OCNIdleState=

    TIM_OC2Init(TIM2,&TIM_OS);

    TIM_OC4Init(TIM2,&TIM_OS);

    TIM_CtrlPWMOutputs(TIM2,ENABLE);
    
    TIM_Cmd(TIM2,ENABLE);
		
		GPIO_S.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_S);
		
		
}
#endif
void dianji_init(void)
{
    GPIO_InitTypeDef GPIO_S;
    TIM_TimeBaseInitTypeDef TIM_S;
    TIM_OCInitTypeDef TIM_OS;

    GPIO_S.GPIO_Pin=GPIO_Pin_1;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB,&GPIO_S);

		GPIO_S.GPIO_Pin=GPIO_Pin_6;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_S);

	
    TIM_S.TIM_Prescaler=71;
    TIM_S.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_S.TIM_Period=999;
    TIM_S.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_S.TIM_RepetitionCounter=0;

    TIM_TimeBaseInit(TIM3,&TIM_S);

    TIM_OS.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OS.TIM_OutputState=TIM_OutputState_Enable;
 // TIM_OS.TIM_OutputNState  
    TIM_OS.TIM_Pulse=500;       
    TIM_OS.TIM_OCPolarity=TIM_OCPolarity_High;
 // TIM_OS.TIM_OCNPolarity=
//  TIM_OS.TIM_OCIdleState=TIM_OCIdleState_Reset;
//  TIM_OS.TIM_OCNIdleState=

    TIM_OC1Init(TIM3,&TIM_OS);

    TIM_OC4Init(TIM3,&TIM_OS);

    TIM_CtrlPWMOutputs(TIM3,ENABLE);
    
    TIM_Cmd(TIM3,ENABLE);
		
		GPIO_S.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_S);
		
		GPIO_S.GPIO_Pin=GPIO_Pin_7;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_S);
		
		GPIO_S.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_12;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_S);
		
}

