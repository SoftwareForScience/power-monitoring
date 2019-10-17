cmake_minimum_required(VERSION 3.15)
project(ina260)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -lm"   )
set (CMAKE_REQUIRED_FLAGS -std=c++17)

file (GLOB SOURCE_FILES
		"src/*.hpp"
		"src/*.cpp"
		"lib/ina219-linux-lib/ina219.c"
		"lib/ina219-linux-lib/ina219.h"
)

add_executable(ina260 ${SOURCE_FILES})
