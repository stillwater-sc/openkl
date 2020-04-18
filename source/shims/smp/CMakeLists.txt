project(cpu_shim_lib)

# The files in the CPU shim library are organized in their own functional blocks
# cores, memory, toplevel
file (GLOB LIB_SOURCES "*/*.cpp")

message(STATUS "The library sources are ${LIB_SOURCES}") # just for testing

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "cpu_shim_lib " ${CMAKE_SOURCE_DIR})

add_library(cpu_shim_lib ${LIB_SOURCES})
