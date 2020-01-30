# Install script for directory: /Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libsocket" TYPE FILE FILES
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./unixdgram.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./exception.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./inetclientdgram.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./libinetsocket.h"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./unixserverstream.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./dgramclient.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./streamclient.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./inetserverstream.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./unixclientdgram.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./socket.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./inetbase.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./inetserverdgram.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./unixclientstream.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./libunixsocket.h"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./select.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./inetclientstream.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./unixbase.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./unixserverdgram.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./inetdgram.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./dgramoverstream.hpp"
    "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers/./framing.hpp"
    )
endif()

