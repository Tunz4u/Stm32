/*
 * 006spi_testing.c
 *
 *  Created on: Sep 15, 2025
 *      Author: ADMIN
 */
#include "stm32f407xx.h"
#include <string.h>

/*
 * PB14-->SPI2_MISO
 * PB15-->SPI2_MOSI
 * PB13-->SPI2_SCLK
 * PB12-->SPI2_NSS
 * ALT function mode : 5
 */


void SPI2_GPIOInits(void)
{
    GPIO_Handle_t SPIPins;

    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /* SCLK Init */
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&SPIPins);

    /* MOSI Init */
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&SPIPins);

    /* MISO Init */
//    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
//    GPIO_Init(&SPIPins);

    /* NSS Init */
//    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
//    GPIO_Init(&SPIPins);
}

void SPI2_Inits()
{
    SPI_Handle_t SPIHandle;

    SPIHandle.pSPIx = SPI2;
    SPIHandle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPIHandle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPIHandle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; //8MHz
    SPIHandle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;
    SPIHandle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPIHandle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPIHandle.SPI_PinConfig.SPI_SSM = SPI_SSM_EN; //SSM Enabled for NSS pin

    SPI_Init(&SPIHandle);
}


int main ()
{
	char user_data[] = "Hello World!";

	//GPIO behave as SPI
	SPI2_GPIOInits();
	// SPI init
	SPI2_Inits();

	/* Makes NSS sigmal internaly high and avoids MODE error */
	SPI_SSIConfig(SPI2, ENABLE);


	//enable SPI
	SPI_PeripheralControl(SPI2, ENABLE);

	/* Send SPI data */
	SPI_SendData(SPI2, (uint8_t *)user_data, strlen(user_data));

	//confirm SPI not busy
	while (SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

	/* Disable SPI2 peripheral */
	SPI_PeripheralControl(SPI2, DISABLE);

	while(1);

	return 0;
}
