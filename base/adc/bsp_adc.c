#include "bsp_adc.h"
#include "system.h"
/**
  * @brief  ADC GPIO 初始化
  * @param  无
  * @retval 无
  */
/**
  * @brief  ADC配置函数.
  * @param  无
  * @retval 无
  */
static void APP_AdcConfig(void)
{
    ADCTIM = 0x2A;		//设置 ADC 内部时序，ADC采样时间建议设最大值
    ADCCFG = 0x2f;		//设置 ADC 时钟为系统时钟/2/16/16  //采样速度 
    ADC_CONTR = 0x80; //使能 ADC 模块
}
/**
  * @brief  ADC校准函数.
  * @param  无
  * @retval 无
  */
void APP_AdcCalibrate(void)
{

}

/**
  * @brief  ADC使能函数
  * @param  无
  * @retval 无
  */
 void APP_AdcEnable(void)
{
}

/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void ADCx_Init(void)
{
	APP_AdcConfig();
	ADC_CONTR = (ADC_CONTR & 0xf0) | 7; //设置ADC转换通道 ADC7
	
}
u16 Get_ADC12bitResult_a()  //
{
	ADC_START = 1;//启动ADC转换
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
	    _nop_();
    _nop_();
    _nop_();
    _nop_();
    while(ADC_FLAG == 0);   //wait for ADC finish
    ADC_FLAG = 0;     //清除ADC结束标志
    return  (((u16)ADC_RES << 8) | ADC_RESL);
}
u16 Get_ADC12bitResult(u8 channel)  //channel = 0~15
{
    ADC_RES = 0;
    ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xf0) | channel; //设置ADC转换通道
	ADC_START = 1;//启动ADC转换
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    while(ADC_FLAG == 0);   //wait for ADC finish
    ADC_FLAG = 0;     //清除ADC结束标志
    return  (((u16)ADC_RES << 8) | ADC_RESL);
}
#define N 11
uint16_t filter()//中位值滤波
{
    uint16_t value_buf[N];
    uint16_t count, i, j, temp;
    for(count = 0; count < N; count ++) //获取采样值
    {
        value_buf[count] = Get_ADC12bitResult_a();
    }
    for(j = 0; j < (N-1); j++)
    {
        for(i = 0; i < (N-j); i++)
        {
            if(value_buf[i] > value_buf[i+1])
            {
                temp = value_buf[i];
                value_buf[i] = value_buf[i+1];
                value_buf[i+1] = temp;
            }
        }
    }
    return value_buf[(N-1)/2];
		//return value_buf[(N+5)/2];
}
uint16_t GetAdcAverage(uint16_t times)//取多次ADC平均值
{
   uint32_t temp_val = 0;
   uint16_t t;
   for(t = 0; t < times; t++) 
		{	
//				 ADC_START = 1;//启动ADC转换
//					_nop_();
//					_nop_();
//					_nop_();
//					_nop_();
//					while(ADC_FLAG == 0);   //wait for ADC finish
//					ADC_FLAG = 0;     //清除ADC结束标志
//					/* 获取ADC转换数据 */
//					temp_adc = ((u16)ADC_RES << 8) | ADC_RESL;
					temp_val+=filter();		
    }
		temp_val=(temp_val+90)/times;
//		sys.adc_data=temp_val / times;
//		sys.adc_state=1;
    return  temp_val;
		
}
uint16_t channel_GetAdcAverage(u8 channel,uint16_t times)//(通道,取多次ADC平均值)
{
//   uint32_t temp_val = 0;
//   uint16_t t,temp_adc;
//   ADC_RES = 0;
//   ADC_RESL = 0;

	 ADC_CONTR = (ADC_CONTR & 0xf0) | channel; //设置ADC转换通道
					_nop_();
					_nop_();
					_nop_();
					_nop_();
						_nop_();
					_nop_();
					_nop_();
					_nop_();
						_nop_();
					_nop_();
					_nop_();
					_nop_();
						_nop_();
					_nop_();
					_nop_();
					_nop_();
						_nop_();
					_nop_();
					_nop_();
					_nop_();
						_nop_();
					_nop_();
					_nop_();
					_nop_();
		return GetAdcAverage(times);
}
/*********************************************END OF FILE**********************/
