#include "pid.h"

PID pid; //存放PID算法所需要的数据

void PIDOUT_init()//pid输出脚初始化
{
		//PB2_PushPull_Mode;//推挽输出
		do {Pwmheat_GPIO_CLK_ENABLE(); } while(0U);
		/* Configure the GPIO_LED pin */
		LL_GPIO_SetPinMode(Pwmheat_GPIO_PORT,Pwmheat_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
    

		/* 关闭Pwmheat	*/
		LL_GPIO_ResetOutputPin(Pwmheat_GPIO_PORT, Pwmheat_GPIO_PIN);	
	
}
void PID_Init()
{
  pid.Sv=0;//用户设定温度
	pid.Kp=30;
	pid.T=500;//PID计算周期
  pid.Ti=800000;//积分时间
	pid.Td=1000;//微分时间
	pid.pwmcycle=1000;//pwm周期1000
	pid.OUT0=1;
 pid.Ek=0;  //本次偏差
 pid.Ek_1=0;//上次偏差
 pid.SEk=0; //历史偏差之和
	pid.OUT=0;
}
void PID_Calc()  //pid计算
{
 float DelEk;
	float ti,ki;
	float td;
	float kd;
	float out;
 if(pid.C10ms<(pid.T))  //计算周期未到
 {
    return ;
 }

 pid.Ek=pid.Sv-pid.Pv;   //得到当前的偏差值
 pid.Pout=pid.Kp*pid.Ek;      //比例输出
 
 pid.SEk+=pid.Ek;        //历史偏差总和
 
 DelEk=pid.Ek-pid.Ek_1;  //最近两次偏差之差
 
 ti=pid.T/pid.Ti;
 ki=ti*pid.Kp;
 
 //pid.Iout=ki*pid.SEk*pid.Kp;  //积分输出
  pid.Iout=ki*pid.SEk;  //积分输出

 td=pid.Td/pid.T;
 
 kd=pid.Kp*td;
 
 pid.Dout=kd*DelEk;    //微分输出
 
 out= pid.Pout+ pid.Iout+ pid.Dout;
 
 //////////////////////////////////////////////////////////
 
 if(out>pid.pwmcycle)
 {
  pid.OUT=pid.pwmcycle;
 }
 else if(out<0)
 {
  pid.OUT=pid.OUT0; 
 }
 else 
 {
  pid.OUT=out;
 }
 //pid.OUT+=; //本次的计算结果
 pid.Ek_1=pid.Ek;  //更新偏差
 
 pid.C10ms=0;
}


void PID_Calc_overshoot()  //pid计算-过冲处理�
{
 float DelEk;
	float ti,ki;
//	float Iout;
//	float Pout;
//	float Dout;
	float td;
	float kd;
	float out;
  float SvSave;
 if(pid.C10ms<(pid.T))  //计算周期未到
 {
    return ;
 }
 
 
//判断Sv
  SvSave=pid.Sv;
 
 if(pid.Pv<(SvSave*0.55))//温度达到计数开始 66度
 {
    pid.times=0;
 }
 
  if(pid.times<=60)//3分钟 72度  100s
 {
  pid.Sv=SvSave*0.6;
 }
 
 if((pid.times>60)&&(pid.times<=100))//3分钟 96度  100s
 {
  pid.Sv=SvSave*0.8;
 }
 
 if((pid.times>100)&&(pid.times<=200))//2分钟 102度 100s
 {
  pid.Sv=SvSave*0.85;
 }
 
 if((pid.times>200)&&(pid.times<=300))//2分钟 108度 100s
 {
  pid.Sv=SvSave*0.9;
 }
 
  if((pid.times>300)&&(pid.times<=400))//2分钟 114度 100s
 {
  pid.Sv=SvSave*0.95;
 }
 
 if(pid.times>400)
 {
  pid.Sv=SvSave;
 }
//////////////////////////////////


 pid.Ek=pid.Sv-pid.Pv;   //得到当前的偏差值
 pid.Pout=pid.Kp*pid.Ek;      //比例输出
 
 pid.SEk+=pid.Ek;        //历史偏差总和
 
 DelEk=pid.Ek-pid.Ek_1;  //最近两次偏差之差
 
 ti=pid.T/pid.Ti;
 ki=ti*pid.Kp;
 
  pid.Iout=ki*pid.SEk*pid.Kp;  //积分输出

 td=pid.Td/pid.T;
 
 kd=pid.Kp*td;
 
  pid.Dout=kd*DelEk;    //微分输出
 
 out= pid.Pout+ pid.Iout+ pid.Dout;
 
 //////////////////////////////////////////////////////////
 
 if(out>pid.pwmcycle)
 {
  pid.OUT=pid.pwmcycle;
 }
 else if(out<0)
 {
  pid.OUT=pid.OUT0; 
 }
 else 
 {
  pid.OUT=out;
 }
 //pid.OUT+=; //本次的计算结果
 pid.Ek_1=pid.Ek;  //更新偏差
 
 pid.C10ms=0;
 pid.Sv=SvSave;
}
void PID_out()  //输出PID运算结果到负载---每1ms被调用1次
{
   static unsigned short pw;
	 pw++;
	 if(pw>=pid.pwmcycle)  //
	 {
	   pw=0;
	 }
	  //0  ~  pid.pwmcycle-1
	 
	 if(pw<pid.OUT)
	 {
	   pwmout_1;//加热
	 }
	 else
	 {
	   pwmout_0;//停止加热
	 }
	 
}











