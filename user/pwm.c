#include "pwm.h"
/*********************************************************
TIM3输出4路pwm,单独控制占空比
*********************************************************/
 

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
 
 u16 arr;
 u16 psc;
 
void TIM3_PWM_Init(u16 Fpwm)
{  
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;
 
arr=CLOCK/Fpwm-1; //不分频。PWM频率=72000/(899+1)=80Khz 
psc=0;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能
                                                                                     
                                                                             
 
   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 ; //TIM_CH1
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 ; //TIM_CH1
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
 
        TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值         80K
        TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
        TIM_TimeBaseStructure.TIM_ClockDivision =0; //设置时钟分割:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//TIM3通道一
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
        TIM_OCInitStructure.TIM_Pulse = 1;  /*占空长度 0 – 周期(max)*/
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
        TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
//TIM3通道二
  TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1; /*占空长度 0 – 周期(max)*/
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//TIM3通道三
  TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1; /*占空长度 0 – 周期(max)*/
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
//TIM3通道四
  TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1; /*占空长度 0 – 周期(max)*/
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
  TIM_CtrlPWMOutputs(TIM3,ENABLE);        //MOE 主输出使能        
  TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
        TIM_Cmd(TIM3, ENABLE);  //使能TIM1
}
 
/*******************************************************************************
* 函 数 名         :ste_pwm1_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm1_duty(float value)

{
TIM3->CCR1=arr-(value*arr/100);

}
 
/*******************************************************************************
* 函 数 名         :ste_pwm2_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm2_duty(float value)
{
TIM3->CCR2=arr-(value*arr/100);

}
 
/*******************************************************************************
* 函 数 名         :ste_pwm3_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm3_duty(float value)

{
TIM3->CCR3=arr-(value*arr/100);

}
 
 
/*******************************************************************************
* 函 数 名         :ste_pwm4_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm4_duty(float value)

{
TIM3->CCR4=arr-(value*arr/100);

}
