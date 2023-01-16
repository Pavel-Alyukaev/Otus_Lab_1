cmake_minimum_required(VERSION 3.20)

set(MAJOR_NUMBER 0)
set(MINOR_NUMBER 0)
set(PATCH_VERSION "1" )

project(helloword VERSION 1.0.0 LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_BUILD_TYPE)

SET(BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

add_subdirectory("Main")
add_subdirectory("lib")
add_subdirectory("test")

install(TARGETS HelloWord)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")