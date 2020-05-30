project (test_slm_memory)

# collect the source files
file (GLOB SOURCES *.cpp)
# collect the include files
file (GLOB INCLUDES *.hpp *.h)

# find the packages the code depends on
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(BOOST ${BOOST_VERSION})
find_package(CPPUNIT)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${CPPUNIT_INCLUDE_DIR})
include_directories(${STILLWATER_COMMON_INCLUDE_DIR})
include_directories(${STILLWATER_ROOT_DIR})

# add a library target
add_executable(test_slm_memory ${SOURCES} ${INCLUDES})
target_link_libraries(test_slm_memory common_diagnostics common_automation slm_memory srm_memmgr ${CPPUNIT_LIB})
add_test(slm_memory ${EXECUTABLE_OUTPUT_PATH}/test_slm_memory)
