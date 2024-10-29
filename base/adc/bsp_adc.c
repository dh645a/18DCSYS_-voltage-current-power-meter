#include "bsp_adc.h"
#include "system.h"
/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */
/**
  * @brief  ADC���ú���.
  * @param  ��
  * @retval ��
  */
static void APP_AdcConfig(void)
{
    ADCTIM = 0x2A;		//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
    ADCCFG = 0x2f;		//���� ADC ʱ��Ϊϵͳʱ��/2/16/16  //�����ٶ� 
    ADC_CONTR = 0x80; //ʹ�� ADC ģ��
}
/**
  * @brief  ADCУ׼����.
  * @param  ��
  * @retval ��
  */
void APP_AdcCalibrate(void)
{

}

/**
  * @brief  ADCʹ�ܺ���
  * @param  ��
  * @retval ��
  */
 void APP_AdcEnable(void)
{
}

/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADCx_Init(void)
{
	APP_AdcConfig();
	ADC_CONTR = (ADC_CONTR & 0xf0) | 7; //����ADCת��ͨ�� ADC7
	
}
u16 Get_ADC12bitResult_a()  //
{
	ADC_START = 1;//����ADCת��
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
    ADC_FLAG = 0;     //���ADC������־
    return  (((u16)ADC_RES << 8) | ADC_RESL);
}
u16 Get_ADC12bitResult(u8 channel)  //channel = 0~15
{
    ADC_RES = 0;
    ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xf0) | channel; //����ADCת��ͨ��
	ADC_START = 1;//����ADCת��
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    while(ADC_FLAG == 0);   //wait for ADC finish
    ADC_FLAG = 0;     //���ADC������־
    return  (((u16)ADC_RES << 8) | ADC_RESL);
}
#define N 11
uint16_t filter()//��λֵ�˲�
{
    uint16_t value_buf[N];
    uint16_t count, i, j, temp;
    for(count = 0; count < N; count ++) //��ȡ����ֵ
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
uint16_t GetAdcAverage(uint16_t times)//ȡ���ADCƽ��ֵ
{
   uint32_t temp_val = 0;
   uint16_t t;
   for(t = 0; t < times; t++) 
		{	
//				 ADC_START = 1;//����ADCת��
//					_nop_();
//					_nop_();
//					_nop_();
//					_nop_();
//					while(ADC_FLAG == 0);   //wait for ADC finish
//					ADC_FLAG = 0;     //���ADC������־
//					/* ��ȡADCת������ */
//					temp_adc = ((u16)ADC_RES << 8) | ADC_RESL;
					temp_val+=filter();		
    }
		temp_val=(temp_val+90)/times;
//		sys.adc_data=temp_val / times;
//		sys.adc_state=1;
    return  temp_val;
		
}
uint16_t channel_GetAdcAverage(u8 channel,uint16_t times)//(ͨ��,ȡ���ADCƽ��ֵ)
{
//   uint32_t temp_val = 0;
//   uint16_t t,temp_adc;
//   ADC_RES = 0;
//   ADC_RESL = 0;

	 ADC_CONTR = (ADC_CONTR & 0xf0) | channel; //����ADCת��ͨ��
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
