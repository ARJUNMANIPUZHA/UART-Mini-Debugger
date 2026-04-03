################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/debugger_driver.c \
../Src/gpio_driver.c \
../Src/main.c \
../Src/rcc_driver.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/uart_driver.c 

OBJS += \
./Src/debugger_driver.o \
./Src/gpio_driver.o \
./Src/main.o \
./Src/rcc_driver.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/uart_driver.o 

C_DEPS += \
./Src/debugger_driver.d \
./Src/gpio_driver.d \
./Src/main.d \
./Src/rcc_driver.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/debugger_driver.cyclo ./Src/debugger_driver.d ./Src/debugger_driver.o ./Src/debugger_driver.su ./Src/gpio_driver.cyclo ./Src/gpio_driver.d ./Src/gpio_driver.o ./Src/gpio_driver.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/rcc_driver.cyclo ./Src/rcc_driver.d ./Src/rcc_driver.o ./Src/rcc_driver.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/uart_driver.cyclo ./Src/uart_driver.d ./Src/uart_driver.o ./Src/uart_driver.su

.PHONY: clean-Src

