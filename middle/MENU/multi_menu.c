#include "multi_menu.h"   
#include "lcd.h"
#include "bsp_adc.h"
#include "lcd_init.h"
#include "base_key.h" 
#include "system.h" 
#include "wave.h" 
#include "buzzer.h"
#include "alarm.h"
#include "adjust.h"
static u8 display1_state=1,display2_state=1;
void (*current_operation_index)();
u8 func_index = 0; //��ʼ��ʾ��ӭ����
u8 last_index = 127; //last��ʼΪ��Чֵ
key_table table[32]=
{
	//��0��
	{0,0,0,1,0,(*fun_0)},

    //��1�� ����-����-У׼-����
	{1,4,2, 16,0,(*fun_menu_main)},//current,up,down,enter,����
	{2,1,3, 9,0,(*fun_menu_main)},
	{3,2,4,12,0,(*fun_menu_main)},		
	{4,3,1,14,0,(*fun_menu_main)},
	
    //��2�� 
	{5,6,6,16,1,NULL},		
	{6,5,5,20,1,NULL},
	{7,6,8,NULL,1,NULL},						                	
	{8,7,5,NULL,1,NULL},
	
	{ 9,11,10,24,2,(*fun_menu_font)},	//����				
	{10, 9,11,25,2,(*fun_menu_font)},//����V��ɫ
	{11, 10,9,26,2,(*fun_menu_font)},//����A��ɫ
	
	{12,13,13,21,3,(*fun_menu_adjust)},	//У׼
	{13,12,12,22,3,(*fun_menu_adjust)},
		
	{14,15,15,14,4,(*fun_language)},
	{15,14,14,15,4,(*fun_language)},//����
	
	 //��3��
	{16,19,17,27,1,(*fun_menu_alarm)},//��ѹ��������������������					
	{17,16,18,28,1,(*fun_menu_alarm)},
	{18,17,19,29,1,(*fun_menu_alarm)},						                	
	{19,18,16,30,1,(*fun_menu_alarm)},
	
	{20,23,21,14,6,NULL},			
	{21,20,22,15,6,NULL},
	{22,21,23,16,6,NULL},						                	
	{23,22,20,17,6,NULL},
	
	{24,24,24,24,9,(*fun_fong_style)},//����	
	{25,25,25,25,10,(*fun_font_color_v)},//����V��ɫ
	{26,26,26,26,11,(*fun_font_color_a)},//����A��ɫ
				
	{27,27,27,27,16,(*fun_alarm_H)},						                	
	{28,28,28,28,17,(*fun_alarm_L)},					
	{29,29,29,29,18,(*fun_alarm_In)},
	{30,30,30,30,19,(*fun_alarm_Out)},							
};
void menu_level_1()//����-����-У׼-����
{
	if(sys.language)
	{
		LCD_ShowString(20,2,"1.",RED,BLACK,16,0);
		LCD_ShowString(20,2+20,"2.",RED,BLACK,16,0);
		LCD_ShowString(20,2+40,"3.",RED,BLACK,16,0);
		LCD_ShowString(20,2+60,"4.",RED,BLACK,16,0);
		LCD_ShowChinese(20+16,2,"����",RED,BLACK,16,0);
		LCD_ShowChinese(20+16,2+20,"����",RED,BLACK,16,0);
		LCD_ShowChinese(20+16,2+40,"У׼",RED,BLACK,16,0);
		
	}
	else
	{
		LCD_ShowString(20,2,"1.Alarm",RED,BLACK,16,0);
		LCD_ShowString(20,2+20,"2.Font Color",RED,BLACK,16,0);
		LCD_ShowString(20,2+40,"3.Ajust",RED,BLACK,16,0);
		//LCD_ShowString(20,2+60,"4.Language",RED,BLACK,16,0);
	}
	LCD_ShowString(20,2+60,"4.Lang/",RED,BLACK,16,0);
	LCD_ShowChinese(20+56,2+60,"����",RED,BLACK,16,0);
}
void menu_level_2a()
{
	LCD_ShowString(16,2,"1.Voltage",RED,BLACK,16,0);
	LCD_ShowString(16,2+20,"2.Current",RED,BLACK,16,0);
}
void menu_level_2b()
{
}
/*********��1��***********/
void fun_menu_main()   
{
	switch (func_index)
	{
		case 1: LCD_ShowString(2,2,">",GREEN,BLACK,16,0); break;
		case 2: LCD_ShowString(2,22,">",GREEN,BLACK,16,0);break;
		case 3: LCD_ShowString(2,42,">",GREEN,BLACK,16,0); break;
		case 4: LCD_ShowString(2,62,">",GREEN,BLACK,16,0);break;
		//defau1t: break;
	}	
	menu_level_1();																				
}

/*********��2��***********/
void font_str()
{
	if(sys.language)
	{
		LCD_ShowString(20,2,"1.",RED,BLACK,16,0);
		LCD_ShowString(20,2+20,"2.",RED,BLACK,16,0);
		LCD_ShowString(20,2+40,"3.",RED,BLACK,16,0);
		LCD_ShowChinese(20+16,2,"����",RED,BLACK,16,0);
		LCD_ShowChinese(20+16,2+20,"������ɫ",RED,BLACK,16,0);LCD_ShowString(20+16+16*4,2+20,"V",RED,BLACK,16,0);
		LCD_ShowChinese(20+16,2+40,"������ɫ",RED,BLACK,16,0);LCD_ShowString(20+16+16*4,2+40,"A",RED,BLACK,16,0);
		
	}
	else
	{
		LCD_ShowString(20,2,"1.Font",RED,BLACK,16,0);
		LCD_ShowString(20,2+20,"2.Font Color V",RED,BLACK,16,0);
		LCD_ShowString(20,2+40,"3.Font Color A",RED,BLACK,16,0);
	}
}

void fun_menu_font()    
{	
	switch (func_index)
	{
		case 9 : LCD_ShowString(2,2,">",GREEN,BLACK,16,0); break;
		case 10:  LCD_ShowString(2,22,">",GREEN,BLACK,16,0);break;
		case 11:  LCD_ShowString(2,42,">",GREEN,BLACK,16,0);break;
		//defau1t: break;
	}	
	font_str();														
}
void fun_menu_adjust()    
{	
	switch (func_index)
	{
		case 12 : LCD_ShowString(2,2,">",GREEN,BLACK,16,0); break;
		case 13:  LCD_ShowString(2,22,">",GREEN,BLACK,16,0);break;
		//defau1t: break;
	}	
	menu_level_2a();														
}
void fun_c21()   //У׼ 
{	
		LCD_ShowString(16,2,"adjust",RED,BLACK,16,0);
		LCD_ShowString(16,2+16,"k=",RED,BLACK,16,0);
		LCD_ShowFloatNum(16+8*2,2+16,adjustv.factor,5,4,RED,BLACK,16); //��ѹϵ��
		LCD_ShowString(16,2+16+16,"v=",RED,BLACK,16,0);

		#ifdef DC40V
		LCD_ShowFloatNum(16+8*2,2+16+16,sys.voltage,4,2,RED,BLACK,16); //��ѹ	
		#endif
		#ifdef DC400V
		LCD_ShowFloatNum(16+8*2,2+16+16,sys.voltage,4,1,RED,BLACK,16); //��ѹ	
		#endif
		LCD_ShowFloatNum(16+8*2,2+16+16+16,channel_GetAdcAverage(7,100),4,0,RED,BLACK,16); //adc
		LCD_ShowFloatNum(16+8*2+8*6,2+16+16+16,channel_GetAdcAverage(0,100),4,0,RED,BLACK,16); //adc
		if(sys_key_up.Key_short||sys_key_up.Key_long)//��⵽���̰� ���Ӽ�
    {
			Key_value_init();
			beep_key(BTN_UP);
      adjustv.factor++;
      if(adjustv.factor>20000) adjustv.factor=10000;
    }
		if(sys_key_down.Key_short||sys_key_down.Key_long)//��⵽3���̰� ��С��
    {
			Key_value_init();
			beep_key(BTN_DOWN);
      adjustv.factor--;
      if(adjustv.factor<=0) adjustv.factor=10000;		
    }
}

void fun_language()     
{

	switch (func_index)
	{
		case 14 : 	LCD_ShowString(160-40,2+60,"EN",GREEN,BLACK,16,0);
								sys.language=english; break;
		case 15:  	
								LCD_ShowChinese(160-40,2+60,"��",GREEN,BLACK,16,0);
								sys.language=chinese;break;
	}		
		menu_level_1();
	LCD_ShowString(2,62," ",GREEN,BLACK,16,0);
}
/*********��3��***********/
void menu_level_3a()
{
	LCD_ShowString(16,2,"1.High",RED,BLACK,16,0);
	LCD_ShowString(16,2+20,"2.Low",RED,BLACK,16,0);
	LCD_ShowString(16,2+40,"3.Within",RED,BLACK,16,0);
	LCD_ShowString(16,2+60,"4.Beyond",RED,BLACK,16,0);
	if(alarma_table.Alarm_H_state)
	LCD_ShowString(160-8*3,2,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*3,2,"OFF",LBBLUE,BLACK,16,0);
	if(alarma_table.Alarm_L_state)
	LCD_ShowString(160-8*3,2+20,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*3,2+20,"OFF",LBBLUE,BLACK,16,0);
	if(alarma_table.Alarm_Range_in_state)
	LCD_ShowString(160-8*3,2+40,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*3,2+40,"OFF",LBBLUE,BLACK,16,0);
	if(alarma_table.Alarm_Range_out_state)
	LCD_ShowString(160-8*3,2+60,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*3,2+60,"OFF",LBBLUE,BLACK,16,0);
	//-------------------------------------------------
	LCD_ShowString(160-8*4,2,"|",RED,BLACK,16,0);
	LCD_ShowString(160-8*4,2+20,"|",RED,BLACK,16,0);
	LCD_ShowString(160-8*4,2+40,"|",RED,BLACK,16,0);
	LCD_ShowString(160-8*4,2+60,"|",RED,BLACK,16,0);
	//-------------------------------------------------
	if(alarmv_table.Alarm_H_state)
	LCD_ShowString(160-8*7,2,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*7,2,"OFF",LBBLUE,BLACK,16,0);
	if(alarmv_table.Alarm_L_state)
	LCD_ShowString(160-8*7,2+20,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*7,2+20,"OFF",LBBLUE,BLACK,16,0);
	if(alarmv_table.Alarm_Range_in_state)
	LCD_ShowString(160-8*7,2+40,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*7,2+40,"OFF",LBBLUE,BLACK,16,0);
	if(alarmv_table.Alarm_Range_out_state)
	LCD_ShowString(160-8*7,2+60,"ON ",GREEN,BLACK,16,0);
	else
	LCD_ShowString(160-8*7,2+60,"OFF",LBBLUE,BLACK,16,0);
}
void fun_menu_alarm()   
{
	switch (func_index)
	{
		case 16: LCD_ShowString(2,2,">",GREEN,BLACK,16,0); break;
		case 17: LCD_ShowString(2,22,">",GREEN,BLACK,16,0);break;
		case 18: LCD_ShowString(2,42,">",GREEN,BLACK,16,0); break;
		case 19: LCD_ShowString(2,62,">",GREEN,BLACK,16,0);break;
		//defau1t: break;
	}	
	menu_level_3a();																				
}

//// ��ʾ��ֵ����λ����ѹ�������
//void display_alarm_value(u8 x, u8 y, u16 value, u8 decimal_places, const char* unit, u16 fg_color, u16 bg_color) {
//    LCD_ShowFloatNum(x, y, value, 4, decimal_places, fg_color, bg_color, 16);  // ��ʾ��ֵ
//    LCD_ShowString(x + 40, y, unit, fg_color, bg_color, 16, 0);  // ��ʾ��λ
//}

//// ��ʾ����״̬ (ON/OFF)
//void display_alarm_state(u8 x, u8 y, u8 alarm_state, u8 is_selected, u16 fg_color, u16 bg_color) {
//    if (alarm_state) {
//        LCD_ShowString(x, y, "ON ", is_selected ? bg_color : fg_color, is_selected ? fg_color : bg_color, 16, 0);
//    } else {
//        LCD_ShowString(x, y, "OFF", is_selected ? bg_color : fg_color, is_selected ? fg_color : bg_color, 16, 0);
//    }
//}

//// �������߼�
//void handle_alarm(u16 *alarm_value, u8 *alarm_state, u8 i, u8 item_base, u8 y_pos, const char* label, u8 decimal_places, const char* unit) {
//    LCD_ShowString(0, y_pos, label, RED, BLACK, 16, 0);  // ��ʾ��ǩ����ѹ�������
//    
//    // ��ʾ������ֵ
//    if (i == item_base) {  // �жϵ�ǰ�Ƿ������ֵ
//        display_alarm_value(16+48, y_pos, *alarm_value, decimal_places, unit, BLACK, RED);  // ������ʾ
//    } else {
//        display_alarm_value(16+48, y_pos, *alarm_value, decimal_places, unit, RED, BLACK);  // ������ʾ
//    }
//    // ��ʾ����״̬
//    display_alarm_state(16+48+8+40+16, y_pos, *alarm_state, i == item_base + 1,GREEN , BLACK);

//    // ��������ֵ��״̬�ĵ���
//    if (i == item_base) {
//        set_alarm_value(alarm_value);
//    } else if (i == item_base + 1) {
//        set_alarm_state(alarm_state);
//    }
//}

//// fun_alarm_H �Ż�
//void fun_alarm_H() {
//    static u8 i = 1;

//    // ��1����ʾ��ѹ����
//    handle_alarm(&alarmv_table.Alarm_H, &alarmv_table.Alarm_H_state, i, 1, 2, "1.High", 2, "V");
//    
//    // ��2����ʾ��������
//    handle_alarm(&alarma_table.Alarm_H, &alarma_table.Alarm_H_state, i, 3, 22, "2.High", 3, "A");

//    // �л�ѡ��
//    if (sys_key_set.Key_short) {
//        sys_key_set.Key_short = 0;
//        beep_key(BTN_SET);
//        i++;
//        if (i > 4) {
//            i = 1;
//        }
//    }
//}

//// fun_alarm_L �Ż�
//void fun_alarm_L() {
//    static u8 i = 1;

//    // ��1����ʾ�͵�ѹ����
//    handle_alarm(&alarmv_table.Alarm_L, &alarmv_table.Alarm_L_state, i, 1, 2, "1.Low", 2, "V");
//    
//    // ��2����ʾ�͵�������
//    handle_alarm(&alarma_table.Alarm_L, &alarma_table.Alarm_L_state, i, 3, 22, "2.Low", 3, "A");

//    // �л�ѡ��
//    if (sys_key_set.Key_short) {
//        sys_key_set.Key_short = 0;
//        beep_key(BTN_SET);
//        i++;
//        if (i > 4) {
//            i = 1;
//        }
//    }
//}
void fun_alarm_H()    
{	
	static u8 i=1;
	LCD_ShowString((160-sizeof("High")*8)/2,0,"High",RED,BLACK,16,0);
	#ifdef DC40V
	if(i==1)
	LCD_ShowFloatNum(16+16,2+20,alarmv_table.Alarm_H,4,2,BLACK,RED,16); //��ѹ
	else
	LCD_ShowFloatNum(16+16,2+20,alarmv_table.Alarm_H,4,2,RED,BLACK,16); //��ѹ
	#endif
	#ifdef DC400V
	LCD_ShowFloatNum(16+16,2+20,alarmv_table.Alarm_H,4,1,RED,BLACK,16); //��ѹ
	#endif
	
	LCD_ShowString(16+16+40,2+20,"V",RED,BLACK,16,0);
	if(alarmv_table.Alarm_H_state)
	{
			if(i==2)
				LCD_ShowString(16+16+8+40+16,2+20,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+16+8+40+16,2+20,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==2)
			LCD_ShowString(16+16+8+40+16,2+20,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+16+8+40+16,2+20,"OFF",LBBLUE,BLACK,16,0);
	}
	#ifdef DC4A
	if(i==3)
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_H,4,3,BLACK,RED,16); //����
	else
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_H,4,3,RED,BLACK,16); //
	#endif
	#ifdef DC10A
	if(i==3)
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_H,4,2,BLACK,RED,16); //	
	else
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_H,4,2,RED,BLACK,16); //
	#endif
	
	LCD_ShowString(16+16+40,2+40,"A",RED,BLACK,16,0);
	if(alarma_table.Alarm_H_state)
	{
			if(i==4)
				LCD_ShowString(16+16+8+40+16,2+40,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+16+8+40+16,2+40,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==4)
			LCD_ShowString(16+16+8+40+16,2+40,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+16+8+40+16,2+40,"OFF",LBBLUE,BLACK,16,0);
	}
	switch (i)
	{
		case 1 : 	
							set_alarm_value(&alarmv_table.Alarm_H);							
							break;
		case 2:  			
							set_alarm_state(&alarmv_table.Alarm_H_state);
							break;

		case 3:		
							set_alarm_value(&alarma_table.Alarm_H);								
							break; 
		case 4:  			
							set_alarm_state(&alarma_table.Alarm_H_state);
							break;
	}	
	if(sys_key_set.Key_short)
	{
		sys_key_set.Key_short=0;
		beep_key(BTN_SET);
		i++;
		if(i>4)
			i=1;
	}	

}
void fun_alarm_L()    
{	
	static u8 i=1;
	LCD_ShowString((160-sizeof("Low")*8)/2,0,"Low",RED,BLACK,16,0);
	#ifdef DC40V
	if(i==1)
	LCD_ShowFloatNum(16+16,2+20,alarmv_table.Alarm_L,4,2,BLACK,RED,16); //��ѹ
	else
	LCD_ShowFloatNum(16+16,2+20,alarmv_table.Alarm_L,4,2,RED,BLACK,16); //��ѹ
	#endif
	#ifdef DC400V
	LCD_ShowFloatNum(16+16,2+20,alarmv_table.Alarm_L,4,1,RED,BLACK,16); //��ѹ
	#endif
	LCD_ShowString(16+16+40,2+20,"V",RED,BLACK,16,0);
	if(alarmv_table.Alarm_L_state)
	{
			if(i==2)
				LCD_ShowString(16+16+8+40+16,2+20,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+16+8+40+16,2+20,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==2)
			LCD_ShowString(16+16+8+40+16,2+20,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+16+8+40+16,2+20,"OFF",LBBLUE,BLACK,16,0);
	}
	#ifdef DC4A
	if(i==3)
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_L,4,3,BLACK,RED,16); //����
	else
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_L,4,3,RED,BLACK,16); //
	#endif
	#ifdef DC10A
	if(i==3)
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_L,4,2,BLACK,RED,16); //	
	else
	LCD_ShowFloatNum(16+16,2+40,alarma_table.Alarm_L,4,2,RED,BLACK,16); //
	#endif
	LCD_ShowString(16+16+40,2+40,"A",RED,BLACK,16,0);
	if(alarma_table.Alarm_L_state)
	{
			if(i==4)
				LCD_ShowString(16+16+8+40+16,2+40,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+16+8+40+16,2+40,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==4)
			LCD_ShowString(16+16+8+40+16,2+40,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+16+8+40+16,2+40,"OFF",LBBLUE,BLACK,16,0);
	}
	switch (i)
	{
		case 1 : 	
							set_alarm_value(&alarmv_table.Alarm_L);							
							break;
		case 2:  			
							set_alarm_state(&alarmv_table.Alarm_L_state);
							break;

		case 3:		
							set_alarm_value(&alarma_table.Alarm_L);								
							break; 
		case 4:  			
							set_alarm_state(&alarma_table.Alarm_L_state);
							break;
	}	
	if(sys_key_set.Key_short)
	{
		sys_key_set.Key_short=0;
		beep_key(BTN_SET);
		i++;
		if(i>4)
			i=1;
	}	

}
void fun_alarm_In()    
{	
  static u8 i=1;
	LCD_ShowString((160-sizeof("In")*8)/2,0,"In",RED,BLACK,16,0);
	LCD_ShowString(16+48-8,2+20,"-",RED,BLACK,16,0);
	LCD_ShowString(16+48-8,2+40,"-",RED,BLACK,16,0);
	#ifdef DC40V
	if(i==1)
	LCD_ShowFloatNum(16,2+20,alarmv_table.Alarm_Range_in_a,4,2,BLACK,RED,16); //��ѹ
	else
	LCD_ShowFloatNum(16,2+20,alarmv_table.Alarm_Range_in_a,4,2,RED,BLACK,16); //��ѹ
	if(i==2)
	LCD_ShowFloatNum(16+48,2+20,alarmv_table.Alarm_Range_in_b,4,2,BLACK,RED,16); //��ѹ
	else
	LCD_ShowFloatNum(16+48,2+20,alarmv_table.Alarm_Range_in_b,4,2,RED,BLACK,16); //��ѹ
	#endif
	#ifdef DC400V
	#endif
	
	LCD_ShowString(16+48+40,2+20,"V",RED,BLACK,16,0);
	if(alarmv_table.Alarm_Range_in_state)
	{
			if(i==3)
				LCD_ShowString(16+48+8+40+16,2+20,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+48+8+40+16,2+20,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==3)
			LCD_ShowString(16+48+8+40+16,2+20,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+48+8+40+16,2+20,"OFF",LBBLUE,BLACK,16,0);
	}
	#ifdef DC4A
	if(i==4)
	LCD_ShowFloatNum(16,2+40,alarma_table.Alarm_Range_in_a,4,3,BLACK,RED,16); //����
	else
	LCD_ShowFloatNum(16,2+40,alarma_table.Alarm_Range_in_a,4,3,RED,BLACK,16); //
	if(i==5)
	LCD_ShowFloatNum(16+48,2+40,alarma_table.Alarm_Range_in_b,4,3,BLACK,RED,16); //����
	else
	LCD_ShowFloatNum(16+48,2+40,alarma_table.Alarm_Range_in_b,4,3,RED,BLACK,16); //
	#endif
	#ifdef DC10A
	#endif
	LCD_ShowString(16+48+40,2+40,"A",RED,BLACK,16,0);
	if(alarma_table.Alarm_Range_in_state)
	{
			if(i==6)
				LCD_ShowString(16+48+8+40+16,2+40,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+48+8+40+16,2+40,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==6)
			LCD_ShowString(16+48+8+40+16,2+40,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+48+8+40+16,2+40,"OFF",LBBLUE,BLACK,16,0);
	}
	switch (i)
	{
		case 1 : set_alarm_value(&alarmv_table.Alarm_Range_in_a);			
							break;
		case 2:  set_alarm_value(&alarmv_table.Alarm_Range_in_b);
							break;
		case 3:  	set_alarm_state(&alarmv_table.Alarm_Range_in_state);			
							break;
		case 4 : set_alarm_value(&alarma_table.Alarm_Range_in_a);			
							break;
		case 5:  set_alarm_value(&alarma_table.Alarm_Range_in_b);
							break;
		case 6:  	set_alarm_state(&alarma_table.Alarm_Range_in_state);			
							break;
	}	
	if(sys_key_set.Key_short)
	{
		sys_key_set.Key_short=0;
		beep_key(BTN_SET);
		i++;
		if(i>6)
			i=1;
	}																							
}
void fun_alarm_Out()    
{	
  static u8 i=1;
	LCD_ShowString((160-sizeof("Out")*8)/2,0,"Out",RED,BLACK,16,0);
	LCD_ShowString(16+48-8,2+20,"#",RED,BLACK,16,0);
	LCD_ShowString(16+48-8,2+40,"#",RED,BLACK,16,0);
	#ifdef DC40V
	if(i==1)
	LCD_ShowFloatNum(16,2+20,alarmv_table.Alarm_Range_out_a,4,2,BLACK,RED,16); //��ѹ
	else
	LCD_ShowFloatNum(16,2+20,alarmv_table.Alarm_Range_out_a,4,2,RED,BLACK,16); //��ѹ
	if(i==2)
	LCD_ShowFloatNum(16+48,2+20,alarmv_table.Alarm_Range_out_b,4,2,BLACK,RED,16); //��ѹ
	else
	LCD_ShowFloatNum(16+48,2+20,alarmv_table.Alarm_Range_out_b,4,2,RED,BLACK,16); //��ѹ
	#endif
	#ifdef DC400V
	#endif
	
	LCD_ShowString(16+48+40,2+20,"V",RED,BLACK,16,0);
	if(alarmv_table.Alarm_Range_out_state)
	{
			if(i==3)
				LCD_ShowString(16+48+8+40+16,2+20,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+48+8+40+16,2+20,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==3)
			LCD_ShowString(16+48+8+40+16,2+20,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+48+8+40+16,2+20,"OFF",LBBLUE,BLACK,16,0);
	}
	#ifdef DC4A
	if(i==4)
	LCD_ShowFloatNum(16,2+40,alarma_table.Alarm_Range_out_a,4,3,BLACK,RED,16); //����
	else
	LCD_ShowFloatNum(16,2+40,alarma_table.Alarm_Range_out_a,4,3,RED,BLACK,16); //
	if(i==5)
	LCD_ShowFloatNum(16+48,2+40,alarma_table.Alarm_Range_out_b,4,3,BLACK,RED,16); //����
	else
	LCD_ShowFloatNum(16+48,2+40,alarma_table.Alarm_Range_out_b,4,3,RED,BLACK,16); //
	#endif
	#ifdef DC10A
	#endif
	LCD_ShowString(16+48+40,2+40,"A",RED,BLACK,16,0);
	if(alarma_table.Alarm_Range_out_state)
	{
			if(i==6)
				LCD_ShowString(16+48+8+40+16,2+40,"ON ",BLACK,GREEN,16,0);
			else
				LCD_ShowString(16+48+8+40+16,2+40,"ON ",GREEN,BLACK,16,0);
	}
	else
	{
			if(i==6)
			LCD_ShowString(16+48+8+40+16,2+40,"OFF",BLACK,LBBLUE,16,0);
			else
			LCD_ShowString(16+48+8+40+16,2+40,"OFF",LBBLUE,BLACK,16,0);
	}
	switch (i)
	{
		case 1 : set_alarm_value(&alarmv_table.Alarm_Range_out_a);			
							break;
		case 2:  set_alarm_value(&alarmv_table.Alarm_Range_out_b);
							break;
		case 3:  	set_alarm_state(&alarmv_table.Alarm_Range_out_state);			
							break;
		case 4 : set_alarm_value(&alarma_table.Alarm_Range_out_a);			
							break;
		case 5:  set_alarm_value(&alarma_table.Alarm_Range_out_b);
							break;
		case 6:  	set_alarm_state(&alarma_table.Alarm_Range_out_state);			
							break;
	}	
	if(sys_key_set.Key_short)
	{
		sys_key_set.Key_short=0;
		beep_key(BTN_SET);
		i++;
		if(i>6)
			i=1;
	}																							
}

void fun_fong_style()    
{	
	//digital-7,gungsuhche
		static u8 i=1;
		font_str();	
		LCD_ShowString(2,2," ",GREEN,BLACK,16,0);
		if(sys_key_up.Key_short)
			{
				sys_key_up.Key_short=0;
				beep_key(BTN_UP);
					i--;
				if(i<1)
					i=4;
			}
			if(sys_key_down.Key_short)
			{
				sys_key_down.Key_short=0;
				beep_key(BTN_DOWN);
						i++;
				if(i>4)
					i=1;
			}
		switch (i)
		{
			case 1 : LCD_ShowString(160-8*4,2,"F1",GREEN,BLACK,16,0);sys.font_style=40; break;
			case 2:  LCD_ShowString(160-8*4,2,"F2",GREEN,BLACK,16,0);sys.font_style=41; break;
			case 3:  LCD_ShowString(160-8*4,2,"F3",GREEN,BLACK,16,0);sys.font_style=42; break;
			case 4:  LCD_ShowString(160-8*4,2,"F4",GREEN,BLACK,16,0);sys.font_style=43; break;
		}																		
}
void fun_font_color_v()    
{	
		static u8 i=1;
		font_str();	
		LCD_ShowString(2,22," ",GREEN,BLACK,16,0);
		//LCD_ShowString(2,2," ",GREEN,BLACK,16,0);
		if(sys_key_up.Key_short)
			{
				sys_key_up.Key_short=0;
				beep_key(BTN_UP);
					i--;
				if(i<1)
					i=15;
			}
			if(sys_key_down.Key_short)
			{
				sys_key_down.Key_short=0;
				beep_key(BTN_DOWN);
						i++;
				if(i>15)
					i=1;
			}
	switch (i)
	{
		case 1 : LCD_Fill(140,2+20,156,2+20+16,WHITE);sys.v_font_color=WHITE; break;
		case 2:  LCD_Fill(140,2+20,156,2+20+16,BLUE);sys.v_font_color=BLUE;    break;
		case 3:  LCD_Fill(140,2+20,156,2+20+16,GBLUE);sys.v_font_color=GBLUE;    break;
		case 4:  LCD_Fill(140,2+20,156,2+20+16,RED);sys.v_font_color=RED;    break;
		case 5:  LCD_Fill(140,2+20,156,2+20+16,MAGENTA);sys.v_font_color=MAGENTA;    break;
		case 6:  LCD_Fill(140,2+20,156,2+20+16,GREEN);sys.v_font_color=GREEN;    break;
		case 7:  LCD_Fill(140,2+20,156,2+20+16,YELLOW);sys.v_font_color=YELLOW;    break;
		case 8:  LCD_Fill(140,2+20,156,2+20+16,BROWN);sys.v_font_color=BROWN;    break;
		case 9:  LCD_Fill(140,2+20,156,2+20+16,BRRED);sys.v_font_color=BRRED;    break;
		case 10: LCD_Fill(140,2+20,156,2+20+16,GRAY);sys.v_font_color=GRAY;    break;
		case 11: LCD_Fill(140,2+20,156,2+20+16,DARKBLUE);sys.v_font_color=DARKBLUE;    break;
		case 12: LCD_Fill(140,2+20,156,2+20+16,LIGHTBLUE);sys.v_font_color=LIGHTBLUE;    break;
		case 13: LCD_Fill(140,2+20,156,2+20+16,GRAYBLUE);sys.v_font_color=GRAYBLUE;    break;
		case 14: LCD_Fill(140,2+20,156,2+20+16,LIGHTGREEN);sys.v_font_color=LIGHTGREEN;    break;
		case 15: LCD_Fill(140,2+20,156,2+20+16,LGRAY);sys.v_font_color=LGRAY;    break;
	}																							
}
void fun_font_color_a()    
{	
		static u8 i=1;
		font_str();	
		LCD_ShowString(2,22," ",GREEN,BLACK,16,0);
		LCD_ShowString(2,2," ",GREEN,BLACK,16,0);
		if(sys_key_up.Key_short)
			{
				sys_key_up.Key_short=0;
				beep_key(BTN_UP);
					i--;
				if(i<1)
					i=15;
			}
			if(sys_key_down.Key_short)
			{
				sys_key_down.Key_short=0;
				beep_key(BTN_DOWN);
						i++;
				if(i>15)
					i=1;
			}
	switch (i)
	{
		case 1 : LCD_Fill(140,2+40,156,2+40+16,WHITE);sys.a_font_color=WHITE; break;
		case 2:  LCD_Fill(140,2+40,156,2+40+16,BLUE);sys.a_font_color=BLUE;    break;
		case 3:  LCD_Fill(140,2+40,156,2+40+16,GBLUE);sys.a_font_color=GBLUE;    break;
		case 4:  LCD_Fill(140,2+40,156,2+40+16,RED);sys.a_font_color=RED;    break;
		case 5:  LCD_Fill(140,2+40,156,2+40+16,MAGENTA);sys.a_font_color=MAGENTA;    break;
		case 6:  LCD_Fill(140,2+40,156,2+40+16,GREEN);sys.a_font_color=GREEN;    break;
		case 7:  LCD_Fill(140,2+40,156,2+40+16,YELLOW);sys.a_font_color=YELLOW;    break;
		case 8:  LCD_Fill(140,2+40,156,2+40+16,BROWN);sys.a_font_color=BROWN;    break;
		case 9:  LCD_Fill(140,2+40,156,2+40+16,BRRED);sys.a_font_color=BRRED;    break;
		case 10: LCD_Fill(140,2+40,156,2+40+16,GRAY);sys.a_font_color=GRAY;    break;
		case 11: LCD_Fill(140,2+40,156,2+40+16,DARKBLUE);sys.a_font_color=DARKBLUE;    break;
		case 12: LCD_Fill(140,2+40,156,2+40+16,LIGHTBLUE);sys.a_font_color=LIGHTBLUE;    break;
		case 13: LCD_Fill(140,2+40,156,2+40+16,GRAYBLUE);sys.a_font_color=GRAYBLUE;    break;
		case 14: LCD_Fill(140,2+40,156,2+40+16,LIGHTGREEN);sys.a_font_color=LIGHTGREEN;    break;
		case 15: LCD_Fill(140,2+40,156,2+40+16,LGRAY);sys.a_font_color=LGRAY;    break;
	}																							
}
void fun_b33()    
{	

}

void fun_b34()    
{		
}
/*********��0��***********/
void fun_0()
{


	switch (sys.display)
	{
			case 1 :
							if(display1_state==1)
							{
								LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
								display1_state=0;
								display2_state=1;
							}
							LCD_ShowChinese(0,8,"��",sys.v_font_color,BLACK,24,0);
							LCD_ShowChinese(0,48,"��",sys.a_font_color,BLACK,24,0);
							#ifdef DC40V
//							sys.voltage=4000;
//							sys.current=5000;
							LCD_ShowFloatNum(30,0,sys.voltage,4,2,sys.v_font_color,BLACK,sys.font_style); //��ѹ
							LCD_ShowFloatNum(30,40,sys.current,4,3,sys.a_font_color,BLACK,sys.font_style); //����
							#endif
							#ifdef DC400V
							LCD_ShowFloatNum(2,0,sys.voltage,4,1,sys.v_font_color,BLACK,sys.font_style); //��ѹ
							#endif	
								LCD_ShowChar1(135,10,95+(sys.font_style%40*2),sys.v_font_color,BLACK,24,0);//V
								LCD_ShowChar1(135,50,96+(sys.font_style%40*2),sys.a_font_color,BLACK,24,0);//A
								alarm_update(); //
							break;
			case 2:  
							if(display2_state==1)
							{
								LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
								display1_state=1;
								display2_state=0;
							}
						
							#ifdef DC40V
							LCD_ShowFloatNum(2,16,sys.voltage,4,2,sys.v_font_color,BLACK,48); //��ѹ
							#endif
							#ifdef DC400V
							LCD_ShowFloatNum(2,16,sys.voltage,4,1,sys.v_font_color,BLACK,48); //��ѹ
							#endif	
							LCD_ShowChar1(28*5+6,36,95,BLACK,sys.v_font_color,24,0);//V    
							break;
//		case 3:  
//			
//							wave(GetAdcAverage(1),1);
//							break;
	}	

}
	u8 isEditableFunction(u8 index) {
			//return (index < 24 || index > 30);
		return (func_index!=24)&&(func_index!=25)&&(func_index!=26)&&(func_index!=27)&&(func_index!=28)&&(func_index!=29)&&(func_index!=30);
	}
void menu_update()
{
	static u8 flag_Key_set_long=1;
		if(sys_key_up.Key_short&&isEditableFunction(func_index))
		{
			Key_value_init();
			beep_key(BTN_UP);
			func_index = table[func_index].up;    //���Ϸ�
			if(func_index==14||func_index==15)
			LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
			if(func_index==0)
			{
			sys.display++;
			if(sys.display>2)
			sys.display=1;
			}
		}
		if(sys_key_down.Key_short&&isEditableFunction(func_index))
		{
			Key_value_init();
			beep_key(BTN_DOWN);
			if(func_index==14||func_index==15)
			LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
			func_index = table[func_index].down;    //���·�
			if(func_index==0)
			{
			sys.display--;
			if(sys.display<1)
			sys.display=2;	
			}
		}
			if(func_index!=0)
			{
				display1_state=1;
				display2_state=1;
			}
		if(sys_key_set.Key_short&&(func_index!=12)&&(func_index!=13)&&(func_index!=27)&&(func_index!=28)&&(func_index!=29)&&(func_index!=30))
		{
			Key_value_init();
			beep_key(BTN_SET);
			func_index = table[func_index].enter;    //ȷ��
			LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
			
		}
		if(sys_key_set.Key_long&&(func_index==0)&&flag_Key_set_long)
		{
//			flag_Key_set_long=0;
//			Key_value_init();
//			beep_key(BTN_SET);
//			func_index = table[func_index].enter;    //����
//			LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
		}
		 if(KEY_SET)//�����ͷ�
		 {
			 flag_Key_set_long=1;		
			 sys_key_set.Key_long=0; 
		 }
		 if(sys_key_return.Key_short)
			{
				sys_key_return.Key_short=0;
				beep_key(BTN_SET);
				func_index = table[func_index].return_key;    //����
				if(func_index==0)
					sys_EEPROM_write();//
				LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
				display1_state=1;
				display2_state=1;
					
			}
			if ((func_index != last_index)&&(func_index>0))
			{
				current_operation_index = table[func_index].current_operation;
				if(0<func_index<9)
				LCD_Fill(0,0,16,80,BLACK);
				else
				LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
				(*current_operation_index)();//ִ�е�ǰ��������
				last_index = func_index;
			}
			if(func_index==0||!isEditableFunction(func_index))
			{
							current_operation_index = table[func_index].current_operation;
							(*current_operation_index)();//ִ�е�ǰ��������
							last_index = func_index;
			}
			
}
