################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cellular.cpp \
../file_ops.cpp \
../main.cpp \
../multi_hop.cpp \
../single_hop.cpp 

OBJS += \
./cellular.o \
./file_ops.o \
./main.o \
./multi_hop.o \
./single_hop.o 

CPP_DEPS += \
./cellular.d \
./file_ops.d \
./main.d \
./multi_hop.d \
./single_hop.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


