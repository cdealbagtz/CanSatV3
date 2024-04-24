/*
 * BMP280.h
 *
 *  Created on: Apr 23, 2024
 *      Author: cdealba
 */

#ifndef INC_PERIPHERAL_BMP280_H_
#define INC_PERIPHERAL_BMP280_H_

#include "Global/Global_definitions.h"
#include <math.h>

/*!
 * @def 	SPI_BMP280
 * @brief 	Almacena el puntero a la configuración del SPI para el BMP280
 */
#define SPI_BMP280				&hspi2

/*!
 * @def 	BMP280_select()
 * @brief 	Definición para dar un valor de bajo al pin de CSN del NRF24
 */
#define BMP280_select()			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET)

/*!
 * @def 	BMP280_unselect()
 * @brief 	Definición para dar un valor de alto al pin de CSN del NRF24
 */
#define BMP280_unselect()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET)

enum BMP280_memoryMap{
	ID 			= 0xD0,
	reset		= 0xE0,
	status		= 0xF3,
	ctrl_meas 	= 0xF4,
	config      = 0xF5,
	press_msb   = 0xF7,
	press_lsb,
	press_xlsb,
	temp_msb,
	temp_lsb,
	temp_xlsb
};

void BMP280_init(void);
void BMP280_calculate(void);

#endif /* INC_PERIPHERAL_BMP280_H_ */
