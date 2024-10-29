
#ifndef   __BUZZER_H
#define   __BUZZER_H
#include "config.h"
typedef void (*buzzFinish_f)(void);//使用了typedef关键字来创建一个函数指针类型的别名
void Init_buzzer(void);//蜂鸣器初始化
void beep(u16 frequency,u16 duty,u16 time,u8 state,buzzFinish_f _onFinish);
void beep_update();
void beep_key(btn_t btn);
void beep_alarm(u8 i);
void tune_stop();
#endif
