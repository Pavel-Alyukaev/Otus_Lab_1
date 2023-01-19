cmake_minimum_required(VERSION 3.10)

project(test_version VERSION ${MAJOR_NUMBER}.${MINOR_NUMBER}.${PATCH_VERSION} DESCRIPTION "Test" LANGUAGES CXX)
message(STATUS "${CMAKE_SOURCE_DIR}/lib/include")
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE
        src/test_version.cpp
        )
#find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(${PROJECT_NAME} ${SOURCE})
set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR} )

#set_target_properties(${PROJECT_NAME} PROPERTIES
#
        #INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#        )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(${PROJECT_NAME}
        #PRIVATE ${Boost_LIBRARIES}
        PRIVATE lib
        )

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

