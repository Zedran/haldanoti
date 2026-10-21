# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

cmake_minimum_required(VERSION 3.31)

option(MAKE_TESTS "Build test target" OFF)
option(COVER "Generate test coverage report target if MAKE_TESTS=ON" OFF)
option(HALDANOTI_VERSION "Version info is typically set through git describe. This override can be used when building from archive.")
option(HALDANOTI_SET_TC_FLAGS "Set compiler flags defined in cmake/TC_*.cmake files." OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD           20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        OFF)

if(HALDANOTI_SET_TC_FLAGS)
    if(LINUX)
        include(TC_GCC)
    elseif(WIN32)
        include(TC_MSVC)
    endif()
endif()

project(haldanoti C CXX)

set(BUILD_SHARED_LIBS OFF)

include(FetchSFML)
include(FetchJSON)
include(FetchFont)

include(MakeAppDataDev)

add_custom_target(configure_header
    COMMAND ${CMAKE_COMMAND}
        -DPROJECT_NAME="${PROJECT_NAME}"
        -DHALDANOTI_VERSION="${HALDANOTI_VERSION}"
        -DINPUT_FILE="${CMAKE_SOURCE_DIR}/src/config.hpp.in"
        -DOUTPUT_FILE="${CMAKE_BINARY_DIR}/src/config.hpp"
        -P "${CMAKE_SOURCE_DIR}/cmake/configure_header.cmake"
)

add_library(core_defs INTERFACE)

add_subdirectory(core)

if(WIN32 AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME} WIN32
        src/main.cpp
        ${CMAKE_SOURCE_DIR}/platform/windows/haldanoti.rc
    )
else()
    add_executable(${PROJECT_NAME} src/main.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE core)

if(NOT LINUX)
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Main)
endif()

add_dependencies(${PROJECT_NAME} configure_header)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/src)

if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
    execute_process(
        COMMAND
            ${CMAKE_COMMAND} -E create_symlink
            "${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}"
            "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
        COMMAND_ERROR_IS_FATAL ANY
    )
endif()

include(InstallArtifacts)

if(WIN32 AND CPACK_GENERATOR)
    include(BuildNSIS)
endif()

if(MAKE_TESTS)
    include(FetchCatch2)

    enable_testing()
    add_subdirectory(tests)
endif()
