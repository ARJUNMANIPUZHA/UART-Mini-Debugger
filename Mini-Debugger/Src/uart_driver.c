#include "stm32f407disc1.h"

void USART_Init(void)
{
	USART_RegDef_t* pUSART = USART2;

	/* Enable the clock */
	USART2_PCCK_EN();

	/* Calculate and set baudrate */
	USART_SetBaudRate(pUSART);

	/* Set RE, Receiver enable bit */
	pUSART->CR1 |= (1U << USART_CR1_RE);

	/* Set TE, Transmitter enable bit */
	pUSART->CR1 |= (1U << USART_CR1_TE);

	/* Set RXNE interrupt enable bit */
	pUSART->CR1 |= (1 << USART_CR1_RXNEIE);

	/* Enable the USART2 interrupt */
	USART_InterrputConfig();

	/* Set UE, USART enable bit after clearing it*/
	pUSART->CR1 |= (1 << USART_CR1_UE);
}

void USART_SetBaudRate(USART_RegDef_t* pUsart)
{
	/* Variables to hold various calculation parametes */
	uint32_t PCLKx;
	uint32_t usartdiv, temp_reg = 0;
	uint32_t M_part, F_part;

	PCLKx = RCC_GetPCLK1Value();

	/* By default OVER8 = 0 : oversampling by 16*/
	usartdiv = ((25 * PCLKx) / (4 * BAUDRATE));

	/* Calculation of BRR value */
	// Mantissa
	M_part = usartdiv / 100;

	temp_reg |= M_part << 4;

	//Fraction
	F_part = (usartdiv - (M_part * 100));
	F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);

	temp_reg |= F_part;
	pUsart->BRR = temp_reg;
}

uint8_t USART_GetFlagStatus(USART_RegDef_t* pUsart, uint8_t StatusFlagName)
{
	if(pUsart->SR & StatusFlagName)
	{
    	return SET;
	}
	return RESET;
}

void USART_SendChar(USART_RegDef_t* pUsart, char ch)
{
	/* Wait until TXE flag is set */
	while(!(USART_GetFlagStatus(pUsart, USART_FLAG_TXE)));
	pUsart->DR = (uint8_t)ch;
}

void USART_SendString(USART_RegDef_t* pUsart, char *str)
{
	while(*str)
	{
		USART_SendChar(pUsart, *(str++));
	}
}

void USART_SendHex(USART_RegDef_t* pUsart, uint32_t value)
{
	const char hex_chars[] = "0123456789ABCDEF";

	for (int i = 7; i >= 0; i--)
	{
        uint8_t nibble = (value >> (i * 4)) & 0xF;
        USART_SendChar(pUsart, hex_chars[nibble]);
	}
}



void USART_InterrputConfig()
{
	*NVIC_ISER1 |= (1 << (IRQ_NO_USART2 % 32));
}



void USART2_IRQHandler(void)
{
    uint8_t data;

    if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
    {
        data = (uint8_t)(USART2->DR & 0xFFU);

        USART_ApplicationEventCallback(USART_EVENT_RX_CHAR, data);
    }
}


void USART_ApplicationEventCallback(uint8_t event, uint8_t data)
{
    if(event == USART_EVENT_RX_CHAR)
    {
        if(data == 'H' || data == 'h')
        {
            g_debugState = DEBUG_STATE_HALTED;
        }
        else if(data == 'R' || data == 'r')
        {
            if(g_debugState == DEBUG_STATE_WAIT_RESUME)
            {
                g_debugState = DEBUG_STATE_RUNNING;
            }
        }
    }
}



