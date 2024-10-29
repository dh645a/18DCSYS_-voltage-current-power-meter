#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "config.h"

//  ���Ŷ���
typedef struct
{
		unsigned char Key_short;
    unsigned char Key_temp;
    unsigned char Key_long;
    unsigned char Key_state;
} Key_Typedef;

#define  N_ms  12  // (N_ms+1)*4 ms ����һ��
#define	 One   30   //���嵥��һ����Ҫ�ļ��������������������������
extern Key_Typedef sys_key_up;
extern Key_Typedef sys_key_down;
extern Key_Typedef sys_key_set;
extern Key_Typedef sys_key_return;

 /** �������±��ú�
	*  ��������Ϊ�͵�ƽ������ KEY_ON=0�� KEY_OFF=1
	*  ����������Ϊ�ߵ�ƽ���Ѻ����ó�KEY_ON=1 ��KEY_OFF=0 ����
	*/
#define KEY_ON	0
#define KEY_OFF	1

void Key_GPIO_Config(void);
void Key_value_init(void);
//uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
//void key_scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,Key_Typedef *sys_key);//����ɨ��
void key_scan(uint32_t key,Key_Typedef *sys_key);//����ɨ��
void key(uint8_t period);//����ɨ��
#endif /* __BSP_KEY_H */




















