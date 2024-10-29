#include "adjust.h"
#include "base_key.h"
#include "lcd.h"
#include "bsp_adc.h"
#include "base_key.h"
#include "STC32G_EEPROM.h"
#include "config.h"
#include "system.h"
#include "main.h"
#include "lcd.h"
#include "lcd_init.h"
Adjust adjustv;
Adjust adjusta;
void adjust_Init(void)
{
	//adjustv.adc_tare=0;
//	adjustv.standard=40000000;
//	//adjusta.adc_tare=0;
//	adjusta.standard=40000000;
	while(adjustv.state)
	{
		adjust_menu();
	}
	
}
u16 linear_function(u16 x1,u16 y1,u16 x2,u16 y2,u16 x,float k_t,u16 k_adj )//y=kx+b,k_t温度系数,k_adj校准系数
{
	float k=0.0000,b=0.0000,dat=0.0000;//y=kx+b
  k = (y2 -  y1)*1.000/(x2-x1);//求出斜率k
	b=y1-(x1*k);//求出b
	dat = (x*k+b)*k_adj/10000/k_t;//
	if(dat<0)
	dat = 0;
	return (unsigned int)dat;  
}
void adjust_menu()
{
		static u8 keyset_sum=0;
		LCD_ShowString(40,0,"adjust",RED,BLACK,16,0);
		LCD_ShowString(0,16,"give the voltage",RED,BLACK,16,0);
		#ifdef DC40V
		LCD_ShowString(0,32,"as 40.00v ",RED,BLACK,16,0);
		#endif
		#ifdef DC40V0
		LCD_ShowString(0,32,"as 400.0v ",RED,BLACK,16,0);
		#endif
		LCD_ShowString(0,48,"then press SET",RED,BLACK,16,0);
		//LCD_ShowChinese(130,50,"铃",RED,BLACK,24,0);
		if(sys_key_set.Key_short||sys_key_return.Key_short)//检测到键短按
    {
			Key_value_init();
			//beep_key(BTN_SET);
			keyset_sum++;
      switch(keyset_sum)
      {
				case 1:  // 第一次短按
							LCD_ShowString(152,0,"-",RED,BLACK,16,0);
							adjustv.adc_tare=channel_GetAdcAverage(7,100);
							adjusta.adc_tare=channel_GetAdcAverage(0,100);//取多次ADC平均值;
							break;
				case 2: // 第二次短按
							adjustv.adc_standard=channel_GetAdcAverage(7,100);//取多次ADC平均值;
							adjusta.adc_standard=channel_GetAdcAverage(0,100);//取多次ADC平均值;
							adjustv.state=0;
							EEPROM_read_n(EE_ADDRESS,EE_Data,30);
							EE_Data[0] = (u8)(adjustv.adc_standard >> 8);
							EE_Data[1] = (u8)adjustv.adc_standard;
							EE_Data[2] =	adjustv.state;
							EE_Data[20] = (u8)(adjusta.adc_tare >> 8);
							EE_Data[21] = (u8)adjusta.adc_tare;
							EE_Data[22] = (u8)(adjusta.adc_standard >> 8);
							EE_Data[23] = (u8)adjusta.adc_standard;	
							EE_Data[28] = (u8)(adjustv.adc_tare >> 8);
							EE_Data[29] = (u8)adjustv.adc_tare;		
							sys_EEPROM_datainit();
							EEPROM_SectorErase(EE_ADDRESS); //擦除扇区
							EEPROM_write_n(EE_ADDRESS,EE_Data,30);//保存
							keyset_sum=0;
				      LCD_ShowString(152,0," ",RED,BLACK,16,0);
							break;
				default :   break;         //  当所有选择皆不成立，则进入预设区块。
      }
    }
		if(T0_Count>60000)
	  adjustv.state=0;	
		if(adjustv.state==0)
		LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
}
void adjust_reset()
{
		if(sys_key_set.Key_short||sys_key_set.Key_long)//检测到键短按
    {
			Key_value_init();
			//beep_key(BTN_SET);
      adjustv.state=1;
    }
}