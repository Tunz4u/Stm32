/*
 * msp.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ADMIN
 */
#include "stm32f4xx_hal.h"




void HAL_UART_MspInit (UART_HandleTypeDef *huart)
{
	/*	Set group priority	*/
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* 	Enable system exception for arm cortex 	*/
	SCB->SHCSR |= 0x7<<16;
	/*	Enable memory management
	 *	bus fault
	 *	usage fault	*/

	/*	Configure priority for system exception	*/
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);



}

