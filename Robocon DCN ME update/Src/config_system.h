
#ifndef __CONFIG_SYSTEM_H
#define __CONFIG_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"


void SystemClock_Config(void);
void GPIO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
