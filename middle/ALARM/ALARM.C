#include "alarm.h"
#include "buzzer.h"
#include "system.h"
#include "main.h"
#include "base_key.h"
 Alarm  alarmv_table={4010,3900,3700,3800,700,800,1,0,0,0};
 Alarm  alarma_table={4010,3900,3700,3800,700,800,1,0,0,0};
 Alarm alarmv;
 Alarm alarma;
 void set_alarm_value(uint16_t *alarm_value) {
    if(sys_key_up.Key_short) {
        Key_value_init();
        beep_key(BTN_UP);
        (*alarm_value)++;
    }
    if(sys_key_up.Key_long) {
        Key_value_init();
        (*alarm_value) += 10;
    }
    if(sys_key_down.Key_short) {
        Key_value_init();
        beep_key(BTN_DOWN);
			//if(*alarm_value>0)
        (*alarm_value)--;
    }
    if(sys_key_down.Key_long) {
        Key_value_init();
			//if(*alarm_value>10)
        (*alarm_value) -= 10;
    }
}
void set_alarm_state(uint8_t *alarm_state) {

    // 处理 Alarm state 的逻辑
    if(sys_key_up.Key_short) {
        Key_value_init();
        beep_key(BTN_UP);
        (*alarm_state)++;
        if (*alarm_state > 1) {
            *alarm_state = 0;
        }
    }
    if(sys_key_down.Key_short) {
        Key_value_init();
        beep_key(BTN_DOWN);
        (*alarm_state)--;
        if (*alarm_state != 0) {
            *alarm_state = 1;
        }
    }
}
void handleAlarm(u8 alarmState, u8 condition, u8* tempState, u8 alarmType) {
    if (alarmState && condition && *tempState) {
        *tempState = 0;
        beep_alarm(alarmType); // 报警类型，例如2或3
    }
    if (alarmState && !condition && !(*tempState)) {
        *tempState = 1;
        tune_stop();
    }
}
void alarm_update(void)//上限 下限 区间 区外 报警
{
	static u8 tempstate_in=1,tempstate_out=1,tempstate_h=1,tempstate_l=1;	
	handleAlarm(alarmv_table.Alarm_H_state, sys.voltage > alarmv_table.Alarm_H, &tempstate_h, 2);
	handleAlarm(alarmv_table.Alarm_L_state, sys.voltage < alarmv_table.Alarm_L, &tempstate_l, 2);
	handleAlarm(alarmv_table.Alarm_Range_in_state, (alarmv_table.Alarm_Range_in_a < sys.voltage) && (sys.voltage < alarmv_table.Alarm_Range_in_b), &tempstate_in, 3);
	handleAlarm(alarmv_table.Alarm_Range_out_state, (alarmv_table.Alarm_Range_out_a > sys.voltage) || (sys.voltage > alarmv_table.Alarm_Range_out_b), &tempstate_out, 3);
}
//void alarm_update(void)//上限 下限 区间 区外 报警
//{
//	static u8  tempstate_in=1,tempstate_out=1,tempstate_h=1,tempstate_l=1;	
//	if(alarmv_table.Alarm_H_state&&(sys.voltage>alarmv_table.Alarm_H)&&tempstate_h)
//	{
//			tempstate_h=0;
//			beep_alarm(2);

//	}
//	if(alarmv_table.Alarm_H_state&&(sys.voltage<alarmv_table.Alarm_H)&&(tempstate_h==0))
//	{
//			tempstate_h=1;tune_stop();
//		
//	}	
//	if(alarmv_table.Alarm_L_state&&(sys.voltage<alarmv_table.Alarm_L)&&tempstate_l)
//	{
//			tempstate_l=0;
//			beep_alarm(2);
//	}
//	if(alarmv_table.Alarm_L_state&&(sys.voltage>alarmv_table.Alarm_L)&&(tempstate_l==0))
//	{
//			tempstate_l=1;tune_stop();		
//	}		
//	if(alarmv_table.Alarm_Range_in_state&&(alarmv_table.Alarm_Range_in_a<sys.voltage)&&(sys.voltage<alarmv_table.Alarm_Range_in_b)&&tempstate_in)
//	{
//			tempstate_in=0;
//			beep_alarm(3);
//	}
//	if(alarmv_table.Alarm_Range_in_state&&((alarmv_table.Alarm_Range_in_a>sys.voltage)||(sys.voltage>alarmv_table.Alarm_Range_in_b))&&(tempstate_in==0))
//	{
//			tempstate_in=1;tune_stop();		
//	}
//	if(alarmv_table.Alarm_Range_out_state&&((alarmv_table.Alarm_Range_out_a>sys.voltage)||(sys.voltage>alarmv_table.Alarm_Range_out_b))&&tempstate_out)
//	{
//			tempstate_out=0;
//			beep_alarm(3);
//	}
//	if((alarmv_table.Alarm_Range_out_a<sys.voltage)&&(sys.voltage<alarmv_table.Alarm_Range_out_b)&&(tempstate_out==0))
//	{
//			tempstate_out=1;tune_stop();		
//	}			
//}

