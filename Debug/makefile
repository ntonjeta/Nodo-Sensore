################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/src/stm32f4-hal/subdir.mk
-include system/src/newlib/subdir.mk
-include system/src/diag/subdir.mk
-include system/src/cortexm/subdir.mk
-include system/src/cmsis/subdir.mk
-include src/usb/MSC/Src/subdir.mk
-include src/usb/Core/Src/subdir.mk
-include src/fat/src/subdir.mk
-include src/Sys_Timer/Src/subdir.mk
-include src/Security/wolf/src/subdir.mk
-include src/Security/src/subdir.mk
-include src/GSI/fip/subdir.mk
-include src/GSI/subdir.mk
-include src/FreeRTOS/Source/portable/MemMang/subdir.mk
-include src/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include src/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include src/FreeRTOS/Source/subdir.mk
-include src/EventLogger/Src/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ReteDiSensori-NodoSensore.hex \

SECONDARY_SIZE += \
ReteDiSensori-NodoSensore.siz \


# All Target
all: ReteDiSensori-NodoSensore.elf secondary-outputs

# Tool invocations
ReteDiSensori-NodoSensore.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -T "/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/ldscripts/libs.ld" -T "/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/ldscripts/mem.ld" -T "/home/ntonjeta/workspace/ReteDiSensori-NodoSensore/ldscripts/sections.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"ReteDiSensori-NodoSensore.map" --specs=nano.specs -o "ReteDiSensori-NodoSensore.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ReteDiSensori-NodoSensore.hex: ReteDiSensori-NodoSensore.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "ReteDiSensori-NodoSensore.elf"  "ReteDiSensori-NodoSensore.hex"
	@echo 'Finished building: $@'
	@echo ' '

ReteDiSensori-NodoSensore.siz: ReteDiSensori-NodoSensore.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "ReteDiSensori-NodoSensore.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) ReteDiSensori-NodoSensore.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
