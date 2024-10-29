#ifndef __BSP_ADC_H
#define	__BSP_ADC_H
#include "config.h"


void ADCx_Init(void);
u16 Get_ADC12bitResult(u8 channel);  //channel = 0~15
uint16_t GetAdcAverage(uint16_t times);//取多次ADC平均值
uint16_t channel_GetAdcAverage(u8 channel,uint16_t times);//(通道,取多次ADC平均值)
#endif /* __ADC_H */
