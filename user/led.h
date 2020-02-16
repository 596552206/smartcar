#ifndef __LED_H
#define __LED_H

#define LED_PORT GPIOA
#define LED_PIN_LEFT GPIO_Pin_11
#define LED_PIN_RIGHT GPIO_Pin_10
#define LED_PIN_MID GPIO_Pin_12

#define LED_LEFT(a) if (a) \
											GPIO_SetBits(LED_PORT,LED_PIN_LEFT);\
										else \
											GPIO_ResetBits(LED_PORT,LED_PIN_LEFT);
										
#define LED_MID(a) if (a) \
											GPIO_SetBits(LED_PORT,LED_PIN_MID);\
										else \
											GPIO_ResetBits(LED_PORT,LED_PIN_MID);
										
#define LED_RIGHT(a) if (a) \
											GPIO_SetBits(LED_PORT,LED_PIN_RIGHT);\
										else \
											GPIO_ResetBits(LED_PORT,LED_PIN_RIGHT);

void m_LED_Init(void);
										
#endif
