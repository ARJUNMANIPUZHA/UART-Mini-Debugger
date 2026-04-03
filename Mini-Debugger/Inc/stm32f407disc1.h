

#ifndef STM32F407DISC1_H_
#define STM32F407DISC1_H_

#include <stdint.h>
#include <stddef.h>

#define __vo volatile
#define __weak __attribute__((weak))

#define __disable_irq()        __asm volatile ("cpsid i")// Setting PRIMASK = 1,disables Maskable interrupts via PRIMASK
#define __enable_irq()         __asm volatile ("cpsie i")// Setting PRIMASK = 0,enables Maskable interrupts via PRIMASK


/****************************** START: Processor Specific details *********************************************/
/*
 * ARM Cortex Mx processor NVIC ISERx register Addresses
 */

#define NVIC_ISER0						((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1						((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2						((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3						((__vo uint32_t*)0xE000E10C)

/*
 * ARM Cortex Mx processor NVIC ICERx register Addresses
 */

#define NVIC_ICER0						((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1						((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2						((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3						((__vo uint32_t*)0xE000E18C)

/*
 * ARM Cortex Mx processor Priority register Addresses
 */

#define NVIC_PR_BASEADDR				(( __vo uint32_t*)0xE000E400)

/*
 * ARM Cortex Mx processor number of Priority bits implemented in Priority register
 */
#define NO_PR_BITS_IMPLEMENTED			4   ///Specific to ST


/*
 * Base addresses of FLASH and SRAM memories
 */

#define FLASH_BASEADDR				0x08000000U
#define SRAM1_BASEADDR				0x20000000U //112KB
#define SRAM2_BASEADDR				0x20001C00U //SRAM1_BASEADDR + 112 x 1024
#define ROM_BASEADDR 				0x1FFF0000U
#define SRAM  						SRAM1_BASEADDR

/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASEADDR					0x40000000U
#define APB1PERIPH_BASEADDR             PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR				0x40010000U
#define AHB1PERIPH_BASEADDR				0x40020000U
#define AHB2PERIPH_BASEADDR    			0x50000000U


/*
 * Base addresses of peripherals which are hanging on AHB1 Bus
 */
#define GPIOA_BASEADDR					(AHB1PERIPH_BASEADDR + 0x0000)
#define RCC_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x3800)

/*
 * Base addresses of peripherals which are hanging on APB1 Bus
 */
#define USART2_BASEADDR                 (APB1PERIPH_BASEADDR + 0x4400)


/***************************** PERIPHERAL REGISTER DEFINITION STRUCTURES ***************************************/

typedef struct
{
	__vo uint32_t MODER;                         /* GPIO port mode register         					Address offset : 0x00 */
	__vo uint32_t OTYPER;						 /* GPIO port output type register  					Address offset : 0x04 */
	__vo uint32_t OSPEEDR;						 /* GPIO port output speed register 					Address offset : 0x08 */
	__vo uint32_t PUPDR;						 /* GPIO port pull-up/pull-down register 				Address offset : 0x0C */
	__vo uint32_t IDR;							 /* GPIO port input data register 						Address offset : 0x10 */
	__vo uint32_t ODR;							 /* GPIO port output data register           			Address offset : 0x14 */
	__vo uint32_t BSRR;							 /* GPIO port bit set/reset register					Address offset : 0x18 */
	__vo uint32_t LCKR;						     /* GPIO port configuration lock register				Address offset : 0x1C */
	__vo uint32_t AFR[2];						 /* AFR[0] : GPIO alternate function low register 		Address offset : 0x20
	 	 	 	 	 	 	 	 	 	 	        AFR[1] : GPIO alternate function high register 		Address offset : 0x24*/

}GPIO_RegDef_t;

/*
 *  Peripheral register definition for RCC
 */

typedef struct
{
  __vo uint32_t CR;            /* RCC clock control register  											Address offset: 0x00 */
  __vo uint32_t PLLCFGR;       /* RCC PLL configuration register     									Address offset: 0x04 */
  __vo uint32_t CFGR;          /* RCC clock configuration register										Address offset: 0x08 */
  __vo uint32_t CIR;           /* RCC clock interrupt register     										Address offset: 0x0C */
  __vo uint32_t AHB1RSTR;      /* RCC AHB1 peripheral reset register    								Address offset: 0x10 */
  __vo uint32_t AHB2RSTR;      /* RCC AHB2 peripheral reset register     								Address offset: 0x14 */
  __vo uint32_t AHB3RSTR;      /* RCC AHB3 peripheral reset register     								Address offset: 0x18 */
  uint32_t      RESERVED0;     /* Reserved, 0x1C                                                       						 */
  __vo uint32_t APB1RSTR;      /* RCC APB1 peripheral reset register     								Address offset: 0x20 */
  __vo uint32_t APB2RSTR;      /* RCC APB2 peripheral reset register     								Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /* Reserved, 0x28-0x2C                                                  						 */
  __vo uint32_t AHB1ENR;       /* RCC AHB1 peripheral clock register     								Address offset: 0x30 */
  __vo uint32_t AHB2ENR;       /* RCC AHB2 peripheral clock register     								Address offset: 0x34 */
  __vo uint32_t AHB3ENR;       /* RCC AHB3 peripheral clock register     								Address offset: 0x38 */
  uint32_t      RESERVED2;     /* Reserved, 0x3C                                                       						 */
  __vo uint32_t APB1ENR;       /* RCC APB1 peripheral clock enable register     						Address offset: 0x40 */
  __vo uint32_t APB2ENR;       /* RCC APB2 peripheral clock enable register     						Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /* Reserved, 0x48-0x4C                                                  						 */
  __vo uint32_t AHB1LPENR;     /* RCC AHB1 peripheral clock enable in low power mode register     		Address offset: 0x50 */
  __vo uint32_t AHB2LPENR;     /* RCC AHB2 peripheral clock enable in low power mode register     		Address offset: 0x54 */
  __vo uint32_t AHB3LPENR;     /* RCC AHB3 peripheral clock enable in low power mode register     		Address offset: 0x58 */
  uint32_t      RESERVED4;     /* Reserved, 0x5C                                                       						 */
  __vo uint32_t APB1LPENR;     /* RCC APB1 peripheral clock enable in low power mode register     		Address offset: 0x60 */
  __vo uint32_t APB2LPENR;     /* RCC APB2 peripheral clock enable in low power mode register     		Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /* Reserved, 0x68-0x6C                                                  						 */
  __vo uint32_t BDCR;          /* RCC Backup domain control register     								Address offset: 0x70 */
  __vo uint32_t CSR;           /* RCC clock control & status register      								Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /* Reserved, 0x78-0x7C                                                  						 */
  __vo uint32_t SSCGR;         /* RCC spread spectrum clock generation register     					Address offset: 0x80 */
  __vo uint32_t PLLI2SCFGR;    /* RCC PLLI2S configuration register     								Address offset: 0x84 */
  __vo uint32_t PLLSAICFGR;    /* RCC PLL configuration register      									Address offset: 0x88 */
  __vo uint32_t DCKCFGR;       /* RCC Dedicated Clock Configuration Register     						Address offset: 0x8C */
  __vo uint32_t CKGATENR;      /*     																	Address offset: 0x90 */
  __vo uint32_t DCKCFGR2;      /*     																	Address offset: 0x94 */

} RCC_RegDef_t;

/*
 * peripheral register definition structure for USART
 */
typedef struct
{
	__vo uint32_t SR;     /*!< Status register
	                            Indicates TXE, RXNE, TC, ORE, NE, FE flags.
	                            Used to check transmit/receive status             Address offset: 0x00 */

	__vo uint32_t DR;     /*!< Data register
	                            Holds transmit and receive data byte              Address offset: 0x04 */

	__vo uint32_t BRR;    /*!< Baud rate register
	                            Configures USART baud rate using mantissa
	                            and fraction values                               Address offset: 0x08 */

	__vo uint32_t CR1;    /*!< Control register 1
	                            USART enable, word length, parity control,
	                            transmitter/receiver enable, RXNE interrupt       Address offset: 0x0C */

	__vo uint32_t CR2;    /*!< Control register 2
	                            STOP bits configuration, clock enable,
	                            LIN mode and address detection settings           Address offset: 0x10 */

	__vo uint32_t CR3;    /*!< Control register 3
	                            Hardware flow control (CTS/RTS),
	                            DMA enable, error interrupt control               Address offset: 0x14 */

	__vo uint32_t GTPR;   /*!< Guard time and prescaler register
	                            Used mainly in Smartcard and IrDA modes           Address offset: 0x18 */
} USART_RegDef_t;



/*
 *  Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t
 */

#define GPIOA							((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define RCC								((RCC_RegDef_t*)RCC_BASEADDR)
#define USART2  						((USART_RegDef_t*)USART2_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()					( RCC -> AHB1ENR |= ( 1 << 0 ) )

/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART2_PCCK_EN() 				( RCC -> APB1ENR |= ( 1 << 17 ))

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()					( RCC -> AHB1ENR &= ~( 1 << 0 ) )

/*
 * Clock Disable Macros for USARTx peripherals
 */
#define USART2_PCCK_DI() 				( RCC -> APB1ENR &= ~( 1 << 17 ))

/*
 * Some generic Macros
 */

#define ENABLE 							1
#define DISABLE 						0
#define SET 							ENABLE
#define RESET 							DISABLE
#define GPIO_PIN_SET					SET
#define GPIO_PIN_RESET					RESET
#define FLAG_RESET						RESET
#define FLAG_SET						SET



#define IRQ_NO_USART2	    38


/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

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

#include "gpio_driver.h"
#include "uart_driver.h"
#include "rcc_driver.h"
#include "debugger_driver.h"

#endif /* STM32F407DISC1_H_ */
