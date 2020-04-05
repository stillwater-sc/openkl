project (test_common_statistics)

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp *.h)

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})

# add a library target
add_executable(test_common_statistics ${SOURCES} ${INCLUDES})
target_link_libraries(test_common_statistics common_diagnostics_lib common_statistics_lib)

add_test(common_statistics ${EXECUTABLE_OUTPUT_PATH}/test_common_statistics)
#add_test(common_statistics ${CMAKE_CTEST_COMMAND}
#		--build-and-test "${STILLWATER_ROOT_DIR}/Stillwater/Common/Libraries/statistics/statistics-test" ${EXECUTABLE_OUTPUT_PATH}
#		--build-generator ${CMAKE_GENERATOR}
#		--build-makeprogram ${CMAKE_MAKE_PROGRAM}
#		--build-project test_common_statistics
#		--test-command ${CMAKE_CURRENT_BINARY_DIR}/test_common_statistics
#		)
