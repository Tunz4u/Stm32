 /*
 * 001ledtoggle.c
 *
 *  Created on: Sep 10, 2025
 *      Author: ADMIN
 */

#include <stdint.h>
#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i= 0;i<500000;i++);
}

int main (void)
{
	GPIO_Handler_t GpioLed;
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GpioLed.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GpioLed.pGPIOx, ENABLE);

	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin( GpioLed.pGPIOx ,GpioLed.GPIO_PinConfig.GPIO_PinNumber);
		delay();
	}

	return 0;
}
