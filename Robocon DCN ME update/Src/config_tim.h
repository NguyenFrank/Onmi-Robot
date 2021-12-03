
#ifndef __CONFIG_TIM_H
#define __CONFIG_TIM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"

extern	void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void config_pwm(void);
void Clear_Encoder_all(void);
void Clear_En_1(void);
void Clear_En_2(void);
int32_t read_en_1(void);
int32_t read_en_2(void);
void config_encotder(void);
void config_all_tim(void);
	
extern int32_t en1,en2;


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
