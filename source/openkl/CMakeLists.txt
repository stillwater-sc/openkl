file (GLOB LIB_SOURCES "*/*.cpp")

message(STATUS "The library sources are ${LIB_SOURCES}") # only for testing

add_library(openkl_lib ${LIB_SOURCES})
set_target_properties(openkl_lib PROPERTIES FOLDER "Libraries")
