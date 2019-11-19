cmake_minimum_required(VERSION 3.15)
project(ina260)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lm -lwiringPi -lpugixml -lpthread -Wall" )
set (CMAKE_REQUIRED_FLAGS -std=c++17)

file (GLOB SOURCE_FILES
		"src/*.hpp"
		"src/*.cpp"
		"lib/pugixml/src/*"
#		"lib/date/src/*"
#		"lib/date/include/date/*"
)

add_executable(ina260 ${SOURCE_FILES})

include_directories(
		"/usr/local/include"
)

target_link_libraries(ina260 stdc++fs pugixml)

