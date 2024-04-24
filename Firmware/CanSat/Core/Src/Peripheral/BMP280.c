/*
 * BMP280.c
 *
 *  Created on: Apr 23, 2024
 *      Author: cdealba
 */


#include "Peripheral/BMP280.h"

uint8_t BMP280_ID;
uint8_t BMP280_measuring;
uint8_t BMP280_im_update;

void BMP280_write(uint8_t Address, uint8_t Data){
	BMP280_select();
	Address &= 0x7F;
	HAL_SPI_Transmit(SPI_BMP280, &Address, 1, 100);
	HAL_SPI_Transmit(SPI_BMP280, &Data, 1, 100);

	BMP280_unselect();
}

uint8_t BMP280_read(uint8_t Address){
	uint8_t Buffer = (Address|0x80);
	BMP280_select();
	HAL_SPI_Transmit(SPI_BMP280, &Buffer, 1, 100);
	HAL_SPI_Receive(SPI_BMP280, &Buffer, 1, 100);
	BMP280_unselect();

	return Buffer;
}

void BMP280_config(void){
	BMP280_write(ctrl_meas, 0x57);
	BMP280_write(config, 0x10);
}

void BMP280_reset(void){
	BMP280_write(reset, 0xB6);
}

void BMP280_flags(void){
	uint8_t Buffer   = BMP280_read(status);
	BMP280_im_update = (Buffer&0x01);
	BMP280_measuring = (Buffer&0x08)>>3;
}

void BMP280_init(void){
	BMP280_unselect();
	BMP280_config();
	BMP280_ID = BMP280_read(ctrl_meas);
	BMP280_ID = BMP280_read(config);
}
