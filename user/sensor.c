#include "sensor.h"

void m_Sensor_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitTypeDef gpioinitstruct1;
	gpioinitstruct1.GPIO_Pin = SENSOR_PIN_LEFT_SIDE|SENSOR_PIN_LEFT_MID|SENSOR_PIN_RIGHT_MID|SENSOR_PIN_RIGHT_SIDE; //避障传感器引脚
	gpioinitstruct1.GPIO_Mode = GPIO_Mode_IPU;//采用上拉输入模式，传感器默认状态为高电位。
	GPIO_Init(SENSOR_PORT,&gpioinitstruct1);
}

_Bool read_sensor_left_side(void){
	_Bool last_bit = SENSOR_LEFT_SIDE;
	left_side_logged<<=1;
	left_side_logged|=last_bit;
	left_side_logged&=bitnum2log;
	return left_side_logged>0;
}
_Bool read_sensor_left_mid(void){
	_Bool last_bit = SENSOR_LEFT_MID;
	left_mid_logged<<=1;
	left_mid_logged|=last_bit;
	left_mid_logged&=bitnum2log;
	return left_mid_logged>0;
}
_Bool read_sensor_right_side(void){
	_Bool last_bit = SENSOR_RIGHT_SIDE;
	right_side_logged<<=1;
	right_side_logged|=last_bit;
	right_side_logged&=bitnum2log;
	return right_side_logged>0;
}
_Bool read_sensor_right_mid(void){
	_Bool last_bit = SENSOR_RIGHT_MID;
	right_mid_logged<<=1;
	right_mid_logged|=last_bit;
	right_mid_logged&=bitnum2log;
	return right_mid_logged>0;
}

void get_offset(void){
	#if IS_BIT_LOG_ON
			_Bool l_s = read_sensor_left_side();
			_Bool l_m = read_sensor_left_mid();
			_Bool r_s = read_sensor_right_side();
			_Bool r_m = read_sensor_right_mid();
	#else
			u8 l_s = SENSOR_LEFT_SIDE;
			u8 l_m = SENSOR_LEFT_MID;
			u8 r_s = SENSOR_RIGHT_SIDE;
			u8 r_m = SENSOR_RIGHT_MID;
	#endif
			u8 offset;
			switch(l_s<<3 | l_m<<2 | r_m<<1 | r_s){
				case 8:
					offset = 2;
				break;
				case 12:
					offset = 3;
				break;
				case 14:
					offset = 5;
				break;
				case 4:
					offset = 4;
				break;
				case 6:
					offset = 5;
				break;
				case 7:
					offset = 5;
				break;
				case 2:
					offset = 6;
				break;
				case 3:
					offset = 7;
				break;
				case 1:
					offset = 8;
				break;
				case 15:
					offset = 0;
				break;
				default:
					if(car_offset>=1&&car_offset<=4)offset=1;
					else if(car_offset>=6&&car_offset<=9)offset=9;
					else offset=0;
				break;
			}
			car_offset = offset;
}



void calc_speed(void){
	int err = IDEAL_OFFSET - car_offset;
	car_k = calc_pid_direction(err,car_k);
	speed_ideal_left = IDEAL_AUTO_SPEED;
	speed_ideal_right = IDEAL_AUTO_SPEED;
//	if(car_direction>0){//zuo
//		//speed_ideal_left*=((90.0-car_direction)/90.0);
//		speed_ideal_left -= AUTO_SPEED_RANGE*AUTO_SPEED_RANGE_RATIO*car_direction/90.0;
//	}else if(car_direction<0){
//		//speed_ideal_right*=((90.0+car_direction)/90.0);
//		speed_ideal_right += AUTO_SPEED_RANGE*AUTO_SPEED_RANGE_RATIO*car_direction/90.0;
//	}
	if(car_k>=0){
		speed_ideal_left *= (1-8*car_k)/(1+8*car_k);
	}else{
		speed_ideal_right *= (1+8*car_k)/(1-8*car_k);
	}
}