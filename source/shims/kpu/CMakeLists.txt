project(kpu_shim_lib)

# The files in the KPU shim library are organized in their own functional blocks
# frontend, memory, and fabric
file (GLOB LIB_SOURCES "toplevel/*.cpp" "frontend/*.cpp" "memory/*.cpp" "fabric/*.cpp")

message(STATUS "The library sources are ${LIB_SOURCES}") # just for testing

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "kpu_shim_lib " ${CMAKE_SOURCE_DIR})

add_library(kpu_shim_lib ${LIB_SOURCES})
set_target_properties(kpu_shim_lib PROPERTIES FOLDER "Libraries/shims")
