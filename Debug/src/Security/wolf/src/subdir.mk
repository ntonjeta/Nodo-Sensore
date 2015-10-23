################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Security/wolf/src/aes.c \
../src/Security/wolf/src/arc4.c \
../src/Security/wolf/src/des3.c \
../src/Security/wolf/src/hmac.c \
../src/Security/wolf/src/md5.c \
../src/Security/wolf/src/misc.c \
../src/Security/wolf/src/sha.c \
../src/Security/wolf/src/sha256.c \
../src/Security/wolf/src/sha512.c 

OBJS += \
./src/Security/wolf/src/aes.o \
./src/Security/wolf/src/arc4.o \
./src/Security/wolf/src/des3.o \
./src/Security/wolf/src/hmac.o \
./src/Security/wolf/src/md5.o \
./src/Security/wolf/src/misc.o \
./src/Security/wolf/src/sha.o \
./src/Security/wolf/src/sha256.o \
./src/Security/wolf/src/sha512.o 

C_DEPS += \
./src/Security/wolf/src/aes.d \
./src/Security/wolf/src/arc4.d \
./src/Security/wolf/src/des3.d \
./src/Security/wolf/src/hmac.d \
./src/Security/wolf/src/md5.d \
./src/Security/wolf/src/misc.d \
./src/Security/wolf/src/sha.d \
./src/Security/wolf/src/sha256.d \
./src/Security/wolf/src/sha512.d 


# Each subdirectory must supply rules for building sources it contributes
src/Security/wolf/src/%.o: ../src/Security/wolf/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOPERATIVE_NODE -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/EventLogger/Inc" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/GSI" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/fat/inc" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/Sys_Timer/Inc" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/include" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/FreeRTOS/Source/CMSIS_RTOS" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/FreeRTOS/Source/include" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/system/include" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/system/include/cmsis" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/system/include/stm32f4-hal" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/Security/include" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/Security/wolf/include" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/usb/MSC/Inc" -I"/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/src/usb/Core/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


