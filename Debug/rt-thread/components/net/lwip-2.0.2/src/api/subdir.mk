################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/components/net/lwip-2.0.2/src/api/api_lib.c \
../rt-thread/components/net/lwip-2.0.2/src/api/api_msg.c \
../rt-thread/components/net/lwip-2.0.2/src/api/err.c \
../rt-thread/components/net/lwip-2.0.2/src/api/netbuf.c \
../rt-thread/components/net/lwip-2.0.2/src/api/netdb.c \
../rt-thread/components/net/lwip-2.0.2/src/api/netifapi.c \
../rt-thread/components/net/lwip-2.0.2/src/api/sockets.c \
../rt-thread/components/net/lwip-2.0.2/src/api/tcpip.c 

OBJS += \
./rt-thread/components/net/lwip-2.0.2/src/api/api_lib.o \
./rt-thread/components/net/lwip-2.0.2/src/api/api_msg.o \
./rt-thread/components/net/lwip-2.0.2/src/api/err.o \
./rt-thread/components/net/lwip-2.0.2/src/api/netbuf.o \
./rt-thread/components/net/lwip-2.0.2/src/api/netdb.o \
./rt-thread/components/net/lwip-2.0.2/src/api/netifapi.o \
./rt-thread/components/net/lwip-2.0.2/src/api/sockets.o \
./rt-thread/components/net/lwip-2.0.2/src/api/tcpip.o 

C_DEPS += \
./rt-thread/components/net/lwip-2.0.2/src/api/api_lib.d \
./rt-thread/components/net/lwip-2.0.2/src/api/api_msg.d \
./rt-thread/components/net/lwip-2.0.2/src/api/err.d \
./rt-thread/components/net/lwip-2.0.2/src/api/netbuf.d \
./rt-thread/components/net/lwip-2.0.2/src/api/netdb.d \
./rt-thread/components/net/lwip-2.0.2/src/api/netifapi.d \
./rt-thread/components/net/lwip-2.0.2/src/api/sockets.d \
./rt-thread/components/net/lwip-2.0.2/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/components/net/lwip-2.0.2/src/api/%.o: ../rt-thread/components/net/lwip-2.0.2/src/api/%.c
	arm-none-eabi-gcc -march=armv7-a -marm -mfloat-abi=soft -O0 -Wall  -g -gdwarf-2 -DDEBUG -I"C:\OSES_project\SBS" -I"C:\OSES_project\SBS\applications" -I"C:\OSES_project\SBS\drivers" -I"C:\OSES_project\SBS\rt-thread\components\cplusplus" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\devfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\elmfat" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\ramfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\romfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi\sfud\inc" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi" -I"C:\OSES_project\SBS\rt-thread\components\finsh" -I"C:\OSES_project\SBS\rt-thread\components\libc\aio" -I"C:\OSES_project\SBS\rt-thread\components\libc\compilers\newlib" -I"C:\OSES_project\SBS\rt-thread\components\libc\mmap" -I"C:\OSES_project\SBS\rt-thread\components\libc\pthreads" -I"C:\OSES_project\SBS\rt-thread\components\libc\signal" -I"C:\OSES_project\SBS\rt-thread\components\libc\termios" -I"C:\OSES_project\SBS\rt-thread\components\libc\time" -I"C:\OSES_project\SBS\rt-thread\components\lwp" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\arch\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include\netif" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src" -I"C:\OSES_project\SBS\rt-thread\components\net\netdev\include" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\impl" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\dfs_net" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket\sys_socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include" -I"C:\OSES_project\SBS\rt-thread\include" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\common" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\cortex-a" -include"C:\OSES_project\SBS\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

