
# Quick hack, replace it by find_package at some point
set(MTL_INCLUDE_DIRS "" CACHE PATH "The include directory for MTL5")
include_directories(${MTL_INCLUDE_DIRS})    
message(STATUS "The MTL5 INCLUDE DIR is " ${MTL_INCLUDE_DIRS})

add_subdirectory("posit")

add_subdirectory("vec")
add_subdirectory("mat")

add_subdirectory("operations")
