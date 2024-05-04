/*
 * Coms.c
 *
 *  Created on: May 3, 2024
 *      Author: Chris
 */


#include <Application/ComsTx.h>
#include "Peripheral/mpu6050.h"


extern S32_t Temperature, Altitud;
extern U32_t Presure;
extern uint8_t ErrorFlags;
extern MPU6050_t MPU6050;
extern uint8_t N_message;
extern uint8_t Struct2transmit;

uint8_t CheckSum = 0;
S32_t AngleX, AngleY;

extern uint8_t TxBuffer[32];
extern uint8_t RxBuffer[32];

void Tx_MainFrame(void){
	AngleX.data =  (int32_t)(MPU6050.KalmanAngleX * 100);
	AngleY.data =  (int32_t)(MPU6050.KalmanAngleY * 100);

	TxBuffer[0]  = 0xA5;
	TxBuffer[1]  = 0x5A;
	TxBuffer[2]  = 0x10;
	TxBuffer[3]  = N_message;

	TxBuffer[4]  = Temperature.bytes[0];
	TxBuffer[5]  = Temperature.bytes[1];
	TxBuffer[6]  = Temperature.bytes[2];
	TxBuffer[7]  = Temperature.bytes[3];

	TxBuffer[8]  = Altitud.bytes[0];
	TxBuffer[9]  = Altitud.bytes[1];
	TxBuffer[10] = Altitud.bytes[2];
	TxBuffer[11] = Altitud.bytes[3];

	TxBuffer[12] = Presure.bytes[0];
	TxBuffer[13] = Presure.bytes[1];
	TxBuffer[14] = Presure.bytes[2];
	TxBuffer[15] = Presure.bytes[3];

	TxBuffer[16] = AngleX.bytes[0];
	TxBuffer[17] = AngleX.bytes[1];
	TxBuffer[18] = AngleX.bytes[2];
	TxBuffer[19] = AngleX.bytes[3];

	TxBuffer[20] = AngleY.bytes[0];
	TxBuffer[21] = AngleY.bytes[1];
	TxBuffer[22] = AngleY.bytes[2];
	TxBuffer[23] = AngleY.bytes[3];

	TxBuffer[24] = 0xFF;
	TxBuffer[25] = 0xFF;
	TxBuffer[26] = 0xFF;
	TxBuffer[27] = 0xFF;

	TxBuffer[28] = 0x00;
	TxBuffer[29] = 0x00;
	TxBuffer[30] = 0x00;

	for (uint8_t n = 0; n < 30; ++n) {
		CheckSum += TxBuffer[n];
	}
	TxBuffer[31] = CheckSum;
	CheckSum = 0;
}

void Tx_SecondaryFrame(void){
	TxBuffer[0] = 0xA5;
	TxBuffer[1] = 0x5A;
	TxBuffer[2] = 0x20;
	TxBuffer[3] = N_message;

	for (uint8_t n = 0; n < 30; ++n) {
		CheckSum += TxBuffer[n];
	}

	TxBuffer[31] = CheckSum;
	CheckSum = 0;
}

void Tx_CommandReplay(uint8_t Replay2Send){
	Struct2transmit = CommandReplay;
	switch (Replay2Send) {
		case 1:

			break;
		default:
			break;
	}
}
