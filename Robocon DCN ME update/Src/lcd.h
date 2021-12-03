#ifndef		__LCD_H
#define		__LCD_H

#include "stm32f4xx.h"



#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0


#define RS_Port GPIOD
#define EN_Port GPIOD
#define D4_Port GPIOD
#define D5_Port GPIOD
#define D6_Port GPIOD
#define D7_Port GPIOD


#define RS_Pin GPIO_PIN_15
#define EN_Pin GPIO_PIN_14
#define D4_Pin GPIO_PIN_8
#define D5_Pin GPIO_PIN_9
#define D6_Pin GPIO_PIN_10
#define D7_Pin GPIO_PIN_11

void LCD_Enable(void);
void LCD_Send4Bit(unsigned char Data);
void LCD_SendCommand(unsigned char command);
void LCD_Clear(void);
void LCD_Init(void);
void LCD_Gotoxy(unsigned char x, unsigned char y);
void LCD_PutChar(unsigned char Data);
void LCD_print(char *s);
void LCD_printInt(int number);
void LCD_printFloat(float number, int decimalPoints);



#endif

