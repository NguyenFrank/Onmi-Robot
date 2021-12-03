#include "config_uart.h"
#include "stdio.h"

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart3_rx;

uint8_t data_ps2;//bien tam doc ps2 tuc thoi
uint8_t data_angle[2]; //bien tam doc angle

uint8_t cmd_la_ban; //lenh lay data la ban
uint8_t num;//bien dem dat trong system tick;

uint8_t ps2[3];//byte 1 nut up doan, byte nut tam giac tron, byte 3 analog
uint8_t count;
int16_t goc;//goc hien tai cua robot
uint8_t reset_goc='a';

extern int16_t v_A, v_B, v_C, v_D;//bien luu v 4 banh
extern int16_t v_thuc;
extern int16_t v_tinh_tien;//van toc tinh tien cho phep
extern int32_t en1,en2;
uint8_t run;

void UART4_Init(uint32_t baudrate)
{

  huart4.Instance = UART4;
  huart4.Init.BaudRate = baudrate;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart4);
}



void UART2_Init(uint32_t baudrate)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = baudrate;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart2);
  
}

void UART3_Init(uint32_t baudrate)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = baudrate;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart3);
}

void uart_init(void)
{
	UART2_Init(115200);//ket noi voi la ban
	UART3_Init(115200);//ket noi ps2
	UART4_Init(115200);//dieu khien cau pid
	
	HAL_UART_Receive_DMA(&huart2,data_angle,2);//doc 2 byte la ban
	HAL_UART_Receive_DMA(&huart3,&data_ps2,1);//doc du lieu ps2
		
	cmd_la_ban='a';//set la ban bang 0
	HAL_Delay(100);
	cmd_la_ban='z';//1ms lay du lieu la ban
	HAL_Delay(100);
	
}
//==================cac ham viet de doc la ban============================//
void read_goc(void)
{
	if(num++>10) 
		{
			HAL_UART_Transmit(&huart2,&cmd_la_ban,1,10);
			num=0;
		}
}
void set_goc_0(void)
{
	HAL_UART_Transmit(&huart2,&reset_goc,1,5);
	HAL_UART_Transmit(&huart2,&reset_goc,1,5);
}
//================cac ham viet doc tay ps2==============================//

void read_ps2(void)
{
	if(data_ps2!='.')
	{
		ps2[count++]=data_ps2;
	}
	else
	{
		count=0;
	}	
	if(ps2[1]==223)
		run=1;
	
}