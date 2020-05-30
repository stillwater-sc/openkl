project (common_automation)

# set the include directory that contains the types
set(STILLWATER_STATISTICS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/common/include/stillwater/automation)

# collect the source files
file (GLOB LIB_SOURCES *.cpp)
# collect the include files
file (GLOB LIB_INCLUDES "${STILLWATER_AUTOMATION_INCLUDE_DIR}/*.hpp")

# Remember that source files refer to these files as
# #include <stillwater/automation/Logger.hpp> and thus the include
# directory to use for the compiler is COMMON
include_directories ("${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR}")

add_library (common_automation_lib STATIC ${LIB_SOURCES} ${LIB_INCLUDES})
set_target_properties(common_automation_lib PROPERTIES FOLDER "Libraries/common")