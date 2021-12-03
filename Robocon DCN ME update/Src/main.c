#include "main.h"
#include "config_system.h"
#include "config_DMA.h"
#include "config_adc.h"
#include "config_tim.h"
#include "config_uart.h"
#include "4_banh_omi.h"
#include "lcd.h"
#include "tm_stm32_delay.h"
#include "math.h"

uint16_t dem_lcd=0;
uint8_t a='a';

uint16_t Lazer1,Lazer2,Lazer3,Lazer4;

uint8_t dulieu[2]={0,0},line=0;

void hien_lcd(void) 
{
if(dem_lcd>200)
	{
		LCD_Gotoxy(5,0);       LCD_printInt(Lazer1);
		LCD_Gotoxy(12,0);       	LCD_printInt(Lazer2);	
		LCD_Gotoxy(5,1);       LCD_printInt(Lazer3); 
		LCD_Gotoxy(13,1);       	LCD_printInt(Lazer4);
		dem_lcd=0;
	}

}

int main(void)
{

  HAL_Init();
	SystemClock_Config();
  GPIO_Init();
	
	DMA_Init();//config dma va muc do uu tien
	read_sick(); //config adc doc sick
	config_encotder();//config encotder tim2 tim5 2ch
	//config_pwm();//config tim1 tim8 de pwm
  config_all_tim();//config TIM3 ngat
	uart_init();//khai bao tat ca su dung uart
	
  while (1)
  {
	//	hien_lcd();
		robot_run(0,20,900,1);
  }
 
}




