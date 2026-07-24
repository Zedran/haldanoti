# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

set (TEST_NAME t)

add_executable(${TEST_NAME}
    game/test_Game.cpp
    game/test_Row.cpp
    game/test_helpers.cpp
    utils/test_Source.cpp
    utils/test_utils.cpp
)

set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain SFML::Graphics)

add_test(
    NAME ${TEST_NAME}
    COMMAND $<TARGET_FILE:${TEST_NAME}>
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 30)

if(COVER)
    target_link_libraries(${TEST_NAME} PRIVATE "-Wl,--whole-archive" core_coverage "-Wl,--no-whole-archive")

    target_compile_options(${TEST_NAME} PRIVATE -g --coverage)
    target_link_options(${TEST_NAME} PRIVATE --coverage)

    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)

    add_custom_target(cover
        COMMAND ${LCOV} --quiet --zerocounters --directory ${PROJECT_SOURCE_DIR}
        COMMAND ${TEST_NAME}
        COMMAND ${LCOV} --quiet --capture --directory ${PROJECT_SOURCE_DIR} --output-file coverage.info 2> lcov.log
        COMMAND ${LCOV} --quiet --extract coverage.info '${PROJECT_SOURCE_DIR}/core/*' --output-file coverage.info
        COMMAND ${GENHTML} coverage.info --quiet --filter brace --demangle-cpp --flat --dark --output-directory cover
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
else()
    target_link_libraries(${TEST_NAME} PRIVATE core)
endif()
