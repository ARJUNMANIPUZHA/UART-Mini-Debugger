/*
 * uart_driver.h
 *
 *  Created on: Apr 1, 2026
 *      Author: arjunm
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#define BAUDRATE 9600

typedef enum
{
    USART_EVENT_RX_CHAR
} USART_Event_t;

/*
 * USART flags
 */

#define USART_FLAG_TXE 			( 1 << USART_SR_TXE)
#define USART_FLAG_RXNE 		( 1 << USART_SR_RXNE)
#define USART_FLAG_TC 			( 1 << USART_SR_TC)

#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0


void USART_Init();
void USART_SetBaudRate(USART_RegDef_t* pUsart);
uint8_t USART_GetFlagStatus(USART_RegDef_t* pUsart, uint8_t StatusFlagName);
void USART_SendChar(USART_RegDef_t* pUsart, char ch);
void USART_SendString(USART_RegDef_t* pUsart, char *str);
void USART_SendHex(USART_RegDef_t* pUsart, uint32_t value);

char USART_ReceiveChar(USART_RegDef_t* pUsart);

void run_debugger(USART_RegDef_t* pUsart, uint8_t ch);

void USART_InterrputConfig();

void USART_ApplicationEventCallback(uint8_t event, uint8_t data);

#endif /* UART_DRIVER_H_ */
