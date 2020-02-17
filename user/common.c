#include "common.h"
int SMART_CAR_MODE = SMART_CAR_MODE_REMOTE;
int ENCODER_LEFT = 0;
int ENCODER_RIGHT = 0;
int speed_ideal_left = 0;
int speed_ideal_right = 0;
float pwm_left_2set = 0;
float pwm_right_2set = 0;
u8 car_offset = 0;
int car_direction = 0;
float car_k = 0.0; //曲率
float direction_x=1,direction_y=1;
int kp_direction = 28000;
int ki_direction = 50;
int kd_direction = 0;
short IDEAL_AUTO_SPEED = 400;