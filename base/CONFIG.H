/*********************************************************************************
 * COPYRIGHT NOTICE
 * All rights reserved.
 *
 * 文件名		:	config.h
 * 描述 		:	系统配置
 *
 * 版本			:	V1.0
 * 作者			:	浩
 * 日期			:	2023-12-22
 * 
**********************************************************************************/
#include    "stc32g.h"
#ifndef		__CONFIG_H
#define		__CONFIG_H
typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;
typedef     unsigned char   uint8_t;
typedef     unsigned int    uint16_t;
typedef     unsigned long   uint32_t;
#define NULL 0

/************************定义系统时钟*****************************/
//#define MAIN_Fosc		22118400L	//定义主时钟
//#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟
#define MAIN_Fosc        30000000UL
#define EE_ADDRESS  0x000000  //保存的EEPROM起始地址
#define DC40V
#define DC4A
//#define DC400V
//==========================================================================

#define Timer0_Reload   (MAIN_Fosc / 1000)      //Timer 0 中断频率, 1000次/秒
#define Timer1_Reload   (MAIN_Fosc / 2000)      //Timer 1 中断频率, 2000次/秒
#define Timer2_Reload   (MAIN_Fosc / 3000)      //Timer 2 中断频率, 3000次/秒
#define Timer3_Reload   (MAIN_Fosc / 4000)      //Timer 3 中断频率, 4000次/秒
#define Timer4_Reload   (MAIN_Fosc / 5000)      //Timer 4 中断频率, 5000次/秒
/****************************用户可调设置****************************/

/****************************IO设置****************************/
/* 定义LED数码管连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
/* 定义液晶GPIO端口 */
sbit LCD_BLK=P3^3; //BLK

/*  OLED Pin */
sbit OLED_SCLK = P1 ^ 5; //时钟（D0/SCLK）
sbit OLED_SDIN = P1 ^ 3; //数据（D1/MOSI）
sbit OLED_RST = P1 ^ 4;  //复位（RES）
sbit OLED_DC = P1 ^ 6;   //数据/命令控制（DC）
sbit OLED_CS = P1 ^ 2;   //片选（CS）
//以下是4个按键
sbit KEY_SET=P3^2;//
sbit KEY_RETURN=P3^5;//
sbit KEY_UP=P3^6;//
sbit KEY_DOWN =P3^7;//
typedef enum
{
	BTN_UP = 0,
	BTN_DOWN = 1,
	BTN_SET = 2,
	BTN_RETURN = 3,
	BTN_COUNT = 4 // must be last
} btn_t;
//蜂鸣器


//PWM

//ADC设置


/***************************包含库函数***************************/

/***************************包含用户函数***************************/


#endif
