#include "led.h"
#include "stm32f10x.h" 

void m_LED_Init(void){
	GPIO_InitTypeDef gpioinitstruct;
	gpioinitstruct.GPIO_Pin = LED_PIN_LEFT | LED_PIN_MID | LED_PIN_RIGHT;
	gpioinitstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioinitstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT,&gpioinitstruct);
}
