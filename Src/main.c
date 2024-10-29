/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/


/*************  功能说明    **************

本例程基于STC32G为主控芯片

使用Keil C251编译器，Memory Model推荐设置XSmall模式，默认定义变量在edata，单时钟存取访问速度快。

edata建议保留1K给堆栈使用，空间不够时可将大数组、不常用变量加xdata关键字定义到xdata空间。

下载时, 选择时钟 30MHz (用户可自行修改频率).

******************************************/

#include "stc32g.h"       //包含此头文件后，不需要再包含"reg51.h"头文件
#include "intrins.h"
#include "lcd_init.h"
#include "lcd.h"
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
#include "STC32G_EEPROM.h"
/*************	Pin define	*****************************************************/
uint32_t T0_Count=0,temp_t0_count=0;
unsigned int Task_Delay[NumOfTask]={ 0 };  
uint32_t temp_adc;
uint16_t adc;
uint16_t temp_adcv,temp_adca;
void main(void)
{
    WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度
    
    P1M1 = 0x83;   P1M0 = 0x00;   //P1.7P1.1P1.0 为 ADC 高阻输入，其余设置为准双向口
		P1SR|=0x7C;//端口速率
    P3M1 = 0x00;   P3M0 = 0x18;   //设置P3.4、P3.3为推挽,其余为准双向口
		P3PU=0xE4;//按键上拉
		//P3SR|=0xe0;//端口速率
		ADCx_Init();
		HAL_SPI_Init();
	  //SPI_init();
		LCD_Init();//LCD初始化
	  LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
		sys_control_Init();
		Timer0_init();
		Init_buzzer();
		//pwm_init_blk();
	  EA = 1;     //打开总中断
		//beep(12000,6000,100,1);
		sys_EEPROM_read();//读取EEPROM数据
		delay_ms(5000);
		adjust_reset();

		adjust_Init();//注意带1分钟死循环
    while(1)
    {
//						LCD_ShowChinese(40,0,"中景园电子",RED,BLACK,16,0);
					  //LCD_ShowFloatNum1(10,60,temp_adc,5,GREEN,BLACK,16);
						//LCD_ShowIntNum(80,60,adjust_adj_a(),4,GREEN,BLACK,16);
						//LCD_ShowPicture(100,20,40,40,gImage_1);
						if (Task_Delay[0] == 0)
						{
							/* 任务 0 主体Task(0); */
							/* 任务 0 延时 1ms */
							//if(sys.adc_state==0)

							Task_Delay[0] = 10;
						}

						if (Task_Delay[1] == 0)
						{
							/* 任务 1 主体Task(1); */
							/* 任务 1 延时 50ms */

							menu_update();
							beep_update();													
							Task_Delay[1] = 20;
						}
						if (Task_Delay[2] == 0)
						{
							/* 任务 1 主体Task(1); */
								/*翻转LED*/
							//LL_GPIO_TogglePin(LED1_GPIO_PORT,LED1_GPIO_PIN);
							/* 任务 1 延时 50ms */
							temp_adcv=channel_GetAdcAverage(7,100);
							temp_adca=channel_GetAdcAverage(0,100);
						
//							if(temp_GetAdcAverage>3600)//分段处理误差
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor);//电压v
//							else if(temp_GetAdcAverage>3100)
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+7);//电压v	
//							else if(temp_GetAdcAverage>2100)
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+10);//电压v	
//							else if(temp_GetAdcAverage>1100)
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+15);//电压v
//							else
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+25);//电压v	
							sys.voltage=linear_function(0,0,adjustv.adc_standard,4000,temp_adcv,1.0,adjustv.factor);
							sys.current=linear_function(adjusta.adc_tare,0,adjusta.adc_standard,4000,temp_adca,1.0,adjusta.factor);
							Task_Delay[2] = 200;
						}


    }
}
/**
  * @brief  TIM更新中断回调函数
  * @param  无
  * @retval 无
  */
void APP_UpdateCallback(void)//
{
  T0_Count++;
  key(50);//按键扫描   period扫描周期
}


