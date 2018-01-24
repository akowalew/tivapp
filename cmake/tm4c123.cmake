# tm4c123.cmake
# Toolchain file for TM4C123 series microcontrollers
# Author: akowalew

include (CMakeForceCompiler)

set(CMAKE_CROSSCOMPILE ON CACHE BOOL "Cross-compiling" FORCE)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(MCU TM4C123GH6PM)

# specify the cross compiler
# set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)

# prevent from running linekr during compiler test
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY CACHE STRING "" FORCE)

set(CMAKE_C_FLAGS "\
	-march=armv7e-m \
	-mcpu=cortex-m4 \
	-mtune=cortex-m4 \
	-mfpu=fpv4-sp-d16 \
	-mthumb \
	-mfloat-abi=hard \
	-DPART_${MCU} \
	-DTARGET_IS_TM4C123_RA3"
	CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "\
	-march=armv7e-m \
	-mcpu=cortex-m4 \
	-mtune=cortex-m4 \
	-mfpu=fpv4-sp-d16 \
	-mthumb \
	-mfloat-abi=hard \
	-DPART_${MCU} \
	-DTARGET_IS_TM4C123_RA3"
	CACHE STRING "" FORCE)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  
	/opt/embedded/bleeding-edge-toolchain/installNative
)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
