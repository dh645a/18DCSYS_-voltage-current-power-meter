#ifndef __SPI_H__
#define __SPI_H__

#include "config.h"

#define U8g2_SPI_MODE   1    /* SPI 模式使能 */
#define SPI_DMA_CFG     1    /* SPI DMA 使能 */

void HAL_SPI_Init(void);
void SPI_init(void);
#endif /*__SPI_H__*/

