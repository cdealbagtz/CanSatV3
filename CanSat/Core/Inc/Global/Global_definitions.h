/*
 * Global_definitions.h
 *
 *  Created on: Apr 9, 2024
 *      Author: cdealba
 */

#ifndef INC_GLOBAL_GLOBAL_DEFINITIONS_H_
#define INC_GLOBAL_GLOBAL_DEFINITIONS_H_

#include "stm32f4xx.h"
#include "spi.h"
#include "dma.h"
#include "gpio.h"
#include "i2c.h"


extern uint8_t test[32];
extern uint8_t PIPE0_Addres[5];
extern uint8_t NRF24_Cannel;

/*!
 * @struct 	auto_pilot_datalink_def
 * @brief	Estructura para los diferentes tipos de mision de AP
 */
typedef struct NRF24_Address_Configurations
{
	uint8_t CONFIG;
	uint8_t EN_AA;
	uint8_t EN_RXADDR;
	uint8_t SETUP_AW;
	uint8_t SETUP_RETR;
	uint8_t RF_CH;
	uint8_t RF_SETUP;
	uint8_t STATUS;
	uint8_t OBSERVE;
	uint8_t CD;
	uint8_t RX_ADDR_P0[5];
	uint8_t RX_ADDR_P1[5];
	uint8_t RX_ADDR_P2;
	uint8_t RX_ADDR_P3;
	uint8_t RX_ADDR_P4;
	uint8_t RX_ADDR_P5;
	uint8_t TX_ADDR[5];
	uint8_t RX_PW_P0;
	uint8_t RX_PW_P1;
	uint8_t RX_PW_P2;
	uint8_t RX_PW_P3;
	uint8_t RX_PW_P4;
	uint8_t RX_PW_P5;
	uint8_t FIFO_STATUS;
	uint8_t DYNPD;
	uint8_t FEATURE;
}NRF24_Address_Configurations_t;



typedef struct NRF24_Config{
	NRF24_Address_Configurations_t Default;
	NRF24_Address_Configurations_t Tx_mode;
	NRF24_Address_Configurations_t Rx_mode;
	NRF24_Address_Configurations_t Actual;
}NRF24_Config_t;

typedef union U16{
	uint16_t data;
	uint8_t  bytes[2];
}U16_t;

typedef union S32{
	int32_t data;
	uint8_t  bytes[4];
}S32_t;

typedef union U32{
	int32_t data;
	uint8_t  bytes[4];
}U32_t;

void ErrorFlags_check(void);

#endif /* INC_GLOBAL_GLOBAL_DEFINITIONS_H_ */
