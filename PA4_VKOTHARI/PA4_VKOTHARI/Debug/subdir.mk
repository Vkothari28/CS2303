################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Ant.cpp \
../Board.cpp \
../Doodlebug.cpp \
../Organism.cpp \
../main.cpp 

OBJS += \
./Ant.o \
./Board.o \
./Doodlebug.o \
./Organism.o \
./main.o 

CPP_DEPS += \
./Ant.d \
./Board.d \
./Doodlebug.d \
./Organism.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


