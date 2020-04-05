# The files in the KPU shim library are organized in their own functional blocks
# frontend, memory, and fabric
file (GLOB LIB_SOURCES "*/*.cpp")

message(STATUS "The library sources are ${LIB_SOURCES}") # just for testing

# pull in the common include directory, which contain logging and monitoring cross-cut functionality
include_directories(${COMMON_INCLUDE_DIR})

add_library(kpu_shim_lib ${LIB_SOURCES})
