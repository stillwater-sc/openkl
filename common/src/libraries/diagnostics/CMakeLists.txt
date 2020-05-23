# set the include directory that contains the types
set(STILLWATER_DIAGNOSTICS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/common/include/stillwater/diagnostics)

# collect the source files
file (GLOB LIB_SOURCES *.cpp)
# collect the include files
file (GLOB LIB_INCLUDES "${STILLWATER_DIAGNOSTICS_INCLUDE_DIR}/*.hpp")

# However, remember that includes refer to these files as
# #include <stillwater/diagnostics/Logger.hpp> and thus the include
# directory to use for the compiler is COMMON
include_directories("${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR}")

add_library(common_diagnostics_lib ${LIB_SOURCES} ${LIB_INCLUDES})
set_target_properties(common_diagnostics_lib PROPERTIES FOLDER "Libraries/common")