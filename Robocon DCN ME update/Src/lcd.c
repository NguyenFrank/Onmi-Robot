#include "lcd.h"
#include "tm_stm32_delay.h"

void LCD_Enable()
{
HAL_GPIO_WritePin(EN_Port,EN_Pin,1);
Delay(100);
HAL_GPIO_WritePin(EN_Port,EN_Pin,0);	
Delay(100);	
}

void LCD_Send4Bit(unsigned char Data)
{
HAL_GPIO_WritePin(D4_Port,D4_Pin,(Data&0x10)>>4);
HAL_GPIO_WritePin(D5_Port,D5_Pin,(Data&0x20)>>5);
HAL_GPIO_WritePin(D6_Port,D6_Pin,(Data&0x40)>>6);		
HAL_GPIO_WritePin(D7_Port,D7_Pin,(Data&0x80)>>7);
}

void LCD_SendCommand(unsigned char command)
{
	LCD_Send4Bit(command);
	LCD_Enable();
	LCD_Send4Bit(command<<4);
	LCD_Enable();
}

void LCD_Clear()
{
 	LCD_SendCommand(0x01);  
}

void LCD_Init()
{
  HAL_GPIO_WritePin(RS_Port,RS_Pin,0);
	LCD_Send4Bit(0x30);
	LCD_Enable();
	LCD_Enable();
	LCD_Enable();
	LCD_Send4Bit(0x20);
	LCD_Enable();
	LCD_SendCommand(0x28);
	LCD_SendCommand(0x0C);
	LCD_SendCommand(0x06);
	LCD_SendCommand(0x01);
}

void LCD_Gotoxy(unsigned char x, unsigned char y)
{
unsigned char address;
if(y==0)
address=0x80;
else if(y==1)
{
address=0xc0;
}
else if(y==2)
{
address=0x94;
}
else
address=0xd4;
address+=x;
LCD_SendCommand(address);
}

void LCD_PutChar(unsigned char Data)
{
  HAL_GPIO_WritePin(RS_Port,RS_Pin,1);
 	LCD_SendCommand(Data);
  HAL_GPIO_WritePin(RS_Port,RS_Pin,0);
}

void LCD_print(char *s)
{
   	while (*s)
		{
      	LCD_PutChar(*s);
				s++;
   	}
}
void LCD_printInt(int number)
{
	char numStr[16];
	sprintf(numStr,"%d ", number);
	LCD_print(numStr);
}

void LCD_printFloat(float number, int decimalPoints)
{
	char numStr[16];
	sprintf(numStr,"%.*f ",decimalPoints, number);
	LCD_print(numStr);
}
