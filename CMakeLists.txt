# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

cmake_minimum_required(VERSION 3.25)

option(MAKE_TESTS "Build test target" OFF)
option(COVER "Generate test coverage report target if MAKE_TESTS=ON" OFF)
option(MM_VERSION "Version info is typically set through git describe. This override can be used when building from archive.")
option(MM_SET_TC_FLAGS "Set compiler flags defined in cmake/TC_*.cmake files." OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD           20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        OFF)

if(MM_SET_TC_FLAGS)
    if(LINUX)
        include(TC_GCC)
    elseif(WIN32)
        include(TC_MSVC)
    endif()
endif()

project(mm-game C CXX)

set(BUILD_SHARED_LIBS OFF)

include(FetchSFML)
include(FetchJSON)
include(FetchFont)

add_custom_target(configure_header
    COMMAND ${CMAKE_COMMAND}
        -DPROJECT_NAME="${PROJECT_NAME}"
        -DMM_VERSION="${MM_VERSION}"
        -DINPUT_FILE="${CMAKE_SOURCE_DIR}/src/config.hpp.in"
        -DOUTPUT_FILE="${CMAKE_BINARY_DIR}/src/config.hpp"
        -P "${CMAKE_SOURCE_DIR}/cmake/configure_header.cmake"
)

add_library(core_defs INTERFACE)

target_compile_definitions(core_defs INTERFACE
    FONT_FILE_PATH_DEV="${FONT_FILE_PATH}"
    ICON_FILE_PATH_DEV="${CMAKE_SOURCE_DIR}/assets/mm.png"
    LANG_DIR_PATH_DEV="${CMAKE_SOURCE_DIR}/assets/lang"
)

add_subdirectory(core)

if(WIN32 AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME} WIN32
        src/main.cpp
        ${CMAKE_SOURCE_DIR}/platform/windows/mm-game.rc
    )
    target_link_options(${PROJECT_NAME} PRIVATE "/ENTRY:mainCRTStartup")
else()
    add_executable(${PROJECT_NAME} src/main.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE core)

add_dependencies(${PROJECT_NAME} configure_header)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/src)

include(InstallArtifacts)

if(WIN32 AND CPACK_GENERATOR)
    include(BuildNSIS)
endif()

if(MAKE_TESTS)
    include(FetchCatch2)

    enable_testing()
    add_subdirectory(tests)
endif()
