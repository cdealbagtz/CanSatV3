/*
 * Task_schedule.c
 *
 *  Created on: Apr 9, 2024
 *      Author: cdealba
 */

#include "Global/Task_schedule.h"


/**
  * @fn  	task_init_1ms
  * @brief  Inicializaciones para tarea de 1 milisegundo
  */
void task_init_1ms(void){

}

/**
  * @fn  	task_1ms
  * @brief  Ejecucion de tareas de 1 milisegundo
  */
void task_1ms(void){
	NRF24_StateMachine();

}

/**
  * @fn  	task_init_10ms
  * @brief  Inicializaciones para tarea de 10 milisegundos
  */
void task_init_10ms(void){

}

/**
  * @fn  	task_10ms
  * @brief  Ejecucion de tareas de 10 milisegundos
  */
void task_10ms(void){
	MPU6050_calculate();
}

/**
  * @fn  	task_init_100ms
  * @brief  Inicializaciones para tarea de 100 milisegundos
  */
void task_init_100ms(void){

}

/**
  * @fn  	task_100ms
  * @brief  Ejecucion de tareas de 100 milisegundos
  */
void task_100ms(void){
	BMP280_calculate();

}

/**
  * @fn  	task_init_1000ms
  * @brief  Inicializaciones para tarea de 1000 milisegundos
  */
void task_init_1000ms(void){

}

/**
  * @fn  	task_1000ms
  * @brief  Ejecucion de tareas de 1000 milisegundos
  */
void task_1000ms(void){
}
