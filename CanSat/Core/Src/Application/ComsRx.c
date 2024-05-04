/*
 * ComsRx.c
 *
 *  Created on: May 4, 2024
 *      Author: Chris
 */

#include "Application/ComsRx.h"
#include "Application/ComsTx.h"


extern uint8_t RxBuffer[32];




uint8_t RxDecode (void){
	uint8_t RxCheckSum = 0;

	switch (RxBuffer[2]) {
		case Init_Transmision:

			for (uint8_t n = 0; n < 8; ++n) {
				RxCheckSum += RxBuffer[n];
			}
			if(RxCheckSum!=RxBuffer[9])return InvalidChecksum;
			NRF24_TxConfiguration();
			Tx_CommandReplay(Init_Transmision);

			break;

		default:
			return CommandNotFound;
			break;
	}

	return HAL_OK;
}
