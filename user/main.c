/*********************************************************************************************
模板制作：  杜洋工作室/洋桃电子
出品：		
程序名：	
编写时间：	201年月日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

修改日志：　　
1-	
	
							
说明：
 # 本模板加载了STM32F103内部的RCC时钟设置，并加入了利用滴答定时器的延时函数。
 # 可根据自己的需要增加或删减。

*********************************************************************************************/
#include "stm32f10x.h"//STM32头文件
#include "sys.h"
#include "delay.h"
#include "sensor.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"
#include "usart.h"
#include "common.h"
#include "pid.h"

#define speed_forward 840
#define speed_turning 550
#define speed_sharp_turning 630

u8 l_s,l_m,r_s,r_m;//无反射(压黑线)则为高电平 TRUE ,有反射为低电平 FALSE
u8 status = 0; //0:holding;1:forward;2:left;3:right;4:left-sharp;5:right-sharp;6:crossing;

void adjust_left(u8 speed);
void adjust_right(u8 speed);
void adjust_left_sharp(u8 speed);
void adjust_right_sharp(u8 speed);
void cope_cross(u8 speed);
void tracking(void);
void remoting(void);

int main (void){//主程序
	SystemInit();
	RCC_Configuration(); //时钟设置
	m_LED_Init(); //led灯初始化
	m_Sensor_Init(); //红外传感器初始化
	m_Motor_Init(); //电机初始化
	USART3_Init(9600);//蓝牙串口初始化，波特率设置为9600.
	NVIC_CONF();
	m_Encoder_Init_1(); //编码器初始化
	m_Encoder_Init_2(); //编码器初始化
	m_Encoder_Init_TIM1(); //编码器初始化
	int counter = 0;
	u8 logs[1000] = {0};
	float logave = 0;
	float jfc = 0;
	int logctr = 0;
	while(1){
		delay_ms(10);
		if(SMART_CAR_MODE == SMART_CAR_MODE_AUTO){
			tracking();
					if((counter++)==20){
						logave += logs[logctr++] = car_k*1000;
						counter=0;
					}
		}else{
			remoting();
				if(logctr!=0){
					logave/=logctr;
					for(int i=0;i<logctr;i++){
						jfc += (logs[i]-logave)*(logs[i]-logave);
					}
					jfc/=logctr;
					printf("JFC=%f.\n",jfc);
					logctr = 0;
					logave = 0;
					jfc = 0;
				}
		}
	}
//int spd = 150;
//int ctr = 0;
//while(spd<=1000){
//	delay_ms(50);
//	speed_ideal_left=spd;
//	speed_ideal_right=spd;
//	speed(speed_ideal_left,speed_ideal_right);
//	spd++;
//	ctr++;
//	ctr%=20;
//	if(!ctr){
//		int left = read_encoder_l();
//		int right = read_encoder_r();
//		printf("%d~%d~%d\n",spd,left,right);
//	}
//}
}


void tracking(){
			//u8 old_offset = car_offset;
			get_offset();
			if(car_offset)calc_speed();
			else{
				//car_direction=0;
				//如果脱离轨道，有可能是轨道间断，交会的地方，可以先保持行进一段时间，再停车。
				car_k = 0;
				CAR_STOP;
			}
			speed(speed_ideal_left,speed_ideal_right);
			//if(car_offset!=old_offset)printf("%f~%d~%d\n",car_k,speed_ideal_left,speed_ideal_right);
}
void remoting(){
		if(speed_ideal_left==99999&&speed_ideal_right==99999){
			WHEEL_LEFT_BRAKE;
			WHEEL_RIGHT_BRAKE;
		}else{
			speed(direction_x*speed_ideal_left,direction_y*speed_ideal_right);
		}
}

	
	
/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/
/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒
*/

