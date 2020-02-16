#ifndef __PWM_H
#define __PWM_H

#include "sys.h"

/*********************************************************
TIM3输出4路pwm,单独控制占空比
**********************************************************/

#include "stm32f10x.h"
 
#define  CLOCK 72000
 
extern u16 arr; //预加载值
 
extern u16 psc; //分频值
 
/*******************************************************************************
* 函 数 名         :TIM3_PWM_Init(u16 arr,u16 psc)
* 函数功能     : 4路pwm初始化函数
* 输    入         : 频率，分频
频率：
//Fpwm = 72M / ((arr+1)*(psc+1))(单位：Hz)

* 输    出         : 无
*******************************************************************************/
void TIM3_PWM_Init(u16 Fpwm);
 
/*******************************************************************************
* 函 数 名         :ste_pwm1_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm1_duty(float value);
 
/*******************************************************************************
* 函 数 名         :ste_pwm2_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm2_duty(float value);
 
/*******************************************************************************
* 函 数 名         :ste_pwm3_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm3_duty(float value);
 
/*******************************************************************************
* 函 数 名         :ste_pwm4_duty(u16 value)
* 函数功能     : 设置pwm占空比函数
* 输    入         : 占空比 
* 输    出         : 无
*******************************************************************************/
void ste_pwm4_duty(float value);
 
#endif
