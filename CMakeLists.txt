# Set minimum version of CMake. Since we are using the VERSION option of the
# project command, we need at least 3.0. To honor the amazing work that
# the folks at KitWare have done for the open source community, we are
# going to specify a recent version. 
# As of UNIVERSAL v2.0 December 2018
# Ubuntu 16.04 LTS runs cmake 3.5.1
# Ubuntu 18.04 LTS runs cmake 3.10.2
# container runs cmake 3.7.1
cmake_minimum_required(VERSION 3.5)

####
## Enable project() command to manage VERSION variables
if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)
####
## Enable package_ROOT variables
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif(POLICY CMP0074)


############
# OpenKL: Virtual Machine for Knowledge Processing
# set project variables
if(NOT DEFINED OPENKL_VERSION_MAJOR)
  set(OPENKL_VERSION_MAJOR 0)
endif()
if(NOT DEFINED OPENKL_VERSION_MINOR)
  set(OPENKL_VERSION_MINOR 1)
endif()
if(NOT DEFINED OPENKL_VERSION_PATCH)
  set(OPENKL_VERSION_PATCH 1)
endif()
project (openkl 
	VERSION "${OPENKL_VERSION_MAJOR}.${OPENKL_VERSION_MINOR}.${OPENKL_VERSION_PATCH}"
	LANGUAGES C CXX ASM)

# C++ package manager configuration
# set the vcpkg-root
set(VCPKG_ROOT "" CACHE PATH "Root directory of the vcpkg manager's database of installed C++ environments")
set(CMAKE_TOOL_CHAIN_FILE "" CACHE PATH "Full path to the vcpkg.cmake file, typically under VCPKG-ROOT/scripts/buildsystem/vcpkg.cmake")

####
# Change default build type to Release
#
# The CACHE STRING logic here and elsewhere is needed to force CMake
# to pay attention to the value of these variables.
if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No default build type specified: setting CMAKE_BUILD_TYPE=Release")
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the build type: options are: Debug Release RelWithDebInfo MinSizeRel"
		FORCE)
else(NOT CMAKE_BUILD_TYPE)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message("====================================================================================")
		message(STATUS "Build type is set to Debug: Performance will be negatively impacted")
		message(STATUS "Add -DCMAKE_BUILD_TYPE=Release to the CMake command line to get an optimized build")
		message("====================================================================================")
	endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif(NOT CMAKE_BUILD_TYPE)

######
# Set build options
option(USE_AVX2                      "Build code with AVX2 ISA support"          OFF)
#
####
# control which project get enabled
option(BUILD_ALL                     "Build all projects"                        ON)
#
option(MSVC_USE_FOLDERS              "Enable folders in Visual Study, disable for Express" ON)
if(MSVC_USE_FOLDERS)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

####
# Create the library target
set(project_library_target_name ${PROJECT_NAME})
set(PACKAGE_NAME openkl)

####
# Set environmental options for tracing, testing, and verbosity
option(OPENKL_CMAKE_TRACE "Tracing CMake results, i.e. printing variable settings." OFF)
option(OPENKL_ENABLE_TESTS "Enable the build and run of tests." ON)
option(OPENKL_VERBOSE_TESTS "Always print test output, otherwise only errors. Only relevant when tests enabled." OFF)

macro(trace_variable variable)
    if (OPENKL_CMAKE_TRACE)
        message(STATUS "${variable} = ${${variable}}")
    endif()
endmacro()
        
# TODO: Check whether this is needed for old CMake versions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake") 
trace_variable(CMAKE_MODULE_PATH)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake") 
trace_variable(CMAKE_PREFIX_PATH)

# Must be located in root dir, doesn't work in tests
if (OPENKL_ENABLE_TESTS)
    enable_testing()
    # include(Dart)
endif()

# Let's try without Boost if possible
# find_package(Boost)
# message(STATUS "Boost_FOUND " ${Boost_FOUND})
# if (Boost_FOUND)
# 	message(STATUS "Including Boost_INCLUDE_DIR " ${Boost_INCLUDE_DIR})
# 	include_directories(${Boost_INCLUDE_DIR})
# endif (Boost_FOUND)

# And without MTL for the moment
# MTL5 is used in the tests but for the moment not in the implementation
# cmake_policy(SET CMP0054 NEW)
# find_package(MTL REQUIRED)
# include_directories(${MTL_INCLUDE_DIRS})
# add_definitions(${MTL_CXX_DEFINITIONS})
# message(STATUS "MTL INCLUDE DIR " ${MTL_INCLUDE_DIRS})

# Set posit include directory
#find_package(UNIVERSAL REQUIRED) # where do I get the package?
set(UNIVERSAL_INCLUDE_DIRS "" CACHE PATH "The include directory for the Universal number library")
include_directories(${UNIVERSAL_INCLUDE_DIRS})
    
message(STATUS "The UNIVERSAL INCLUDE DIR is " ${UNIVERSAL_INCLUDE_DIRS})

#The package protobuf:x64-windows provides CMake targets:
#find_package(protobuf CONFIG REQUIRED)
#target_link_libraries(main PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

find_package(gRPC "1.29.1" CONFIG REQUIRED)
#add_executable(my_exe my_exe.cpp)
#target_link_libraries(my_exe gRPC::grpc++)

# Set openkl include directory
set(OPENKL_INCLUDE_DIR "include")
include_directories(${OPENKL_INCLUDE_DIR})
message(STATUS "The OPENKL INCLUDE DIR is " ${OPENKL_INCLUDE_DIR})

# set common include directory
set(COMMON_INCLUDE_DIR "common/include")
message(STATUS "The COMMON INCLUDE DIR is " ${COMMON_INCLUDE_DIR})

####
# Configure the compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++17 support has been enabled by default")

macro (compile_all testing prefix folder)
    # cycle through the sources
    # For the according directories, we assume that each cpp file is a separate test
    # and create a executable target and an associated test target for that file
    foreach (source ${ARGN})
        get_filename_component (test ${source} NAME_WE)
        string(REPLACE " " ";" new_source ${source})
        set(test_name ${prefix}_${test})
        message(STATUS "Add test ${test_name} from source ${new_source}.")
        add_executable (${test_name} ${new_source})
		set_target_properties(${test_name} PROPERTIES FOLDER ${folder})
		target_link_libraries(${test_name} openkl_lib proxy_lib kpu_shim_lib)
        if (${testing} STREQUAL "true")
	    if (OPENKL_CMAKE_TRACE)
                message(STATUS "testing: ${test_name} ${RUNTIME_OUTPUT_DIRECTORY}/${test_name}")
            endif()
            add_test(${test_name} ${RUNTIME_OUTPUT_DIRECTORY}/${test_name})
        endif()
    endforeach (source)
endmacro (compile_all)

# Set up install directories. INCLUDE_INSTALL_DIR and
# CMAKECONFIG_INSTALL_DIR must not be absolute paths.
if(WIN32)
    set(include_install_dir Include)
    set(include_install_dir_full Include)
    set(config_install_dir CMake)
elseif(UNIX)
    set(include_install_dir include)
    set(include_install_dir_postfix "${project_library_target_name}")
    set(include_install_dir_full    "${include_install_dir}/${include_install_dir_postfix}")

    set(config_install_dir share/${PACKAGE_NAME})
else()
    message(FATAL_ERROR "Not supported system type. Options: UNIX or WIN32.")
endif()

# build the libraries
add_subdirectory("common/src/libraries")
add_subdirectory("source/openkl")
add_subdirectory("source/proxy")
add_subdirectory("source/shims/smp")
add_subdirectory("source/shims/kpu")

# build test suites
add_subdirectory("tests")
add_subdirectory("source/shims/kpu/memory/test_bench")
add_subdirectory("source/shims/kpu/test_bench")
add_subdirectory("source/proxy/test_bench")

# build the cloud-native container-based distributed memory machine
add_subdirectory("cdmm")

# build demo programs
add_subdirectory("applications/krylov")
add_subdirectory("demos")

