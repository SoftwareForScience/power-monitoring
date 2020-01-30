cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME ina260)
project(${PROJECT_NAME})

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lm -lwiringPi -lsocket++ -lpugixml -lpthread -Wall" )
set (CMAKE_REQUIRED_FLAGS -std=c++17)

file (GLOB SOURCE_FILES
		"src/*.hpp"
		"src/*.cpp"
		"lib/pugixml/src/*"
#		"lib/date/src/*"
#		"lib/date/include/date/*"
		"lib/args/args.hxx"
		"lib/args/catch.hpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(
		"/usr/local/include"
)

target_link_libraries(${PROJECT_NAME} stdc++fs pugixml socket++)

