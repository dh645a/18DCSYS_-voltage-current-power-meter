/************************ �Զ��幫��ͷ�ļ� **************************************/

#ifndef _PBDATA_H//�궨�壬�����ļ�����
#define _PBDATA_H
#include "stc32g.h"       //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
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
void delay_us(u16 nCount); //΢����ʱ����
void delay_ms(u16 nCount); //������ʱ����
void bsp_Idle(void);

#endif //�����ļ����ƽ���


/************************ ��̳��ַ www.zxkjmcu.com ******************************/