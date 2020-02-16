#include "motor.h"
#include "stm32f10x.h"
#include "pwm.h"
#include "usart.h"
#include "common.h"
#include "pid.h"
#include "math.h"
#include "delay.h"
#include "encoder.h"

#define HIGH_SPEED 840; //55
#define MEDIUM_SPEED 630; //40
#define LOW_SPEED 550 ; //35

int SPEED_FOR_REMOTER = MEDIUM_SPEED;

void m_Motor_Init(void){
	TIM3_PWM_Init(0);
}

void remoterHandler(char data){
	switch(data){
			case 'a' :
				CAR_FORWARD(SPEED_FOR_REMOTER);
				printf("FORWARD (%d)",SPEED_FOR_REMOTER);	
			break;
			case 'b' :
				CAR_BACKWARD(SPEED_FOR_REMOTER);
				printf("BACKWARD (%d)",SPEED_FOR_REMOTER);
			break;
//			case 'c' :
//				CAR_LEFT_TURN(SPEED_FOR_REMOTER);
//				printf("LEFT (%d)",SPEED_FOR_REMOTER);
//			break;
//			case 'd' :
//				CAR_RIGHT_TURN(SPEED_FOR_REMOTER);
//				printf("RIGHT (%d)",SPEED_FOR_REMOTER);
//			break;
			case 'e' :
				CAR_BRAKE;
				printf("BRAKED");
			break;
			case 'f' :
				CAR_STOP;
				printf("STOPPED");
			break;
			case 'g' :
				SPEED_FOR_REMOTER = HIGH_SPEED;
				printf("SWITCHED TO HIGH SPEED");
			break;
			case 'h' :
				SPEED_FOR_REMOTER = MEDIUM_SPEED;
				printf("SWITCHED TO MEDIUM SPEED");
			break;
			case 'i' :
				SPEED_FOR_REMOTER = LOW_SPEED;
				printf("SWITCHED TO LOW SPEED");
			break;
			case 'j' :
				CAR_FORWARD_LEFT(SPEED_FOR_REMOTER);
				printf("FORWARD LEFT (%d)",SPEED_FOR_REMOTER);
			break;
			case 'k' :
				CAR_FORWARD_RIGHT(SPEED_FOR_REMOTER);
				printf("FORWARD RIGHT (%d)",SPEED_FOR_REMOTER);
			break;
			case 'l' :
				SMART_CAR_MODE = SMART_CAR_MODE_AUTO;
				printf("MODE AUTO");
			break;
			case 'm' :
				SMART_CAR_MODE = SMART_CAR_MODE_REMOTE;
				printf("MODE REMOTE");
			break;
			case '1' :
				direction_x=-0.4;direction_y=0.4;
				printf("DIRECTION_1");
			break;
			case '2' :
				direction_x=0.4;direction_y=1;
				printf("DIRECTION_2");
			break;
			case '3' :
				direction_x=0.6;direction_y=1;
				printf("DIRECTION_3");
			break;
			case '4' :
				direction_x=0.8;direction_y=1;
				printf("DIRECTION_4");
			break;
			case '5' :
				direction_x=1;direction_y=1;
				printf("DIRECTION_5");
			break;
			case '6' :
				direction_x=1;direction_y=0.8;
				printf("DIRECTION_6");
			break;
			case '7' :
				direction_x=1;direction_y=0.6;
				printf("DIRECTION_7");
			break;
			case '8' :
				direction_x=1;direction_y=0.4;
				printf("DIRECTION_8");
			break;
			case '9' :
				direction_x=0.4;direction_y=-0.4;
				printf("DIRECTION_9");
			break;
		}
}

void set_speed(int left,int right){
				speed_ideal_left = left;
				speed_ideal_right = right;
}

void speed(int speed_ideal_left,int speed_ideal_right){
	int speed_cur_left = read_encoder_l();
	int speed_cur_right = read_encoder_r();
	int err_left;
	int err_right;
	int speed_left_to_set = 0;
	int speed_right_to_set = 0;
	int left_status,right_status;
	const int threshold_up = 50;
	const int threshold_down = -50;
	//
	if(speed_ideal_left==0){
			left_status=0;
			speed_left_to_set=0;
			pwm_left_2set = 0;
	}else if(speed_ideal_left>0){
		left_status=1;
		err_left = speed_ideal_left-speed_cur_left;
		if(err_left>=threshold_down && err_left<=threshold_up){
			pwm_left_2set = calc_pid(err_left,pwm_left_2set);
			speed_left_to_set = pwm_left_2set;
		}else{
			pwm_left_2set = speed2PWM(speed_ideal_left);
			speed_left_to_set = pwm_left_2set;
		}
	}else{
		left_status=-1;
		err_left = speed_cur_left-speed_ideal_left;
		if(err_left>=threshold_down&&err_left<=threshold_up){
			pwm_left_2set = calc_pid(err_left,pwm_left_2set);
			speed_left_to_set = pwm_left_2set;
		}else{
			pwm_left_2set = speed2PWM(-speed_ideal_left);
			speed_left_to_set = pwm_left_2set;
		}
	}
	//	
	if(speed_ideal_right==0){
			right_status=0;
			speed_right_to_set=0;
			pwm_right_2set = 0;
	}else if(speed_ideal_right>0){
		right_status=1;
		err_right = speed_ideal_right-speed_cur_right;
		if(err_right>=threshold_down&&err_right<=threshold_up){
			pwm_right_2set = calc_pid_r(err_right,pwm_right_2set);
			speed_right_to_set = pwm_right_2set;
		}else{
			pwm_right_2set = speed2PWM(speed_ideal_right);
			speed_right_to_set = pwm_right_2set;
		}
	}else{
		right_status=-1;
		err_right = speed_cur_right-speed_ideal_right;
		if(err_right>=threshold_down&&err_right<=threshold_up){
			pwm_right_2set = calc_pid_r(err_right,pwm_right_2set);
			speed_right_to_set = pwm_right_2set;
		}else{
			pwm_right_2set = speed2PWM(-speed_ideal_right);
			speed_right_to_set = pwm_right_2set;
		}
	}
	//
	if(left_status==0){
		WHEEL_LEFT_STOP;
	}else if(left_status==1){
		WHEEL_LEFT_FORWARD(speed_left_to_set);
	}else{
		WHEEL_LEFT_BACKWARD(speed_left_to_set);
	}
	//
	if(right_status==0){
		WHEEL_RIGHT_STOP;
	}else if(right_status==1){
		WHEEL_RIGHT_FORWARD(speed_right_to_set);
	}else{
		WHEEL_RIGHT_BACKWARD(speed_right_to_set);
	}
	//printf("%d~%d~%d~%d\n",speed_cur_left,speed_left_to_set,speed_cur_right,speed_right_to_set);
}
int speed2PWM(int speed){
	//const static int mymap[30] = {0,0,0,24,27,30,31,33,36,38,40,43,46,50,54,59,67,73,83,94,99,0,0,0,0,0,0,0,0,0};
	u8 p = 0;
	switch(speed/50){
		case 3:
			p=24;
		break;
		case 4:
			p=27;
		break;
		case 5:
			p=30;
		break;
		case 6:
			p=31;
		break;
		case 7:
			p=33;
		break;
		case 8:
			p=36;
		break;
		case 9:
			p=38;
		break;
		case 10:
			p=40;
		break;
		case 11:
			p=43;
		break;
		case 12:
			p=46;
		break;
		case 13:
			p=50;
		break;
		case 14:
			p=54;
		break;
		case 15:
			p=59;
		break;
		case 16:
			p=67;
		break;
		case 17:
			p=73;
		break;
		case 18:
			p=83;
		break;
		case 19:
			p=94;
		break;
		case 20:
			p=99;
		break;
		default:
			p=0;
	}
	return p;
}