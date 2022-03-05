################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include rt-thread/src/subdir.mk
-include rt-thread/libcpu/arm/cortex-a/subdir.mk
-include rt-thread/libcpu/arm/common/subdir.mk
-include rt-thread/components/net/sal_socket/src/subdir.mk
-include rt-thread/components/net/sal_socket/socket/subdir.mk
-include rt-thread/components/net/sal_socket/impl/subdir.mk
-include rt-thread/components/net/sal_socket/dfs_net/subdir.mk
-include rt-thread/components/net/netdev/src/subdir.mk
-include rt-thread/components/net/lwip-2.0.2/src/netif/subdir.mk
-include rt-thread/components/net/lwip-2.0.2/src/core/ipv4/subdir.mk
-include rt-thread/components/net/lwip-2.0.2/src/core/subdir.mk
-include rt-thread/components/net/lwip-2.0.2/src/arch/subdir.mk
-include rt-thread/components/net/lwip-2.0.2/src/apps/ping/subdir.mk
-include rt-thread/components/net/lwip-2.0.2/src/api/subdir.mk
-include rt-thread/components/lwp/arch/arm/cortex-a/subdir.mk
-include rt-thread/components/lwp/subdir.mk
-include rt-thread/components/libc/time/subdir.mk
-include rt-thread/components/libc/termios/subdir.mk
-include rt-thread/components/libc/signal/subdir.mk
-include rt-thread/components/libc/pthreads/subdir.mk
-include rt-thread/components/libc/mmap/subdir.mk
-include rt-thread/components/libc/compilers/newlib/subdir.mk
-include rt-thread/components/libc/aio/subdir.mk
-include rt-thread/components/finsh/subdir.mk
-include rt-thread/components/drivers/watchdog/subdir.mk
-include rt-thread/components/drivers/src/subdir.mk
-include rt-thread/components/drivers/spi/sfud/src/subdir.mk
-include rt-thread/components/drivers/spi/subdir.mk
-include rt-thread/components/drivers/serial/subdir.mk
-include rt-thread/components/drivers/sdio/subdir.mk
-include rt-thread/components/drivers/rtc/subdir.mk
-include rt-thread/components/drivers/mtd/subdir.mk
-include rt-thread/components/drivers/misc/subdir.mk
-include rt-thread/components/drivers/i2c/subdir.mk
-include rt-thread/components/dfs/src/subdir.mk
-include rt-thread/components/dfs/filesystems/romfs/subdir.mk
-include rt-thread/components/dfs/filesystems/ramfs/subdir.mk
-include rt-thread/components/dfs/filesystems/elmfat/option/subdir.mk
-include rt-thread/components/dfs/filesystems/elmfat/subdir.mk
-include rt-thread/components/dfs/filesystems/devfs/subdir.mk
-include rt-thread/components/cplusplus/subdir.mk
-include drivers/subdir.mk
-include applications/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
rtthread.bin \

SECONDARY_SIZE += \
rtthread.siz \


# All Target
all: rtthread.elf secondary-outputs

# Tool invocations
rtthread.elf: $(OBJS) $(USER_OBJS)
	arm-none-eabi-g++ -march=armv7-a -marm -mfloat-abi=soft -O0 -Wall  -g -gdwarf-2 -T "C:\OSES_project\SBS\link.lds" -Xlinker --gc-sections -Wl,-Map,"rtthread.map" -o "rtthread.elf" $(OBJS) $(USER_OBJS) $(LIBS)

rtthread.bin: rtthread.elf
	arm-none-eabi-objcopy -O binary "rtthread.elf"  "rtthread.bin"

rtthread.siz: rtthread.elf
	arm-none-eabi-size --format=berkeley "rtthread.elf"

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) rtthread.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
