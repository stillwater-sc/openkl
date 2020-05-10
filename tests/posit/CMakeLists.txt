file (GLOB SOURCES "./*.cpp")

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})

#compile_all("true" "posit" "Tests/posit" "${SOURCES}")
# cycle through the sources
# For the according directories, we assume that each cpp file is a separate test
# and create a executable target and an associated test target for that file
foreach (source ${SOURCES})
    get_filename_component (test ${source} NAME_WE)
    string(REPLACE " " ";" new_source ${source})
    set(test_name "posit_${test}")
    message(STATUS "Add test ${test_name} from source ${new_source}.")
    add_executable (${test_name} ${new_source})
    set_target_properties(${test_name} PROPERTIES FOLDER "Tests/posit")
    target_link_libraries(${test_name} openkl_lib proxy_lib kpu_shim_lib common_automation_lib common_diagnostics_lib)

	if (OPENKL_CMAKE_TRACE)
        message(STATUS "testing: ${test_name} ${RUNTIME_OUTPUT_DIRECTORY}/${test_name}")
    endif()
    add_test(${test_name} ${RUNTIME_OUTPUT_DIRECTORY}/${test_name})
endforeach (source)

