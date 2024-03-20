/*
 * NRF24L01.c
 *
 *  Created on: Mar 20, 2024
 *      Author: cdealba
 */


#include "NRF24L01.h"
#include "spi.h"
#include "dma.h"

#define NRF24_select() 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)
#define NRF24_unselect()	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_SET)

#define NRF24_enable()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_SET)
#define NRF24_disable()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_RESET)

void WriteRegister(uint8_t Register, uint8_t Data)
{
	uint8_t Data2Transmit[2] = {(Register|W_REGISTER), Data};
	NRF24_select();
	HAL_SPI_Transmit_DMA(&hspi1, Data2Transmit, 2);
	NRF24_unselect();
}

void WriteMultiRegister(uint8_t Register, uint8_t *Data, uint8_t size)
{
	NRF24_select();
	HAL_SPI_Transmit_DMA(&hspi1, &Register, 1);
	HAL_SPI_Transmit_DMA(&hspi1, Data, size);
	NRF24_unselect();
}
uint8_t ReadRegister(uint8_t Register){
	uint8_t DataReceived;
	NRF24_select();
	HAL_SPI_Transmit_DMA(&hspi1, &Register, 1);
	HAL_SPI_Receive_DMA(&hspi1, &DataReceived, 1);
	return DataReceived;
}

void ReadMultiRegister(uint8_t Register, uint8_t *Data, uint8_t size)
{
	NRF24_select();
	HAL_SPI_Transmit_DMA(&hspi1, &Register, 1);
	HAL_SPI_Receive_DMA(&hspi1, Data, size);
	NRF24_unselect();
}

void SendCommand(uint8_t Command){
	NRF24_select();
	HAL_SPI_Transmit_DMA(&hspi1, &Command, 1);
	NRF24_unselect();
}

void NRF24_Init(void)
{
	NRF24_disable();
	WriteRegister(Register, Data);
	NRF24_enable();
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // TX Done .. Do Something ...
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // RX Done .. Do Something ...
}
