/*
 * 006_gpio_interrupt.c
 *
 *  Created on: Sep 19, 2025
 *      Author: ADMIN
 */



#include <stdint.h>
#include "stm32f407xx.h"
#include <string.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define HIGH			1
#define LOW				0
#define BUTTON_PRESS 	LOW // PU
//HIGH // PD



void delay (void)
{
	for(int i=0;i<500000/2;i++);
}

int main(void)
{
	GPIO_Handle_t GPIOLed,GPIOBtn;

	memset(&GPIOLed,0,sizeof(GPIOLed));
	memset(&GPIOBtn,0,sizeof(GPIOBtn));

	GPIOLed.pGPIOx = GPIOA;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOLed.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;
	GPIOLed.GPIO_PinConfig.GPIO_PinOType = GPIO_OPType_PP;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO10;

	GPIO_init(&GPIOLed);



	GPIOBtn.pGPIOx = GPIOB;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO12;

	GPIO_init(&GPIOBtn);

	GPIO_IRQ_Prio_Config(IRQ_EXTI15_10, NVIC_IRQ_PRIO_15);
	GPIO_IRQ_NVIC_Config(IRQ_EXTI15_10, ENABLE);

	while(1);



	return 0;
}

void EXTI15_10_IRQHandler()
{
	delay();
	GPIO_IRQ_Handler(GPIO_PIN_NO12);
	GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO10);
}


