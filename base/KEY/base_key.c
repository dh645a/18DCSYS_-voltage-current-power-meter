/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  Alexander
  * @version V1.0
  * @date    2022-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:HK32F030M开发板 
  * 论坛    :https://bbs.21ic.com/iclist-1010-1.html
  *
  ******************************************************************************
  */ 
  
#include "base_key.h"
/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
Key_Typedef sys_key_up;
Key_Typedef sys_key_down;
Key_Typedef sys_key_set;
Key_Typedef sys_key_return;
void Key_GPIO_Config(void)
{
	 /* 初始化按键BUTTON */

}
void Key_value_init(void)
{
	 /* 初始化按键BUTTON */
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
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
/*********************************************END OF FILE**********************/
void key_scan(uint32_t key,Key_Typedef *sys_key)//按键扫描
{
		if(sys_key->Key_temp)//如果已经按下了  
		{
			if(key == KEY_ON)//如果第二次检测有效。
			{
				sys_key->Key_temp ++;
				if(sys_key->Key_temp > One)
				sys_key->Key_long = 1;
			}
			else //一旦检测到松手了，要么是单击了一次。要么是长按过后想松手了，也就是不希望发生长按的功能了
			{
				sys_key->Key_state=1;//松手标志
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
			if(key == KEY_ON)//第一次检测到按键按下
				sys_key->Key_temp++ ;//把按键状态送到临时变量里面
			else
			{
				sys_key->Key_long = 0;
				sys_key->Key_temp =0;
			}
		}
}
void key(uint8_t period)//按键扫描   period扫描周期
{
		static uint8_t i=0;
		i++;
		if(i==period)
		{
			i=0;	
			key_scan(KEY_SET,&sys_key_set);//按键扫描
			key_scan(KEY_RETURN,&sys_key_return);//按键扫描
			key_scan(KEY_UP,&sys_key_up);//按键扫描
			key_scan(KEY_DOWN,&sys_key_down);//按键扫描

		}
}