set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-std=gnu++17 \
-Wall \
-Werror \
-fno-rtti \
-fno-exceptions \
-fno-unwind-tables \
-fno-asynchronous-unwind-tables \
-fno-threadsafe-statics \
-ffunction-sections \
-fdata-sections \
")

set(LD_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/tm4c123gh6pm.ld")
set(CMAKE_EXE_LINKER_FLAGS "\
-Wl,-gc-sections \
-Wl,-Map=main.map \
-Wl,-T ${LD_SCRIPT} \
")

find_package(TivaWare REQUIRED COMPONENTS driverlib QUIET)

include_directories(
	${TivaWare_INCLUDE_DIRS}
)

add_executable(example
	example.cpp
	startup.cpp)

target_link_libraries(example
	${TivaWare_LIBRARIES}
)

# add 'objdump' target - makes objdump from compiled program without code snippets
add_custom_target(objdump
	COMMAND arm-none-eabi-objdump -d -C example >objdump
	DEPENDS example)

# add 'objdump-full' target - makes objdump, but with full code listing
add_custom_target(objdump-full
	COMMAND arm-none-eabi-objdump -D -x -s -t -r -S -C example >objdump
	DEPENDS example)