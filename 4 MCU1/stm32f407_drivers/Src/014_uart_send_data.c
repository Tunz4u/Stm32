/*
 * 014_uart_send_data.c
 *
 *  Created on: Oct 12, 2025
 *      Author: ADMIN
 */

#include<stdio.h>
#include<string.h>
#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

USART_Handle_t USART2Handle;


void USART2_GPIOInits(void)
{
	GPIO_Handle_t USART2Pins;

	/*Note : Internal pull-up resistors are used */

	USART2Pins.pGPIOx = GPIOA;
	USART2Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AFT_FUNCTION;
	USART2Pins.GPIO_PinConfig.GPIO_PinOType = GPIO_OPType_PP;
	/*
	 * Note : In the below line use GPIO_NO_PUPD option if you want to use external pullup resistors, then you have to use 3.3K pull up resistors
	 * for both SDA and SCL lines
	 */
	USART2Pins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU;
	USART2Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;
	USART2Pins. GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

	//TX : PA2
	USART2Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO2;
	GPIO_init(&USART2Pins);


	//RX : PA3
	USART2Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO3;
	GPIO_init(&USART2Pins);


}

void USART2_Inits(void)
{
	USART2Handle.pUSARTx = USART2;
	USART2Handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	USART2Handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	USART2Handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	USART2Handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	USART2Handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART2Handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;

	USART_Init(&USART2Handle);

}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;

	GPIO_init(&GPIOBtn);

}

char msg[1024] = "Vu Ho Yen VY...\n";

int main(void)
{


	//button init
	GPIO_ButtonInit();

	//usart2 inits
	USART2_Inits();

	//usart2 pin init
	USART2_GPIOInits();

	//enable peripheral USART
	USART_PeripheralControl(USART2, ENABLE);


	while(1)
	{
		while(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO0)));

		delay();

		USART_SendData(&USART2Handle, (uint8_t *)msg, strlen(msg));

	}

	return 0;

}
