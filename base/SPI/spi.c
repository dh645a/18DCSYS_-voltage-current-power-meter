#include "spi.h"
#include "lcd_init.h"
/*************  本地常量声明    **************/

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
    SPCTL |=  (1 << 7); //忽略 SS 引脚功能，使用 MSTR 确定器件是主机还是从机
    SPCTL |=  (1 << 6); //使能 SPI 功能
    SPCTL &= ~(1 << 5); //先发送/接收数据的高位（ MSB）
    SPCTL |=  (1 << 4); //设置主机模式
    SPCTL &= ~(1 << 3); //SCLK 空闲时为低电平，SCLK 的前时钟沿为上升沿，后时钟沿为下降沿
    SPCTL &= ~(1 << 2); //数据 SS 管脚为低电平驱动第一位数据并在 SCLK 的后时钟沿改变数据
    SPCTL = (SPCTL & ~3) | 3;   //SPI 时钟频率选择, 0: 4T, 1: 8T,  2: 16T,  3: 2T
    HSSPI_CFG2|=0x20;//使能高速SPI
    P_SW1 = (P_SW1 & ~(3<<2)) | (0<<2);     //IO口切换. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 1: P2.2 P2.3 P2.4 P2.5, 2: P5.4 P4.0 P4.1 P4.3, 3: P3.5 P3.4 P3.3 P3.2
    OLED_SCLK = 0;    // set clock to low initial state
    OLED_SDIN = 1;
    SPIF = 1;   //清SPIF标志
    WCOL = 1;   //清WCOL标志
	
}
void SPI_init(void)//高速spi
{
    //选择PLL输出时钟
#if (PLL_SEL == PLL_96M)
    CLKSEL &= ~CKMS;            //选择PLL的96M作为PLL的输出时钟
#elif (PLL_SEL == PLL_144M)
    CLKSEL |= CKMS;             //选择PLL的144M作为PLL的输出时钟
#else
    CLKSEL &= ~CKMS;            //默认选择PLL的96M作为PLL的输出时钟
#endif

    //选择PLL输入时钟分频,保证输入时钟为12M
    USBCLK &= ~PCKI_MSK;
#if (MAIN_Fosc == 12000000UL)
    USBCLK |= PCKI_D1;          //PLL输入时钟1分频
#elif (MAIN_Fosc == 24000000UL)
    USBCLK |= PCKI_D2;          //PLL输入时钟2分频
#elif (MAIN_Fosc == 48000000UL)
    USBCLK |= PCKI_D4;          //PLL输入时钟4分频
#elif (MAIN_Fosc == 96000000UL)
    USBCLK |= PCKI_D8;          //PLL输入时钟8分频
#else
    USBCLK |= PCKI_D1;          //默认PLL输入时钟1分频
#endif

    //启动PLL
    USBCLK |= ENCKM;            //使能PLL倍频
    delay_ms(1);                //等待PLL锁频

    //选择HSPWM/HSSPI时钟
#if (HSCK_SEL == HSCK_MCLK)
    CLKSEL &= ~HSIOCK;          //HSPWM/HSSPI选择主时钟为时钟源
#elif (HSCK_SEL == HSCK_PLL)
    CLKSEL |= HSIOCK;           //HSPWM/HSSPI选择PLL输出时钟为时钟源
#else
    CLKSEL &= ~HSIOCK;          //默认HSPWM/HSSPI选择主时钟为时钟源
#endif

    HSCLKDIV = 1;               //HSPWM/HSSPI时钟源4分频

//    SSIG = 1; //忽略 SS 引脚功能，使用 MSTR 确定器件是主机还是从机
//    SPEN = 1; //使能 SPI 功能
//    DORD = 0; //先发送/接收数据的高位（ MSB）
//    MSTR = 1; //设置主机模式
//    CPOL = 1; //SCLK 空闲时为高电平，SCLK 的前时钟沿为下降沿，后时钟沿为上升沿
//    CPHA = 1; //数据在 SCLK 前时钟沿驱动，后时钟沿采样
    SPCTL |=  (1 << 7); //忽略 SS 引脚功能，使用 MSTR 确定器件是主机还是从机
    SPCTL |=  (1 << 6); //使能 SPI 功能
    SPCTL &= ~(1 << 5); //先发送/接收数据的高位（ MSB）
    SPCTL |=  (1 << 4); //设置主机模式
    SPCTL &= ~(1 << 3); //SCLK 空闲时为低电平，SCLK 的前时钟沿为上升沿，后时钟沿为下降沿
    SPCTL &= ~(1 << 2); //数据 SS 管脚为低电平驱动第一位数据并在 SCLK 的后时钟沿改变数据
    SPCTL = (SPCTL & ~3) | 2;   //SPI 时钟频率选择, 0: 4T, 1: 8T,  2: 16T,  3: 2T
    //P_SW1 = (P_SW1 & ~(3<<2)) | (1<<2);     //IO口切换. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 1: P2.2 P2.3 P2.4 P2.5, 2: P5.4 P4.0 P4.1 P4.3, 3: P3.5 P3.4 P3.3 P3.2
		P_SW1 = (P_SW1 & ~(3<<2)) | (0<<2);     //IO口切换. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 1: P2.2 P2.3 P2.4 P2.5, 2: P5.4 P4.0 P4.1 P4.3, 3: P3.5 P3.4 P3.3 P3.2
//    P_PM25LV040_SCK = 0;    // set clock to low initial state
//    P_PM25LV040_SI = 1;
    SPIF = 1;   //清SPIF标志
    WCOL = 1;   //清WCOL标志

    HSSPI_CFG2 |= 0x20;         //使能SPI高速模式
}