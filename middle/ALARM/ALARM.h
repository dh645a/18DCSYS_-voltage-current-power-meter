#ifndef _ALARM_H
#define _ALARM_H
#include "config.h"
typedef	struct 
{
	uint16_t 	Alarm_H;//
	uint16_t 	Alarm_L;
	uint16_t 	Alarm_Range_in_a; 
	uint16_t 	Alarm_Range_in_b; 
	uint16_t  Alarm_Range_out_a;
	uint16_t  Alarm_Range_out_b;
	uint8_t Alarm_H_state;
	uint8_t Alarm_L_state;
	uint8_t Alarm_Range_in_state;
	uint8_t Alarm_Range_out_state;
}Alarm;
extern Alarm  alarmv_table;
extern Alarm  alarmv;
extern Alarm  alarma_table;
extern Alarm  alarma;
void set_alarm_value(uint16_t *alarm_value);
void set_alarm_state(uint8_t *alarm_state);
void alarm_update(void);
#endif
