/*
 * 011_i2c_master_receive.c
 *
 *  Created on: Oct 5, 2025
 *      Author: ADMIN
 */



#include<stdio.h>
#include<string.h>
#include "stm32f407xx.h"

#define MY_ADDR 0x61;

#define SLAVE_ADDR  0x68

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

I2C_Handle_t I2C1Handle;

//some data
uint8_t RcvBuff[32] ;
/*
 * PB6-> SCL
 * PB9 or PB7 -> SDA
 */

void I2C1_GPIOInits(void)
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
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO6;
	GPIO_init(&I2CPins);


	//sda
	//Note : since we found a glitch on PB9 , you can also try with PB7
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO9;

	GPIO_init(&I2CPins);


}

void I2C1_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);

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


int main(void)
{

	uint8_t command,length ;

	GPIO_ButtonInit();

	//i2c pin inits
	I2C1_GPIOInits();

	//i2c peripheral configuration
	I2C1_Inits();

	//enable the i2c peripheral
	I2C_PeripheralControl(I2C1,ENABLE);

	//after enable PE, enable I2C CR1 ACK
	I2C1Handle.pI2Cx->CR1 |= (1<<I2C_CR1_ACK);

	while(1)
	{
		//wait till button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		//send command to get data length
		command = 0x51;
		I2C_MasterSendData(&I2C1Handle,&command,1,SLAVE_ADDR,I2C_ENABLE_SR);
		//get data length from slave
		I2C_MasterReceiveData(&I2C1Handle, &length, 1, SLAVE_ADDR,I2C_ENABLE_SR );

		//send command to tell slave to send data and this master will receive
		command = 0x52;
		I2C_MasterSendData(&I2C1Handle,&command,1,SLAVE_ADDR,I2C_ENABLE_SR);
		//get data length from slave
		I2C_MasterReceiveData(&I2C1Handle, RcvBuff, length, SLAVE_ADDR,I2C_DISABLE_SR );

		printf("receive : %s",RcvBuff);

	}

}
