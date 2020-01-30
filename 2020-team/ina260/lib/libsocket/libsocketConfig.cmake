set(libsocket_INCLUDE_DIRS "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket/headers")

set(libsocket_BINARY_DIR "/Users/stefanschokker/Documents/school/SFS/power/ina260/lib/libsocket")

include(${libsocket_BINARY_DIR}/libsocketTargets.cmake)

set(libsocket_LIBRARIES socket++)
