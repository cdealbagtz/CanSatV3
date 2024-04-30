/*
 * NRF24.h
 *
 *  Created on: Apr 9, 2024
 *      Author: cdealba
 */

#ifndef INC_PERIPHERAL_NRF24_H_
#define INC_PERIPHERAL_NRF24_H_

#include "Global/Global_definitions.h"



/*!
 * @def 	SPI_NRF24
 * @brief 	Almacena el puntero a la configuración del SPI para el NF24
 */
#define SPI_NRF24				&hspi1

/*!
 * @def 	NRF24_select()
 * @brief 	Definición para dar un valor de bajo al pin de CSN del NRF24
 */
#define NRF24_select()			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)

/*!
 * @def 	NRF24_unselect()
 * @brief 	Definición para dar un valor de alto al pin de CSN del NRF24
 */
#define NRF24_unselect()		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)

/*!
 * @def 	NRF24_Enable()
 * @brief 	Definición para dar un valor alto al pin de activación del NRF24
 */
#define NRF24_Enable()			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)

/*!
 * @def 	NRF24_Disable()
 * @brief 	Definición para dar un valor bajo al pin de activación del NRF24
 */
#define NRF24_Disable()			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)



enum NRF24_Commands{
	R_REGISTER				=	0x00,
	W_REGISTER				=	0x20,
	R_RX_PAYLOAD			=	0X61,
	W_TX_PAYLOAD			=	0XA0,
	FLUSH_TX				=	0XE1,
	FLUSH_RX				=	0XE2,
	REUSE_TX_PL				=	0XE3,
	ACTIVATE				=	0X50,
	R_RX_PL_WID				=	0X60,
	W_ACK_PAYLOAD			=	0XA8,
	W_TX_PAYLOAD_NO_ACK		=	0XB0,
	NOP						= 	0XFF
};

enum NRF24_ADDRESS{
	CONFIG					=	0X00,
	EN_AA					=	0X01,
	EN_RXADDR				=	0X02,
	SETUP_AW				=	0X03,
	SETUP_RETR				=	0X04,
	RF_CH					=	0X05,
	RF_SETUP				=	0X06,
	STATUS					=	0X07,
	OBSERVE					=	0X08,
	CD						=	0X09,
	RX_ADDR_P0				=	0X0A,
	RX_ADDR_P1				=	0X0B,
	RX_ADDR_P2				=	0X0C,
	RX_ADDR_P3				=	0X0D,
	RX_ADDR_P4				=	0X0E,
	RX_ADDR_P5				=	0X0F,
	TX_ADDR					=	0X10,
	RX_PW_P0				=	0X11,
	RX_PW_P1				=	0X12,
	RX_PW_P2				=	0X13,
	RX_PW_P3				=	0X14,
	RX_PW_P4				=	0X15,
	RX_PW_P5				=	0X16,
	FIFO_STATUS				=	0X17,
	DYNPD					=	0X1C,
	FEATURE					=	0X1D
};

enum NRF24_modes{
	Init,
	TxMode,
	RxMode,
	PowerSave
};

void NRF24_init(void);

void NRF24_StateMachine(void);

#endif /* INC_PERIPHERAL_NRF24_H_ */
