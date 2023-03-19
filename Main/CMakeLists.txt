cmake_minimum_required(VERSION 3.10)

project(Allocator VERSION ${MAJOR_NUMBER}.${MINOR_NUMBER}.${PATCH_VERSION} DESCRIPTION "Allocator" LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE
        src/main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE})

set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR} )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(${PROJECT_NAME} PRIVATE lib)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()


