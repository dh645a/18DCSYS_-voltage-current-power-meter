#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "config.h"

#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 80
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 80
#endif


//-----------------LCD�˿ڶ���----------------

//#define LCD_SCLK_Clr() LCD_SCL=0//SCL=SCLK
//#define LCD_SCLK_Set() LCD_SCL=1

//#define LCD_MOSI_Clr() LCD_SDA=0//SDA=MOSI
//#define LCD_MOSI_Set() LCD_SDA=1

//#define LCD_RES_Clr() LCD_RES=0//RES
//#define LCD_RES_Set() LCD_RES=1

//#define LCD_DC_Clr() LCD_DC=0//DC
//#define LCD_DC_Set() LCD_DC=1

//#define LCD_CS_Clr()  LCD_CS=0//CS
//#define LCD_CS_Set()  LCD_CS=1

#define LCD_BLK_Clr()  LCD_BLK=0//BLK
#define LCD_BLK_Set()  LCD_BLK=1

/*  OLED Command */
#define OLED_CS_Clr() OLED_CS = 0
#define OLED_CS_Set() OLED_CS = 1

#define OLED_RST_Clr() OLED_RST = 0
#define OLED_RST_Set() OLED_RST = 1

#define OLED_DC_Clr() OLED_DC = 0
#define OLED_DC_Set() OLED_DC = 1

#define OLED_SCLK_Clr() OLED_SCLK = 0
#define OLED_SCLK_Set() OLED_SCLK = 1

#define OLED_SDIN_Clr() OLED_SDIN = 0
#define OLED_SDIN_Set() OLED_SDIN = 1

void delay_ms(unsigned int ms);//��׼ȷ��ʱ����
void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif



