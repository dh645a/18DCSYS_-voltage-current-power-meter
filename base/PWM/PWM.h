
#ifndef   __PWM_H
#define   __PWM_H
#include "config.h"
void pwm_init_beep(void);
void pwm_init_blk(void);
void UpdatePwm(u16 frequency,u16 duty);
#endif

