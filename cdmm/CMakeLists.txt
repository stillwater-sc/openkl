file (GLOB SOURCES "*.cpp")

# include directories we need
include_directories(${CMAKE_SOURCE_DIR}/${COMMON_INCLUDE_DIR})

set(cdmm "cdmm")
add_executable (${cdmm} ${SOURCES})
set_target_properties(${cdmm} PROPERTIES FOLDER "CDMM")
target_link_libraries(${cdmm} common_diagnostics_lib)


