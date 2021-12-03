
#ifndef __4_BANH_OMI_H
#define __4_BANH_OMI_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"

void send_PID(uint8_t _chieu, uint8_t _dia_chi, uint8_t _vantoc);
extern int16_t goc;
extern uint8_t data_send_PID[3];
void robot_stop(uint8_t _che_do_dung,uint8_t _giam_toc);
void phanh_robot(void);
void robot_run(int16_t _goc_tinh_tien,int16_t _v_tinh_tien,int16_t _goc_quay,int16_t _v_xoay);
void chinh_robot(void);
void xoay_phai(void);
void xoay_trai(void);
extern uint8_t he_so_gia_toc,he_so_giam_toc;//he so tang giam toc do
extern float Kp, Ki, Kd;//he so pid dieu chinh bu goc
extern int16_t v_A, v_B, v_C, v_D;//bien luu v 4 banh
extern float chieu_A,chieu_B,chieu_C,chieu_D;
extern int16_t v_thuc;
extern int16_t v_tinh_tien;//van toc tinh tien cho phep
extern int16_t v_quay;
extern uint8_t che_do;
extern uint8_t ps2[3];//byte 1 nut up doan, byte nut tam giac tron, byte 3 analog
extern uint8_t chieuA,chieuB,chieuC,chieuD;
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
