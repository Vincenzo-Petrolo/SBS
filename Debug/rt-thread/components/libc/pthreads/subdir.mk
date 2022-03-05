################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/components/libc/pthreads/mqueue.c \
../rt-thread/components/libc/pthreads/pthread.c \
../rt-thread/components/libc/pthreads/pthread_attr.c \
../rt-thread/components/libc/pthreads/pthread_barrier.c \
../rt-thread/components/libc/pthreads/pthread_cond.c \
../rt-thread/components/libc/pthreads/pthread_mutex.c \
../rt-thread/components/libc/pthreads/pthread_rwlock.c \
../rt-thread/components/libc/pthreads/pthread_spin.c \
../rt-thread/components/libc/pthreads/pthread_tls.c \
../rt-thread/components/libc/pthreads/sched.c \
../rt-thread/components/libc/pthreads/semaphore.c 

OBJS += \
./rt-thread/components/libc/pthreads/mqueue.o \
./rt-thread/components/libc/pthreads/pthread.o \
./rt-thread/components/libc/pthreads/pthread_attr.o \
./rt-thread/components/libc/pthreads/pthread_barrier.o \
./rt-thread/components/libc/pthreads/pthread_cond.o \
./rt-thread/components/libc/pthreads/pthread_mutex.o \
./rt-thread/components/libc/pthreads/pthread_rwlock.o \
./rt-thread/components/libc/pthreads/pthread_spin.o \
./rt-thread/components/libc/pthreads/pthread_tls.o \
./rt-thread/components/libc/pthreads/sched.o \
./rt-thread/components/libc/pthreads/semaphore.o 

C_DEPS += \
./rt-thread/components/libc/pthreads/mqueue.d \
./rt-thread/components/libc/pthreads/pthread.d \
./rt-thread/components/libc/pthreads/pthread_attr.d \
./rt-thread/components/libc/pthreads/pthread_barrier.d \
./rt-thread/components/libc/pthreads/pthread_cond.d \
./rt-thread/components/libc/pthreads/pthread_mutex.d \
./rt-thread/components/libc/pthreads/pthread_rwlock.d \
./rt-thread/components/libc/pthreads/pthread_spin.d \
./rt-thread/components/libc/pthreads/pthread_tls.d \
./rt-thread/components/libc/pthreads/sched.d \
./rt-thread/components/libc/pthreads/semaphore.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/components/libc/pthreads/%.o: ../rt-thread/components/libc/pthreads/%.c
	arm-none-eabi-gcc -march=armv7-a -marm -mfloat-abi=soft -O0 -Wall  -g -gdwarf-2 -DDEBUG -I"C:\OSES_project\SBS" -I"C:\OSES_project\SBS\applications" -I"C:\OSES_project\SBS\drivers" -I"C:\OSES_project\SBS\rt-thread\components\cplusplus" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\devfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\elmfat" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\ramfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\filesystems\romfs" -I"C:\OSES_project\SBS\rt-thread\components\dfs\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\include" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi\sfud\inc" -I"C:\OSES_project\SBS\rt-thread\components\drivers\spi" -I"C:\OSES_project\SBS\rt-thread\components\finsh" -I"C:\OSES_project\SBS\rt-thread\components\libc\aio" -I"C:\OSES_project\SBS\rt-thread\components\libc\compilers\newlib" -I"C:\OSES_project\SBS\rt-thread\components\libc\mmap" -I"C:\OSES_project\SBS\rt-thread\components\libc\pthreads" -I"C:\OSES_project\SBS\rt-thread\components\libc\signal" -I"C:\OSES_project\SBS\rt-thread\components\libc\termios" -I"C:\OSES_project\SBS\rt-thread\components\libc\time" -I"C:\OSES_project\SBS\rt-thread\components\lwp" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\arch\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include\netif" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src\include" -I"C:\OSES_project\SBS\rt-thread\components\net\lwip-2.0.2\src" -I"C:\OSES_project\SBS\rt-thread\components\net\netdev\include" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\impl" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\dfs_net" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket\sys_socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include\socket" -I"C:\OSES_project\SBS\rt-thread\components\net\sal_socket\include" -I"C:\OSES_project\SBS\rt-thread\include" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\common" -I"C:\OSES_project\SBS\rt-thread\libcpu\arm\cortex-a" -include"C:\OSES_project\SBS\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

