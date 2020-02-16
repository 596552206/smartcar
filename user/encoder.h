#ifndef __ENCODER_H
#define __ENCODER_H

void m_Encoder_Init_1(void);
void m_Encoder_Init_2(void);
void m_Encoder_Init_TIM1(void);
int read_encoder_l(void);
int read_encoder_r(void);
int read_encoder_v_l(void);
int read_encoder_v_r(void);
void EncoderTim2IRQ(void);
void NVIC_CONF(void);
#endif
