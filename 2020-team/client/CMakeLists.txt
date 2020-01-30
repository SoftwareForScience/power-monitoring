cmake_minimum_required(VERSION 3.13)
project(client)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lsocket++ -Wall" )
set (CMAKE_REQUIRED_FLAGS -std=c++17)

file (GLOB SOURCE_FILES
		"src/*.hpp"
		"src/*.cpp"
)

add_executable(client ${SOURCE_FILES})

include_directories(
		"/usr/local/include"
)

target_link_libraries(client socket++)

