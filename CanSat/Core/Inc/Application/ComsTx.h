/*
 * Coms.h
 *
 *  Created on: May 3, 2024
 *      Author: Chris
 */

#ifndef INC_APPLICATION_COMSTX_H_
#define INC_APPLICATION_COMSTX_H_

#include "Peripheral/NRF24.h"

void Tx_MainFrame(void);
void Tx_SecondaryFrame(void);

enum TelemetryFrames{
	MainFrame,
	SecondaryFrame,
	CommandReplay
};


#endif /* INC_APPLICATION_COMSTX_H_ */
