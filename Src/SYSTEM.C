#include "system.h"
#include "base_key.h" 
#include "lcd.h" 
#include "adjust.h"
#include "STC32G_EEPROM.h"
#include "alarm.h"
SYS sys;//智能电压表
uint8_t EE_Data[30];

void sys_control_Init()
{
	sys.v_font_color=RED;
	sys.a_font_color=GREEN;
	sys.font_style=40;
	sys.adc_state=0;
	sys.adc_data=0;
	sys.voltage=0;
	sys.current=0;
	sys.language=chinese;
	sys.display=0;
}
void sys_EEPROM_datainit(void)//EEPROM
{
			alarmv_table.Alarm_H=4100;
			alarmv_table.Alarm_H_state=0;
			alarmv_table.Alarm_L=0;
			alarmv_table.Alarm_L_state=0;	
			alarmv_table.Alarm_Range_in_a=4200;
			alarmv_table.Alarm_Range_in_b=4300;
			alarmv_table.Alarm_Range_in_state=0;
			alarma_table.Alarm_H=4100;
			alarma_table.Alarm_H_state=0;
			alarma_table.Alarm_L=0;
			alarma_table.Alarm_L_state=0;	
			alarma_table.Alarm_Range_in_a=4200;
			alarma_table.Alarm_Range_in_b=4300;
			alarma_table.Alarm_Range_in_state=0;
			adjustv.factor=10000;
			adjusta.factor=10000;
			sys.language=english;
			sys.v_font_color=RED;
			sys.a_font_color=GREEN;
			sys.display=1;
			EE_Data[3] =	alarmv_table.Alarm_H;
			EE_Data[4] =	alarmv_table.Alarm_H_state;
			EE_Data[5] =	alarmv_table.Alarm_L;
			EE_Data[6] =	alarmv_table.Alarm_L_state;
			EE_Data[7] =	(u8)alarmv_table.Alarm_L;
			EE_Data[8] =	alarmv_table.Alarm_L_state;
			EE_Data[9] =	(u8)(alarmv_table.Alarm_Range_in_a >> 8);
			EE_Data[10] =	(u8)alarmv_table.Alarm_Range_in_a;
			EE_Data[11] =	(u8)(alarmv_table.Alarm_Range_in_b >> 8);
			EE_Data[12] =	(u8)alarmv_table.Alarm_Range_in_b;
			EE_Data[13] =	alarmv_table.Alarm_Range_in_state;
			EE_Data[14] = (u8)(sys.v_font_color >> 8);
			EE_Data[15] = (u8)sys.v_font_color;			
			EE_Data[16] = (u8)(adjustv.factor >> 8);
			EE_Data[17] = (u8)adjustv.factor;
			EE_Data[18] = (u8)sys.language;
			EE_Data[19]	=sys.display;
			EE_Data[24] = (u8)(adjusta.factor >> 8);
			EE_Data[25] = (u8)adjusta.factor;	
			EE_Data[26] = (u8)(sys.a_font_color >> 8);
			EE_Data[27] = (u8)sys.a_font_color;			
}
void sys_EEPROM_write(void)//EEPROM
{
			EEPROM_read_n(EE_ADDRESS,EE_Data,30);
			EE_Data[3] =	(u8)(alarmv_table.Alarm_H >> 8);
			EE_Data[4] =	(u8)alarmv_table.Alarm_H;
			EE_Data[5] =	alarmv_table.Alarm_H_state;
			EE_Data[6] =	(u8)(alarmv_table.Alarm_L >> 8);
			EE_Data[7] =	(u8)alarmv_table.Alarm_L;
			EE_Data[8] =	alarmv_table.Alarm_L_state;
			EE_Data[9] =	(u8)(alarmv_table.Alarm_Range_in_a >> 8);
			EE_Data[10] =	(u8)alarmv_table.Alarm_Range_in_a;
			EE_Data[11] =	(u8)(alarmv_table.Alarm_Range_in_b >> 8);
			EE_Data[12] =	(u8)alarmv_table.Alarm_Range_in_b;
			EE_Data[13] =	alarmv_table.Alarm_Range_in_state;
			EE_Data[14] = (u8)(sys.v_font_color >> 8);
			EE_Data[15] = (u8)sys.v_font_color;
			EE_Data[16] = (u8)(adjustv.factor >> 8);
			EE_Data[17] = (u8)adjustv.factor;	
			EE_Data[18] = (u8)sys.language;
			EE_Data[19]	=	sys.display;
			EE_Data[24] = (u8)(adjusta.factor >> 8);
			EE_Data[25] = (u8)adjusta.factor;
			EE_Data[26] = (u8)(sys.a_font_color >> 8);
			EE_Data[27] = (u8)sys.a_font_color;	
					
			EEPROM_SectorErase(EE_ADDRESS); //擦除扇区
			EEPROM_write_n(EE_ADDRESS,EE_Data,30);//保存
}
void sys_EEPROM_read(void)//EEPROM
{
			EEPROM_read_n(EE_ADDRESS,EE_Data,30);
			adjustv.adc_standard = ((u16)EE_Data[0] << 8) + EE_Data[1]; //
			adjustv.state=EE_Data[2];
			alarmv_table.Alarm_H=((u16)EE_Data[3] << 8) + EE_Data[4];
			alarmv_table.Alarm_H_state=EE_Data[5];
			alarmv_table.Alarm_L=((u16)EE_Data[6] << 8) + EE_Data[7];
			alarmv_table.Alarm_L_state=EE_Data[8];
			alarmv_table.Alarm_Range_in_a=((u16)EE_Data[9] << 8) + EE_Data[10]; 
			alarmv_table.Alarm_Range_in_b=((u16)EE_Data[11] << 8) + EE_Data[12]; 
			alarmv_table.Alarm_Range_in_state=EE_Data[13];
			sys.v_font_color=((u16)EE_Data[14] << 8) + EE_Data[15];
			adjustv.factor=((u16)EE_Data[16] << 8) + EE_Data[17];
			sys.language=EE_Data[18];
			sys.display=EE_Data[19];
			adjusta.adc_tare = ((u16)EE_Data[20] << 8) + EE_Data[21]; //
			adjusta.adc_standard = ((u16)EE_Data[22] << 8) + EE_Data[23]; //
			adjusta.factor=((u16)EE_Data[24] << 8) + EE_Data[25];
			sys.a_font_color=((u16)EE_Data[26] << 8) + EE_Data[27];
			adjustv.adc_tare = ((u16)EE_Data[28] << 8) + EE_Data[29]; //
}
void power(void)//电源状态
{

}








