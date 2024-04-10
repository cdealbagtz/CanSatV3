/*
 * NRF24.c
 *
 *  Created on: Apr 9, 2024
 *      Author: cdealba
 */

#include "Peripheral/NRF24.h"

NRF24_Config_t NRF24_Configurations_Struct;



void NRF24_write(uint8_t Adr, uint8_t data){
	Adr |= W_REGISTER;
	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	HAL_SPI_Transmit_DMA(SPI_NRF24, &data, 1);
	NRF24_unselect();
}

void NRF24_Addr_write(uint8_t Adr,uint8_t *ADDRESS){
	Adr |= W_REGISTER;
	uint8_t buffer[5];
	buffer[0] = ADDRESS[4];
	buffer[1] = ADDRESS[3];
	buffer[2] = ADDRESS[2];
	buffer[3] = ADDRESS[1];
	buffer[4] = ADDRESS[0];

	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	for (uint8_t n = 0; n < 5; ++n) {
		HAL_SPI_Transmit_DMA(SPI_NRF24, &buffer[n], 1);
	}

	NRF24_unselect();

}

uint8_t NRF24_read(uint8_t Adr){
	uint8_t Replay;
	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	HAL_SPI_Receive_DMA(SPI_NRF24, &Replay, 1);
	NRF24_unselect();
	return Replay;
}

void NRF24_Addr_read(uint8_t Adr){
	uint8_t Buffer[5];
	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	for (uint8_t i = 0; i < 5; ++i) {
		HAL_SPI_Receive_DMA(SPI_NRF24, &Buffer[i], 1);
	}
	NRF24_unselect();
	switch (Adr) {
		case RX_ADDR_P0:
			NRF24_Configurations_Struct.Actual.RX_ADDR_P0[4]=Buffer[0];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P0[3]=Buffer[1];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P0[2]=Buffer[2];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P0[1]=Buffer[3];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P0[0]=Buffer[4];
			break;
		case RX_ADDR_P1:
			NRF24_Configurations_Struct.Actual.RX_ADDR_P1[4]=Buffer[0];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P1[3]=Buffer[1];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P1[2]=Buffer[2];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P1[1]=Buffer[3];
			NRF24_Configurations_Struct.Actual.RX_ADDR_P1[0]=Buffer[4];
			break;
		case TX_ADDR:
			NRF24_Configurations_Struct.Actual.TX_ADDR[4]=Buffer[0];
			NRF24_Configurations_Struct.Actual.TX_ADDR[3]=Buffer[1];
			NRF24_Configurations_Struct.Actual.TX_ADDR[2]=Buffer[2];
			NRF24_Configurations_Struct.Actual.TX_ADDR[1]=Buffer[3];
			NRF24_Configurations_Struct.Actual.TX_ADDR[0]=Buffer[4];
			break;
	}
}

void NRF24_DefaultConfiguration(void){
	NRF24_Configurations_Struct.Default.CONFIG 			= 0x08;
	NRF24_Configurations_Struct.Default.EN_AA  			= 0x3F;
	NRF24_Configurations_Struct.Default.EN_RXADDR  		= 0x03;
	NRF24_Configurations_Struct.Default.SETUP_AW  		= 0x03;
	NRF24_Configurations_Struct.Default.SETUP_RETR 		= 0x00;
	NRF24_Configurations_Struct.Default.RF_CH  			= 0x02;
	NRF24_Configurations_Struct.Default.RF_SETUP  		= 0x0F;
	NRF24_Configurations_Struct.Default.STATUS  			= 0X0E;
	NRF24_Configurations_Struct.Default.OBSERVE  		= 0X00;
	NRF24_Configurations_Struct.Default.CD  				= 0x00;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[0]   	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[1]   	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[2]   	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[3]   	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[4]   	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[0]   	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[1]   	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[2]   	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[3]   	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[4]   	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P2  		= 0xC3;
	NRF24_Configurations_Struct.Default.RX_ADDR_P3 		= 0xC4;
	NRF24_Configurations_Struct.Default.RX_ADDR_P4  		= 0xC5;
	NRF24_Configurations_Struct.Default.RX_ADDR_P5  		= 0xC6;
	NRF24_Configurations_Struct.Default.TX_ADDR[0]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[1]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[2]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[3]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[4]   	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_PW_P0  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P1  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P2  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P3  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P4  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P5  		= 0X00;
	NRF24_Configurations_Struct.Default.FIFO_STATUS  	= 0X11;
	NRF24_Configurations_Struct.Default.DYNPD  			= 0X00;
	NRF24_Configurations_Struct.Default.FEATURE  		= 0X00;
}

void NRF24_ActualConfiguration(void){
	NRF24_Configurations_Struct.Actual.CONFIG 		= NRF24_read(CONFIG);
	NRF24_Configurations_Struct.Actual.EN_AA  		= NRF24_read(EN_AA);
	NRF24_Configurations_Struct.Actual.EN_RXADDR  	= NRF24_read(EN_RXADDR);
	NRF24_Configurations_Struct.Actual.SETUP_AW  	= NRF24_read(SETUP_AW);
	NRF24_Configurations_Struct.Actual.SETUP_RETR 	= NRF24_read(SETUP_RETR);
	NRF24_Configurations_Struct.Actual.RF_CH  		= NRF24_read(RF_CH);
	NRF24_Configurations_Struct.Actual.RF_SETUP  	= NRF24_read(RF_SETUP);
	NRF24_Configurations_Struct.Actual.STATUS  		= NRF24_read(STATUS);
	NRF24_Configurations_Struct.Actual.OBSERVE  	= NRF24_read(OBSERVE);
	NRF24_Configurations_Struct.Actual.CD  			= NRF24_read(CD);
	NRF24_Addr_read(RX_ADDR_P0);
	NRF24_Addr_read(RX_ADDR_P1);
	NRF24_Configurations_Struct.Actual.RX_ADDR_P2  	= NRF24_read(RX_ADDR_P2);
	NRF24_Configurations_Struct.Actual.RX_ADDR_P3 	= NRF24_read(RX_ADDR_P3);
	NRF24_Configurations_Struct.Actual.RX_ADDR_P4  	= NRF24_read(RX_ADDR_P4);
	NRF24_Configurations_Struct.Actual.RX_ADDR_P5  	= NRF24_read(RX_ADDR_P5);
	NRF24_Addr_read(TX_ADDR);
	NRF24_Configurations_Struct.Actual.RX_PW_P0  	= NRF24_read(RX_PW_P0);
	NRF24_Configurations_Struct.Actual.RX_PW_P1  	= NRF24_read(RX_PW_P1);
	NRF24_Configurations_Struct.Actual.RX_PW_P2  	= NRF24_read(RX_PW_P2);
	NRF24_Configurations_Struct.Actual.RX_PW_P3  	= NRF24_read(RX_PW_P3);
	NRF24_Configurations_Struct.Actual.RX_PW_P4  	= NRF24_read(RX_PW_P4);
	NRF24_Configurations_Struct.Actual.RX_PW_P5  	= NRF24_read(RX_PW_P5);
	NRF24_Configurations_Struct.Actual.FIFO_STATUS  = NRF24_read(FIFO_STATUS);
	NRF24_Configurations_Struct.Actual.DYNPD  		= NRF24_read(DYNPD);
	NRF24_Configurations_Struct.Actual.FEATURE  	= NRF24_read(FEATURE);
}

void NRF24_config(NRF24_Address_Configurations_t Configuration_struct){
	uint8_t buffer[5] = {0};
	buffer[0] = Configuration_struct.CONFIG;
	NRF24_write(CONFIG,	buffer[0]);
	NRF24_write(EN_AA, Configuration_struct.EN_AA);
	NRF24_write(EN_RXADDR,Configuration_struct.EN_RXADDR);
	NRF24_write(SETUP_AW,Configuration_struct.SETUP_AW);
	NRF24_write(SETUP_RETR,Configuration_struct.SETUP_RETR);
	NRF24_write(RF_CH,Configuration_struct.RF_CH);
	NRF24_write(RF_SETUP,Configuration_struct.RF_SETUP);
	NRF24_write(STATUS,Configuration_struct.STATUS);
	NRF24_write(OBSERVE,Configuration_struct.OBSERVE);
	NRF24_write(CD,Configuration_struct.CD);
	uint8_t RX_ADDR_P0_ADDRESS[5];
	uint8_t RX_ADDR_P1_ADDRESS[5];
	uint8_t TX_ADDR_ADDRESS[5];

	RX_ADDR_P0_ADDRESS[4]=Configuration_struct.RX_ADDR_P0[0];
	RX_ADDR_P0_ADDRESS[3]=Configuration_struct.RX_ADDR_P0[1];
	RX_ADDR_P0_ADDRESS[2]=Configuration_struct.RX_ADDR_P0[2];
	RX_ADDR_P0_ADDRESS[1]=Configuration_struct.RX_ADDR_P0[3];
	RX_ADDR_P0_ADDRESS[0]=Configuration_struct.RX_ADDR_P0[4];
	NRF24_Addr_write(RX_ADDR_P0, RX_ADDR_P0_ADDRESS);
	RX_ADDR_P1_ADDRESS[4]=Configuration_struct.RX_ADDR_P1[0];
	RX_ADDR_P1_ADDRESS[3]=Configuration_struct.RX_ADDR_P1[1];
	RX_ADDR_P1_ADDRESS[2]=Configuration_struct.RX_ADDR_P1[2];
	RX_ADDR_P1_ADDRESS[1]=Configuration_struct.RX_ADDR_P1[3];
	RX_ADDR_P1_ADDRESS[0]=Configuration_struct.RX_ADDR_P1[4];
	NRF24_Addr_write(RX_ADDR_P1, RX_ADDR_P1_ADDRESS);
	NRF24_write(RX_ADDR_P2,Configuration_struct.RX_ADDR_P2);
	NRF24_write(RX_ADDR_P3,Configuration_struct.RX_ADDR_P3);
	NRF24_write(RX_ADDR_P4,Configuration_struct.RX_ADDR_P4);
	NRF24_write(RX_ADDR_P5,Configuration_struct.RX_ADDR_P5);
	TX_ADDR_ADDRESS[4]=Configuration_struct.TX_ADDR[0];
	TX_ADDR_ADDRESS[3]=Configuration_struct.TX_ADDR[1];
	TX_ADDR_ADDRESS[2]=Configuration_struct.TX_ADDR[2];
	TX_ADDR_ADDRESS[1]=Configuration_struct.TX_ADDR[3];
	TX_ADDR_ADDRESS[0]=Configuration_struct.TX_ADDR[4];
	NRF24_Addr_write(TX_ADDR, TX_ADDR_ADDRESS);
	NRF24_write(RX_PW_P0,Configuration_struct.RX_PW_P0);
	NRF24_write(RX_PW_P1,Configuration_struct.RX_PW_P1);
	NRF24_write(RX_PW_P2,Configuration_struct.RX_PW_P2);
	NRF24_write(RX_PW_P3,Configuration_struct.RX_PW_P3);
	NRF24_write(RX_PW_P4,Configuration_struct.RX_PW_P4);
	NRF24_write(RX_PW_P5,Configuration_struct.RX_PW_P5);
	NRF24_write(FIFO_STATUS,Configuration_struct.FIFO_STATUS);
	NRF24_write(DYNPD,Configuration_struct.DYNPD);
	NRF24_write(FEATURE,Configuration_struct.FEATURE);
}
void NRF24_init(void){
	NRF24_Disable();
	NRF24_unselect();
	NRF24_DefaultConfiguration();
	NRF24_config(NRF24_Configurations_Struct.Default);
	NRF24_ActualConfiguration();
}
