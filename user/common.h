#ifndef __COMMON_H
#define __COMMON_H

#include "sys.h"

#define SMART_CAR_MODE_REMOTE 1
#define SMART_CAR_MODE_AUTO 0

extern int SMART_CAR_MODE;
extern int ENCODER_LEFT;
extern int ENCODER_RIGHT;
extern int speed_ideal_left;
extern int speed_ideal_right;
extern float pwm_left_2set;
extern float pwm_right_2set;
extern u8 car_offset;
extern int car_direction;
extern float car_k;
extern float direction_x,direction_y;

#endif
