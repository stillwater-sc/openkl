project (proxy_testbench)

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp *.h)

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "proxy_testbench " ${CMAKE_SOURCE_DIR})

# add a library target
add_executable(test_proxy ${SOURCES} ${INCLUDES})
target_link_libraries(test_proxy proxy_lib cpu_shim_lib kpu_shim_lib common_automation_lib common_diagnostics_lib)

add_test(test_proxy ${EXECUTABLE_OUTPUT_PATH}/test_proxy)
set_target_properties(test_proxy PROPERTIES FOLDER "Tests/components")