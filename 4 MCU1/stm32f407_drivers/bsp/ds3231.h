/*
 * ds3231.h
 *
 *  Created on: Oct 15, 2025
 *      Author: ADMIN
 */

#ifndef DS3231_H_
#define DS3231_H_


#include "stm32f407xx.h"

/*Application configurable items */
#define DS3231_I2C  			I2C1
#define DS3231_I2C_GPIO_PORT    GPIOB
#define DS3231_I2C_SDA_PIN 		GPIO_PIN_NO9
#define DS3231_I2C_SCL_PIN 		GPIO_PIN_NO6
#define DS3231_I2C_SPEED 		I2C_SCL_SPEED_SM
#define DS3231_I2C_PUPD			GPIO_PU

//Register address
#define DS3231_ADDR_SECOND		0x00
#define DS3231_ADDR_MINUTE		0x01
#define DS3231_ADDR_HOUR		0x02
#define DS3231_ADDR_DAY			0x03		//WEEK
#define DS3231_ADDR_DATE		0x04
#define DS3231_ADDR_MONTH		0x05
#define DS3231_ADDR_YEAR		0x06
#define DS3231_ADDR_TEMPERATURE_INTEGER		0x11
#define DS3231_ADDR_TEMPERATURE_FRACTION	0x12

//time format
#define	TIME_FORMAT_12_AM	0
#define	TIME_FORMAT_12_PM	1
#define	TIME_FORMAT_24		2

#define DS3231_I2C_ADDRESS	0x68

#define SUNDAY  	1;
#define MONDAY  	2;
#define TUESDAY  	3;
#define WEDNESDAY   4;
#define THURSDAY  	5;
#define FRIDAY  	6;
#define SATURDAY  	7;
typedef struct
{
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t day;
}RTC_date_t;


typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t time_format;
}RTC_time_t;



//Function prototypes

uint8_t DS3231_init(void);

void ds3231_set_current_time(RTC_time_t *);
void ds3231_get_current_time(RTC_time_t *);

void ds3231_set_current_date(RTC_date_t *);
void ds3231_get_current_date(RTC_date_t *);

char * ds3231_get_current_temperature();


#endif /* DS3231_H_ */
