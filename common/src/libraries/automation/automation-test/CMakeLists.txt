project (test_common_automation)

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp *.h)

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})
message(STATUS "test_common_automation " ${CMAKE_SOURCE_DIR})

# add a library target
add_executable(test_common_automation ${SOURCES} ${INCLUDES})
target_link_libraries(test_common_automation common_diagnostics_lib common_automation_lib)
set_target_properties(test_common_automation PROPERTIES FOLDER "Tests/common")

add_test(common_automation ${EXECUTABLE_OUTPUT_PATH}/test_common_automation)
#add_test(common_automation ${CMAKE_CTEST_COMMAND}
#		--build-and-test "${STILLWATER_ROOT_DIR}/Stillwater/Common/Libraries/automation/automation-test" ${EXECUTABLE_OUTPUT_PATH}
#		--build-generator ${CMAKE_GENERATOR}
#		--build-makeprogram ${CMAKE_MAKE_PROGRAM}
#		--build-project test_common_automation
#		--test-command ${CMAKE_CURRENT_BINARY_DIR}/test_common_automation
#		)