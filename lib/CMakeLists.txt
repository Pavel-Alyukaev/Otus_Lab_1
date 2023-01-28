cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(MAJOR_NUMBER 0 )
set(MINOR_NUMBER 0 )

project(lib VERSION ${MAJOR_NUMBER}.${MINOR_NUMBER}.${PATCH_VERSION} DESCRIPTION "LIB" LANGUAGES CXX)

message(STATUS ${MAJOR_NUMBER})


SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(include/version.h.in ${CMAKE_SOURCE_DIR}/lib/include/version.h)

set(SOURCE
        stdafx.h

        include/version.h
        include/lib.h

        src/lib.cpp
        include/SimpleCustomAllocator.h
        include/pretty.h)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()