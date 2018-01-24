cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(tivapp)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

option(TIVAPP_COMPILE_EXAMPLES "Compile example programs" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories(include)

if(TIVAPP_COMPILE_EXAMPLES)
	add_subdirectory(examples)
endif()

add_subdirectory(src)