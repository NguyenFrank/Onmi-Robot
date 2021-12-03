#include "ps_2.h"
#include "tm_stm32_delay.h"
//    ******************    chuong trinh con    **************


uint8_t PS2_CONFIGMODE[5] = {0x01, 0x43, 0x00, 0x01, 0x00};
uint8_t PS2_ANALOGMODE[9] = {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};
uint8_t PS2_SETUPMOTOR[9] = {0x01, 0x4D, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff};
uint8_t PS2_RETURNPRES[9] = {0x01, 0x4f, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00};
uint8_t PS2_EXITCONFIG[9] = {0x01, 0x43, 0x00, 0x00, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a};
uint8_t read[9]={0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// *************    khai bao bien toan cuc     ***********

uint8_t GP_BTN [15];






uint8_t SPIxmit (uint8_t dta)
{
    unsigned char tmp = 0;
    unsigned char i;
    for (i = 0x01; i > 0; i <<= 1)
    {
        SPI_SCK_0;
        Delay(10);
        if(dta & i) SPI_MOSI_1;
        if((dta & i)==0) SPI_MOSI_0;
        SPI_SCK_1;
        Delay(16);
        if (SPI_MISO) tmp |= i;
    }
    return tmp;
}

void send_ps2 (uint8_t*cmd,uint8_t length)
{
	  SPI_CS_0;
		Delay(10);
	  for(uint8_t i=0;i<length;i++)
    SPIxmit(cmd[i]);
    Delay(10);
		SPI_CS_1;
}


void read_ps (void)
{
	  SPI_CS_0;
		Delay(10);
    SPIxmit(0x01);
    SPIxmit(0x42);
    SPI_CS_1;
    Delay(16);
	  SPI_CS_0;
    Delay(10);
		for(int i=0;i<9;i++)
	  {
    GP_BTN[i]=SPIxmit(read[i]);    //start command
			
    }
    SPI_CS_1;
}





void ps_2_int(void)
{
	send_ps2(PS2_CONFIGMODE,5);
	Delay(10);
	send_ps2(PS2_ANALOGMODE,9);
	Delay(10);
}



