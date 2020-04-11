project(kpu_shim_lib)

# The files in the KPU shim library are organized in their own functional blocks
# frontend, memory, and fabric
file (GLOB LIB_SOURCES "*/*.cpp")

message(STATUS "The library sources are ${LIB_SOURCES}") # just for testing

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "kpu_shim_lib " ${CMAKE_SOURCE_DIR})

add_library(kpu_shim_lib ${LIB_SOURCES})
