#include "encoder.h"
#include "stm32f10x.h" 
#include "usart.h"
#include "delay.h"
#include "common.h"
void m_Encoder_Init_1(void){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//TIM_DeInit(TIM2);
	//TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2,ENABLE);
}

void m_Encoder_Init_2(void){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//TIM_DeInit(TIM4);
	//TIM_InternalClockConfig(TIM4);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4,&TIM_ICInitStructure);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4,ENABLE);
}

void m_Encoder_Init_TIM1(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_Period = 1999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM1,ENABLE);
}

int read_encoder_l(void){
	return ENCODER_LEFT;
}
int read_encoder_r(void){
	return ENCODER_RIGHT;
}
int read_encoder_v_l(void){
	return ENCODER_LEFT/3.2;
}
int read_encoder_v_r(void){
	return ENCODER_RIGHT/3.2;
}

void NVIC_CONF(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
}
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET){
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
void TIM4_IRQHandler(void){
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!= RESET){
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}
void TIM1_UP_IRQHandler(void){
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!= RESET){
			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
			ENCODER_LEFT = (short)TIM2->CNT;
			TIM2->CNT=0;
			ENCODER_RIGHT = (short)TIM4->CNT;
			TIM4->CNT=0;
		}
}
