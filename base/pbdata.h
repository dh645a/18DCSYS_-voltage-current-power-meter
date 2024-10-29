/************************ 自定义公共头文件 **************************************/

#ifndef _PBDATA_H//宏定义，定义文件名称
#define _PBDATA_H
#include "stc32g.h"       //包含此头文件后，不需要再包含"reg51.h"头文件
#include "intrins.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "bsp_adc.h"
#include "time.h"
#include "main.h"
#include "base_key.h"  
#include "adjust.h"
#include "multi_menu.h"  
#include "system.h"
#include "pwm.h"
#include "spi.h"
#include "buzzer.h"
#include "math.h"
#include "adjust.h"
#include "alarm.h"
#include "lcdfont.h"
#include "wave.h"
#include "STC32G_EEPROM.h"
void delay_us(u16 nCount); //微秒延时程序
void delay_ms(u16 nCount); //毫秒延时程序
void bsp_Idle(void);

#endif //定义文件名称结束


/************************ 论坛地址 www.zxkjmcu.com ******************************/