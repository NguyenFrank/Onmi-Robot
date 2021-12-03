#ifndef		__PS_2_H
#define		__PS_2_H



#include "stm32f4xx_hal.h"

extern uint8_t GP_BTN [15];

#define SPI_MISO        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)//data

#define SPI_MOSI_0      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0)//cmd
#define SPI_MOSI_1      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1)

#define SPI_CS_0        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0)//cs
#define SPI_CS_1        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1)

#define SPI_SCK_0       HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0)
#define SPI_SCK_1       HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1)//aten





//-------------------------------------- Dat bien nut nhan -------------------------------------
#define GP_MASK_SELECT 			0x01
#define GP_MASK_START				0x08
#define GP_MASK_UP					0x10
#define GP_MASK_RIGHT				0x20
#define GP_MASK_DOWN				0x40
#define GP_MASK_LEFT				0x80
#define GP_MASK_L2					0x01
#define GP_MASK_R2					0x02
#define GP_MASK_L1					0x04
#define GP_MASK_R1					0x08
#define GP_MASK_TRIANGLE    0x10
#define GP_MASK_O           0x20
#define GP_MASK_X           0x40
#define GP_MASK_SQUARE      0x80
#define GP_MASK_RJOY        0x02
#define GP_MASK_LJOY        0x04

#define SELECT        (GP_BTN[3] & GP_MASK_SELECT)
#define START        	(GP_BTN[3] & GP_MASK_START)
#define LJOY        	(GP_BTN[3] & GP_MASK_RJOY)
#define RJOY        	(GP_BTN[3] & GP_MASK_LJOY)

#define UP            (GP_BTN[3] & GP_MASK_UP)
#define RIGHT        	(GP_BTN[3] & GP_MASK_RIGHT)
#define DOWN        	(GP_BTN[3] & GP_MASK_DOWN)
#define LEFT        	(GP_BTN[3] & GP_MASK_LEFT)

#define L2            (GP_BTN[4] & GP_MASK_L2)
#define R2            (GP_BTN[4] & GP_MASK_R2)
#define L1            (GP_BTN[4] & GP_MASK_L1)
#define R1            (GP_BTN[4] & GP_MASK_R1)

#define TRIANGLE    	(GP_BTN[4] & GP_MASK_TRIANGLE)
#define O            	(GP_BTN[4] & GP_MASK_O)
#define X            	(GP_BTN[4] & GP_MASK_X)
#define SQUARE        (GP_BTN[4] & GP_MASK_SQUARE)

#define RJOY_LR       (GP_BTN[5])
#define RJOY_UD       (GP_BTN[6])
#define LJOY_LR       (GP_BTN[7])
#define LJOY_UD       (GP_BTN[8])






// *************    khai bao bien toan cuc     ***********


uint8_t SPIxmit (uint8_t dta);
void send_ps2 (uint8_t*cmd,uint8_t length);
void read_ps (void);
void ps_2_int(void);


#endif
