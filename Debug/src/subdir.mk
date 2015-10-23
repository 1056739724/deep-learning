################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/cost_gradient.cc \
../src/gradient_checking.cc \
../src/helper.cc \
../src/matrix_maths.cc \
../src/read_config.cc \
../src/read_data.cc \
../src/result_predict.cc \
../src/sample.cc \
../src/train_network.cc \
../src/weight_init.cc \
../src/weights_IO.cc 

OBJS += \
./src/cost_gradient.o \
./src/gradient_checking.o \
./src/helper.o \
./src/matrix_maths.o \
./src/read_config.o \
./src/read_data.o \
./src/result_predict.o \
./src/sample.o \
./src/train_network.o \
./src/weight_init.o \
./src/weights_IO.o 

CC_DEPS += \
./src/cost_gradient.d \
./src/gradient_checking.d \
./src/helper.d \
./src/matrix_maths.d \
./src/read_config.d \
./src/read_data.d \
./src/result_predict.d \
./src/sample.d \
./src/train_network.d \
./src/weight_init.d \
./src/weights_IO.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -std=c++11 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


