/*
 * Error.c
 *
 *  Created on: May 2, 2024
 *      Author: Chris
 */

#include "Global/Global_definitions.h"

#include "Peripheral/BMP280.h"
#include "Peripheral/NRF24.h"
#include "Peripheral/mpu6050.h"

extern NRF24_Config_t NRF24_Configurations_Struct;

uint8_t ErrorFlags = 0;

uint8_t BMP280_checkState(void){\
	if(BMP280_read(ID)==0x58){
		return 0b00000001;
	}
	return 0;
}

uint8_t NRF24_checkState(void){
	NRF24_ActualConfiguration();
	if(NRF24_Configurations_Struct.Actual.TX_ADDR[0]==NRF24_Configurations_Struct.Actual.TX_ADDR[4]){
		if(NRF24_Configurations_Struct.Actual.TX_ADDR[0]==0xE7) return 0b00000010;
	}
	return 0;
}

uint8_t mpu6050_checkState(void){
	uint8_t state;
	HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x75, 1, &state, 1, 100);
	if (state == 104) return 0b00000100;
	return 0;
}

void ErrorFlags_check(void){
	uint8_t BMP280_error = BMP280_checkState();
	uint8_t NRF24_error = NRF24_checkState();
	uint8_t mpu6050_error = mpu6050_checkState();
	ErrorFlags = 0;
	ErrorFlags = BMP280_error|NRF24_error|mpu6050_error;
}
