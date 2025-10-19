/*
 * ds3231.c
 *
 *  Created on: Oct 15, 2025
 *      Author: ADMIN
 */
#include<stdint.h>
#include<string.h>
#include "ds3231.h"

I2C_Handle_t DS3231I2CHandle;

static void DS3231_I2C_GPIO_PinConfig();
static void DS3231_I2C_Config();
static void DS3231_write (uint8_t register_addr,uint8_t value);
static void number_to_string(uint8_t num , char* buf);
static uint8_t convert_Decimal_toBCD(uint8_t num);
static uint8_t convert_BCD_toDecimal(uint8_t num);


// return 0 if init succes
// return 1 if init fail
uint8_t DS3231_init(void)
{
	DS3231_I2C_GPIO_PinConfig();

	DS3231_I2C_Config();

	I2C_PeripheralControl(DS3231I2CHandle.pI2Cx, ENABLE);

	DS3231I2CHandle.pI2Cx->CR1 |= (1<<I2C_CR1_ACK);

	I2C_MasterSendDataDS3231(&DS3231I2CHandle);

	if(DS3231I2CHandle.pI2Cx->SR1&(1<<I2C_SR1_AF))
	{
		return 1;
	}

	return 0;
}



static void DS3231_write (uint8_t register_addr,uint8_t value)
{
	uint8_t buf[2];
	buf[0] = register_addr;
	buf[1] = value;
	I2C_MasterSendData(&DS3231I2CHandle, buf, 2, DS3231_I2C_ADDRESS, I2C_DISABLE_SR);
	while(DS3231I2CHandle.pI2Cx->SR2&(uint8_t)(1<<1)); //check BSY flag in SR2
}

static uint8_t DS3231_read (uint8_t register_addr)
{
	uint8_t data;
	I2C_MasterSendData(&DS3231I2CHandle, &register_addr, 1, DS3231_I2C_ADDRESS, I2C_ENABLE_SR);
	I2C_MasterReceiveData(&DS3231I2CHandle, &data, 1, DS3231_I2C_ADDRESS, I2C_DISABLE_SR);
	while(DS3231I2CHandle.pI2Cx->SR2&(uint8_t)(1<<1)); //check BSY flag in SR2

	return data;
}

static uint8_t convert_Decimal_toBCD(uint8_t num)
{
	uint8_t digit1= num/10;
	digit1 = digit1 <<4;
	num%=10;
	return (num | digit1);
}

static uint8_t convert_BCD_toDecimal(uint8_t num)
{
	uint8_t digit1 = num>>4;
	digit1 *=10;
	num &= (0x0F);
	return (num + digit1);
}

static void DS3231_I2C_GPIO_PinConfig()
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

static void DS3231_I2C_Config()
{
	DS3231I2CHandle.pI2Cx = DS3231_I2C;
	DS3231I2CHandle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
	DS3231I2CHandle.I2C_Config.I2C_SCLSpeed = DS3231_I2C_SPEED;
	DS3231I2CHandle.I2C_Config.I2C_DeviceAddress = 0x68;
	DS3231I2CHandle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C_Init(&DS3231I2CHandle);
}

void ds3231_set_current_time(RTC_time_t *rtc_time)
{
	DS3231_write(DS3231_ADDR_SECOND, convert_Decimal_toBCD(rtc_time->seconds));
	DS3231_write(DS3231_ADDR_MINUTE, convert_Decimal_toBCD(rtc_time->minutes));

	uint8_t hour = convert_Decimal_toBCD(rtc_time->hours);
	if(rtc_time->time_format == TIME_FORMAT_24)
	{
		hour &= ~(1<<6);
	}else
	{
		hour |= (1<<6);
		hour = (rtc_time->time_format == TIME_FORMAT_12_AM) ? hour |(1<<5): hour &~(1<<5);
	}
	DS3231_write(DS3231_ADDR_HOUR, hour);

}
void ds3231_get_current_time(RTC_time_t *rtc_time)
{
	uint8_t hour;
	rtc_time->seconds = convert_BCD_toDecimal(DS3231_read(DS3231_ADDR_SECOND));
	rtc_time->minutes = convert_BCD_toDecimal(DS3231_read(DS3231_ADDR_MINUTE));
	hour = DS3231_read(DS3231_ADDR_HOUR);
	if(hour&(1<<6))
	{
		if(hour&(1<<5))
		{
			rtc_time->time_format = TIME_FORMAT_12_PM;
		}else
		{
			rtc_time->time_format = TIME_FORMAT_12_AM;
		}
		hour &= ~(0x3 << 5);//Clear 6 and 5

	}else
	{
		rtc_time->time_format = TIME_FORMAT_24;
	}

	rtc_time->hours = convert_BCD_toDecimal(hour);
}

void ds3231_set_current_date(RTC_date_t *rtc_date)
{
	DS3231_write(DS3231_ADDR_MONTH, convert_Decimal_toBCD(rtc_date->month) );
	DS3231_write(DS3231_ADDR_YEAR,convert_Decimal_toBCD(rtc_date->year) );
	DS3231_write(DS3231_ADDR_DATE, convert_Decimal_toBCD(rtc_date->date) );
	DS3231_write(DS3231_ADDR_DAY, convert_Decimal_toBCD(rtc_date->day) );
}
void ds3231_get_current_date(RTC_date_t *rtc_date)
{
	rtc_date->day =  convert_BCD_toDecimal(DS3231_read(DS3231_ADDR_DAY));
	rtc_date->date = convert_BCD_toDecimal(DS3231_read(DS3231_ADDR_DATE));
	rtc_date->month = convert_BCD_toDecimal(DS3231_read(DS3231_ADDR_MONTH));
	rtc_date->year = convert_BCD_toDecimal(DS3231_read(DS3231_ADDR_YEAR));

}

static void number_to_string(uint8_t num , char* buf)
{

	if(num < 10){
		buf[0] = '0';
		buf[1] = num+48;
	}else if(num >= 10 && num < 99)
	{
		buf[0] = (num/10) + 48;
		buf[1]= (num % 10) + 48;
	}
}

char * ds3231_get_current_temperature()
{
	uint8_t interger = DS3231_read(DS3231_ADDR_TEMPERATURE_INTEGER);
	uint8_t fraction = DS3231_read(DS3231_ADDR_TEMPERATURE_FRACTION)>>6;
	if(fraction == 0)
	{
		fraction = 0;
	}else if(fraction ==1)
	{
		fraction =25;
	}else if(fraction ==2)
	{
		fraction =50;
	}else if(fraction ==3)
	{
		fraction =75;
	}

	static char temperature[6];

	number_to_string(interger, temperature);
	temperature [2] = ',';

	number_to_string(fraction, &temperature[3]);

	return temperature;
}


void I2C_Bus_Recovery(void)
{
    GPIO_Handle_t pin;
    pin.pGPIOx = GPIOB;
    pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
    pin.GPIO_PinConfig.GPIO_PinOType = GPIO_OPType_OD;
    pin.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD;
    pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

    // SCL = PB6
    pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO6;
    GPIO_init(&pin);
    // SDA = PB9
    pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO9;
    GPIO_init(&pin);

    // Tạo 16 xung clock để slave nhả SDA nếu đang giữ thấp
    for (int i = 0; i < 16; i++) {
        GPIO_ToggleOutputPin(GPIOB, GPIO_PIN_NO6);
        for (volatile int j = 0; j < 1000; j++); // delay nhỏ
    }

    // Kéo SDA lên lại
    GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO9, 1);
}

