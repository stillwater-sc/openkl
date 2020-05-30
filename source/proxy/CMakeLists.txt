file (GLOB LIB_SOURCES "*.cpp")

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "The library sources are ${LIB_SOURCES}") # only for testing

add_library(proxy_lib ${LIB_SOURCES})
set_target_properties(proxy_lib PROPERTIES FOLDER "Libraries")
