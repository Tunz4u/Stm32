/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Sep 13, 2025
 *      Author: ADMIN
 */

#include"stm32f407xx_spi_driver.h"


/*****************************************************************
 * @fn          - SPI_PeriClockControl
 *
 * @brief       - This function enables or disables peripheral
 *                clock for the SPIx
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   - Macros: Enable or Disable
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi==ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}
}

/*****************************************************************
 * @fn          - SPI_PeriClockControl
 *
 * @brief       - This function initialize SPI peripheral
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   -
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//first Configure SPI_CR1

	uint32_t tempreg = 0;

	//enable SPI clock

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	//1. device mode

	tempreg |= pSPIHandle->SPI_PinConfig.SPI_DeviceMode<<SPI_CR1_MSTR;

	//2. bus configure

	if ( pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// bidi should be clear
		tempreg &= ~(1<<SPI_CR1_BIDI_MODE);
	}else if( pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// bidi should be set
		tempreg |= (1<<SPI_CR1_BIDI_MODE);
	}else if( pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY)
	{
		// bidi should be clear
		tempreg &= ~(1<<SPI_CR1_BIDI_MODE);
		// receive only should be set
		tempreg |= (1<<SPI_CR1_RX_ONLY);
	}

	//3. configure baud rate
	tempreg |= (pSPIHandle->SPI_PinConfig.SPI_SclkSpeed<SPI_CR1_BR);

	//4. configure data format
	tempreg |= (pSPIHandle->SPI_PinConfig.SPI_DFF<<SPI_CR1_DFF);

	//5. configure clock polarity
	tempreg |= (pSPIHandle->SPI_PinConfig.SPI_CPOL<<SPI_CR1_CPOL);

	//6. configure clock phase
	tempreg |= (pSPIHandle->SPI_PinConfig.SPI_CPHA<<SPI_CR1_CPHA);

	//7. configure Software management
	tempreg |= (pSPIHandle->SPI_PinConfig.SPI_SSM<<SPI_CR1_SSM);

	pSPIHandle->pSPIx->CR1 =tempreg;


}
/*****************************************************************
 * @fn          - SPI_PeriClockControl
 *
 * @brief       - This function de-initialize SPI peripheral
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   -
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx==SPI1)
	{
		SPI1_REG_RESET();
	}else if (pSPIx==SPI2)
	{
		SPI2_REG_RESET();
	}else if (pSPIx==SPI3)
	{
		SPI3_REG_RESET();
	}
}



uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName)
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
 * @brief       - This function de-initialize SPI peripheral
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   -
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Length)
{
	while (Length >0)
	{
		//1 wait until TXE is set
		while (SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);
		//2 check DFF
		if(pSPIx->CR1 &(1<<SPI_CR1_DFF))
		{
			//16 bit DFF
			//1.load data to DR
			pSPIx->DR = *((uint16_t *)pTxBuffer);
			Length-=2;
			(uint16_t *)pTxBuffer++;
		}else
		{
			//8 bit DFF
			pSPIx->DR = *pTxBuffer;
			Length --;
			pTxBuffer++;
		}

	}
}


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi ==  ENABLE)
	{
		pSPIx->CR1|=(1<<SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1&= ~(1<<SPI_CR1_SPE);
	}
}

/*****************************************************************
 * @fn          - SPI_SSIConfig
 *
 * @brief       - This function sets SSI register
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   - Enable or Disable command
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
    }
}

/*****************************************************************
 * @fn          - SPI_SSOEConfig
 *
 * @brief       - This function sets SSEO register
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   - Enable or Disable command
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
    }
    else
    {
        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}

