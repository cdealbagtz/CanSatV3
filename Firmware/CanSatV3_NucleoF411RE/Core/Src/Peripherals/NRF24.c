/*
 * NRF24.c
 *
 *  Created on: Feb 12, 2024
 *      Author: Chris
 */

#include "Peripherals/NRF24.h"

extern SPI_HandleTypeDef hspi1;


//Se definen 2 "funciones" para controlar el pin CSN del NRF24
#define CS_Select() HAL_GPIO_WritePin(CSN_NRF24_GPIO_Port, CSN_NRF24_Pin, GPIO_PIN_RESET)
#define CS_UnSelect() HAL_GPIO_WritePin(CSN_NRF24_GPIO_Port, CSN_NRF24_Pin, GPIO_PIN_SET)

//Se definen 2 "funciones" para controlar el pin CE del NRF24
#define CE_Enable() HAL_GPIO_WritePin(CE_NRF24_GPIO_Port, CE_NRF24_Pin, GPIO_PIN_SET)
#define CE_Disable() HAL_GPIO_WritePin(CE_NRF24_GPIO_Port, CE_NRF24_Pin, GPIO_PIN_RESET)

//Escribir registro
void NRF24_WriteRegister(uint8_t Reg, uint8_t config){
	uint8_t TxBuffer[2];
	TxBuffer[0]=Reg|1<<5;
	TxBuffer[1]= config;

	CS_Select();
	HAL_SPI_Transmit_DMA(&hspi1, TxBuffer, 2);
	CS_UnSelect();
}


void NRF24_WriteMultiRegister(uint8_t Reg, uint8_t *config, uint8_t size){
	Reg=Reg|1<<5;

	CS_Select();
	HAL_SPI_Transmit_DMA(&hspi1, &Reg, 1);
	HAL_SPI_Transmit_DMA(&hspi1, config, size);
	HAL_Delay(1);
	CS_UnSelect();
}

void NRF24_ReadMultiRegister(uint8_t Reg, uint8_t *config, uint8_t size){
	CS_Select();
		HAL_SPI_Transmit_DMA(&hspi1, &Reg, 1);
		HAL_SPI_Receive_DMA(&hspi1, config, size);
		HAL_Delay(1);
	CS_UnSelect();
}

//Leer registro
uint8_t NRF24_ReadRegister(uint8_t Reg){
	uint8_t RxBuffer;
	CS_Select();
	HAL_SPI_Transmit_DMA(&hspi1, &Reg, 1);
	HAL_SPI_Receive_DMA(&hspi1, &RxBuffer, 1);
	CS_UnSelect();
	return RxBuffer;
}

void NRF24_sendCmd (uint8_t cmd)
{
	CS_Select();
	HAL_SPI_Transmit_DMA(&hspi1, &cmd, 1);
	CS_UnSelect();
}

void NRF24_RxConfig(){

	u32_t TxAdress;
	uint8_t ADDR_TxBuffer[5];
	TxAdress.u32 = CanSat_ADDR;

	ADDR_TxBuffer[0]=TxAdress.bytes[3];
	ADDR_TxBuffer[1]=TxAdress.bytes[2];
	ADDR_TxBuffer[2]=TxAdress.bytes[1];
	ADDR_TxBuffer[3]=TxAdress.bytes[0];
	ADDR_TxBuffer[4]=0;

	CE_Disable();

	NRF24_WriteRegister(EN_AA, 0x03);
	NRF24_WriteRegister(EN_RXADDR, 0x03);
	NRF24_WriteRegister(SETUP_AW, 0x02);
	NRF24_WriteRegister(SETUP_RETR, 0x15);
	NRF24_WriteRegister(RF_CH, CanSat_Ch);
	NRF24_WriteRegister(RF_SETUP, 0x0F);
	NRF24_WriteMultiRegister(RX_ADDR_P0, ADDR_TxBuffer, 5);
	NRF24_WriteMultiRegister(TX_ADDR, ADDR_TxBuffer, 5);
	NRF24_WriteRegister(DYNPD, 0x03);
	NRF24_WriteRegister(FEATURE, 0x06);

	NRF24_WriteRegister(CONFIG, 0x6b);

	CE_Enable();
}

void NRF24_ResetConfig(){
	uint8_t ADDR_Buffer[5];

	ADDR_Buffer[0]=0xE7;
	ADDR_Buffer[1]=0xE7;
	ADDR_Buffer[2]=0xE7;
	ADDR_Buffer[3]=0xE7;
	ADDR_Buffer[4]=0xE7;

	CE_Disable();

	NRF24_WriteRegister(EN_AA, 0x3F);
	NRF24_WriteRegister(EN_RXADDR, 0x03);
	NRF24_WriteRegister(SETUP_AW, 0x03);
	NRF24_WriteRegister(SETUP_RETR, 0x03);
	NRF24_WriteRegister(RF_CH, 0x03);
	NRF24_WriteRegister(RF_SETUP, 0x0F);
	NRF24_WriteMultiRegister(RX_ADDR_P0, ADDR_Buffer, 5);
	NRF24_WriteMultiRegister(TX_ADDR, ADDR_Buffer, 5);
	NRF24_WriteRegister(DYNPD, 0x00);
	NRF24_WriteRegister(FEATURE, 0x00);

	NRF24_WriteRegister(CONFIG, 0x08);

	CE_Enable();
}

void NRF24_TxConfig(){

	u32_t TxAdress;
	uint8_t ADDR_TxBuffer[5];
	TxAdress.u32 = CanSat_ADDR;

	ADDR_TxBuffer[0]=TxAdress.bytes[3];
	ADDR_TxBuffer[1]=TxAdress.bytes[2];
	ADDR_TxBuffer[2]=TxAdress.bytes[1];
	ADDR_TxBuffer[3]=TxAdress.bytes[0];
	ADDR_TxBuffer[4]=0;

	CE_Disable();

	NRF24_WriteRegister(EN_AA, 0x03);
	NRF24_WriteRegister(EN_RXADDR, 0x03);
	NRF24_WriteRegister(SETUP_AW, 0x02);
	NRF24_WriteRegister(SETUP_RETR, 0x15);
	NRF24_WriteRegister(RF_CH, CanSat_Ch);
	NRF24_WriteRegister(RF_SETUP, 0x0F);
	NRF24_WriteMultiRegister(RX_ADDR_P0, ADDR_TxBuffer, 5);
	NRF24_WriteMultiRegister(TX_ADDR, ADDR_TxBuffer, 5);
	NRF24_WriteRegister(DYNPD, 0x03);
	NRF24_WriteRegister(FEATURE, 0x06);

	NRF24_WriteRegister(CONFIG, 0x0A);

	CE_Enable();
}

void NRF24_transmit(uint8_t *data){
	uint8_t cmd = W_TX_PAYLOAD;

	CS_Select();
	HAL_SPI_Transmit_DMA(&hspi1,&cmd , 1);
	HAL_SPI_Transmit_DMA(&hspi1, data, 32);
	CS_UnSelect();
}

uint8_t isDataAvailable (int pipenum)
{
	uint8_t status = NRF24_ReadRegister(STATUS);

	if ((status&(1<<6))&&(status&(pipenum<<1)))
	{

		NRF24_WriteRegister(STATUS, (1<<6));

		return 1;
	}

	return 0;
}


void NRF24_Receive (uint8_t *data)
{
	uint8_t cmdtosend = 0;

	// select the device
	CS_Select();

	// payload command
	cmdtosend = R_RX_PAYLOAD;
	HAL_SPI_Transmit_DMA(&hspi1, &cmdtosend, 1);

	// Receive the payload
	HAL_SPI_Receive_DMA(&hspi1, data, 32);

	// Unselect the device
	CS_UnSelect();

	HAL_Delay(1);

	cmdtosend = FLUSH_RX;
	NRF24_sendCmd(cmdtosend);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // TX Done .. Do Something ...
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // RX Done .. Do Something ...
}

