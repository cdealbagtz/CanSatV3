/*
 * Task_schedule.h
 *
 *  Created on: Apr 9, 2024
 *      Author: cdealba
 */

#ifndef INC_GLOBAL_TASK_SCHEDULE_H_
#define INC_GLOBAL_TASK_SCHEDULE_H_

#include "Peripheral/NRF24.h"

void task_init_10ms(void);
void task_10ms(void);

void task_init_100ms(void);
void task_100ms(void);

void task_init_1000ms(void);
void task_1000ms(void);



#endif /* INC_GLOBAL_TASK_SCHEDULE_H_ */
