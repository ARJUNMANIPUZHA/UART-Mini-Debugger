#include "stm32f407disc1.h"

/* Structure to hold CPU state */
typedef struct
{
    uint32_t REGx[13];   // R0–R12
    uint32_t MSP;
    uint32_t PSP;
    uint32_t CONTROL;
    uint32_t PRIMASK;
    uint32_t LR;
    uint32_t PC;
    uint32_t xPSR;

} CPU_State_t;

CPU_State_t cpu_state;
CPU_State_t *state = &cpu_state;

USART_RegDef_t* pUSART = USART2;

volatile DebugState_t g_debugState = DEBUG_STATE_RUNNING;

/* Capture CPU state */
void capture_cpu_state(void)
{
    /* Capture R0–R12 */
    __asm volatile(
        "stmia %0, {r0-r12}"
        :
        : "r"(state->REGx)
        : "memory"
    );

    uint32_t temp;

    /* MSP */
    __asm volatile ("MRS %0, MSP" : "=r" (temp));
    state->MSP = temp;

    /* PSP */
    __asm volatile ("MRS %0, PSP" : "=r" (temp));
    state->PSP = temp;

    /* CONTROL */
    __asm volatile ("MRS %0, CONTROL" : "=r" (temp));
    state->CONTROL = temp;

    /* PRIMASK */
    __asm volatile ("MRS %0, PRIMASK" : "=r" (temp));
    state->PRIMASK = temp;

    /* LR */
    __asm volatile ("MOV %0, LR" : "=r" (temp));
    state->LR = temp;

    /* PC (approximation) */
    __asm volatile ("ADR %0, ." : "=r" (temp));
    state->PC = temp;

    /* xPSR */
    __asm volatile ("MRS %0, xPSR" : "=r" (temp));
    state->xPSR = temp;

	USART_SendString(pUSART, "\r\n");
	USART_SendString(pUSART, "========================================\r\n");
	USART_SendString(pUSART, "        UART-TRIGGERED MINI DEBUGGER    \r\n");
	USART_SendString(pUSART, "========================================\r\n");
	USART_SendString(pUSART, "Status   : HALTED                      \r\n");
	USART_SendString(pUSART, "----------------------------------------\r\n");
    USART_SendString(pUSART, "\r\n=== CPU SNAPSHOT ===\r\n");

        /* General Purpose Registers */
        USART_SendString(pUSART, "General Purpose Registers\r\n");

        for(uint32_t i = 0; i < 13; i++)
        {
            USART_SendChar(pUSART, 'R');

            if(i < 10)
            {
                USART_SendChar(pUSART, '0' + i);
            }
            else
            {
                USART_SendChar(pUSART, '1');
                USART_SendChar(pUSART, '0' + (i - 10));
            }

            USART_SendString(pUSART, " = 0x");
            USART_SendHex(pUSART, state->REGx[i]);
            USART_SendString(pUSART, "\r\n");
        }

        USART_SendString(pUSART, "\r\n--- Special Registers ---\r\n");

        USART_SendString(pUSART, "MSP     = 0x");
        USART_SendHex(pUSART, state->MSP);
        USART_SendString(pUSART, "\r\n");

        USART_SendString(pUSART, "PSP     = 0x");
        USART_SendHex(pUSART, state->PSP);
        USART_SendString(pUSART, "\r\n");

        USART_SendString(pUSART, "CONTROL = 0x");
        USART_SendHex(pUSART, state->CONTROL);
        USART_SendString(pUSART, "\r\n");

        USART_SendString(pUSART, "PRIMASK = 0x");
        USART_SendHex(pUSART, state->PRIMASK);
        USART_SendString(pUSART, "\r\n");

        USART_SendString(pUSART, "LR      = 0x");
        USART_SendHex(pUSART, state->LR);
        USART_SendString(pUSART, "\r\n");

        USART_SendString(pUSART, "PC      = 0x");
        USART_SendHex(pUSART, state->PC);
        USART_SendString(pUSART, "\r\n");

        USART_SendString(pUSART, "xPSR    = 0x");
        USART_SendHex(pUSART, state->xPSR);
        USART_SendString(pUSART, "\r\n");

}

void debug_handler()
{
	__disable_irq();
	USART2->CR1 &= ~USART_CR1_RXNEIE;
	capture_cpu_state();
	__enable_irq();
	USART2->CR1 |= USART_CR1_RXNEIE;
	USART_SendString(pUSART, "\r\nPress R to resume...\r\n");
	/* Clean line for spinner */
	USART_SendChar(pUSART, '\r');
	USART_SendString(pUSART, "                                        ");
	USART_SendChar(pUSART, '\r');
}

void debug_process(void)
{
    static uint8_t isHaltedHandled = 0;

    switch(g_debugState)
    {
        case DEBUG_STATE_RUNNING:
            isHaltedHandled = 0;
            break;

        case DEBUG_STATE_HALTED:
            if(!isHaltedHandled)
            {
                debug_handler();
                g_debugState = DEBUG_STATE_WAIT_RESUME;
                isHaltedHandled = 1;
            }
            break;

        case DEBUG_STATE_WAIT_RESUME:
            // Do nothing, wait for 'R' from UART callback
            break;
    }
}
