/*
 * stm32f407xx_gpio_drivers.c
 *
 *  Created on: Sep 17, 2025
 *      Author: ADMIN
 */
#include "stm32f407xx_gpio_drivers.h"

/*****************************************************************
 * @fn          - GPIO_PeriClockControl
 *
 * @brief       - This function enables or disables peripheral
 *                clock for the given GPIO port
 *
 * @param[in]   - Base address of the GPIO peripheral
 * @param[in]   - Macros: Enable or Disable
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIOx_Clock_Control (GPIO_RegDef_t * pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}

	}
}

#define GPIO_BASEADDR_TO_CODE(x)   ( (x == GPIOA) ? 0 : \
                                    (x == GPIOB) ? 1 : \
                                    (x == GPIOC) ? 2 : \
                                    (x == GPIOD) ? 3 : \
                                    (x == GPIOE) ? 4 : \
                                    (x == GPIOF) ? 5 : \
                                    (x == GPIOG) ? 6 : \
                                    (x == GPIOH) ? 7 : \
                                    (x == GPIOI) ? 8 : 0 )

/*****************************************************************
 * @fn          - GPIO_init
 *
 * @brief       - This function init for the given GPIO pin
 *
 * @param[in]   - Base address of the GPIO peripheral
 * @param[in]   - Macros: Enable or Disable
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIO_init(GPIO_Handle_t *pGPIO_handle)
{
	//0 GPIO enable Clock control
	GPIOx_Clock_Control (pGPIO_handle->pGPIOx, ENABLE);


	uint32_t temp=0;
	//1 configure mode
	if(pGPIO_handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		if(pGPIO_handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_INPUT)
		{
			temp = pGPIO_handle->GPIO_PinConfig.GPIO_PinMode
					<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIO_handle->pGPIOx->MODER &= ~(0x3<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber));//clear
			pGPIO_handle->pGPIOx->MODER |= temp;//set
			temp = 0;
		}else if(pGPIO_handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUTPUT)
		{
			temp = pGPIO_handle->GPIO_PinConfig.GPIO_PinMode
					<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIO_handle->pGPIOx->MODER &= ~(0x3<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber));//clear
			pGPIO_handle->pGPIOx->MODER |= temp;//set
			temp = 0;
		}else if (pGPIO_handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_AFT_FUNCTION)
		{
			temp = pGPIO_handle->GPIO_PinConfig.GPIO_PinMode
					<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIO_handle->pGPIOx->MODER &= ~(0x3<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber));//clear
			pGPIO_handle->pGPIOx->MODER |= temp;//set
			temp = 0;
		}else if (pGPIO_handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ANALOG)
		{
			temp = pGPIO_handle->GPIO_PinConfig.GPIO_PinMode
					<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIO_handle->pGPIOx->MODER &= ~(0x3<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber));//clear
			pGPIO_handle->pGPIOx->MODER |= temp;//set
			temp = 0;
		}
	}else
	{
		//1 falling edge , raising edge trigger config

		if(pGPIO_handle->GPIO_PinConfig.GPIO_PinMode  == GPIO_MODE_IT_FT)
		{
			//set exti ftsr
			EXTI->FTSR |= (1<<pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
			//clear exti rtsr
			EXTI->RTSR &= ~(1<<pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
		}else if (pGPIO_handle->GPIO_PinConfig.GPIO_PinMode  == GPIO_MODE_IT_RT)
		{
			//set exti ftsr
			EXTI->RTSR |= (1<<pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
			//clear exti rtsr
			EXTI->FTSR &= ~(1<<pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
		}else if (pGPIO_handle->GPIO_PinConfig.GPIO_PinMode  == GPIO_MODE_IT_RFT)
		{
			//set exti ftsr
			EXTI->FTSR |= (1<<pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
			//set exti rtsr
			EXTI->RTSR |= (1<<pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
		}
		//2 decide port to send interrupt
		uint8_t exticr = pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber/4; // select EXTICR
		uint8_t bitshift = (pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber%4)*4; //shift bit
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[exticr] |= (GPIO_BASEADDR_TO_CODE(pGPIO_handle->pGPIOx))<<bitshift;

		//3 enable interrupt to delivery from peripheral to processor
		EXTI->IMR |= (1<<pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);


	}

	//2 configure speed

	temp = pGPIO_handle->GPIO_PinConfig.GPIO_PinSpeed
			<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_handle->pGPIOx->OSPEEDR &= ~(0x3<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber));//clear
	pGPIO_handle->pGPIOx->OSPEEDR |= temp;//set
	temp = 0;

	//3 pupd control

	temp = pGPIO_handle->GPIO_PinConfig.GPIO_PinPupdControl
				<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_handle->pGPIOx->PUPDR &= ~(0x3<<(2*pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber));//clear
	pGPIO_handle->pGPIOx->PUPDR |= temp;//set
	temp = 0;

	//4 output type

	temp = pGPIO_handle->GPIO_PinConfig.GPIO_PinOType
					<<(pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_handle->pGPIOx->OTYPER &= ~(0x1<<(pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber));//clear
	pGPIO_handle->pGPIOx->OTYPER |= temp;//set
	temp = 0;

	//5 alternate function
	uint32_t temp1=0;
	uint32_t temp2=0;
	temp1 = pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber/8;		// decide High or Low AF
	temp2 = pGPIO_handle->GPIO_PinConfig.GPIO_PinNumber%8;	// decide which pin

	pGPIO_handle->pGPIOx->AFR[temp1] &= ~(0xF<<(4*temp2));		//clear
	pGPIO_handle->pGPIOx->AFR[temp1] |=
			((pGPIO_handle->GPIO_PinConfig.GPIO_PinAltFunMode)<<(4*temp2)); //set



}


/*****************************************************************
 * @fn          - GPIO_de_init
 *
 * @brief       - This function de init for the given GPIO pin
 *
 * @param[in]   - Base address of the GPIO peripheral
 * @param[in]   - Macros: Enable or Disable
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIO_de_init(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}
/*****************************************************************
 * @fn          - GPIO_ReadFromInputPin
 *
 * @brief       - This function read from given GPIO pin
 *
 * @param[in]   - Base address of the GPIO peripheral
 * @param[in]   - GPIO pin number
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1);
    return value;
}
/*****************************************************************
 * @fn          - GPIO_ReadFromInputPort
 *
 * @brief       - This function read from given GPIO port
 *
 * @param[in]   - Base address of the GPIO peripheral
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
uint32_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint32_t value;
    value = pGPIOx->IDR ;
    return value;
}

/*****************************************************************
 * @fn          - GPIO_WriteToOutputPin
 *
 * @brief       - This function write to given GPIO pin
 *
 * @param[in]   - Base address of the GPIO peripheral
 * @param[in]	- PinNumber
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value)
{
	if(Value == ENABLE)
	{
		pGPIOx->ODR |= (1<<PinNumber);
	}else if (Value == DISABLE)
	{
		pGPIOx->ODR &= ~(1<<PinNumber);
	}
}

/*****************************************************************
 * @fn          - GPIO_WriteToOutputPin
 *
 * @brief       - This function write to given GPIO pin
 *
 * @param[in]   - Base address of the GPIO peripheral
 * @param[in]	- PinNumber
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint32_t Value)
{
	pGPIOx->ODR = Value ;
}
/*****************************************************************
 * @fn          - GPIO_ToogleOutputPin
 *
 * @brief       - This function toogle to given GPIO pin
 *
 * @param[in]   - Base address of the GPIO peripheral
 * @param[in]	- PinNumber
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);
}

/*****************************************************************
 * @fn          - GPIO_IRQ_NVIC_Config
 *
 * @brief       - This function configure Enable/Disable
 * 				  for corressponding IRQ number in vector table
 *
 *
 * @param[in]   - IRQ number
 * @param[in]	- Enable or Disable
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIO_IRQ_NVIC_Config(uint8_t IrqNumber,uint8_t EnorDI)
{
	if(EnorDI ==ENABLE)
	{
		if(IrqNumber <32)
		{
			*NVIC_ISER0 |=(1<< (IrqNumber%32));
		}else if (IrqNumber <=64)
		{
			*NVIC_ISER1 |=(1<< (IrqNumber%32));
		}else if (IrqNumber <=96)
		{
			*NVIC_ISER2 |=(1<< (IrqNumber%32));
		}
	}else
	{
		if(IrqNumber <32)
		{
			*NVIC_ICER0 |=(1<< (IrqNumber%32));
		}else if (IrqNumber <=64)
		{
			*NVIC_ICER1 |=(1<< (IrqNumber%32));
		}else if (IrqNumber <=96)
		{
			*NVIC_ICER2 |=(1<< (IrqNumber%32));
		}
	}

}

/*****************************************************************
 * @fn          - GPIO_IRQ_Prio_Config
 *
 * @brief       - This function configure Priority level
 * 				  for corressponding IRQ number
 *
 *
 * @param[in]   - IRQ number
 * @param[in]	- Priority level
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void GPIO_IRQ_Prio_Config(uint8_t IrqNumber,uint32_t PrioLevel)
{
	uint8_t iprx = IrqNumber/4;
	uint32_t bitshift = (IrqNumber%4)*8 + (8-NUMBER_OF_IMPLEMENT_BIT_PRIO);

	*(NVIC_PR_BASE_ADDR+iprx) |= (PrioLevel <<bitshift);
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear pending of exti
	if(EXTI->PR &(1<<PinNumber))
	{
		EXTI->PR |=(1<<PinNumber);
	}
}
