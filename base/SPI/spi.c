#include "spi.h"
#include "lcd_init.h"
/*************  ���س�������    **************/

#define HSCK_MCLK       0
#define HSCK_PLL        1
#define HSCK_SEL        HSCK_PLL

#define PLL_96M         0
#define PLL_144M        1
#define PLL_SEL         PLL_96M

#define CKMS            0x80
#define HSIOCK          0x40
#define MCK2SEL_MSK     0x0c
#define MCK2SEL_SEL1    0x00
#define MCK2SEL_PLL     0x04
#define MCK2SEL_PLLD2   0x08
#define MCK2SEL_IRC48   0x0c
#define MCKSEL_MSK      0x03
#define MCKSEL_HIRC     0x00
#define MCKSEL_XOSC     0x01
#define MCKSEL_X32K     0x02
#define MCKSEL_IRC32K   0x03

#define ENCKM           0x80
#define PCKI_MSK        0x60
#define PCKI_D1         0x00
#define PCKI_D2         0x20
#define PCKI_D4         0x40
#define PCKI_D8         0x60

void HAL_SPI_Init(void)
{
    SPCTL |=  (1 << 7); //���� SS ���Ź��ܣ�ʹ�� MSTR ȷ���������������Ǵӻ�
    SPCTL |=  (1 << 6); //ʹ�� SPI ����
    SPCTL &= ~(1 << 5); //�ȷ���/�������ݵĸ�λ�� MSB��
    SPCTL |=  (1 << 4); //��������ģʽ
    SPCTL &= ~(1 << 3); //SCLK ����ʱΪ�͵�ƽ��SCLK ��ǰʱ����Ϊ�����أ���ʱ����Ϊ�½���
    SPCTL &= ~(1 << 2); //���� SS �ܽ�Ϊ�͵�ƽ������һλ���ݲ��� SCLK �ĺ�ʱ���ظı�����
    SPCTL = (SPCTL & ~3) | 3;   //SPI ʱ��Ƶ��ѡ��, 0: 4T, 1: 8T,  2: 16T,  3: 2T
    HSSPI_CFG2|=0x20;//ʹ�ܸ���SPI
    P_SW1 = (P_SW1 & ~(3<<2)) | (0<<2);     //IO���л�. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 1: P2.2 P2.3 P2.4 P2.5, 2: P5.4 P4.0 P4.1 P4.3, 3: P3.5 P3.4 P3.3 P3.2
    OLED_SCLK = 0;    // set clock to low initial state
    OLED_SDIN = 1;
    SPIF = 1;   //��SPIF��־
    WCOL = 1;   //��WCOL��־
	
}
void SPI_init(void)//����spi
{
    //ѡ��PLL���ʱ��
#if (PLL_SEL == PLL_96M)
    CLKSEL &= ~CKMS;            //ѡ��PLL��96M��ΪPLL�����ʱ��
#elif (PLL_SEL == PLL_144M)
    CLKSEL |= CKMS;             //ѡ��PLL��144M��ΪPLL�����ʱ��
#else
    CLKSEL &= ~CKMS;            //Ĭ��ѡ��PLL��96M��ΪPLL�����ʱ��
#endif

    //ѡ��PLL����ʱ�ӷ�Ƶ,��֤����ʱ��Ϊ12M
    USBCLK &= ~PCKI_MSK;
#if (MAIN_Fosc == 12000000UL)
    USBCLK |= PCKI_D1;          //PLL����ʱ��1��Ƶ
#elif (MAIN_Fosc == 24000000UL)
    USBCLK |= PCKI_D2;          //PLL����ʱ��2��Ƶ
#elif (MAIN_Fosc == 48000000UL)
    USBCLK |= PCKI_D4;          //PLL����ʱ��4��Ƶ
#elif (MAIN_Fosc == 96000000UL)
    USBCLK |= PCKI_D8;          //PLL����ʱ��8��Ƶ
#else
    USBCLK |= PCKI_D1;          //Ĭ��PLL����ʱ��1��Ƶ
#endif

    //����PLL
    USBCLK |= ENCKM;            //ʹ��PLL��Ƶ
    delay_ms(1);                //�ȴ�PLL��Ƶ

    //ѡ��HSPWM/HSSPIʱ��
#if (HSCK_SEL == HSCK_MCLK)
    CLKSEL &= ~HSIOCK;          //HSPWM/HSSPIѡ����ʱ��Ϊʱ��Դ
#elif (HSCK_SEL == HSCK_PLL)
    CLKSEL |= HSIOCK;           //HSPWM/HSSPIѡ��PLL���ʱ��Ϊʱ��Դ
#else
    CLKSEL &= ~HSIOCK;          //Ĭ��HSPWM/HSSPIѡ����ʱ��Ϊʱ��Դ
#endif

    HSCLKDIV = 1;               //HSPWM/HSSPIʱ��Դ4��Ƶ

//    SSIG = 1; //���� SS ���Ź��ܣ�ʹ�� MSTR ȷ���������������Ǵӻ�
//    SPEN = 1; //ʹ�� SPI ����
//    DORD = 0; //�ȷ���/�������ݵĸ�λ�� MSB��
//    MSTR = 1; //��������ģʽ
//    CPOL = 1; //SCLK ����ʱΪ�ߵ�ƽ��SCLK ��ǰʱ����Ϊ�½��أ���ʱ����Ϊ������
//    CPHA = 1; //������ SCLK ǰʱ������������ʱ���ز���
    SPCTL |=  (1 << 7); //���� SS ���Ź��ܣ�ʹ�� MSTR ȷ���������������Ǵӻ�
    SPCTL |=  (1 << 6); //ʹ�� SPI ����
    SPCTL &= ~(1 << 5); //�ȷ���/�������ݵĸ�λ�� MSB��
    SPCTL |=  (1 << 4); //��������ģʽ
    SPCTL &= ~(1 << 3); //SCLK ����ʱΪ�͵�ƽ��SCLK ��ǰʱ����Ϊ�����أ���ʱ����Ϊ�½���
    SPCTL &= ~(1 << 2); //���� SS �ܽ�Ϊ�͵�ƽ������һλ���ݲ��� SCLK �ĺ�ʱ���ظı�����
    SPCTL = (SPCTL & ~3) | 2;   //SPI ʱ��Ƶ��ѡ��, 0: 4T, 1: 8T,  2: 16T,  3: 2T
    //P_SW1 = (P_SW1 & ~(3<<2)) | (1<<2);     //IO���л�. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 1: P2.2 P2.3 P2.4 P2.5, 2: P5.4 P4.0 P4.1 P4.3, 3: P3.5 P3.4 P3.3 P3.2
		P_SW1 = (P_SW1 & ~(3<<2)) | (0<<2);     //IO���л�. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 1: P2.2 P2.3 P2.4 P2.5, 2: P5.4 P4.0 P4.1 P4.3, 3: P3.5 P3.4 P3.3 P3.2
//    P_PM25LV040_SCK = 0;    // set clock to low initial state
//    P_PM25LV040_SI = 1;
    SPIF = 1;   //��SPIF��־
    WCOL = 1;   //��WCOL��־

    HSSPI_CFG2 |= 0x20;         //ʹ��SPI����ģʽ
}