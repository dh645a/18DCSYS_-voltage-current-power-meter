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
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/


/*************  ����˵��    **************

�����̻���STC32GΪ����оƬ��ʵ����9.6�汾���б�д���ԡ�

ʹ��Keil C251��������Memory Model�Ƽ�����XSmallģʽ��Ĭ�϶��������edata����ʱ�Ӵ�ȡ�����ٶȿ졣

edata���鱣��1K����ջʹ�ã��ռ䲻��ʱ�ɽ������顢�����ñ�����xdata�ؼ��ֶ��嵽xdata�ռ䡣

����LCD1602�ַ���.

��ʾЧ��Ϊ: LCD��ʾʱ��.

��һ����ʾ ---Clock demo---
�ڶ�����ʾ     12-00-00


R179����0ŷ���裬��16PIN�̽ӵ�GND.

����ʱ, ѡ��ʱ�� 24MHz (�û��������޸�Ƶ��).

******************************************/

#include "stc32g.h"       //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
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
    WTST = 0;  //���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
    EAXFR = 1; //��չ�Ĵ���(XFR)����ʹ��
    CKCON = 0; //��߷���XRAM�ٶ�
    
    P1M1 = 0x83;   P1M0 = 0x00;   //P1.7P1.1P1.0 Ϊ ADC �������룬��������Ϊ׼˫���
		P1SR|=0x7C;//�˿�����
    P3M1 = 0x00;   P3M0 = 0x18;   //����P3.4��P3.3Ϊ����,����Ϊ׼˫���
		P3PU=0xE4;//��������
		//P3SR|=0xe0;//�˿�����
		ADCx_Init();
		HAL_SPI_Init();
	  //SPI_init();
		LCD_Init();//LCD��ʼ��
	  LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
		sys_control_Init();
		Timer0_init();
		Init_buzzer();
		//pwm_init_blk();
	  EA = 1;     //�����ж�
		//beep(12000,6000,100,1);
		sys_EEPROM_read();//��ȡEEPROM����
		delay_ms(5000);
		adjust_reset();

		adjust_Init();//ע���1������ѭ��
    while(1)
    {
//						LCD_ShowChinese(40,0,"�о�԰����",RED,BLACK,16,0);
					  //LCD_ShowFloatNum1(10,60,temp_adc,5,GREEN,BLACK,16);
						//LCD_ShowIntNum(80,60,adjust_adj_a(),4,GREEN,BLACK,16);
						//LCD_ShowPicture(100,20,40,40,gImage_1);
						if (Task_Delay[0] == 0)
						{
							/* ���� 0 ����Task(0); */
							/* ���� 0 ��ʱ 1ms */
							//if(sys.adc_state==0)

							Task_Delay[0] = 10;
						}

						if (Task_Delay[1] == 0)
						{
							/* ���� 1 ����Task(1); */
							/* ���� 1 ��ʱ 50ms */

							menu_update();
							beep_update();													
							Task_Delay[1] = 20;
						}
						if (Task_Delay[2] == 0)
						{
							/* ���� 1 ����Task(1); */
								/*��תLED*/
							//LL_GPIO_TogglePin(LED1_GPIO_PORT,LED1_GPIO_PIN);
							/* ���� 1 ��ʱ 50ms */
							temp_adcv=channel_GetAdcAverage(7,100);
							temp_adca=channel_GetAdcAverage(0,100);
						
//							if(temp_GetAdcAverage>3600)//�ֶδ������
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor);//��ѹv
//							else if(temp_GetAdcAverage>3100)
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+7);//��ѹv	
//							else if(temp_GetAdcAverage>2100)
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+10);//��ѹv	
//							else if(temp_GetAdcAverage>1100)
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+15);//��ѹv
//							else
//							sys.voltage=adc_to_actual(0,adjust.adc_standard,0,4000,temp_GetAdcAverage,1.0,adjust.factor+25);//��ѹv	
							sys.voltage=linear_function(0,0,adjustv.adc_standard,4000,temp_adcv,1.0,adjustv.factor);
							sys.current=linear_function(adjusta.adc_tare,0,adjusta.adc_standard,4000,temp_adca,1.0,adjusta.factor);
							Task_Delay[2] = 200;
						}


    }
}
/**
  * @brief  TIM�����жϻص�����
  * @param  ��
  * @retval ��
  */
void APP_UpdateCallback(void)//
{
  T0_Count++;
  key(50);//����ɨ��   periodɨ������
}


