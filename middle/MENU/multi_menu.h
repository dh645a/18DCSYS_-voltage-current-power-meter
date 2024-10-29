#ifndef __MULTI_MENU_H
#define __MULTI_MENU_H	 
		
#define uchar unsigned char

typedef struct
{
	uchar current;
	uchar up;//向上翻索引号
	uchar down;//向下翻索引号
	uchar enter;//确认索引号
	uchar return_key;//确认索引号
	void (*current_operation)();
} key_table;

extern key_table table[32];

	
extern void fun_menu_main(); 

extern void fun_menu_alarm(); 

extern void fun_menu_font(); 

extern void fun_menu_adjust();   

extern void fun_language(); 

extern void fun_fong_style(); 
extern void fun_font_color_v();  
extern void fun_font_color_a();
extern void fun_alarm_H();  
extern void fun_alarm_L();
extern void fun_alarm_In(); 
extern void fun_alarm_Out(); 

extern void fun_b31(); 
extern void fun_b32();  
extern void fun_b33(); 
extern void fun_b3();

extern void fun_c31(); 
extern void fun_c32();  
extern void fun_c33(); 
  
extern void fun_0();
extern void fun_100();
extern void fun_101();
void menu_update(void);
#endif
