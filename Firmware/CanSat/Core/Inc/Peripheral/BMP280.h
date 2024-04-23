/*
 * BMP280.h
 *
 *  Created on: Apr 23, 2024
 *      Author: cdealba
 */

#ifndef INC_PERIPHERAL_BMP280_H_
#define INC_PERIPHERAL_BMP280_H_

#include "Global/Global_definitions.h"

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



#endif /* INC_PERIPHERAL_BMP280_H_ */
