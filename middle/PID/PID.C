#include "pid.h"

PID pid; //´æ·ÅPIDËã·¨ËùÐèÒªµÄÊý¾Ý

void PIDOUT_init()//pidÊä³ö½Å³õÊ¼»¯
{
		//PB2_PushPull_Mode;//ÍÆÍìÊä³ö
		do {Pwmheat_GPIO_CLK_ENABLE(); } while(0U);
		/* Configure the GPIO_LED pin */
		LL_GPIO_SetPinMode(Pwmheat_GPIO_PORT,Pwmheat_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
    

		/* ¹Ø±ÕPwmheat	*/
		LL_GPIO_ResetOutputPin(Pwmheat_GPIO_PORT, Pwmheat_GPIO_PIN);	
	
}
void PID_Init()
{
  pid.Sv=0;//ÓÃ»§Éè¶¨ÎÂ¶È
	pid.Kp=30;
	pid.T=500;//PID¼ÆËãÖÜÆÚ
  pid.Ti=800000;//»ý·ÖÊ±¼ä
	pid.Td=1000;//Î¢·ÖÊ±¼ä
	pid.pwmcycle=1000;//pwmÖÜÆÚ1000
	pid.OUT0=1;
 pid.Ek=0;  //±¾´ÎÆ«²î
 pid.Ek_1=0;//ÉÏ´ÎÆ«²î
 pid.SEk=0; //ÀúÊ·Æ«²îÖ®ºÍ
	pid.OUT=0;
}
void PID_Calc()  //pid¼ÆËã
{
 float DelEk;
	float ti,ki;
	float td;
	float kd;
	float out;
 if(pid.C10ms<(pid.T))  //¼ÆËãÖÜÆÚÎ´µ½
 {
    return ;
 }

 pid.Ek=pid.Sv-pid.Pv;   //µÃµ½µ±Ç°µÄÆ«²îÖµ
 pid.Pout=pid.Kp*pid.Ek;      //±ÈÀýÊä³ö
 
 pid.SEk+=pid.Ek;        //ÀúÊ·Æ«²î×ÜºÍ
 
 DelEk=pid.Ek-pid.Ek_1;  //×î½üÁ½´ÎÆ«²îÖ®²î
 
 ti=pid.T/pid.Ti;
 ki=ti*pid.Kp;
 
 //pid.Iout=ki*pid.SEk*pid.Kp;  //»ý·ÖÊä³ö
  pid.Iout=ki*pid.SEk;  //»ý·ÖÊä³ö

 td=pid.Td/pid.T;
 
 kd=pid.Kp*td;
 
 pid.Dout=kd*DelEk;    //Î¢·ÖÊä³ö
 
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
 //pid.OUT+=; //±¾´ÎµÄ¼ÆËã½á¹û
 pid.Ek_1=pid.Ek;  //¸üÐÂÆ«²î
 
 pid.C10ms=0;
}


void PID_Calc_overshoot()  //pid¼ÆËã-¹ý³å´¦Àí¿
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
 if(pid.C10ms<(pid.T))  //¼ÆËãÖÜÆÚÎ´µ½
 {
    return ;
 }
 
 
//ÅÐ¶ÏSv
  SvSave=pid.Sv;
 
 if(pid.Pv<(SvSave*0.55))//ÎÂ¶È´ïµ½¼ÆÊý¿ªÊ¼ 66¶È
 {
    pid.times=0;
 }
 
  if(pid.times<=60)//3·ÖÖÓ 72¶È  100s
 {
  pid.Sv=SvSave*0.6;
 }
 
 if((pid.times>60)&&(pid.times<=100))//3·ÖÖÓ 96¶È  100s
 {
  pid.Sv=SvSave*0.8;
 }
 
 if((pid.times>100)&&(pid.times<=200))//2·ÖÖÓ 102¶È 100s
 {
  pid.Sv=SvSave*0.85;
 }
 
 if((pid.times>200)&&(pid.times<=300))//2·ÖÖÓ 108¶È 100s
 {
  pid.Sv=SvSave*0.9;
 }
 
  if((pid.times>300)&&(pid.times<=400))//2·ÖÖÓ 114¶È 100s
 {
  pid.Sv=SvSave*0.95;
 }
 
 if(pid.times>400)
 {
  pid.Sv=SvSave;
 }
//////////////////////////////////


 pid.Ek=pid.Sv-pid.Pv;   //µÃµ½µ±Ç°µÄÆ«²îÖµ
 pid.Pout=pid.Kp*pid.Ek;      //±ÈÀýÊä³ö
 
 pid.SEk+=pid.Ek;        //ÀúÊ·Æ«²î×ÜºÍ
 
 DelEk=pid.Ek-pid.Ek_1;  //×î½üÁ½´ÎÆ«²îÖ®²î
 
 ti=pid.T/pid.Ti;
 ki=ti*pid.Kp;
 
  pid.Iout=ki*pid.SEk*pid.Kp;  //»ý·ÖÊä³ö

 td=pid.Td/pid.T;
 
 kd=pid.Kp*td;
 
  pid.Dout=kd*DelEk;    //Î¢·ÖÊä³ö
 
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
 //pid.OUT+=; //±¾´ÎµÄ¼ÆËã½á¹û
 pid.Ek_1=pid.Ek;  //¸üÐÂÆ«²î
 
 pid.C10ms=0;
 pid.Sv=SvSave;
}
void PID_out()  //Êä³öPIDÔËËã½á¹ûµ½¸ºÔØ---Ã¿1ms±»µ÷ÓÃ1´Î
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
	   pwmout_1;//¼ÓÈÈ
	 }
	 else
	 {
	   pwmout_0;//Í£Ö¹¼ÓÈÈ
	 }
	 
}











