project (memory_lib)

# DERIVED variables
# none in this CMakeLists.txt

#define the include directories this library depends on
include_directories(${STILLWATER_COMMON_INCLUDE_DIR})
include_directories(${STILLWATER_ROOT_DIR})

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp)

add_library (memory STATIC ${SOURCES} ${INCLUDES})

