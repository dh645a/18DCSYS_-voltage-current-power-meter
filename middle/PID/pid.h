#ifndef _pid_
#define _pid_
#include "config.h"

void PIDOUT_init(void);//pid输出脚初始化
void PID_out(void); //输出PID运算结果到负载
typedef struct
{
 float Sv;//用户设定值
 float Pv;
 
 float Kp;
 float T;  //PID计算周期--采样周期
 float Ti;
 float Td; 
	
	
	
 float Ek;  //本次偏差
 float Ek_1;//上次偏差
 float SEk; //历史偏差之和
	
	float Iout;
	float Pout;
	float Dout;
	
 float OUT0;

 float OUT;
	
	
 unsigned short C10ms;
	
 unsigned short pwmcycle;//pwm周期
 
 unsigned long times;
	float k;
}PID;

extern PID pid; //存放PID算法所需要的数据
void PID_Calc(void); //pid计算
void PID_Init(void);
void PID_Calc_overshoot(void);  //pid计算-过冲处理

#endif
