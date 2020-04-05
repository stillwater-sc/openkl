project (slm_memory)

# DERIVED variables
# none in this CMakeLists.txt

# find the library packages it depends on
#set(Boost_USE_STATIC_LIBS        ON)
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#find_package ( Boost ${BOOST_VERSION} )

#define the include directories this library depends on
#include_directories(${Boost_INCLUDE_DIR})
include_directories(${STILLWATER_COMMON_INCLUDE_DIR})
include_directories(${STILLWATER_ROOT_DIR})

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp)

add_library (memory STATIC ${SOURCES} ${INCLUDES})

