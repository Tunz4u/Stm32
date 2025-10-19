/*
 * stm32f407xx_spi_drivers.c
 *
 *  Created on: Sep 20, 2025
 *      Author: ADMIN
 */
#include "stm32f407xx_spi_drivers.h"

/*
 * Helper functions
 */
static void SPI_TXE_InterruptHandle(SPI_Handle_t *pSPIHandle);
static void SPI_RXNE_InterruptHandle(SPI_Handle_t *pSPIHandle);
static void SPI_OVR_ErrInterruptHandle(SPI_Handle_t *pSPIHandle);

/*****************************************************************
 * @fn          - SPI_PeriClockControl
 *
 * @brief       - This function enables or disables peripheral
 *                clock for the given SPI
 *
 * @param[in]   - Base address of the SPIx peripheral
 * @param[in]   - Macros: Enable or Disable
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if (pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}else if (pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}

	}
}


/*****************************************************************
 * @fn          - SPI_Init
 *
 * @brief       - This function init config for peripheral
 *                SPI
 *
 * @param[in]   - SPI_Handle_t
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);

	uint32_t temp=0;
	//Configure SPI_CR1
	//1. device mode
	temp |=(pSPIHandle->SPI_PinConfig.SPI_DeviceMode<<SPI_CR1_MSTR);

	//2. config duplex mode
	if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//clear BIDI
		temp &= ~(1<<SPI_CR1_BIDI_MODE);
	}else if (pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//set BIDI
		temp |= (1<<SPI_CR1_BIDI_MODE);
	}else if (pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY)
	{
		//clear BIDI
		temp &= ~(1<<SPI_CR1_BIDI_MODE);
		// set receive only
		temp |= (1<<SPI_CR1_RX_ONLY);
	}

    /* SPI serial clock speed (baud rate) configuration */
    temp |= pSPIHandle->SPI_PinConfig.SPI_SclkSpeed << SPI_CR1_BR;

    /* DFF configuration */
    temp |= pSPIHandle->SPI_PinConfig.SPI_DFF << SPI_CR1_DFF;

    /* CPOL configuration */
    temp |= pSPIHandle->SPI_PinConfig.SPI_CPOL << SPI_CR1_CPOL;

    /* CPHA configuration */
    temp |= pSPIHandle->SPI_PinConfig.SPI_CPHA << SPI_CR1_CPHA;

    /* SSM configuration */
	temp |= pSPIHandle->SPI_PinConfig.SPI_SSM << SPI_CR1_SSM;

    /* Save temperg in CR1 register */
    pSPIHandle->pSPIx->CR1 = temp;




}

/*****************************************************************
 * @fn          - SPI_DeInit
 *
 * @brief       - This function de - init  for peripheral
 *                SPI
 *
 * @param[in]   - SPI_RegDef_t
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if (pSPIx ==SPI1)
	{
		SPI1_REG_RESET();
	}
	else if(pSPIx ==SPI2)
	{
		SPI2_REG_RESET();
	}
	else if (pSPIx ==SPI3)
	{
		SPI3_REG_RESET();
	}

}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
	    pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else if (EnorDi == DISABLE)
	{
	    pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}

}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi ==ENABLE)
	{
		pSPIx->CR1 |=(1<<SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &=~(1<<SPI_CR1_SSI);
	}
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/*****************************************************************
 * @fn          - SPI_SendData
 *
 * @brief       - This function send data in blockmode  for peripheral
 *                SPI
 *
 * @param[in]   - SPI_RegDef_t
 * @param[in]   - pTxBuffer : data in array form
 * @param[in]   - Length : length of array
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Length)
{
	while (Length > 0)
	{
		while (SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG)== FLAG_RESET);

		if(pSPIx->CR1 & (1<<SPI_CR1_DFF))
		{
			//16 bit
			pSPIx->DR = *(uint16_t *)pTxBuffer;
			Length-=2;
			(uint16_t *)pTxBuffer++;
		}else
		{
			//8 bit
			pSPIx->DR = *pTxBuffer;
			Length--;
			pTxBuffer++;
		}

	}
}


/*****************************************************************
 * @fn          - SPI_ReceiveData
 *
 * @brief       - This function Receive data in blockmode  for peripheral
 *                SPI and Load it into variable name: pRxBuffer ( not real RxBuffer)
 *
 * @param[in]   - SPI_RegDef_t
 * @param[in]   - pTxBuffer : data in array form
 * @param[in]   - Length : length of array
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Length)
{
	{
		while (Length > 0)
		{
			while (SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG)== FLAG_RESET);

			if(pSPIx->CR1 & (1<<SPI_CR1_DFF))
			{
				//16 bit
				*(uint16_t *)pRxBuffer= pSPIx->DR;
				Length-=2;
				(uint16_t *)pRxBuffer++;
			}else
			{
				//8 bit
				*pRxBuffer = pSPIx->DR ;
				Length--;
				pRxBuffer++;
			}

		}
	}
}



/*
 * IRQ Configuration and ISR handling
 */

/*****************************************************************
 * @fn          - SPI_IRQInterruptConfig
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
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDI)
{
	if(EnorDI ==ENABLE)
	{
		if(IRQNumber <32)
		{
			*NVIC_ISER0 |=(1<< (IRQNumber%32));
		}
		else if (IRQNumber <=64)
		{
			*NVIC_ISER1 |=(1<< (IRQNumber%32));
		}
		else if (IRQNumber <=96)
		{
			*NVIC_ISER1 |=(1<< (IRQNumber%32));
		}
	}else
	{
		if(IRQNumber <32)
		{
			*NVIC_ICER0 |=(1<< (IRQNumber%32));
		}
		else if (IRQNumber <=64)
		{
			*NVIC_ICER1 |=(1<< (IRQNumber%32));
		}
		else if (IRQNumber <=96)
		{
			*NVIC_ICER2 |=(1<< (IRQNumber%32));
		}
	}
}
/*****************************************************************
 * @fn          - GPIO_IRQ_Prio_Config
 *
 * @brief       - This function configure Priority level
 * 				  for corressponding IRQ number
 *
 * @param[in]   - IRQ number
 * @param[in]	- Priority level
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber/4;
	uint32_t bitshift = (IRQNumber%4)*8 + (8-NUMBER_OF_IMPLEMENT_BIT_PRIO);

	*(NVIC_PR_BASE_ADDR+iprx) |= (IRQPriority <<bitshift);
}




/*
 * Other peripheral APIs
 */


void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR2 |=(1<<SPI_CR2_SSOE);
	}else
	{
		pSPIx->CR2 &=~(1<<SPI_CR2_SSOE);
	}
}

/*****************************************************************
 * @fn          - SPI_SendDataInterruptMode
 *
 * @brief       - This function save SPI state and trigger Tx interrupt
 *
 * @param[in]   - Pointer to SPI Handle structure
 * @param[in]   - Transmit buffer
 * @param[in]   - Length of transmit buffer
 *
 * @return      - Tx State
 *
 * @Note        - None
 *
 *****************************************************************/
uint8_t SPI_SendDataInterruptMode(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Length)
{
    uint8_t state = pSPIHandle->TxState;

    if(state != SPI_BUSY_IN_TX)
    {
        /* Save Tx buffer address and length information in global variables */
        pSPIHandle->pTxBuffer = pTxBuffer;
        pSPIHandle->TxLen = Length;

        /* Mark SPI state as busy so that no other code can take over SPI peripheral until transmission is over */
        pSPIHandle->TxState = SPI_BUSY_IN_TX;

        /* Enable TXEIE control bit to get interrupt whenever TXE flag is set in SR */
        pSPIHandle->pSPIx->CR2 |=(1 << SPI_CR2_TXEIE);
    }
    /* DBG->Data transmission*/
    return state;
}


/*****************************************************************
 * @fn          - SPI_ReceiveDataInterruptMode
 *
 * @brief       - This function save SPI state and trigger Rx interrupt
 *
 * @param[in]   - Pointer to SPI Handle structure
 * @param[in]   - Transmit buffer
 * @param[in]   - Length of transmit buffer
 *
 * @return      - Rx State
 *
 * @Note        - None
 *
 *****************************************************************/
uint8_t SPI_ReceiveDataInterruptMode(SPI_Handle_t *pSPIHandle,  uint8_t * pRxBuffer, uint32_t Length)
{
    uint8_t state = pSPIHandle->RxState;

    if(state != SPI_BUSY_IN_RX)
    {
        /* Save Rx buffer address and length information in global variables */
        pSPIHandle->pRxBuffer = pRxBuffer;
        pSPIHandle->RxLen = Length;

        /* Mark SPI state as busy so that no other code can take over SPI peripheral until transmission is over */
        pSPIHandle->RxState = SPI_BUSY_IN_RX;

        /* Enable RXNEIE control bit to get interrupt whenever RXE flag is set in SR */
        pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
    }

    return state;
}


/*****************************************************************
 * @fn          - SPI_IRQHandling
 *
 * @brief       - This function handle whenever interrupt trigger by SPI
 * 				  Decide what cause interrupt , base on that to handle
 * 				  what kind of SPI interrupt
 *
 *
 * @param[in]   - Pointer to SPI Handle structure
 *
 * @return      - Rx State
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	uint8_t temp1,temp2;

	//first check TXE
	temp1 = pHandle->pSPIx->SR&(1<<SPI_SR_TXE);
	temp2 = pHandle->pSPIx->CR2&(1<<SPI_CR2_TXEIE);
	if(temp1 && temp2)
	{
		//handle TXE
		SPI_TXE_InterruptHandle(pHandle);
	}



	//second check RXNE
	temp1 = pHandle->pSPIx->SR&(1<<SPI_SR_RXNE);
	temp2 = pHandle->pSPIx->CR2&(1<<SPI_CR2_RXNEIE);
	if(temp1 && temp2)
	{
		//handle RXNE
		SPI_RXNE_InterruptHandle(pHandle);
	}



	//first check  OVR flag
	temp1 = pHandle->pSPIx->SR&(1<<SPI_SR_OVR);
	temp2 = pHandle->pSPIx->CR2&(1<<SPI_CR2_ERRIE);
	if(temp1 && temp2)
	{
		//handle OVR
		SPI_OVR_ErrInterruptHandle(pHandle);
	}


}

static void SPI_TXE_InterruptHandle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_DFF))
	{
		//16 bit
		pSPIHandle->pSPIx->DR = *(uint16_t *)(pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen-=2;
		(uint16_t *)pSPIHandle->pTxBuffer++;
	}else
	{
		//8 bit
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
		pSPIHandle->TxLen--;
		pSPIHandle->pTxBuffer++;
	}

	if(!pSPIHandle->TxLen)
	{
		// If Transmission is done, turn of interrupt by TxBuffer
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT );
	}

}


void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1<<SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxState = SPI_READY;
	pSPIHandle->TxLen = 0;
}





static void SPI_RXNE_InterruptHandle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_DFF))
	{
		//16 bit
		*(uint16_t *)(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen-=2;
		(uint16_t *)pSPIHandle->pRxBuffer++;
	}else
	{
		//8 bit
		*pSPIHandle->pRxBuffer = pSPIHandle->pSPIx->DR ;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer++;
	}
	if(!pSPIHandle->RxLen)
	{
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT );
	}
}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1<<SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxState = SPI_READY;
	pSPIHandle->RxLen = 0;
}




static void SPI_OVR_ErrInterruptHandle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	(void)temp;
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);
}





__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent)
{

}


void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;

	temp = pSPIx->DR;
	temp = pSPIx->SR;

	(void)temp;
}




