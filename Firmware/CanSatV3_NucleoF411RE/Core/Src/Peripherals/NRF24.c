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
	uint8_t TxBuffer=Reg|1<<5;

	CS_Select();
	HAL_SPI_Transmit_DMA(&hspi1, &TxBuffer, 1);
	HAL_SPI_Transmit_DMA(&hspi1, config, size);
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

void nrfsendCmd (uint8_t cmd)
{
	CS_Select();
	HAL_SPI_Transmit_DMA(&hspi1, &cmd, 1);
	CS_UnSelect();
}



void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // TX Done .. Do Something ...
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // TX Done .. Do Something ...
}
