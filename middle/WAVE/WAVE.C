#include "wave.h"
#include "lcd.h"
#include "system.h"
u16 xdata wavebuf_1[40]={0};
void wave(int wavedata_1,bit direction)//波形数据获取处理,画波形 direction波形移动方向
{
	static u8 i=0;
	u8 Xtime;	
	//Lcd_cls();	
	//OLED_Clear_wave();
	//if(T0_Count%600<300)
	//LCD_Fill(9,0,79,62,BLACK);	
//	switch(i)
//	{
//		case 0:LCD_Fill(0,0,160,20,BLACK);i=1;break;
//		case 1:LCD_Fill(0,20,160,40,BLACK);i=2;break;
//		case 2:LCD_Fill(0,40,160,60,BLACK);i=3;break;
//		case 3:LCD_Fill(0,60,160,80,BLACK);i=0;break;

//	}
//	if(sys.adc_state)
//	{
		//LCD_DrawLine( 8, 64-1, 128-8-1, 64-1,RED) ;//下x轴
		//LCD_DrawLine( 8, 0, 8, 64-1,RED) ;//y轴
		//LCD_Draw_densityLine( 0, 64-8-1, 128-8-1, 64-8-1,1,2) ;//上x轴
		
				for (Xtime = 5; Xtime < 155; Xtime++)	
				{
					LCD_DrawLine( Xtime-1, (63-wavebuf_1[Xtime/5-1]/70), Xtime+5, (63-wavebuf_1[Xtime/5]/70),BLACK) ;
					//LCD_DrawLine( Xtime-1, (63-wavebuf_2[Xtime-1]/10), Xtime, (63-wavebuf_2[Xtime]/10),1) ;
				}	
				LCD_ShowFloatNum(2,65,wavedata_1,4,1,sys.v_font_color,BLACK,12); //电压
				if(direction)
				{
					for (Xtime = 1; Xtime < 40; Xtime++)
					{
						wavebuf_1[Xtime - 1] = wavebuf_1[Xtime];        //电压数组左移,前一项覆盖后一项 
					}		
					wavebuf_1[39]=wavedata_1;//电压
					
					for (Xtime = 5; Xtime < 155; Xtime++)	
					{
						LCD_DrawLine( Xtime-1, (63-wavebuf_1[Xtime/5-1]/70), Xtime+5, (63-wavebuf_1[Xtime/5]/70),RED) ;
						//LCD_DrawLine( Xtime-1, (63-wavebuf_2[Xtime-1]/10), Xtime, (63-wavebuf_2[Xtime]/10),1) ;
					}
				}
				else
				{
					for (Xtime = 119; Xtime > 9; Xtime--)
					{
						wavebuf_1[Xtime] = wavebuf_1[Xtime-1];        //数组右移,前一项覆盖后一项
					}		
					wavebuf_1[9]=wavedata_1;//电压
					for (Xtime = 9; Xtime < 119; Xtime++)	
					{
						LCD_DrawLine( Xtime, wavebuf_1[Xtime]/6, Xtime+1,wavebuf_1[Xtime+1]/6,RED) ;
					}	
				}
//				sys.adc_state=0;
//		}
	//OLED_Refresh_Gram_wave(0,0,160,80);
}
