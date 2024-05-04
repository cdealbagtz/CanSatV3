/*
 * ComsRx.h
 *
 *  Created on: May 4, 2024
 *      Author: Chris
 */

#ifndef INC_APPLICATION_COMSRX_H_
#define INC_APPLICATION_COMSRX_H_

#include "Global/Global_definitions.h"

enum Commands{
	Init_Transmision = 0x01,
	InvalidChecksum  = 0xEF,
	CommandNotFound  = 0xFF
};

extern void NRF24_TxConfiguration(void);

uint8_t RxDecode (void);


#endif /* INC_APPLICATION_COMSRX_H_ */
