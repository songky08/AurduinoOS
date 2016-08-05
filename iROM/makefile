################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include CORE2/subdir.mk
-include CORE1/subdir.mk
-include CORE0/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

#rebuild target
rebuild: clean all

# All Target
all: AurduinoOS.elf

# Tool invocations
AurduinoOS.elf: $(OBJS) $(USER_OBJS) $(ASM)
	@echo 'Building target: $@'
	@echo 'Invoking: TriCore C Linker'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -o  "AurduinoOS.elf" -nostartfiles -T"..\ld\tricoreIROM.ld" "src\cint_tc2x.o" "src\cinttab.o" "src\crt0-tc2x.o" "src\interrupts.o" "src\led.o" "src\spi.o" "src\system_tc2x.o" "CORE0\main.o" "CORE0\master.o" "CORE1\slave1.o" "CORE2\slave2.o" -Wl,--gc-sections -mcpu=tc27xx -Wl,--mem-holes -Wl,--no-warn-flags -Wl,-Map="$(basename $(notdir $@)).map" -Wl,--cref -fshort-double -Wl,--extmap="a"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(PCP_S)$(EXECUTABLES)$(OBJS)$(C_DEPS)$(CPCP_DEPS) AurduinoOS.elf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
