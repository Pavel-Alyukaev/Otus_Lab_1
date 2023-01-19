cmake_minimum_required(VERSION 3.20)

set(MAJOR_NUMBER 0)
set(MINOR_NUMBER 0)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

project(helloword VERSION ${MAJOR_NUMBER}.${MINOR_NUMBER}.${PATCH_VERSION} LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_BUILD_TYPE)

SET(BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

add_subdirectory("Main")
add_subdirectory("lib")
add_subdirectory("test")

install(TARGETS ${CMAKE_SOURCE_DIR}/bin/Release/HelloWord RUNTIME DESTINATION ${BIN_DIR})

set(CPACK_GENERATOR DEB)


set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set (CMAKE_INSTALL_RPATH ${CMAKE_SOURCE_DIR})
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version ${BIN_DIR}/test_version)
