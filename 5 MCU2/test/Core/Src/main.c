/*
 * main.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ADMIN
 */


#include "stm32f4xx_hal.h"
#include "main.h"

void SystemClockConfig(void);

UART_HandleTypeDef huart2;
void UART2_Init(void);
void Error_handler();




int main (void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	//HAL_UART_Transmit(huart, pData, Size, Timeout)
	return 0;
}

void SystemClockConfig(void)
{

}


void UART2_Init(void)
{
	huart2.Instance= USART2;


	HAL_UART_Init(&huart2);
}


void Error_handler()
{

}



