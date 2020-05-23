project (memory_testbench)

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp *.h)

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "memory_testbench " ${CMAKE_SOURCE_DIR})

# add a library target
add_executable(test_memory ${SOURCES} ${INCLUDES})
target_link_libraries(test_memory kpu_shim_lib common_automation_lib common_diagnostics_lib)

add_test(test_memory ${EXECUTABLE_OUTPUT_PATH}/test_memory)
set_target_properties(test_memory PROPERTIES FOLDER "Tests/components")
