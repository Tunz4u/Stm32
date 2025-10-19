/*
 * 008_spi_receivedata_arduino.c
 *
 *  Created on: Sep 22, 2025
 *      Author: ADMIN
 */

#include <stdint.h>
#include "stm32f407xx.h"
#include <string.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
/* Command codes */
#define COMMAND_LED_CTRL        0x50
#define COMMAND_SENSOR_READ     0x51
#define COMMAND_LED_READ        0x52
#define COMMAND_PRINT           0x53
#define COMMAND_ID_READ         0x54

#define LED_ON      1
#define LED_OFF     0

/* Analog pins */
#define ANALOG_PIN0     0
#define ANALOG_PIN1     1
#define ANALOG_PIN2     2
#define ANALOG_PIN3     3
#define ANALOG_PIN4     4

/* Arduino LED */
#define LED_PIN         9


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
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;

	SPI2handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; //16/8=2mhz
	SPI2handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPI_PinConfig.SPI_SSM = SPI_SSM_DI;
	SPI2handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;

	SPI_Init(&SPI2handle);

}

void GPIO_ButtonInit(void)
{


	GPIO_Handle_t GPIOBtn;
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO0;

	GPIO_init(&GPIOBtn);
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
	uint8_t dummyRead;


	GPIO_ButtonInit();

	SPI2_GPIOInits();

	SPI2_Inits();

	SPI_SSOEConfig(SPI2,ENABLE);

	while(1)
	{
		while(!GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO0));

		delay();

		SPI_PeripheralControl(SPI2, ENABLE);

		uint8_t commandCode = COMMAND_LED_CTRL;

		//send command to slave
		SPI_SendData(SPI2,&commandCode, 1);

		//clear dummmy byte
		SPI_ReceiveData(SPI2, &dummyRead, 1);

		//send dummy data
		SPI_SendData(SPI2,&dummyWrite, 1);

		//receive ack byte
		uint8_t ackByte;
		SPI_ReceiveData(SPI2, &ackByte, 1);

		uint8_t args[2];
		if(SPI_VerifyResponse(ackByte) )
		{
			args[0] = LED_PIN;
			if(args[1]==LED_ON)
			{
				args[1]=LED_OFF;
			}else
			{
				args[1]=LED_ON;
			}
			SPI_SendData(SPI2, args, 2);
		}

		while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI2, DISABLE);
	}



	return 0;
}
