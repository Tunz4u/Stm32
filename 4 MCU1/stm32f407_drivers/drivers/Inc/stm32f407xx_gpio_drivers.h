/*
 * stm32f407xx_gpio_drivers.h
 *
 *  Created on: Sep 17, 2025
 *      Author: ADMIN
 */

#ifndef STM32F407XX_GPIO_DRIVERS_H_
#define STM32F407XX_GPIO_DRIVERS_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;  		//@posible_PinNumber
	uint8_t GPIO_PinMode;			//@posible_PinMode
	uint8_t GPIO_PinSpeed;			//@posible_PinSpeed
	uint8_t GPIO_PinPupdControl;	//@posible_pupd
	uint8_t GPIO_PinOType;			//@posible_OutputType
	uint8_t GPIO_PinAltFunMode;		//@posible_AltFunctionMode

}GPIO_PinConFig_t;


typedef struct
{
	GPIO_RegDef_t *pGPIOx ;
	GPIO_PinConFig_t GPIO_PinConfig;
}GPIO_Handle_t;


/*
 * @posible_PinNumber
 */
#define GPIO_PIN_NO0	0
#define GPIO_PIN_NO1	1
#define GPIO_PIN_NO2	2
#define GPIO_PIN_NO3	3
#define GPIO_PIN_NO4	4
#define GPIO_PIN_NO5	5
#define GPIO_PIN_NO6	6
#define GPIO_PIN_NO7	7
#define GPIO_PIN_NO8	8
#define GPIO_PIN_NO9	9
#define GPIO_PIN_NO10	10
#define GPIO_PIN_NO11	11
#define GPIO_PIN_NO12	12
#define GPIO_PIN_NO13	13
#define GPIO_PIN_NO14	14
#define GPIO_PIN_NO15	15

/*
 * @posible_PinMode
 */
#define GPIO_MODE_INPUT			0
#define GPIO_MODE_OUTPUT		1
#define GPIO_MODE_AFT_FUNCTION	2
#define GPIO_MODE_ANALOG		3
#define GPIO_MODE_IT_FT			4
#define GPIO_MODE_IT_RT			5
#define GPIO_MODE_IT_RFT		6


/*
 * @posible_PinSpeed
 */
#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MED			1
#define GPIO_SPEED_HIGH			2
#define GPIO_SPEED_VERY_HIGH	3

/*
 * @posible_pupd
 */
#define GPIO_NO_PUPD	0
#define GPIO_PU			1
#define GPIO_PD			2

/*
 * @posible_OutputType
 */
#define GPIO_OPType_PP	0
#define GPIO_OPType_OD	1

/*
 * @posible_AltFunctionMode
 */
#define GPIO_AFT_0 	0
#define GPIO_AFT_1 	1
#define GPIO_AFT_2 	2
#define GPIO_AFT_3 	3
#define GPIO_AFT_4 	4
#define GPIO_AFT_5 	5
#define GPIO_AFT_6 	6
#define GPIO_AFT_7 	7
#define GPIO_AFT_8 	8
#define GPIO_AFT_9 	9
#define GPIO_AFT_10 10
#define GPIO_AFT_11 11
#define GPIO_AFT_12 12
#define GPIO_AFT_13 13
#define GPIO_AFT_14 14
#define GPIO_AFT_15 15

#define NUMBER_OF_IMPLEMENT_BIT_PRIO 4 // specific for mcu stm32f407

/*
 * GPIO clock control
 */
void GPIOx_Clock_Control (GPIO_RegDef_t * pGPIOx, uint8_t EnorDi);

/*
 * GPIO init / de init
 */
void GPIO_init(GPIO_Handle_t  *GPIO_handle);
void GPIO_de_init(GPIO_RegDef_t *pGPIOx);

/*
 * Read from input
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint32_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
/*
 * Write to output
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint32_t Value);
/*
 * Toggle Output Pin
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);


void GPIO_IRQ_NVIC_Config(uint8_t IrqNumber,uint8_t EnorDI);

void GPIO_IRQ_Prio_Config(uint8_t IrqNumber,uint32_t PrioLevel);//@NVIC_Priority_Level

void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* STM32F407XX_GPIO_DRIVERS_H_ */
