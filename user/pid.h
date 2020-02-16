#ifndef __PID_H

#define __PID_H	 

#include "sys.h"

float calc_pid(int err,float cur_pwm);
float calc_pid_r(int err,float cur_pwm);
float calc_pid_direction(int err,float cur_k);
#endif