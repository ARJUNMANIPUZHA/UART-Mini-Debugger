# UART Triggered Mini Debugger (STM32F407)

## Overview

This project implements a UART-controlled mini debugger on the STM32F407 Discovery board using bare-metal programming in C. The system runs continuously and allows external interaction through UART commands to halt execution, capture CPU state, and resume operation.

The objective of this project is to explore low-level debugging concepts and gain hands-on experience with ARM Cortex-M4 architecture, register-level programming, and interrupt handling.

---

## Features

* UART-based command interface
* Interrupt-driven data reception using USART2
* Real-time execution indicator using a spinner
* CPU state capture on demand
* Register dump over UART

Captured CPU state includes:

* General-purpose registers (R0–R12)
* Main Stack Pointer (MSP)
* Process Stack Pointer (PSP)
* CONTROL register
* PRIMASK register
* Link Register (LR)
* Program Counter (PC, approximated)
* xPSR register

---

## Components Required

* STM32F407 Discovery Board
* USB to UART Converter (e.g., FTDI, CP2102)
* Jumper wires
* PC with serial terminal software (PuTTY, minicom, screen, etc.)
* ARM GCC Toolchain (for building the project)

---

## System Behavior

### Normal Execution Mode

* The system runs continuously.
* A spinner is displayed over UART to indicate active execution.

### Debug Mode

* Triggered by sending `H` or `h` via UART.
* The system:

  * Disables interrupts
  * Captures CPU register state using inline assembly
  * Prints the register values over UART

### Resume Execution

* Triggered by sending `R` or `r`.
* The system exits debug mode and resumes normal execution.

---

## Implementation Details

### USART Driver

* Configured USART2 for transmission and reception
* Baud rate configured using peripheral clock calculations (set to 9600)
* RXNE interrupt used for receiving commands
* Basic send functions implemented for character, string, and hexadecimal output

### Interrupt Handling

* NVIC configured to enable USART2 interrupt
* ISR reads received data and triggers debug handler

### Debugger Module

* CPU state stored in a structured format
* Inline assembly used to capture:

  * General-purpose registers (R0–R12)
  * Special registers (MSP, PSP, CONTROL, PRIMASK, xPSR)
* PC captured using ADR instruction (approximation)

### Execution Control

* Interrupts disabled during state capture to ensure consistency
* System waits in a loop for resume command

---

## Project Structure

* `main.c`

  * Application entry point
  * Menu display and spinner task

* `usart.c / usart.h`

  * USART initialization and communication functions
  * Interrupt configuration

* `debugger.c / debugger.h`

  * CPU state capture
  * Debug handler implementation

* `stm32f407disc1.h`

  * Register definitions and macros

---

## Build and Run

1. Compile the project using an ARM GCC toolchain
2. Flash the binary to the STM32F407 Discovery board
3. Connect USART2:

   * PA2 → TX
   * PA3 → RX
   * GND → GND
4. Open a serial terminal (e.g., PuTTY, minicom)
5. Configure the terminal:

   * Baud rate: 9600
   * Data bits: 8
   * Stop bits: 1
   * Parity: None

### Commands

* `H` or `h`
  Halt execution and display CPU state

* `R` or `r`
  Resume execution

---

## Sample Output

```id="2kd8fh"
=== CPU SNAPSHOT ===

General Purpose Registers
R0 = 0x40004400
R1 = 0x00000068
...

--- Special Registers ---
MSP     = 0x2001FF90
PSP     = 0x00000000
CONTROL = 0x00000000
PRIMASK = 0x00000001
LR      = 0x08001234
PC      = 0x08004567
xPSR    = 0x21000000
```

---

## Limitations

* Program Counter (PC) value is approximated using ADR instruction
* No support for memory inspection or modification
* Single-character command interface
* No breakpoint or step execution support

---

## Future Enhancements

* Add memory read/write capabilities
* Implement breakpoint support
* Extend command interface with parsing
* Integrate with external debugging tools (e.g., GDB)
* Improve accuracy of PC capture

---

## Conclusion

This project demonstrates a practical approach to understanding low-level debugging mechanisms in embedded systems. It highlights key concepts such as register-level programming, interrupt handling, and inline assembly integration on ARM Cortex-M4.

## Demo

Watch the demo here:  
[Project Demo Video](https://youtu.be/zrci9QAzYlY)
