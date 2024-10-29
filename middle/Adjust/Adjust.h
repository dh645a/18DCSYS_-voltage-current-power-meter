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
u16 adc_to_actual(u16 adc_Tare,u16 adc_standard,u16 Tare,u16 standard,u16 adc,float k_t,u16 k_adj  );//������Ӧ��adc,У׼ֵ��Ӧ��adc,����,У׼ֵ,ʵʱadc,�¶Ȳ���ϵ���������ʵ��ֵ,y=kx+b
u16 linear_function(u16 x1,u16 y1,u16 x2,u16 y2,u16 x,float k_t,u16 k_adj );//y=kx+b,k_t�¶�ϵ��,k_adjУ׼ϵ��
void adjust_menu();
void adjust_reset();
#endif
