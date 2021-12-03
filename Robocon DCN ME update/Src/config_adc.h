
#ifndef __CONFIG_ADC_H
#define __CONFIG_ADC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"
	
void read_sick(void);	
extern uint16_t adc_value[3];


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
