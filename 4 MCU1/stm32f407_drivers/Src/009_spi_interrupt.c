/*
 * 009_spi)_interrupt.c
 *
 *  Created on: Sep 23, 2025
 *      Author: ADMIN
 */

#include <stdint.h>
#include "stm32f407xx.h"
#include <string.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif




#define MAX_LEN 500

SPI_Handle_t SPI2handle;

__vo uint8_t StartSpiInterrupt =0 ;

__vo uint8_t rcvStop = 0;

__vo char ReadByte ;

char RcvBuff [MAX_LEN];

void delay (void)
{
	for(int i=0;i<500000/2;i++);
}

/*
 * PB14--->SPI2_MISO
 * PB15--->SPI2_MOSI
 * PB13--->SPI2_SCLK
 * PB12--->SPI2_NSS
 * ALT function mode : 5
 */

void SPI2_GPIOInits(void)
{

	GPIO_Handle_t SPIPins;




	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AFT_FUNCTION;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	SPIPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU;
	SPIPins.GPIO_PinConfig.GPIO_PinOType = GPIO_OPType_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AFT_5;

	//Sclk
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO13;
	GPIO_init(&SPIPins);
	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO15;
	GPIO_init(&SPIPins);
	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO14;
	GPIO_init(&SPIPins);
	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO12;
	GPIO_init(&SPIPins);

}


void SPI2_Inits(void)
{


	SPI2handle.pSPIx = SPI2;

	SPI2handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32; //16/8=2mhz
	SPI2handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPI_PinConfig.SPI_SSM = SPI_SSM_DI;
	SPI2handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.TxState = SPI_READY;
	SPI2handle.RxState = SPI_READY;



	SPI_Init(&SPI2handle);

}

void Slave_GPIOInit(void)
{


	GPIO_Handle_t Slave;

	memset(&Slave,0,sizeof(Slave));

	Slave.pGPIOx = GPIOD;
	Slave.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	Slave.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	Slave.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU;
	Slave.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO6;

	GPIO_IRQ_Prio_Config(IRQ_NO_EXTI9_5,NVIC_IRQ_PRIO_15);
	GPIO_IRQ_NVIC_Config(IRQ_NO_EXTI9_5,ENABLE);


	GPIO_init(&Slave);
}

uint8_t SPI_VerifyResponse(uint8_t ackByte)
{
    if(ackByte == (uint8_t)0xF5)
    {
        return 1;
    }

    return 0;
}

int main(void)
{
	uint8_t dummyWrite = 0xFF;

	Slave_GPIOInit();

	SPI2_GPIOInits();

	SPI2_Inits();

	SPI_SSOEConfig(SPI2,ENABLE);

	SPI_IRQInterruptConfig(IRQ_NO_SPI2,ENABLE);

	while(1)
	{
		while(!StartSpiInterrupt);

		delay();

		GPIO_IRQ_NVIC_Config(IRQ_NO_EXTI9_5, DISABLE);

		SPI_PeripheralControl(SPI2, ENABLE);

		while (!rcvStop)
		{

			while(SPI_SendDataInterruptMode(&SPI2handle,&dummyWrite,1)==SPI_BUSY_IN_TX) ;
			while(SPI_ReceiveDataInterruptMode(&SPI2handle,&ReadByte,1)==SPI_BUSY_IN_RX);
		}

		while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI2, DISABLE);

		printf("Receive : %s\n",RcvBuff);

		StartSpiInterrupt=0;

		rcvStop=0;

		GPIO_IRQ_NVIC_Config(IRQ_NO_EXTI9_5, ENABLE);

	}



	return 0;
}

void SPI2_IRQHandler()
{
	SPI_IRQHandling(&SPI2handle);
}

//clear pending bit
// escape from gpio hang
void EXTI9_5_IRQHandler()
{
	GPIO_IRQHandling(GPIO_PIN_NO6);
	StartSpiInterrupt =1;
}

//to Read Data from ReadByte to RcvBuff
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent)
{
	static uint8_t i=0;

	if(AppEvent == SPI_EVENT_RX_CMPLT )
	{
		RcvBuff[i++] = ReadByte;
		if(ReadByte =='\0'||i==MAX_LEN)
		{
			RcvBuff[i-1]='\0';
			rcvStop =1;
			i=0;
		}
	}
}
