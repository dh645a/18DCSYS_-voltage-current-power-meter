#ifndef _pid_
#define _pid_
#include "config.h"

void PIDOUT_init(void);//pid����ų�ʼ��
void PID_out(void); //���PID������������
typedef struct
{
 float Sv;//�û��趨ֵ
 float Pv;
 
 float Kp;
 float T;  //PID��������--��������
 float Ti;
 float Td; 
	
	
	
 float Ek;  //����ƫ��
 float Ek_1;//�ϴ�ƫ��
 float SEk; //��ʷƫ��֮��
	
	float Iout;
	float Pout;
	float Dout;
	
 float OUT0;

 float OUT;
	
	
 unsigned short C10ms;
	
 unsigned short pwmcycle;//pwm����
 
 unsigned long times;
	float k;
}PID;

extern PID pid; //���PID�㷨����Ҫ������
void PID_Calc(void); //pid����
void PID_Init(void);
void PID_Calc_overshoot(void);  //pid����-���崦��

#endif
