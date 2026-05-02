/*
 * it.c
 *
 *  Created on: Nov 30, 2025
 *      Author: ADMIN
 */

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
