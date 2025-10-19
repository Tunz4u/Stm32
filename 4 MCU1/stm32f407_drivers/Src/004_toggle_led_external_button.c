/*
 * 004_toggle_led_external_button.c
 *
 *  Created on: Sep 17, 2025
 *      Author: ADMIN
 */
#include <stdint.h>
#include "stm32f407xx.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define HIGH			1
#define LOW				0
#define BUTTON_PRESS	LOW //default for PD



void delay (void)
{
	for(int i=0;i<500000/2;i++);
}

int main(void)
{
	GPIO_Handle_t GPIOLed;
	GPIOLed.pGPIOx = GPIOD;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOLed.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;
	GPIOLed.GPIO_PinConfig.GPIO_PinOType = GPIO_OPType_PP;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO13;

	GPIO_init(&GPIOLed);



	GPIO_Handle_t GPIOBtn;
	GPIOBtn.pGPIOx = GPIOB;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO1;

	GPIO_init(&GPIOBtn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOBtn.pGPIOx, GPIO_PIN_NO1)== BUTTON_PRESS)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOLed.pGPIOx, GPIO_PIN_NO13);
		}
	}



}

