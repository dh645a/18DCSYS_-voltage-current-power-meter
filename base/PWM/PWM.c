/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************

//***********************************************************************************************************
#include "PWM.h"
/****************************** 用户定义宏 ***********************************/

#define PWM1_0      0x00	//P:P1.0  N:P1.1
#define PWM1_1      0x01	//P:P2.0  N:P2.1
#define PWM1_2      0x02	//P:P6.0  N:P6.1

#define PWM2_0      0x00	//P:P1.2/P5.4  N:P1.3
#define PWM2_1      0x04	//P:P2.2  N:P2.3
#define PWM2_2      0x08	//P:P6.2  N:P6.3

#define PWM3_0      0x00	//P:P1.4  N:P1.5
#define PWM3_1      0x10	//P:P2.4  N:P2.5
#define PWM3_2      0x20	//P:P6.4  N:P6.5

#define PWM4_0      0x00	//P:P1.6  N:P1.7
#define PWM4_1      0x40	//P:P2.6  N:P2.7
#define PWM4_2      0x80	//P:P6.6  N:P6.7
#define PWM4_3      0xC0	//P:P3.4  N:P3.3

#define ENO1P       0x01
#define ENO1N       0x02
#define ENO2P       0x04
#define ENO2N       0x08
#define ENO3P       0x10
#define ENO3N       0x20
#define ENO4P       0x40
#define ENO4N       0x80

#define PWM5_0      0x00	//P2.0
#define PWM5_1      0x01	//P1.7
#define PWM5_2      0x02	//P0.0
#define PWM5_3      0x03	//P7.4

#define PWM6_0      0x00	//P2.1
#define PWM6_1      0x04	//P5.4
#define PWM6_2      0x08	//P0.1
#define PWM6_3      0x0C	//P7.5

#define PWM7_0      0x00	//P2.2
#define PWM7_1      0x10	//P3.3
#define PWM7_2      0x20	//P0.2
#define PWM7_3      0x30	//P7.6

#define PWM8_0      0x00	//P2.3
#define PWM8_1      0x40	//P3.4
#define PWM8_2      0x80	//P0.3
#define PWM8_3      0xC0	//P7.7

#define ENO5P       0x01
#define ENO6P       0x04
#define ENO7P       0x10
#define ENO8P       0x40

/*****************************************************************************/


/*************  本地常量声明    **************/

#define PWM_PERIOD  30000    //设置周期值

/*************  本地变量声明    **************/

bit B_1ms;          //1ms标志

u16 PWM1_Duty;
u16 PWM2_Duty;
u16 PWM3_Duty;
u16 PWM4_Duty;

bit PWM1_Flag;
bit PWM2_Flag;
bit PWM3_Flag;
bit PWM4_Flag;


/********************* pwm函数 *************************/
void pwm_init_beep(void)
{

    PWMA_CCER1 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    PWMA_CCER2 = 0x00;
    PWMA_CCMR4 = 0x68;//通道模式配置
    //PWMA_CCER1 = 0x57; //配置通道输出使能和极性 低电平有效
    PWMA_CCER2 = 0x30;//pwm4  配置通道输出使能和极性 高电平有效
	
		PWMA_PSCRH = 0x01;		// 预分频寄存器, 分频 Fck_cnt = Fck_psc/(PSCR[15:0}+1), (默认)边沿对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)), 中央对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)*2).
		PWMA_PSCRL = 0xDF;
    PWMA_ARRH = (u8)(PWM_PERIOD >> 8); //设置周期时间  自动重装载寄存器,  控制PWM周期, 
    PWMA_ARRL = (u8)PWM_PERIOD;

    PWMA_ENO = 0x00;
    PWMA_ENO |= ENO4P; //使能输出
    //PWMA_ENO |= ENO4N; //使能输出

    PWMA_PS = 0x00;  //高级 PWM 通道输出脚选择位
    PWMA_PS |= PWM4_3; //选择 PWM4_3 通道 P3.4

    PWMA_BKR = 0x80;  //使能主输出
    PWMA_CR1 |= 0x81; //使能ARR预装载,开始计时

}
void pwm_init_blk(void)
{
    PWMB_CCER2 = 0x00;//写 CCMRx 前必须先清零 CCxE 关闭通道
    PWMB_CCMR3 = 0x68;//通道模式配置
    PWMB_CCER2 = 0x01; //配置通道输出使能和极性
    PWMB_ARRH = (u8)(PWM_PERIOD >> 8); //设置周期时间 (默认)边沿对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1))=30000000/30000=1000  PSCR=0不分频
    PWMB_ARRL = (u8)PWM_PERIOD;
    PWMB_CCR7H = (u8)(20000 >> 8); //设置占空比时间
    PWMB_CCR7L = (u8)((20000));
    PWMB_ENO = 0x00;
    PWMB_ENO |= ENO7P; //使能输出

    PWMB_PS = 0x00;    //高级 PWM 通道输出脚选择位
    PWMB_PS |= PWM7_1; //选择 PWM7_1 通道

    PWMB_BKR = 0x80;   //使能主输出
    PWMB_CR1 |= 0x81;  //使能ARR预装载，开始计时
}
//========================================================================
// 函数: UpdatePwm(void)
// 描述: 更新PWM占空比. 
// 参数: none.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
void UpdatePwm(u16 frequency,u16 duty)
{
		PWMA_ARRH = (u8)(frequency >> 8); //设置周期时间
    PWMA_ARRL = (u8)frequency;
    PWMA_CCR4H = (u8)(duty >> 8); //设置占空比时间
    PWMA_CCR4L = (u8)(duty);
	
}
