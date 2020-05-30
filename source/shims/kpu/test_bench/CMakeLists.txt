project (shim_kpu_testbench)

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp *.h)

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "memory_testbench " ${CMAKE_SOURCE_DIR})

# add a library target
add_executable(test_shim_kpu ${SOURCES} ${INCLUDES})
target_link_libraries(test_shim_kpu kpu_shim_lib common_automation_lib common_diagnostics_lib)

add_test(test_shim_kpu ${EXECUTABLE_OUTPUT_PATH}/test_shim_kpu)
set_target_properties(test_shim_kpu PROPERTIES FOLDER "Tests/components")