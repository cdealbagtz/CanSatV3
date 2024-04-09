/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Global/Task_schedule.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Task10msHandle;
osThreadId Task100msHandle;
osThreadId Task1000msHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Task_10ms(void const * argument);
void Task_100ms(void const * argument);
void Task_1000ms(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task10ms */
  osThreadDef(Task10ms, Task_10ms, osPriorityNormal, 0, 128);
  Task10msHandle = osThreadCreate(osThread(Task10ms), NULL);

  /* definition and creation of Task100ms */
  osThreadDef(Task100ms, Task_100ms, osPriorityNormal, 0, 128);
  Task100msHandle = osThreadCreate(osThread(Task100ms), NULL);

  /* definition and creation of Task1000ms */
  osThreadDef(Task1000ms, Task_1000ms, osPriorityIdle, 0, 128);
  Task1000msHandle = osThreadCreate(osThread(Task1000ms), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Task_10ms */
/**
  * @brief  Function implementing the Task10ms thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_10ms */
void Task_10ms(void const * argument)
{
  /* USER CODE BEGIN Task_10ms */
	task_init_10ms();
  /* Infinite loop */
  for(;;)
  {
	task_10ms();
    osDelay(10);
  }
  /* USER CODE END Task_10ms */
}

/* USER CODE BEGIN Header_Task_100ms */
/**
* @brief Function implementing the Task100ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_100ms */
void Task_100ms(void const * argument)
{
  /* USER CODE BEGIN Task_100ms */
	task_init_100ms();
  /* Infinite loop */
  for(;;)
  {
	task_100ms();
    osDelay(100);
  }
  /* USER CODE END Task_100ms */
}

/* USER CODE BEGIN Header_Task_1000ms */
/**
* @brief Function implementing the Task1000ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_1000ms */
void Task_1000ms(void const * argument)
{
  /* USER CODE BEGIN Task_1000ms */
	task_init_1000ms();
  /* Infinite loop */
  for(;;)
  {
	task_1000ms();
    osDelay(1000);
  }
  /* USER CODE END Task_1000ms */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
