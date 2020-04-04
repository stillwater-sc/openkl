file (GLOB LIB_SOURCES "*.cpp")

message(STATUS "The library sources are ${LIB_SOURCES}") # only for testing

add_library(proxy_lib ${LIB_SOURCES})
