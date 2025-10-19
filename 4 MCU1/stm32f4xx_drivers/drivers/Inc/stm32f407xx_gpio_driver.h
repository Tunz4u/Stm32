/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Sep 9, 2025
 *      Author: ADMIN
 */

#ifndef STM32F407XX_GPIO_DRIVER_H_
#define STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"


// configure struct for gpio pin

typedef struct
{
	uint8_t GPIO_PinNumber;     	// posible value from @GPIO_PIN_NUMBER
	uint8_t GPIO_PinMode;			// posible value from @GPIO_PIN_MODE
	uint8_t GPIO_PinSpeed;			// posible value from @GPIO_PIN_SPEED
	uint8_t GPIO_PinPupdControl;	// posible value from @GPIO_PIN_PUPD_CONTROL
	uint8_t GPIO_PinOPType;			// posible value from @GPIO_PIN_OPTYPE
	uint8_t GPIO_PinAltFunMode;		// posible value from @GPIO_PIN_ALTFUN
}GPIO_PinConFig_t;



/*
 handle struct for GPIO
*/

typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConFig_t GPIO_PinConfig;
}GPIO_Handle_t;



/*
 * @GPIO_PIN_NUMBER
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15




/*
 * @GPIO_PIN_MODE
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALFN 		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT 	4
#define GPIO_MODE_IT_RT 	5
#define GPIO_MODE_IT_RFT 	6

/*
 * GPIO pin possible output types
 */

#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1

/*
 * GPIO pin possible output speeds
 */

#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

/*
 * @GPIO_PIN_PUPD_CONTROL
 * GPIO pin pull up AND pull down configuration macros
 */
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

/*
 * Peripheral Clock setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi);


/*
 * Init and De-Init
 */


void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


/*
 * Data Read and Write
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);


/*
 * IRQ Configuration and ISR Handling
 */

void GPIO_IRQInterruptConfig (uint8_t IRQNumber,uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriorit);
void GPIO_IRQHandling(uint8_t PinNumber);






#endif /* STM32F407XX_GPIO_DRIVER_H_ */
