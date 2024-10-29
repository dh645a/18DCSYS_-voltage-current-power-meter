/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************

//***********************************************************************************************************
#include "buzzer.h" 
#include "pwm.h" 
#include "main.h" 
static u32 beep_startTime;
static u16 beep_lenTime;
static u8 beep_state;
static u8 idx;
typedef u16 tune_t;
static const tune_t* tune;	// The tune
static buzzFinish_f onFinish;
static void next(void);
typedef enum
{
	TONE_STOP = 0,
	TONE_PAUSE = 1,
	TONE_REPEAT = 2,
	TONE_1KHZ = 63,
	TONE_2KHZ = 31,
	TONE_2_5KHZ = 200-1,
	TONE_3KHZ = 21,
	TONE_3_5KHZ = 143-1,
	TONE_4KHZ = 15,
	TONE_4_5KHZ = 111-1,
	TONE_5KHZ = 12,
	TONE_5L= 159,
	TONE_6L= 142,
	TONE_1M= 120,
	TONE_2M= 106,
	TONE_3M= 95,
	TONE_4M= 90,
	TONE_5M= 80,
	TONE_6M= 71,
	TONE_7M= 64,
	TONE_1H= 60,
} tone_t;
const tune_t code tuneAlarm[]  = {
	TONE_2KHZ<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_2KHZ<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_3KHZ<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_3KHZ<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_STOP
};
const tune_t code tuneAlarm_L[]  = {
	TONE_3KHZ<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_REPEAT
};
const tune_t code tuneAlarm_H[]  = {//两只老虎
	TONE_1M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_2M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_3M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_1M<<8 | 100,
	TONE_PAUSE<<8 | 200,
	TONE_1M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_2M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_3M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_1M<<8 | 100,
	TONE_PAUSE<<8 | 200,
	TONE_3M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_4M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_5M<<8 | 100,
	TONE_PAUSE<<8 | 250,
	TONE_3M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_4M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_5M<<8 | 100,
	TONE_PAUSE<<8 | 250,
	TONE_REPEAT
};
const tune_t code tuneAlarm_IN[]  = {
	TONE_6M<<8 | 100,
	TONE_PAUSE<<8 | 150,
	TONE_5L<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_3M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_5M<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_1H<<8 | 100,
	TONE_PAUSE<<8 | 100,
	TONE_6L<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_5L<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_6M<<8 | 100,
	TONE_PAUSE<<8 | 250,
	TONE_REPEAT
//	TONE_2KHZ<<8 | 100,
//	TONE_PAUSE<<8 |50,
//	TONE_3KHZ<<8 | 100,
//	TONE_PAUSE<<8 | 50,
//	TONE_1KHZ<<8 | 100,
//	TONE_PAUSE<<8 | 50,
//	TONE_REPEAT
};
const tune_t code tuneAlarm_OUT[]  = {
	TONE_3KHZ<<8 | 150,
	TONE_PAUSE<<8 | 150,
	TONE_3KHZ<<8 | 150,
	TONE_PAUSE<<8 | 150,
	TONE_5KHZ<<8 | 250,
	TONE_5KHZ<<8 | 250,
	TONE_STOP
};
const tune_t code tuneUsbCharged[]  = {
	TONE_2KHZ<<8 | 150,
	TONE_PAUSE<<8 | 150,
	TONE_2KHZ<<8 | 150,
	TONE_PAUSE<<8 | 150,
	TONE_4KHZ<<8 | 250,
	TONE_4KHZ<<8 | 250,
	TONE_STOP
};
const tune_t code tuneBtn_up[]  = {
	TONE_2KHZ<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_3KHZ<<8 | 100,
	TONE_STOP
	// 这段代码定义了一个名为 tuneBtn1 的数组，其类型为 tune_t，并使用了 TUNEMEM 宏修饰。
	//数组中的每个元素都是一个音调（tune_t 类型），用于按下按钮时播放的音乐。每个音调由两部分组成：高位表示频率，低位表示持续时间。

	// 下面是对每个元素的解释：

	// TONE_2KHZ << 8 | 100：表示一个频率为 2kHz，持续时间为 100 毫秒的音调。
	// TONE_PAUSE << 8 | 50：表示一个静音，持续时间为 50 毫秒的音调。
	// TONE_3KHZ << 8 | 100：表示一个频率为 3kHz，持续时间为 100 毫秒的音调。
	// TONE_STOP：表示停止播放音调的标志。
	// 这样，tuneBtn1 数组中的元素描述了按下按钮时播放的音乐序列。
};

const tune_t code tuneBtn_set[]  = {
	TONE_3KHZ<<8 | 100,
	TONE_PAUSE<<8 | 50,
	//TONE_3KHZ<<8 | 100,
	TONE_STOP
};

const tune_t code tuneBtn_down[]  = {
	TONE_3KHZ<<8 | 100,
	TONE_PAUSE<<8 | 50,
	TONE_2KHZ<<8 | 100,
	TONE_STOP
};
void Init_buzzer(void)//蜂鸣器初始化
{
	pwm_init_beep();
}

void beep(u16 frequency,u16 duty,u16 time,u8 state,buzzFinish_f _onFinish)
{
		beep_state=state;
		beep_startTime=T0_Count;
		beep_lenTime=time;
		onFinish = _onFinish;
		
		PWMA_ARRH = (u8)(frequency >> 8); //设置周期时间
		PWMA_ARRL = (u8)frequency;
		PWMA_CCR4H = (u8)(duty >> 8); //设置占空比时间
		PWMA_CCR4L = (u8)(duty);
		PWMA_BKR = 0x80;  //使能主输出
}

void beep_update(void)
{
	if(((T0_Count-beep_startTime)>=beep_lenTime)&&beep_state)
	{
		beep_state=0;PWMA_BKR = 0x00;  //不使能
		if(onFinish != NULL)
			onFinish();
	}
		
}
void tune_play(const tune_t* _tune)
{
	// Check priority, if lower than currently playing tune priority then ignore it

	tune	= _tune;
	idx		= 0;

	// Begin playing
	next();
}
static void next()
{
	// Read next tone
	u16 tune_data = tune[idx++];

	u8 len = tune_data;
		// Play next tone
		//buzzer_buzz(len, (tone_t)(data>>8), vol, prio, next);
//	if(tune_data==TONE_PAUSE)
//		PWMA_BKR = 0x00;  //不使能
//	else
//		beep((tone_t)(tune_data>>8),((tone_t)(tune_data>>8))/2,len,1,next);	
//		// If tone was TONE_STOP then reset priority
//		if(len == TONE_STOP)
//		{
//			beep_state=0;PWMA_BKR = 0x00;  //不使能
//		}
		
	if(len != TONE_REPEAT)
	{
		// Play next tone
		beep((tone_t)(tune_data>>8),((tone_t)(tune_data>>8))/2,len,1,next);	
		
		// If tone was TONE_STOP then reset priority
		if(len == TONE_STOP)
		{
			beep_state=0;PWMA_BKR = 0x00;  //不使能
		}
	}
	else
	{
		// Repeat
		idx = 0;
		next();
	}
}

void tune_stop()
{
	beep(TONE_STOP,0,0,0,NULL);

}
void beep_key(btn_t btn)
{
		// Read next tone		
	switch (btn)
	{
		case BTN_UP: tune_play(tuneBtn_up);break;
		case BTN_DOWN: tune_play(tuneBtn_down);    break;
		case BTN_SET: tune_play(tuneBtn_set);  break;
		case BTN_RETURN: tune_play(tuneBtn_set); break;
		default: break;
	}
}
void beep_alarm(u8 i)
{
	switch (i)
	{
		case 1: tune_play(tuneAlarm_H);break;
		case 2: tune_play(tuneAlarm_L);    break;
		case 3: tune_play(tuneAlarm_IN);  break;
		case 4: tune_play(tuneAlarm_OUT); break;
		default: break;
	}
	
}