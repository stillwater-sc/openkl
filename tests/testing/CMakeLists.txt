file (GLOB TEST_SOURCES "./*_test.cpp")

compile_all("true" "testing" "Tests/testing" "${TEST_SOURCES}")
