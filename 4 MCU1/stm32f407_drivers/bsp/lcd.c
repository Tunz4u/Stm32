/*
 * lcd_16x2.c
 *
 *  Created on: Oct 17, 2025
 *      Author: ADMIN
 */
#include "lcd.h"
#include<stdio.h>
#include <string.h>

I2C_Handle_t LCDI2CHandle ;


void LCD_I2C_Config()
{
	LCDI2CHandle.pI2Cx = LCD_I2C;
	LCDI2CHandle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
	LCDI2CHandle.I2C_Config.I2C_SCLSpeed = LCD_I2C_SPEED;
	LCDI2CHandle.I2C_Config.I2C_DeviceAddress = 0x27;
	LCDI2CHandle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C_Init(&LCDI2CHandle);
}

void LCD_I2C_GPIO_PinConfig()
{

	GPIO_Handle_t I2CPins;

	/*Note : Internal pull-up resistors are used */

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AFT_FUNCTION;
	I2CPins.GPIO_PinConfig.GPIO_PinOType = GPIO_OPType_OD;
	/*
	 * Note : In the below line use GPIO_NO_PUPD option if you want to use external pullup resistors, then you have to use 3.3K pull up resistors
	 * for both SDA and SCL lines
	 */
	I2CPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins. GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

	//scl
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO8;
	GPIO_init(&I2CPins);


	//sda
	//Note : since we found a glitch on PB9 , you can also try with PB7
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO9;

	GPIO_init(&I2CPins);

}



uint8_t LCD_init(void)
{
	LCD_I2C_GPIO_PinConfig();

	LCD_I2C_Config();

	I2C_PeripheralControl(LCDI2CHandle.pI2Cx, ENABLE);

	LCDI2CHandle.pI2Cx->CR1 |= (1<<I2C_CR1_ACK);

	uint8_t resetRegister = 0x00;
	I2C_MasterSendData(&LCDI2CHandle,&resetRegister,1,LCD_I2C_SLAVE_ADDR,I2C_DISABLE_SR);


	if(LCDI2CHandle.pI2Cx->SR1&(1<<I2C_SR1_AF))
	{
		return 1;
	}

	return 0;
}
