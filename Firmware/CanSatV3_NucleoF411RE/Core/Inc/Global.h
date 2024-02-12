/*
 * Global.h
 *
 *  Created on: Jan 31, 2024
 *      Author: Chris
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stm32f4xx_hal.h"

uint8_t NRF24_TxBuffer[32];

uint8_t NRF24_RxBuffer[32];

typedef union{
	int32_t s32;
	uint8_t bytes[4];
}s32_t;

typedef union{
	uint32_t u32;
	uint8_t bytes[4];
}u32_t;

typedef union{
	int16_t s16;
	uint8_t bytes[2];
}s16_t;

typedef union{
	uint16_t u16;
	uint8_t bytes[2];
}u16_t;



typedef struct{
	uint8_t identificador;
	uint8_t trama;
	s32_t latitud;
	s32_t longitud;
	u16_t altitud;
	u16_t pitch;
	u16_t roll;
	u16_t yaw;
	s16_t vel_x;
	s16_t vel_y;
	s16_t vel_z;
	int8_t temperatura;
	u16_t humedad;
	u16_t presion;
	uint8_t Bateria;
	uint8_t ack;
	uint8_t end;
}cansat_data_t;



#endif /* INC_GLOBAL_H_ */
