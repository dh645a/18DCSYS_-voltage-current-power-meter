/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  Alexander
  * @version V1.0
  * @date    2022-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:HK32F030M������ 
  * ��̳    :https://bbs.21ic.com/iclist-1010-1.html
  *
  ******************************************************************************
  */ 
  
#include "base_key.h"
/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
Key_Typedef sys_key_up;
Key_Typedef sys_key_down;
Key_Typedef sys_key_set;
Key_Typedef sys_key_return;
void Key_GPIO_Config(void)
{
	 /* ��ʼ������BUTTON */

}
void Key_value_init(void)
{
	 /* ��ʼ������BUTTON */
      sys_key_up.Key_short = 0;
			sys_key_down.Key_short = 0;
			sys_key_set.Key_short = 0;
			sys_key_return.Key_short = 0;
      sys_key_up.Key_long = 0;
			sys_key_down.Key_long = 0;
			sys_key_set.Key_long = 0;
			sys_key_return.Key_long = 0;
}
 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
/*********************************************END OF FILE**********************/
void key_scan(uint32_t key,Key_Typedef *sys_key)//����ɨ��
{
		if(sys_key->Key_temp)//����Ѿ�������  
		{
			if(key == KEY_ON)//����ڶ��μ����Ч��
			{
				sys_key->Key_temp ++;
				if(sys_key->Key_temp > One)
				sys_key->Key_long = 1;
			}
			else //һ����⵽�����ˣ�Ҫô�ǵ�����һ�Ρ�Ҫô�ǳ��������������ˣ�Ҳ���ǲ�ϣ�����������Ĺ�����
			{
				sys_key->Key_state=1;//���ֱ�־
				if(sys_key->Key_temp <= One)
				{
					sys_key->Key_long = 0;
					sys_key->Key_short = 1;
				}
				sys_key->Key_temp = 0;
			}
		}
		else
		{
			if(key == KEY_ON)//��һ�μ�⵽��������
				sys_key->Key_temp++ ;//�Ѱ���״̬�͵���ʱ��������
			else
			{
				sys_key->Key_long = 0;
				sys_key->Key_temp =0;
			}
		}
}
void key(uint8_t period)//����ɨ��   periodɨ������
{
		static uint8_t i=0;
		i++;
		if(i==period)
		{
			i=0;	
			key_scan(KEY_SET,&sys_key_set);//����ɨ��
			key_scan(KEY_RETURN,&sys_key_return);//����ɨ��
			key_scan(KEY_UP,&sys_key_up);//����ɨ��
			key_scan(KEY_DOWN,&sys_key_down);//����ɨ��

		}
}