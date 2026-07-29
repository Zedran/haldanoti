# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

cmake_minimum_required(VERSION 3.14)

option(MAKE_TESTS "Build test target" OFF)
option(COVER "Generate test coverage report target if MAKE_TESTS=ON" OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD           20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        OFF)

if(LINUX)
    include(TC_GCC)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

project(mm C CXX)

include(FetchSFML)
include(FetchFont)

add_custom_target(configure_header
    COMMAND ${CMAKE_COMMAND}
        -DPROJECT_NAME="${PROJECT_NAME}"
        -DINPUT_FILE="${CMAKE_SOURCE_DIR}/src/config.hpp.in"
        -DOUTPUT_FILE="${CMAKE_BINARY_DIR}/src/config.hpp"
        -P "${CMAKE_SOURCE_DIR}/cmake/configure_header.cmake"
)

add_subdirectory(core)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE core)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    FONT_FILE_PATH_DEV="${FONT_FILE_PATH}"
    ICON_FILE_PATH_DEV="${CMAKE_SOURCE_DIR}/assets/mm.png"
)

add_dependencies(${PROJECT_NAME} configure_header)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/src)

include(InstallArtifacts)

if(MAKE_TESTS)
    include(FetchCatch2)

    enable_testing()
    add_subdirectory(tests)
endif()
