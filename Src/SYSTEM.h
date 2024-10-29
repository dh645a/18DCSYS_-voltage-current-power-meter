#ifndef _SYSTEM_
#define _SYSTEM_
#include "config.h"
#define english     0
#define chinese     1

typedef struct
{
	uint16_t v_font_color;
	uint16_t a_font_color;//
	uint8_t font_style;
	uint8_t adc_state;//
	uint16_t adc_data;
	int voltage;
	int current;
	uint8_t language;
	uint8_t display;
}SYS;//Intelligent voltmeter
/* 参数结构 */

extern SYS sys;
extern uint8_t EE_Data[30];
void sys_control_Init(void);
void sys_EEPROM_datainit(void);//EEPROM
void sys_EEPROM_write(void);//EEPROM
void sys_EEPROM_read(void);//EEPROM
void power(void);//电源状态

#endif
