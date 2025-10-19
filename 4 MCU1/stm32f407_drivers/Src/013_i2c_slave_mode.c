/*
 * 013_i2c_slave_mode.c
 *
 *  Created on: Oct 10, 2025
 *      Author: ADMIN
 */



#include<stdio.h>
#include<string.h>
#include "stm32f407xx.h"



#define SLAVE_ADDR  0x68
#define MY_ADDR SLAVE_ADDR

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}


//Flag variable
uint8_t rxComplt = RESET;

I2C_Handle_t I2C1Handle;

//some data
uint8_t TxBuff[32] = "chao";
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



	GPIO_ButtonInit();

	//i2c pin inits
	I2C1_GPIOInits();

	//i2c peripheral configuration
	I2C1_Inits();

	//enable the i2c peripheral
	I2C_PeripheralControl(I2C1,ENABLE);

	I2C1Handle.pI2Cx->CR1 |= (1<<I2C_CR1_ACK);

	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);

	I2C_SlaveEnableDisableCallbackEvents(I2C1Handle.pI2Cx,ENABLE);

	while(1);

}

void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler(void)
{
	I2C_ER_IRQHandling(&I2C1Handle);
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv)
{
	static uint8_t commandCode = 0;
	static  uint8_t Cnt = 0;
	if(AppEv == I2C_EV_DATA_REQ)
	{
		//request for data length
		if(commandCode == 0x51)
		{
			I2C_SlaveSendData(pI2CHandle->pI2Cx, strlen((char*)TxBuff));
		}else if(commandCode ==0x52)
		{
			I2C_SlaveSendData(pI2CHandle->pI2Cx, TxBuff[Cnt++]);
		}

	}else if (AppEv == I2C_EV_DATA_RCV)
	{
		//receive command from master
		commandCode = I2C_SlaveReceiveData(pI2CHandle->pI2Cx);


	}else if (AppEv == I2C_ERROR_AF)
     {
    	 //stop communicate
    	 commandCode =0xff;
    	 Cnt = 0;
     }
}

