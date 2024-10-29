#ifndef _Adjust_
#define _Adjust_
#include "config.h"
typedef struct
{
	uint16_t factor;//
	uint16_t adc_tare;
	uint32_t standard;//
	uint16_t adc_standard;
	uint8_t state;
}Adjust;//Intelligent voltmeter
extern Adjust adjustv;
extern Adjust adjusta;
void adjust_Init(void);
u16 adc_to_actual(u16 adc_Tare,u16 adc_standard,u16 Tare,u16 standard,u16 adc,float k_t,u16 k_adj  );//基数对应的adc,校准值对应的adc,基数,校准值,实时adc,温度补偿系数；计算出实际值,y=kx+b
u16 linear_function(u16 x1,u16 y1,u16 x2,u16 y2,u16 x,float k_t,u16 k_adj );//y=kx+b,k_t温度系数,k_adj校准系数
void adjust_menu();
void adjust_reset();
#endif
