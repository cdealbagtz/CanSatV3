/*
 * NRF24.c
 *
 *  Created on: Apr 9, 2024
 *      Author: cdealba
 */

#include "Peripheral/NRF24.h"
#include "Peripheral/mpu6050.h"

NRF24_Config_t NRF24_Configurations_Struct;
uint8_t Transmision_Flag = 0;

uint8_t TX_FULL, RX_P_NO, MAX_RT, TX_DS, RX_DR;
uint8_t RX_EMPTY, RX_FULL, TX_EMPTY, TX_FULL, TX_REUSE;

uint8_t PIPE0_Addres[5] = {0xC5,0xC5,0xC5,0xC5,0xC5};
uint8_t NRF24_Cannel    = 0x56;

uint8_t Cont_TX = 0;
uint8_t NRF24_mode;

uint8_t TxBuffer[32];
uint8_t RxBuffer[32];

uint8_t N_message, Struct2transmit, Transmision_cont;
uint8_t CheckSum = 0;

extern S32_t Temperature, Altitud;
extern U32_t Presure;

extern uint8_t ErrorFlags;

extern MPU6050_t MPU6050;

S32_t AngleX, AngleY;

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

void NRF24_FlushTxFIFO(void){
	uint8_t Adr = FLUSH_TX;
	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	NRF24_unselect();
}

void NRF24_FlushRxFIFO(void){
	uint8_t Adr = FLUSH_RX;
	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	NRF24_unselect();
}

void NRF24_PowerUp(void){
	uint8_t Adr = 0x00;
	uint8_t Buffer= NRF24_read(Adr);
	Adr |= W_REGISTER;
	Buffer |= 0x02;
	NRF24_write(Adr, Buffer);
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
	NRF24_write(CONFIG,	Configuration_struct.CONFIG);
	NRF24_write(EN_AA, Configuration_struct.EN_AA);
	NRF24_write(EN_RXADDR,Configuration_struct.EN_RXADDR);
	NRF24_write(SETUP_AW,Configuration_struct.SETUP_AW);
	NRF24_write(SETUP_RETR,Configuration_struct.SETUP_RETR);
	NRF24_write(RF_CH,Configuration_struct.RF_CH);
	NRF24_write(RF_SETUP,Configuration_struct.RF_SETUP);
	NRF24_write(STATUS,Configuration_struct.STATUS);
	NRF24_write(OBSERVE,Configuration_struct.OBSERVE);
	NRF24_write(CD,Configuration_struct.CD);
	NRF24_Addr_write(RX_ADDR_P0, Configuration_struct.RX_ADDR_P0);
	NRF24_Addr_write(RX_ADDR_P1, Configuration_struct.RX_ADDR_P1);
	NRF24_write(RX_ADDR_P2,Configuration_struct.RX_ADDR_P2);
	NRF24_write(RX_ADDR_P3,Configuration_struct.RX_ADDR_P3);
	NRF24_write(RX_ADDR_P4,Configuration_struct.RX_ADDR_P4);
	NRF24_write(RX_ADDR_P5,Configuration_struct.RX_ADDR_P5);
	NRF24_Addr_write(TX_ADDR, Configuration_struct.TX_ADDR);
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

void NRF24_DefaultConfiguration(void){
	NRF24_FlushTxFIFO();
	NRF24_FlushRxFIFO();
	NRF24_Configurations_Struct.Default.CONFIG 			= 0x78;
	NRF24_Configurations_Struct.Default.EN_AA  			= 0x3F;
	NRF24_Configurations_Struct.Default.EN_RXADDR  		= 0x03;
	NRF24_Configurations_Struct.Default.SETUP_AW  		= 0x03;
	NRF24_Configurations_Struct.Default.SETUP_RETR 		= 0x03;
	NRF24_Configurations_Struct.Default.RF_CH  			= 0x02;
	NRF24_Configurations_Struct.Default.RF_SETUP  		= 0x09;
	NRF24_Configurations_Struct.Default.STATUS  		= 0X70;
	NRF24_Configurations_Struct.Default.OBSERVE  		= 0X00;
	NRF24_Configurations_Struct.Default.CD  			= 0x00;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[0]  	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[1]  	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[2]  	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[3]  	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P0[4]  	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[0]  	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[1]  	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[2]  	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[3]  	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P1[4]  	= 0xC2;
	NRF24_Configurations_Struct.Default.RX_ADDR_P2  	= 0xC3;
	NRF24_Configurations_Struct.Default.RX_ADDR_P3 		= 0xC4;
	NRF24_Configurations_Struct.Default.RX_ADDR_P4  	= 0xC5;
	NRF24_Configurations_Struct.Default.RX_ADDR_P5  	= 0xC6;
	NRF24_Configurations_Struct.Default.TX_ADDR[0]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[1]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[2]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[3]   	= 0xE7;
	NRF24_Configurations_Struct.Default.TX_ADDR[4]   	= 0xE7;
	NRF24_Configurations_Struct.Default.RX_PW_P0  		= 0X20;
	NRF24_Configurations_Struct.Default.RX_PW_P1  		= 0X20;
	NRF24_Configurations_Struct.Default.RX_PW_P2  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P3  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P4  		= 0X00;
	NRF24_Configurations_Struct.Default.RX_PW_P5  		= 0X00;
	NRF24_Configurations_Struct.Default.FIFO_STATUS  	= 0X11;
	NRF24_Configurations_Struct.Default.DYNPD  			= 0X00;
	NRF24_Configurations_Struct.Default.FEATURE  		= 0X00;
	NRF24_config(NRF24_Configurations_Struct.Default);
	NRF24_ActualConfiguration();
	NRF24_mode = Init;
}

void NRF24_TxConfiguration(void){
	NRF24_Configurations_Struct.Tx_mode.CONFIG 			= 0x78;
	NRF24_Configurations_Struct.Tx_mode.EN_AA  			= 0x03;
	NRF24_Configurations_Struct.Tx_mode.EN_RXADDR  		= 0x03;
	NRF24_Configurations_Struct.Tx_mode.SETUP_AW  		= 0x03;
	NRF24_Configurations_Struct.Tx_mode.SETUP_RETR 		= 0x33;
	NRF24_Configurations_Struct.Tx_mode.RF_CH  			= 0x12;
	NRF24_Configurations_Struct.Tx_mode.RF_SETUP  		= 0x09;
	NRF24_Configurations_Struct.Tx_mode.STATUS  		= 0X70;
	NRF24_Configurations_Struct.Tx_mode.OBSERVE  		= 0X00;
	NRF24_Configurations_Struct.Tx_mode.CD  			= 0x00;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P0[0]  	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P0[1]  	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P0[2]  	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P0[3]  	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P0[4]  	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P1[0]  	= 0xC2;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P1[1]  	= 0xC2;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P1[2]  	= 0xC2;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P1[3]  	= 0xC2;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P1[4]  	= 0xC2;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P2  	= 0xC3;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P3 		= 0xC4;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P4  	= 0xC5;
	NRF24_Configurations_Struct.Tx_mode.RX_ADDR_P5  	= 0xC6;
	NRF24_Configurations_Struct.Tx_mode.TX_ADDR[0]   	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.TX_ADDR[1]   	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.TX_ADDR[2]   	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.TX_ADDR[3]   	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.TX_ADDR[4]   	= 0xE7;
	NRF24_Configurations_Struct.Tx_mode.RX_PW_P0  		= 0X20;
	NRF24_Configurations_Struct.Tx_mode.RX_PW_P1  		= 0X20;
	NRF24_Configurations_Struct.Tx_mode.RX_PW_P2  		= 0X00;
	NRF24_Configurations_Struct.Tx_mode.RX_PW_P3  		= 0X00;
	NRF24_Configurations_Struct.Tx_mode.RX_PW_P4  		= 0X00;
	NRF24_Configurations_Struct.Tx_mode.RX_PW_P5  		= 0X00;
	NRF24_Configurations_Struct.Tx_mode.FIFO_STATUS  	= 0X11;
	NRF24_Configurations_Struct.Tx_mode.DYNPD  			= 0X00;
	NRF24_Configurations_Struct.Tx_mode.FEATURE  		= 0X00;
	NRF24_config(NRF24_Configurations_Struct.Tx_mode);
	NRF24_ActualConfiguration();
	NRF24_mode = TxMode;
}

void NRF24_RxConfiguration(void){
	NRF24_Configurations_Struct.Rx_mode.CONFIG 			= 0x79;
	NRF24_Configurations_Struct.Rx_mode.EN_AA  			= 0x03;
	NRF24_Configurations_Struct.Rx_mode.EN_RXADDR  		= 0x03;
	NRF24_Configurations_Struct.Rx_mode.SETUP_AW  		= 0x03;
	NRF24_Configurations_Struct.Rx_mode.SETUP_RETR 		= 0x33;
	NRF24_Configurations_Struct.Rx_mode.RF_CH  			= 0x12;
	NRF24_Configurations_Struct.Rx_mode.RF_SETUP  		= 0x09;
	NRF24_Configurations_Struct.Rx_mode.STATUS  		= 0X70;
	NRF24_Configurations_Struct.Rx_mode.OBSERVE  		= 0X00;
	NRF24_Configurations_Struct.Rx_mode.CD  			= 0x00;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P0[0]  	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P0[1]  	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P0[2]  	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P0[3]  	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P0[4]  	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P1[0]  	= 0xC2;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P1[1]  	= 0xC2;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P1[2]  	= 0xC2;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P1[3]  	= 0xC2;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P1[4]  	= 0xC2;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P2  	= 0xC3;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P3 		= 0xC4;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P4  	= 0xC5;
	NRF24_Configurations_Struct.Rx_mode.RX_ADDR_P5  	= 0xC6;
	NRF24_Configurations_Struct.Rx_mode.TX_ADDR[0]   	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.TX_ADDR[1]   	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.TX_ADDR[2]   	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.TX_ADDR[3]   	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.TX_ADDR[4]   	= 0xE7;
	NRF24_Configurations_Struct.Rx_mode.RX_PW_P0  		= 0X20;
	NRF24_Configurations_Struct.Rx_mode.RX_PW_P1  		= 0X20;
	NRF24_Configurations_Struct.Rx_mode.RX_PW_P2  		= 0X00;
	NRF24_Configurations_Struct.Rx_mode.RX_PW_P3  		= 0X00;
	NRF24_Configurations_Struct.Rx_mode.RX_PW_P4  		= 0X00;
	NRF24_Configurations_Struct.Rx_mode.RX_PW_P5  		= 0X00;
	NRF24_Configurations_Struct.Rx_mode.FIFO_STATUS  	= 0X11;
	NRF24_Configurations_Struct.Rx_mode.DYNPD  			= 0X00;
	NRF24_Configurations_Struct.Rx_mode.FEATURE  		= 0X00;
	NRF24_config(NRF24_Configurations_Struct.Rx_mode);
	NRF24_ActualConfiguration();
	NRF24_Enable();
	NRF24_mode = RxMode;
}

void NRF24_CheckFlags(void){
	uint8_t buffer = NRF24_read(STATUS);
	TX_FULL =  buffer & 0x01;
	RX_P_NO = (buffer & 0x0E) >> 1;
	MAX_RT  = (buffer & 0x10) >> 4;
	TX_DS   = (buffer & 0x20) >> 5;
	RX_DR   = (buffer & 0x40) >> 6;

	buffer   = NRF24_read(FIFO_STATUS);
	RX_EMPTY =  buffer & 0x01;
	RX_FULL  = (buffer & 0x02) >> 1;
	TX_EMPTY = (buffer & 0x10) >> 4;
	TX_FULL  = (buffer & 0x20) >> 5;
	TX_REUSE = (buffer & 0x40) >> 6;
}

void NRF24_FIFO_write(uint8_t *pData, uint8_t size){
	uint8_t Adr = W_TX_PAYLOAD;
	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	for (uint8_t n = 0; n < 32; ++n) {
		HAL_SPI_Transmit_DMA(SPI_NRF24, &pData[n], 1);
	}
	NRF24_unselect();
}

void NRF24_FIFO_read(uint8_t *pData){
	uint8_t Adr = R_RX_PAYLOAD;
	NRF24_select();
	HAL_SPI_Transmit_DMA(SPI_NRF24, &Adr, 1);
	for (uint8_t n = 0; n < 32; ++n) {
		HAL_SPI_Receive_DMA(SPI_NRF24, &pData[n], 1);
	}
	NRF24_unselect();
}

void NRF24_init(void){
	NRF24_Disable();
	NRF24_unselect();
	NRF24_DefaultConfiguration();
	NRF24_mode = 0;
}


void NRF24_Receive(void){
	NRF24_CheckFlags();
	if(RX_P_NO != 7){
		NRF24_FIFO_read(RxBuffer);
	}
}

void NRF24_TxBuffer(void){


	switch (Struct2transmit) {
		case 0:
			AngleX.data =  (int32_t)(MPU6050.KalmanAngleX * 100);
			AngleY.data =  (int32_t)(MPU6050.KalmanAngleY * 100);

			TxBuffer[0]  = 0xA5;
			TxBuffer[1]  = 0x5A;
			TxBuffer[2]  = 0x10;
			TxBuffer[3]  = N_message;

			TxBuffer[4]  = Temperature.bytes[0];
			TxBuffer[5]  = Temperature.bytes[1];
			TxBuffer[6]  = Temperature.bytes[2];
			TxBuffer[7]  = Temperature.bytes[3];

			TxBuffer[8]  = Altitud.bytes[0];
			TxBuffer[9]  = Altitud.bytes[1];
			TxBuffer[10] = Altitud.bytes[2];
			TxBuffer[11] = Altitud.bytes[3];

			TxBuffer[12] = Presure.bytes[0];
			TxBuffer[13] = Presure.bytes[1];
			TxBuffer[14] = Presure.bytes[2];
			TxBuffer[15] = Presure.bytes[3];

			TxBuffer[16] = AngleX.bytes[0];
			TxBuffer[17] = AngleX.bytes[1];
			TxBuffer[18] = AngleX.bytes[2];
			TxBuffer[19] = AngleX.bytes[3];

			TxBuffer[20] = AngleY.bytes[0];
			TxBuffer[21] = AngleY.bytes[1];
			TxBuffer[22] = AngleY.bytes[2];
			TxBuffer[23] = AngleY.bytes[3];

			TxBuffer[24] = 0xFF;
			TxBuffer[25] = 0xFF;
			TxBuffer[26] = 0xFF;
			TxBuffer[27] = 0xFF;

			TxBuffer[28] = 0x00;
			TxBuffer[29] = 0x00;
			TxBuffer[30] = 0x00;

			for (uint8_t n = 0; n < 30; ++n) {
				CheckSum += TxBuffer[n];
			}
			TxBuffer[31] = CheckSum;

			CheckSum = 0;

			if(++Transmision_cont>=5){
				Transmision_cont = 0;
				Struct2transmit = 1;
			}
			break;
		case 1:
			TxBuffer[0] = 0xA5;
			TxBuffer[1] = 0x5A;
			TxBuffer[2] = 0x20;
			TxBuffer[3] = N_message;
			for (uint8_t n = 0; n < 30; ++n) {
				CheckSum += TxBuffer[n];
			}
			TxBuffer[31] = CheckSum;

			CheckSum = 0;

			Struct2transmit = 0;
			break;
		default:
			Struct2transmit = 0;
			break;
	}

}

void NRF24_Transmit(void){
	NRF24_CheckFlags();
	if(MAX_RT)  NRF24_write(STATUS, 0x70);
	if(TX_FULL) NRF24_FlushTxFIFO();
	if(Cont_TX > 10){
		NRF24_TxBuffer();
		Cont_TX = 0;
		NRF24_FIFO_write(TxBuffer, 32);
		N_message += 1;
		Transmision_Flag = 0;
	}
	switch (Transmision_Flag) {
		case 0:
			NRF24_Enable();
			Transmision_Flag = 1;
			break;
		case 1:
			NRF24_Disable();
			break;
	}
	++Cont_TX;
}


void NRF24_StateMachine(void){
	switch (NRF24_mode){
		case Init:
			NRF24_TxConfiguration();
			NRF24_PowerUp();
			NRF24_ActualConfiguration();
			break;
		case RxMode:
			NRF24_Receive();
			break;
		case TxMode:
			NRF24_Transmit();
			break;
		case PowerSave:
			break;
		default:
			NRF24_init();
	}
}
