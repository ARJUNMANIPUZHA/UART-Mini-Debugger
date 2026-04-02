#include <stdint.h>
#include "stm32f407disc1.h"

void printMenu(USART_RegDef_t* pUsart);
void spinnerTask(USART_RegDef_t* pUsart);

int main(void)
{
	USART_RegDef_t* pUSART = USART2;

	GPIOA_Init();
	USART_Init();
    printMenu(pUSART);
	while(1)
	{
		spinnerTask(pUSART);
	}

}

void printMenu(USART_RegDef_t* pUsart)
{
	USART_SendString(pUsart, "\r\n");
	USART_SendString(pUsart, "========================================\r\n");
	USART_SendString(pUsart, "        UART-TRIGGERED MINI DEBUGGER    \r\n");
	USART_SendString(pUsart, "========================================\r\n");
	USART_SendString(pUsart, "Status   : RUNNING                      \r\n");
	USART_SendString(pUsart, "----------------------------------------\r\n");
	USART_SendString(pUsart, "Commands:                               \r\n");
	USART_SendString(pUsart,"  H / h: Halt CPU & dump registers     \r\n");
	USART_SendString(pUsart, "  R / r : Resume execution              \r\n");
	USART_SendString(pUsart, "----------------------------------------\r\n");
}

void spinnerTask(USART_RegDef_t* pUsart)
{
    static const char spinner[] = {'|', '/', '-', '\\'};
    static uint8_t index = 0;
    static uint32_t delayCounter = 0;

    delayCounter++;

    /* Slow down spinner (adjust this value if needed) */
    if(delayCounter < 200000)
        return;

    delayCounter = 0;

    USART_SendChar(pUsart, '\r');              // return to same line
    USART_SendChar(pUsart, spinner[index]);    // spinner char
    USART_SendString(pUsart, " System Running...");


    index++;
    if(index >= 4)
        index = 0;
}
