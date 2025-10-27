/*
 * lcd.h
 *
 *  Created on: Oct 17, 2025
 *      Author: ADMIN
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f407xx.h"

/*Application configurable items */
#define LCD_I2C  			I2C1
#define LCD_I2C_GPIO_PORT 	GPIOB
#define LCD_I2C_SDA_PIN 	GPIO_PIN_NO9
#define LCD_I2C_SCL_PIN 	GPIO_PIN_NO6
#define LCD_I2C_SPEED 		I2C_SCL_SPEED_SM
#define LCD_I2C_PUPD		GPIO_PU
#define LCD_I2C_SLAVE_ADDR	0x27

uint8_t LCD_init(void);
void LCD_Scan_I2C_Devices(void);



#endif /* LCD_H_ */
