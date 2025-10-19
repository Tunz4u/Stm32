/*
 * 003external_button_led.c
 *
 *  Created on: Sep 11, 2025
 *      Author: ADMIN
 */

/*
 *  external button output mode pull down ; internal led and external led
 */



#include <string.h>
#include <stdint.h>
#include "stm32f407xx.h"

#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	for(uint32_t i= 0;i<500000/2;i++);
}

int main (void)
{
	GPIO_Handle_t GpioLed,GPIOBtn ;

	memset(&GpioLed, 0, sizeof(GpioLed));
	memset(&GPIOBtn, 0, sizeof(GPIOBtn));

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GpioLed.pGPIOx, ENABLE);

	GPIO_Init(&GpioLed);




	GPIOBtn.pGPIOx = GPIOD;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOBtn.pGPIOx, ENABLE);

	GPIO_Init(&GPIOBtn);



	while(1)
	{

		if (GPIO_ReadFromInputPin(GPIOBtn.pGPIOx, GPIOBtn.GPIO_PinConfig.GPIO_PinNumber) == BTN_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin( GpioLed.pGPIOx ,GpioLed.GPIO_PinConfig.GPIO_PinNumber);
		}

	}

	return 0;
}


