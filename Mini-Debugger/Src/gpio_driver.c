/*
 * Alternate function mapping (AF7)
 * PA2->USART2_TX
 * PA3->USART2_RX
 */

#include "stm32f407disc1.h"


void GPIOA_Init(void)
{
	/* Enable peripheral clock */
	GPIOA_PCLK_EN();

	/* Configure GPIO Mode to Alternate function */

	// Clear the bits before setting
	GPIOA->MODER &= ~((3U << (2 * 2)) | (3U << (2 * 3)));
	// Set PA2 and PA3 as Alt function mode
	GPIOA->MODER |= ((2U << (2 *2)) | (2U << (2 * 3)));

	/* Configure the speed of pins */

	// Clear the bits before setting
	GPIOA->OSPEEDR &= ~(3U << (2 * 2));
	// Set PA2 as high speed pin
	GPIOA->OSPEEDR |= (2U << (2 * 3));

	/* Configure the Pull-up */

	// Set PA3 in PULL-UP state
	GPIOA->PUPDR &= ~(3U << (2 * 3));
	GPIOA->PUPDR |= (1U << (2 * 3));

	/* Configure AF7 to both PA2 and PA3 */
	GPIOA->AFR[0] &= ~((15U << (4 * 2)) | (15U << (4 * 3)));
	GPIOA->AFR[0] |= ((7U << (4 * 2)) | (7U << (4 * 3)));
}
