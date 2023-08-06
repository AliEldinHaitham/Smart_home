################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_prg.c \
../DCMOTOR_PRG.c \
../DIO_prg.c \
../EX_INT_prg.c \
../IMT_FINALPROJECT_PRG.c \
../INTERRUPT_prg.c \
../KeyPad_prg.c \
../LCD_prg.c \
../SERVOMOTOR_prg.c \
../TIMER_PRG.c \
../Timer1_prg.c \
../main.c 

OBJS += \
./ADC_prg.o \
./DCMOTOR_PRG.o \
./DIO_prg.o \
./EX_INT_prg.o \
./IMT_FINALPROJECT_PRG.o \
./INTERRUPT_prg.o \
./KeyPad_prg.o \
./LCD_prg.o \
./SERVOMOTOR_prg.o \
./TIMER_PRG.o \
./Timer1_prg.o \
./main.o 

C_DEPS += \
./ADC_prg.d \
./DCMOTOR_PRG.d \
./DIO_prg.d \
./EX_INT_prg.d \
./IMT_FINALPROJECT_PRG.d \
./INTERRUPT_prg.d \
./KeyPad_prg.d \
./LCD_prg.d \
./SERVOMOTOR_prg.d \
./TIMER_PRG.d \
./Timer1_prg.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


