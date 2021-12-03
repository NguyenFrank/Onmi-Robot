
#ifndef __CONFIG_UART_H
#define __CONFIG_UART_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

void uart_init(void);
void read_goc(void);
void read_ps2(void);
void chon_san(uint8_t _chon_san);
void hien_thi_all(void);//hien thi data len hmi
void set_goc_0(void);
void san_do(void);
void san_xanh(void);
extern int16_t goc;
extern uint8_t ps2[3];//byte 1 nut up doan, byte nut tam giac tron, byte 3 analog
extern uint8_t run;
extern uint8_t che_do_hmi;
	

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
