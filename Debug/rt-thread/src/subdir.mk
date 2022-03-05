################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/src/clock.c \
../rt-thread/src/components.c \
../rt-thread/src/cpu.c \
../rt-thread/src/device.c \
../rt-thread/src/idle.c \
../rt-thread/src/ipc.c \
../rt-thread/src/irq.c \
../rt-thread/src/kservice.c \
../rt-thread/src/mem.c \
../rt-thread/src/memheap.c \
../rt-thread/src/mempool.c \
../rt-thread/src/object.c \
../rt-thread/src/scheduler.c \
../rt-thread/src/signal.c \
../rt-thread/src/thread.c \
../rt-thread/src/timer.c 

OBJS += \
./rt-thread/src/clock.o \
./rt-thread/src/components.o \
./rt-thread/src/cpu.o \
./rt-thread/src/device.o \
./rt-thread/src/idle.o \
./rt-thread/src/ipc.o \
./rt-thread/src/irq.o \
./rt-thread/src/kservice.o \
./rt-thread/src/mem.o \
./rt-thread/src/memheap.o \
./rt-thread/src/mempool.o \
./rt-thread/src/object.o \
./rt-thread/src/scheduler.o \
./rt-thread/src/signal.o \
./rt-thread/src/thread.o \
./rt-thread/src/timer.o 

C_DEPS += \
./rt-thread/src/clock.d \
./rt-thread/src/components.d \
./rt-thread/src/cpu.d \
./rt-thread/src/device.d \
./rt-thread/src/idle.d \
./rt-thread/src/ipc.d \
./rt-thread/src/irq.d \
./rt-thread/src/kservice.d \
./rt-thread/src/mem.d \
./rt-thread/src/memheap.d \
./rt-thread/src/mempool.d \
./rt-thread/src/object.d \
./rt-thread/src/scheduler.d \
./rt-thread/src/signal.d \
./rt-thread/src/thread.d \
./rt-thread/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/src/%.o: ../rt-thread/src/%.c
	arm-none-eabi-gcc -march=armv7-a -marm -mfloat-abi=soft -O0 -Wall  -g -gdwarf-2 -DDEBUG -I"C:\OSES_project\SBS" -I"C:\OSES_project\SBS\applications" -I"C:\OSES_project\SBS\drivers" -I"C:\OSES_project\SBS\rt-thread\components\cplusplus" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\devfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\elmfat" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\ramfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\romfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi\sfud\inc" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi" -I"C:\OSES_project\SBS\rt-thread\components\finsh" -I"C:\OSES_project\SBS\rt-thread\components\libc\aio" -I"C:\OSES_project\SBS\rt-thread\components\libc\compilers\newlib" -I"C:\OSES_project\SBS\rt-thread\components\libc\mmap" -I"C:\OSES_project\SBS\rt-thread\components\libc\pthreads" -I"C:\OSES_project\SBS\rt-thread\components\libc\signal" -I"C:\OSES_project\SBS\rt-thread\components\libc\termios" -I"C:\OSES_project\SBS\rt-thread\components\libc\time" -I"C:\OSES_project\SBS\rt-thread\components\lwp" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\arch\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include\netif" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src" -I"C:\OSES_project\SBS\rt-thread\components\net\netdev\include" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\impl" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\dfs_net" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket\sys_socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include" -I"C:\OSES_project\SBS\rt-thread\include" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\common" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\cortex-a" -include"C:\OSES_project\SBS\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

