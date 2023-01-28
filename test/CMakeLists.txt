cmake_minimum_required(VERSION 3.10)

project(test_version VERSION ${MAJOR_NUMBER}.${MINOR_NUMBER}.${PATCH_VERSION} DESCRIPTION "Test" LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE
        src/test_version.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE})
set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/lib/include
        )

target_link_libraries(${PROJECT_NAME}
        #PRIVATE ${Boost_LIBRARIES}
        PRIVATE lib
        PRIVATE gtest
        PRIVATE gtest_main
        )

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()
