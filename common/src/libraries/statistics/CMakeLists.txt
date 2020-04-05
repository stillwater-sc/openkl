# set the include directory that contains the types
set(STILLWATER_STATISTICS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/common/include/stillwater/statistics)

# collect the source files
file (GLOB LIB_SOURCES *.cpp)
# collect the include files
file (GLOB LIB_INCLUDES "${STILLWATER_STATISTICS_INCLUDE_DIR}/*.hpp")

# Remember that source files refer to these files as
# #include <stillwater/statistics/histogram.hpp> and thus the include
# directory to use for the compiler is COMMON
include_directories ("${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR}")

add_library (common_statistics_lib STATIC ${LIB_SOURCES} ${LIB_INCLUDES})