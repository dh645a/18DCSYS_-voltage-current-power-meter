#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "config.h"

//  引脚定义
typedef struct
{
		unsigned char Key_short;
    unsigned char Key_temp;
    unsigned char Key_long;
    unsigned char Key_state;
} Key_Typedef;

#define  N_ms  12  // (N_ms+1)*4 ms 处理一次
#define	 One   30   //定义单击一次需要的计数，大于这个计数的算作长按
extern Key_Typedef sys_key_up;
extern Key_Typedef sys_key_down;
extern Key_Typedef sys_key_set;
extern Key_Typedef sys_key_return;

 /** 按键按下标置宏
	*  按键按下为低电平，设置 KEY_ON=0， KEY_OFF=1
	*  若按键按下为高电平，把宏设置成KEY_ON=1 ，KEY_OFF=0 即可
	*/
#define KEY_ON	0
#define KEY_OFF	1

void Key_GPIO_Config(void);
void Key_value_init(void);
//uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
//void key_scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,Key_Typedef *sys_key);//按键扫描
void key_scan(uint32_t key,Key_Typedef *sys_key);//按键扫描
void key(uint8_t period);//按键扫描
#endif /* __BSP_KEY_H */




















