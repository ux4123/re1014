#include "myUsart.h"
//void usart1Dma(void)
//{
//		DMA_InitTypeDef dma_s;
//	
//		dma_s.DMA_BufferSize=
//		dma_s.DMA_DIR=
//		dma_s.DMA_M2M=
//		dma_s.DMA_MemoryBaseAddr=
//		dma_s.DMA_MemoryDataSize=
//		dma_s.DMA_MemoryInc=
//		dma_s.DMA_Mode=
//		dma_s.DMA_PeripheralBaseAddr=
//		dma_s.DMA_PeripheralDataSize=
//		dma_s.DMA_PeripheralInc=
//		dma_s.DMA_Priority=
//	
//		DMA_Init(DMA1_Channel5,&dma_s);
//}
u8 myUsart_init(void)
{
    GPIO_InitTypeDef GPIO_S;
    USART_InitTypeDef UART_S;
		NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
		GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
	
    GPIO_S.GPIO_Pin=GPIO_Pin_6;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB,&GPIO_S);
//**************************************************************	chuan kou shu ru jiao xu yao floating 
		GPIO_S.GPIO_Pin=GPIO_Pin_7;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_S);
//**************************************************************		
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//????????3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//???????3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//
		NVIC_Init(&NVIC_InitStructure);	//
	

		
    UART_S.USART_BaudRate=9600;
    UART_S.USART_WordLength=USART_WordLength_8b;
    UART_S.USART_StopBits=USART_StopBits_1;
    UART_S.USART_Parity=USART_Parity_No;
    UART_S.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    UART_S.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init(USART1,&UART_S);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1,ENABLE);
/*******************************************************************/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_S.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
    GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB,&GPIO_S);

    USART_Init(USART3,&UART_S);

    USART_Cmd(USART3,ENABLE);
//************************************************************************
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		
		GPIO_S.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_S.GPIO_Pin=GPIO_Pin_2;
	
		GPIO_Init(GPIOD,&GPIO_S);	
		
		UART_S.USART_BaudRate=9600;
		UART_S.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		UART_S.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		UART_S.USART_Parity=USART_Parity_No;
		UART_S.USART_StopBits=USART_StopBits_1;
		UART_S.USART_WordLength=USART_WordLength_8b;
		USART_Init(UART5,&UART_S);
		
		NVIC_InitStructure.NVIC_IRQChannel=UART5_IRQn ;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStructure);
		
		USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
		
    return 0;
}
//u8 myUsart_init(void)
//{
//    
//	USART_InitTypeDef UART_S;
//	GPIO_InitTypeDef GPIO_S;
//	NVIC_InitTypeDef NVIC_S;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3|RCC_APB1Periph_UART5,ENABLE);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	//************************************************************A9(TX) A10(RX)
//	GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_S.GPIO_Pin=GPIO_Pin_10;
//	GPIO_S.GPIO_Speed=GPIO_Speed_10MHz;
//	
//	GPIO_Init(GPIOB,&GPIO_S);
//	
//	GPIO_S.GPIO_Mode=GPIO_Mode_IPU;
//	GPIO_S.GPIO_Pin=GPIO_Pin_11;
//	
//	GPIO_Init(GPIOB,&GPIO_S);	
//	
//	GPIO_S.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_S.GPIO_Pin=GPIO_Pin_2;
//	
//	GPIO_Init(GPIOD,&GPIO_S);	
//	
//	//************************************************************UART1
//	UART_S.USART_BaudRate=9600;
//	UART_S.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
//	UART_S.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
//	UART_S.USART_Parity=USART_Parity_No;
//	UART_S.USART_StopBits=USART_StopBits_1;
//	UART_S.USART_WordLength=USART_WordLength_8b;
//	USART_Init(USART3,&UART_S);
//	
//	UART_S.USART_BaudRate=9600;
//	UART_S.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
//	UART_S.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
//	UART_S.USART_Parity=USART_Parity_No;
//	UART_S.USART_StopBits=USART_StopBits_1;
//	UART_S.USART_WordLength=USART_WordLength_8b;
//	USART_Init(UART5,&UART_S);
//	//************************************************************
//	NVIC_S.NVIC_IRQChannel=USART3_IRQn;
//	NVIC_S.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_S.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_S.NVIC_IRQChannelSubPriority=1;	
//	NVIC_Init(&NVIC_S);
//	
//	NVIC_S.NVIC_IRQChannel=UART5_IRQn ;
//	NVIC_S.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_S.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_S.NVIC_IRQChannelSubPriority=0;
//	NVIC_Init(&NVIC_S);
//	
//	//************************************************************	
//	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
//	USART_Cmd(USART3,ENABLE);
//	
//	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
//	USART_Cmd(UART5,ENABLE);
//    return 0;
//}
