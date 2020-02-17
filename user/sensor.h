#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32f10x.h"    
#include "sys.h"
#include "common.h"
#include "pid.h"

#define SENSOR_PORT GPIOB
#define SENSOR_PIN_LEFT_SIDE GPIO_Pin_8
#define SENSOR_PIN_LEFT_MID GPIO_Pin_5
#define SENSOR_PIN_RIGHT_SIDE GPIO_Pin_3
#define SENSOR_PIN_RIGHT_MID GPIO_Pin_4

#define SENSOR_LEFT_SIDE GPIO_ReadInputDataBit(SENSOR_PORT,SENSOR_PIN_LEFT_SIDE)
#define SENSOR_LEFT_MID GPIO_ReadInputDataBit(SENSOR_PORT,SENSOR_PIN_LEFT_MID)
#define SENSOR_RIGHT_SIDE GPIO_ReadInputDataBit(SENSOR_PORT,SENSOR_PIN_RIGHT_SIDE)
#define SENSOR_RIGHT_MID GPIO_ReadInputDataBit(SENSOR_PORT,SENSOR_PIN_RIGHT_MID)

#define IDEAL_OFFSET 5

void m_Sensor_Init(void);
void get_offset(void);
void calc_speed(void);

//是否开启红外传感器多次记录模式，开启后，只要连续n次检测中有一个为1，则传感器返回值就是1.
#define IS_BIT_LOG_ON 0
#define bitnum2log 1
//如果要保留最近的四组数据，缓冲区将和00001111按位与，所以log_bit=15
static u8 left_side_logged =0;
static u8 left_mid_logged =0;
static u8 right_side_logged =0;
static u8 right_mid_logged =0;
_Bool read_sensor_left_side(void);
_Bool read_sensor_left_mid(void);
_Bool read_sensor_right_side(void);
_Bool read_sensor_right_mid(void);

#endif
