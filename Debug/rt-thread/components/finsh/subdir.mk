################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/components/finsh/cmd.c \
../rt-thread/components/finsh/finsh_compiler.c \
../rt-thread/components/finsh/finsh_error.c \
../rt-thread/components/finsh/finsh_heap.c \
../rt-thread/components/finsh/finsh_init.c \
../rt-thread/components/finsh/finsh_node.c \
../rt-thread/components/finsh/finsh_ops.c \
../rt-thread/components/finsh/finsh_parser.c \
../rt-thread/components/finsh/finsh_token.c \
../rt-thread/components/finsh/finsh_var.c \
../rt-thread/components/finsh/finsh_vm.c \
../rt-thread/components/finsh/msh.c \
../rt-thread/components/finsh/msh_file.c \
../rt-thread/components/finsh/shell.c 

OBJS += \
./rt-thread/components/finsh/cmd.o \
./rt-thread/components/finsh/finsh_compiler.o \
./rt-thread/components/finsh/finsh_error.o \
./rt-thread/components/finsh/finsh_heap.o \
./rt-thread/components/finsh/finsh_init.o \
./rt-thread/components/finsh/finsh_node.o \
./rt-thread/components/finsh/finsh_ops.o \
./rt-thread/components/finsh/finsh_parser.o \
./rt-thread/components/finsh/finsh_token.o \
./rt-thread/components/finsh/finsh_var.o \
./rt-thread/components/finsh/finsh_vm.o \
./rt-thread/components/finsh/msh.o \
./rt-thread/components/finsh/msh_file.o \
./rt-thread/components/finsh/shell.o 

C_DEPS += \
./rt-thread/components/finsh/cmd.d \
./rt-thread/components/finsh/finsh_compiler.d \
./rt-thread/components/finsh/finsh_error.d \
./rt-thread/components/finsh/finsh_heap.d \
./rt-thread/components/finsh/finsh_init.d \
./rt-thread/components/finsh/finsh_node.d \
./rt-thread/components/finsh/finsh_ops.d \
./rt-thread/components/finsh/finsh_parser.d \
./rt-thread/components/finsh/finsh_token.d \
./rt-thread/components/finsh/finsh_var.d \
./rt-thread/components/finsh/finsh_vm.d \
./rt-thread/components/finsh/msh.d \
./rt-thread/components/finsh/msh_file.d \
./rt-thread/components/finsh/shell.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/components/finsh/%.o: ../rt-thread/components/finsh/%.c
	arm-none-eabi-gcc -march=armv7-a -marm -mfloat-abi=soft -O0 -Wall  -g -gdwarf-2 -DDEBUG -I"C:\OSES_project\SBS" -I"C:\OSES_project\SBS\applications" -I"C:\OSES_project\SBS\drivers" -I"C:\OSES_project\SBS\rt-thread\components\cplusplus" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\devfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\elmfat" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\ramfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\romfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi\sfud\inc" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi" -I"C:\OSES_project\SBS\rt-thread\components\finsh" -I"C:\OSES_project\SBS\rt-thread\components\libc\aio" -I"C:\OSES_project\SBS\rt-thread\components\libc\compilers\newlib" -I"C:\OSES_project\SBS\rt-thread\components\libc\mmap" -I"C:\OSES_project\SBS\rt-thread\components\libc\pthreads" -I"C:\OSES_project\SBS\rt-thread\components\libc\signal" -I"C:\OSES_project\SBS\rt-thread\components\libc\termios" -I"C:\OSES_project\SBS\rt-thread\components\libc\time" -I"C:\OSES_project\SBS\rt-thread\components\lwp" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\arch\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include\netif" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src" -I"C:\OSES_project\SBS\rt-thread\components\net\netdev\include" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\impl" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\dfs_net" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket\sys_socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include" -I"C:\OSES_project\SBS\rt-thread\include" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\common" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\cortex-a" -include"C:\OSES_project\SBS\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

