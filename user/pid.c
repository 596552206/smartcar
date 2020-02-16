#include "pid.h"

#define kp 0.0625
#define ki 0.008
//0.0078125
#define kd 0.008
//0.0078125
int pre_err = 0;
int pre_d_error = 0;
float calc_pid(int err,float cur_pwm){
	int error,d_error,dd_error;
	error = err;
	d_error = error - pre_err;
	dd_error = d_error - pre_d_error;
	pre_err = error;
	pre_d_error = d_error;
	cur_pwm += kp*d_error+ki*error+kd*dd_error;
	if(cur_pwm>=100)cur_pwm=100;
	if(cur_pwm<=0)cur_pwm=0;
	return cur_pwm;
}

int pre_err_r = 0;
int pre_d_error_r = 0;
float calc_pid_r(int err,float cur_pwm){
	int error,d_error,dd_error;
	error = err;
	d_error = error - pre_err_r;
	dd_error = d_error - pre_d_error_r;
	pre_err_r = error;
	pre_d_error_r = d_error;
	cur_pwm += kp*d_error+ki*error+kd*dd_error;
	if(cur_pwm>=100)cur_pwm=100;
	if(cur_pwm<=0)cur_pwm=0;
	return cur_pwm;
}

#define k_scale_d 1.5
//350 400     500
// 1   1.341  1.4
#define kp_d 0.0248*k_scale_d
#define ki_d 0.0005*k_scale_d
#define kd_d 0.03*k_scale_d
//0.0293 0.00074 0.00035
#define max_error_sum 6
#define car_k_range 0.125
int pre_err_d = 0;
float sum_err = 0;
float calc_pid_direction(int err,float cur_k){
	sum_err+=err;
	if(sum_err>max_error_sum)sum_err=max_error_sum;
	if(sum_err<-max_error_sum)sum_err=-max_error_sum;
	float u = err*kp_d+sum_err*ki_d+(err-pre_err_d)*kd_d;
	pre_err_d = err;
	if(u>car_k_range)u=car_k_range;
	if(u<-car_k_range)u=-car_k_range;
	return u;
}