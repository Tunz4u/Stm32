/*
 * stm32f407xx.h
 *
 *  Created on: Sep 16, 2025
 *      Author: ADMIN
 */

#ifndef STM32F407XX_H_
#define STM32F407XX_H_
#include <stddef.h>
#include <stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))
#define FLASH_BASEADDR			0x08000000U
#define ROM_BASEADDR			0x1FFF0000U
#define SRAM1_BASEADDR			0x20000000U
#define SRAM2_BASEADDR			0x2001C000U
#define SRAM_BASEADDR			SRAM1_BASEADDR


#define APB1_BASEADDR			0x40000000U
#define APB2_BASEADDR			0x40010000U
#define AHB1_BASEADDR			0x40020000U
#define AHB2_BASEADDR			0x50000000U
#define AHB3_BASEADDR			0xA0000000U


/*
 * GPIO BASE ADDRESS
 */

#define GPIOA_BASEADDR			((AHB1_BASEADDR) + 0x0000)
#define GPIOB_BASEADDR			((AHB1_BASEADDR) + 0x0400)
#define GPIOC_BASEADDR			((AHB1_BASEADDR) + 0x0800)
#define GPIOD_BASEADDR			((AHB1_BASEADDR) + 0x0C00)
#define GPIOE_BASEADDR			((AHB1_BASEADDR) + 0x1000)
#define GPIOF_BASEADDR			((AHB1_BASEADDR) + 0x1400)
#define GPIOG_BASEADDR			((AHB1_BASEADDR) + 0x1800)
#define GPIOH_BASEADDR			((AHB1_BASEADDR) + 0x1C00)
#define GPIOI_BASEADDR			((AHB1_BASEADDR) + 0x2000)
/*
 * GPIO Register
 */
typedef struct
{
	__vo uint32_t MODER;		//OFFSET 0x00
	__vo uint32_t OTYPER;		//OFFSET 0x04
	__vo uint32_t OSPEEDR;		//OFFSET 0x08
	__vo uint32_t PUPDR;		//OFFSET 0x0C
	__vo uint32_t IDR;			//OFFSET 0x10
	__vo uint32_t ODR;			//OFFSET 0x14
	__vo uint32_t BSSR;			//OFFSET 0x18
	__vo uint32_t LCKR;			//OFFSET 0x1C
	__vo uint32_t AFR[2];		//OFFSET 0x20 for AF Low register 	0-7
								//		 0x24 for AF High register	8-15
}GPIO_RegDef_t;


/*
 * GPIO definition
 */
#define GPIOA		((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB		((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC		((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD		((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE		((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF		((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG		((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH		((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define GPIOI		((GPIO_RegDef_t *)GPIOI_BASEADDR)
/*
 * GPIO clock enable
 */
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()		(RCC->AHB1ENR |= (1<<8))

/*
 * GPIO clock disable
 */
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<8))

/*
 * GPIO reset register
 */
#define GPIOA_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<0);	(RCC->AHB1RSTR)&=~(1<<0);} while(0)
#define GPIOB_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<1);	(RCC->AHB1RSTR)&=~(1<<1);} while(0)
#define GPIOC_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<2);	(RCC->AHB1RSTR)&=~(1<<2);} while(0)
#define GPIOD_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<3);	(RCC->AHB1RSTR)&=~(1<<3);} while(0)
#define GPIOE_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<4);	(RCC->AHB1RSTR)&=~(1<<4);} while(0)
#define GPIOF_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<5);	(RCC->AHB1RSTR)&=~(1<<5);} while(0)
#define GPIOG_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<6);	(RCC->AHB1RSTR)&=~(1<<6);} while(0)
#define GPIOH_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<7);	(RCC->AHB1RSTR)&=~(1<<7);} while(0)
#define GPIOI_REG_RESET()	do {(RCC->AHB1RSTR)|=(1<<8);	(RCC->AHB1RSTR)&=~(1<<8);} while(0)

/*
 * IRQ NUMBER
 */
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40












/*
 * RCC base address
 */
#define RCC_BASEADDR			((AHB1_BASEADDR) + 0x3800)

/*
 * RCC Register
 */
typedef struct
{
    __vo uint32_t CR;           /* RCC clock control register,                                  Address offset: 0x00    */
    __vo uint32_t PLLCFGR;      /* RCC PLL configuration register,                              Address offset: 0x04    */
    __vo uint32_t CFGR;         /* RCC clock configuration register,                            Address offset: 0x08    */
    __vo uint32_t CIR;          /* RCC clock interrupt register,                                Address offset: 0x0C    */
    __vo uint32_t AHB1RSTR;     /* RCC AHB1 peripheral reset register,                          Address offset: 0x10    */
    __vo uint32_t AHB2RSTR;     /* RCC AHB2 peripheral reset register,                          Address offset: 0x14    */
    __vo uint32_t AHB3RSTR;     /* RCC AHB3 peripheral reset register,                          Address offset: 0x18    */
    uint32_t      RESERVED0;    /* RCC reserved register,                                       Address offset: 0x1C    */
    __vo uint32_t APB1RSTR;     /* RCC APB1 peripheral reset register,                          Address offset: 0x20 	*/
    __vo uint32_t APB2RSTR;     /* RCC APB2 peripheral reset register,                          Address offset: 0x24    */
    uint32_t      RESERVED1[2]; /* RCC reserved register,                                       Address offset: 0x28-2C */
    __vo uint32_t AHB1ENR;      /* RCC AHB1 peripheral clock enable register,                   Address offset: 0x30    */
    __vo uint32_t AHB2ENR;      /* RCC AHB2 peripheral clock enable register,                   Address offset: 0x34    */
    __vo uint32_t AHB3ENR;      /* RCC AHB3 peripheral clock enable register,                   Address offset: 0x38    */
    uint32_t      RESERVED2;    /* RCC reserved register,                                       Address offset: 0x3C    */
    __vo uint32_t APB1ENR;      /* RCC APB1 peripheral clock enable register,                   Address offset: 0x40    */
    __vo uint32_t APB2ENR;      /* RCC APB2 peripheral clock enable register,                   Address offset: 0x44    */
    uint32_t      RESERVED3[2];	/* RCC reserved register,                                       Address offset: 0x48-4C */
    __vo uint32_t AHB1LPENR;    /* RCC AHB1 peripheral clock enable in low power mode register,	Address offset: 0x50    */
    __vo uint32_t AHB2LPENR;	/* RCC AHB2 peripheral clock enable in low power mode register,	Address offset: 0x54 	*/
    __vo uint32_t AHB3LPENR;	/* RCC AHB3 peripheral clock enable in low power mode register,	Address offset: 0x58 	*/
    uint32_t      RESERVED4;    /* RCC reserved register,                                       Address offset: 0x5C    */
    __vo uint32_t APB1LPENR;    /* RCC APB1 peripheral clock enable in low power mode register,	Address offset: 0x60    */
    __vo uint32_t APB2LPENR;    /* RCC APB2 peripheral clock enable in low power mode register,	Address offset: 0x64    */
    uint32_t      RESERVED5[2]; /* RCC reserved register,                                       Address offset: 0x68-6C */
    __vo uint32_t BDCR;         /* RCC back up domain control register,                         Address offset: 0x70    */
    __vo uint32_t CSR;          /* RCC clock control & status register,                         Address offset: 0x74    */
    uint32_t      RESERVED6[2]; /* RCC reserved register,                                       Address offset: 0x78-7C */
    __vo uint32_t SSCGR;        /* RCC spread spectrum clock generation register,               Address offset: 0x80    */
    __vo uint32_t PLLI2SCFGR;   /* RCC PLLI2S configuration register,                           Address offset: 0x84    */
    __vo uint32_t PLLSAICFGR;   /* RCC PLL configuration register,                              Address offset: 0x88    */
    __vo uint32_t DCKCFGR;      /* RCC dedicated clock configuration register,                  Address offset: 0x8C    */
    __vo uint32_t CKGATENR;     /* RCC clock gated enable register,                             Address offset: 0x90    */
    __vo uint32_t DCKCFGR2;     /* RCC dedicated clock configuration register 2,                Address offset: 0x94    */
}RCC_RegDef_t;

/*
 * RCC definition
 */
#define RCC			((RCC_RegDef_t *)RCC_BASEADDR)


















/*
 * EXTI base address
 */
#define EXTI_BASEADDR			((APB2_BASEADDR) + 0x3C00)
/*
 * EXTI register
 */
typedef struct
{
	__vo uint32_t IMR;				//			Address offset: 0x00
	__vo uint32_t EMR;				//			Address offset: 0x04
	__vo uint32_t RTSR;				//			Address offset: 0x08
	__vo uint32_t FTSR;				//			Address offset: 0x0C
	__vo uint32_t SWIER;			//			Address offset: 0x10
	__vo uint32_t PR;				//			Address offset: 0x14
}EXTI_RegDef_t;

/*
 * EXTI definition
 */
#define EXTI			((EXTI_RegDef_t *)EXTI_BASEADDR)












/*
 * SYSCFG base address
 */
#define SYSCFG_BASEADDR			((APB2_BASEADDR) + 0x3800)

/*
 * SYSCFG register
 */
typedef struct
{
	__vo uint32_t MEMRMP;			//			Address offset: 0x00
	__vo uint32_t PMC;				//			Address offset: 0x04
	__vo uint32_t EXTICR[4];		//			Address offset: 0x08-0x14
	__vo uint32_t RESERVED1[2];		//			Address offset: 0x18-0x1C
	__vo uint32_t CMPCR;			//			Address offset: 0x20
	__vo uint32_t RESERVED2[2];		//			Address offset: 0x24-0x28
	__vo uint32_t CFGR;				//			Address offset: 0x2C
}SYSCFG_RegDef_t;

/*
 * SYSCFG definition
 */
#define SYSCFG		((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)
/*
 * SYSCFG Enable clock
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |=(1<<14))

/*
 * SYSCFG Disable clock
 */
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1<<14))










/*
 * SPI base address
 */
#define SPI1_BASEADDR				((APB2_BASEADDR) + 0x3000)
#define SPI2_BASEADDR				((APB1_BASEADDR) + 0x3800)
#define SPI3_BASEADDR				((APB1_BASEADDR) + 0x3C00)
/*
 * Peripheral  register definition structure for SPI
 */
typedef struct
{
	__vo uint32_t CR1;				//			Address offset: 0x00
	__vo uint32_t CR2;				//			Address offset: 0x04
	__vo uint32_t SR;				//			Address offset: 0x08
	__vo uint32_t DR;				//			Address offset: 0x0C
	__vo uint32_t CRCPR;			//			Address offset: 0x10
	__vo uint32_t RXCRCR;			//			Address offset: 0x14
	__vo uint32_t TXCRCR;			//			Address offset: 0x18
	__vo uint32_t I2SCFGR;			//			Address offset: 0x1C
	__vo uint32_t I2SPR;			//			Address offset: 0x20
}SPI_RegDef_t;

/*
 * SPI regdef
 */
#define SPI1		((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2		((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3		((SPI_RegDef_t *)SPI3_BASEADDR)


//ENABLE CLOCK FOR SPIx MACROS
#define SPI1_PCLK_EN()		( RCC->APB2ENR |= (1<<12) )
#define SPI2_PCLK_EN()		( RCC->APB1ENR |= (1<<14) )
#define SPI3_PCLK_EN()		( RCC->APB1ENR |= (1<<15) )


//DISABLE CLOCK FOR SPIx MACROS
#define SPI1_PCLK_DI()		( RCC->APB2ENR &= ~(1<<12) )
#define SPI2_PCLK_DI()		( RCC->APB1ENR &= ~(1<<14) )
#define SPI3_PCLK_DI()		( RCC->APB1ENR &= ~(1<<15) )

//RESET SPI BY RCC
#define SPI1_REG_RESET()	do {(RCC->APB2RSTR |= (1<<12)); (RCC->AHB1RSTR &= ~(1<<12));}while(0)
#define SPI2_REG_RESET()	do {(RCC->APB1RSTR |= (1<<14)); (RCC->AHB1RSTR &= ~(1<<14));}while(0)
#define SPI3_REG_RESET()	do {(RCC->APB1RSTR |= (1<<15)); (RCC->AHB1RSTR &= ~(1<<15));}while(0)
/******************************************************************************************
 *			Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR          3
#define SPI_CR1_SPE         6
#define SPI_CR1_LSB_FIRST   7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RX_ONLY     10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRC_NEXT    12
#define SPI_CR1_CRC_EN      13
#define SPI_CR1_BIDI_OE     14
#define SPI_CR1_BIDI_MODE   15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN     0
#define SPI_CR2_TXDMAEN     1
#define SPI_CR2_SSOE        2
#define SPI_CR2_FRF         4
#define SPI_CR2_ERRIE       5
#define SPI_CR2_RXNEIE      6
#define SPI_CR2_TXEIE       7

/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRC_ERR      4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8

/*
 * IRQ NUMBER for SPI peripheral
 */
#define IRQ_NO_SPI1		35
#define IRQ_NO_SPI2		36
#define IRQ_NO_SPI3		51
#define IRQ_NO_SPI4		84














/*
 * I2C base address
 */
#define I2C1_BASEADDR				((APB1_BASEADDR) + 0x5400)
#define I2C2_BASEADDR				((APB1_BASEADDR) + 0x5400)
#define I2C3_BASEADDR				((APB1_BASEADDR) + 0x5C00)
/*
 * Peripheral  register definition structure for I2C
 */
typedef struct
{
	__vo uint32_t CR1;				//			Address offset: 0x00
	__vo uint32_t CR2;				//			Address offset: 0x04
	__vo uint32_t OAR1;				//			Address offset: 0x08
	__vo uint32_t OAR2;				//			Address offset: 0x0C
	__vo uint32_t DR;			//			Address offset: 0x10
	__vo uint32_t SR1;			//			Address offset: 0x14
	__vo uint32_t SR2;			//			Address offset: 0x18
	__vo uint32_t CCR;			//			Address offset: 0x1C
	__vo uint32_t TRISE;			//			Address offset: 0x20
	__vo uint32_t FLTR;			//			Address offset: 0x24
}I2C_RegDef_t;

/*
 * I2C regdef
 */
#define I2C1		((I2C_RegDef_t *)I2C1_BASEADDR)
#define I2C2		((I2C_RegDef_t *)I2C2_BASEADDR)
#define I2C3		((I2C_RegDef_t *)I2C3_BASEADDR)


//ENABLE CLOCK FOR I2Cx MACROS
#define I2C1_PCLK_EN()		( RCC->APB1ENR |= (1<<21) )
#define I2C2_PCLK_EN()		( RCC->APB1ENR |= (1<<22) )
#define I2C3_PCLK_EN()		( RCC->APB1ENR |= (1<<23) )


//DISABLE CLOCK FOR I2Cx MACROS
#define I2C1_PCLK_DI()		( RCC->APB2ENR &= ~(1<<21) )
#define I2C2_PCLK_DI()		( RCC->APB1ENR &= ~(1<<22) )
#define I2C3_PCLK_DI()		( RCC->APB1ENR &= ~(1<<23) )

//RESET SPI BY RCC
#define I2C1_REG_RESET()	do {(RCC->APB1RSTR |= (1<<21)); (RCC->AHB1RSTR &= ~(1<<21));}while(0)
#define I2C2_REG_RESET()	do {(RCC->APB1RSTR |= (1<<22)); (RCC->AHB1RSTR &= ~(1<<22));}while(0)
#define I2C3_REG_RESET()	do {(RCC->APB1RSTR |= (1<<23)); (RCC->AHB1RSTR &= ~(1<<23));}while(0)
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE          0
#define I2C_CR1_SMBUS       1
#define I2C_CR1_SMBTYPE     3
#define I2C_CR1_ENARP       4
#define I2C_CR1_ENPEC       5
#define I2C_CR1_ENGC        6
#define I2C_CR1_NOSTRECH    7
#define I2C_CR1_START       8
#define I2C_CR1_STOP        9
#define I2C_CR1_ACK         10
#define I2C_CR1_POS         11
#define I2C_CR1_PEC         12
#define I2C_CR1_ALERT       13
#define I2C_CR1_RESET       15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ        0
#define I2C_CR2_ITERREN     8
#define I2C_CR2_ITEVTEN     9
#define I2C_CR2_ITBUFEN     10
#define I2C_CR2_DMAEN       11
#define I2C_CR2_LAST        12

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0       0
#define I2C_OAR1_ADD7_1     1
#define I2C_OAR1_ADD9_8     8
#define I2C_OAR1_ADDMODE    15

/*
 * Bit position definitions I2C_OAR2
 */
#define I2C_OAR2_ENDUAL     0
#define I2C_OAR2_ADD2       1

/*
 * Bit position definitions I2C_SR1
 */
#define I2C_SR1_SB          0
#define I2C_SR1_ADDR        1
#define I2C_SR1_BTF         2
#define I2C_SR1_ADD10       3
#define I2C_SR1_STOPF       4
#define I2C_SR1_RXNE        6
#define I2C_SR1_TXE         7
#define I2C_SR1_BERR        8
#define I2C_SR1_ARLO        9
#define I2C_SR1_AF          10
#define I2C_SR1_OVR         11
#define I2C_SR1_PECERR      12
#define I2C_SR1_TIMEOUT     14
#define I2C_SR1_SMBALERT    15

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL         0
#define I2C_SR2_BUSY        1
#define I2C_SR2_TRA         2
#define I2C_SR2_GENCALL     4
#define I2C_SR2_SMBDEFAULT  5
#define I2C_SR2_SMBHOST     6
#define I2C_SR2_DUALF       7
#define I2C_SR2_PEC         8

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 		0
#define I2C_CCR_DUTY 		14
#define I2C_CCR_FS  		15


/*
 * IRQ NUMBER for I2C peripheral
 */
#define IRQ_NO_I2C1_EV              31  // I2C1 event interrupt                                                 */
#define IRQ_NO_I2C1_ER              32  // I2C1 error interrupt                                                 */
#define IRQ_NO_I2C2_EV              33  // I2C2 event interrupt                                                 */
#define IRQ_NO_I2C2_ER              34  // I2C2 error interrupt
#define IRQ_NO_I2C3_EV              72  //I2C3 event interrupt                                                  */
#define IRQ_NO_I2C3_ER              73  // I2C3 error interrupt
#define IRQ_NO_FMPI2C1_EV           95  // FMPI2C1 event interrupt                                              */
#define IRQ_NO_FMPI2C1_ER           96  // FMPI2C1 error interrupt

#define NO_PR_BITS_IMPLEMENTED 4



















/*
 * USARTx base address
 */
#define USART1_BASEADDR						(APB2_BASEADDR + 0x1000)
#define USART6_BASEADDR						(APB2_BASEADDR + 0x1400)
#define USART2_BASEADDR						(APB1_BASEADDR + 0x4400)
#define USART3_BASEADDR						(APB1_BASEADDR + 0x4800)
#define UART4_BASEADDR						(APB1_BASEADDR + 0x4C00)
#define UART5_BASEADDR						(APB1_BASEADDR + 0x5000)
/*
 * Peripheral  register definition structure for USART
 */
typedef struct
{
	__vo uint32_t SR;         /*!< TODO,     										Address offset: 0x00 */
	__vo uint32_t DR;         /*!< TODO,     										Address offset: 0x04 */
	__vo uint32_t BRR;        /*!< TODO,     										Address offset: 0x08 */
	__vo uint32_t CR1;        /*!< TODO,     										Address offset: 0x0C */
	__vo uint32_t CR2;        /*!< TODO,     										Address offset: 0x10 */
	__vo uint32_t CR3;        /*!< TODO,     										Address offset: 0x14 */
	__vo uint32_t GTPR;       /*!< TODO,     										Address offset: 0x18 */
} USART_RegDef_t;


/*
 * USART regdef
 */
#define USART1  			((USART_RegDef_t*)USART1_BASEADDR)
#define USART2  			((USART_RegDef_t*)USART2_BASEADDR)
#define USART3  			((USART_RegDef_t*)USART3_BASEADDR)
#define UART4  				((USART_RegDef_t*)UART4_BASEADDR)
#define UART5  				((USART_RegDef_t*)UART5_BASEADDR)
#define USART6  			((USART_RegDef_t*)USART6_BASEADDR)


//ENABLE CLOCK FOR USARTx MACROS
#define USART1_PCLK_EN() (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN() (RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()  (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()  (RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN() (RCC->APB1ENR |= (1 << 5))


//DISABLE CLOCK FOR USARTx MACROS
#define USART1_PCLK_DI() (RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI() (RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI() (RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI() (RCC->APB1ENR &= ~(1 << 5))

//RESET SPI BY RCC
#define USART1_REG_RESET()	do {(RCC->APB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4));}while(0)
#define USART2_REG_RESET()	do {(RCC->APB1RSTR |= (1<<17)); (RCC->AHB1RSTR &= ~(1<<17));}while(0)
#define USART3_REG_RESET()	do {(RCC->APB1RSTR |= (1<<18)); (RCC->AHB1RSTR &= ~(1<<18));}while(0)
#define UART4_REG_RESET()	do {(RCC->APB1RSTR |= (1<<19)); (RCC->AHB1RSTR &= ~(1<<19));}while(0)
#define UART5_REG_RESET()	do {(RCC->APB1RSTR |= (1<<20)); (RCC->AHB1RSTR &= ~(1<<20));}while(0)
#define USART6_REG_RESET()	do {(RCC->APB1RSTR |= (1<<5)); (RCC->AHB1RSTR &= ~(1<<5));}while(0)
/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10
#define USART_CR3_ONEBIT   				11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9

/*
 * IRQ NUMBER for I2C peripheral
 */
#define IRQ_NO_USART1	    37
#define IRQ_NO_USART2	    38
#define IRQ_NO_USART3	    39
#define IRQ_NO_UART4	    52
#define IRQ_NO_UART5	    53
#define IRQ_NO_USART6	    71









/*
 * NVIC ISERx register
 */
#define NVIC_ISER0		((__vo uint32_t *) 0xE000E100)
#define NVIC_ISER1		((__vo uint32_t *) 0xE000E104)
#define NVIC_ISER2		((__vo uint32_t *) 0xE000E108)

/*
 * NVIC ICERx register
 */
#define NVIC_ICER0		((__vo uint32_t *) 0xE000E180)
#define NVIC_ICER1		((__vo uint32_t *) 0xE000E184)
#define NVIC_ICER2		((__vo uint32_t *) 0xE000E188)

/*
 * NVIC_IPRx register
 */
#define NVIC_PR_BASE_ADDR		((__vo uint32_t *) 0xE000E400)

/*
 * @NVIC_Priority_Level
 */
#define NVIC_IRQ_PRIO_0		0
#define NVIC_IRQ_PRIO_1		1
#define NVIC_IRQ_PRIO_2		2
#define NVIC_IRQ_PRIO_3		3
#define NVIC_IRQ_PRIO_4		4
#define NVIC_IRQ_PRIO_5		5
#define NVIC_IRQ_PRIO_6		6
#define NVIC_IRQ_PRIO_7		7
#define NVIC_IRQ_PRIO_8		8
#define NVIC_IRQ_PRIO_9		9
#define NVIC_IRQ_PRIO_10	10
#define NVIC_IRQ_PRIO_11	11
#define NVIC_IRQ_PRIO_12	12
#define NVIC_IRQ_PRIO_13	13
#define NVIC_IRQ_PRIO_14	14
#define NVIC_IRQ_PRIO_15	15



#define ENABLE   	1
#define DISABLE  	0
#define SET      	ENABLE
#define RESET    	DISABLE
#define FLAG_SET	ENABLE
#define FLAG_RESET	DISABLE



#include "stm32f407xx_gpio_drivers.h"
#include "stm32f407xx_spi_drivers.h"
#include "stm32f407xx_i2c_drivers.h"
#include "stm32f407xx_rcc_drivers.h"
#include "stm32f407xx_usart_drivers.h"

#endif /* STM32F407XX_H_ */
