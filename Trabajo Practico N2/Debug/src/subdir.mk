################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Employee.c \
../src/Trabajo\ Practico\ N2.c \
../src/utn2.c 

OBJS += \
./src/Employee.o \
./src/Trabajo\ Practico\ N2.o \
./src/utn2.o 

C_DEPS += \
./src/Employee.d \
./src/Trabajo\ Practico\ N2.d \
./src/utn2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Trabajo\ Practico\ N2.o: ../src/Trabajo\ Practico\ N2.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Trabajo Practico N2.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


