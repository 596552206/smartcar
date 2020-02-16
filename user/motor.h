#ifndef __MOTOR_H
#define __MOTOR_H

#define SET_ISPID 0

#if SET_ISPID
//60000*(speed/100) speed范围为0-100
#define MOTOR_1_FORWARD(speed) ste_pwm2_duty(0);\
																set_motor_1_speed_by_pid(speed*100);											 
#define MOTOR_1_BACKWARD(speed) ste_pwm1_duty(0);\
															 set_motor_2_speed_by_pid(speed*100);															 
#define MOTOR_1_STOP ste_pwm1_duty(0);\
															 ste_pwm2_duty(0);															 
#define MOTOR_1_BRAKE ste_pwm1_duty(100);\
															 ste_pwm2_duty(100);	
#define MOTOR_2_FORWARD(speed) ste_pwm4_duty(0);\
																set_motor_3_speed_by_pid(speed*100);															 
#define MOTOR_2_BACKWARD(speed) ste_pwm3_duty(0);\
															 set_motor_4_speed_by_pid(speed*100);
#define MOTOR_2_STOP ste_pwm3_duty(0);\
															 ste_pwm4_duty(0);															 
#define MOTOR_2_BRAKE ste_pwm3_duty(100);\
															 ste_pwm4_duty(100);	
#else
#define MOTOR_1_FORWARD(speed) ste_pwm2_duty(0);\
																ste_pwm1_duty(speed);											 
#define MOTOR_1_BACKWARD(speed) ste_pwm1_duty(0);\
															 ste_pwm2_duty(speed);															 
#define MOTOR_1_STOP ste_pwm1_duty(0);\
															 ste_pwm2_duty(0);															 
#define MOTOR_1_BRAKE ste_pwm1_duty(100);\
															 ste_pwm2_duty(100);	
#define MOTOR_2_FORWARD(speed) ste_pwm4_duty(0);\
																ste_pwm3_duty(speed);															 
#define MOTOR_2_BACKWARD(speed) ste_pwm3_duty(0);\
															 ste_pwm4_duty(speed);
#define MOTOR_2_STOP ste_pwm3_duty(0);\
															 ste_pwm4_duty(0);															 
#define MOTOR_2_BRAKE ste_pwm3_duty(100);\
															 ste_pwm4_duty(100);
#endif
												
//车轮控制
//MOTOR1为右轮
//MOTOR2为左轮
#define WHEEL_LEFT_FORWARD(speed) MOTOR_2_FORWARD(speed)
#define WHEEL_LEFT_BACKWARD(speed) MOTOR_2_BACKWARD(speed)
#define WHEEL_LEFT_STOP MOTOR_2_STOP
#define WHEEL_LEFT_BRAKE MOTOR_2_BRAKE
#define WHEEL_RIGHT_FORWARD(speed) MOTOR_1_FORWARD(speed)
#define WHEEL_RIGHT_BACKWARD(speed) MOTOR_1_BACKWARD(speed)
#define WHEEL_RIGHT_STOP MOTOR_1_STOP
#define WHEEL_RIGHT_BRAKE MOTOR_1_BRAKE

//车辆控制
#define CAR_FORWARD(speed) set_speed(speed,speed);
#define CAR_FORWARD_LEFT(speed) set_speed(speed*0.8,speed);
#define CAR_FORWARD_RIGHT(speed) set_speed(speed,speed*0.8);
#define CAR_BACKWARD(speed) set_speed(-speed,-speed);
#define CAR_STOP set_speed(0,0)
#define CAR_BRAKE set_speed(99999,99999);

void m_Motor_Init(void);
void remoterHandler(char data);
void set_motor_1_speed_by_pid(int target);
void set_motor_2_speed_by_pid(int target);
void set_motor_3_speed_by_pid(int target);
void set_motor_4_speed_by_pid(int target);
void wheel_adjust_speed(int speed);
void speed(int speed_ideal_left,int speed_ideal_right);
int speed2PWM(int speed);
void set_speed(int left,int right);
#endif
