set (TEST_NAME t)

add_executable(${TEST_NAME}
    utils/test_Source.cpp
)

set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain core)

add_test(
    NAME ${TEST_NAME}
    COMMAND $<TARGET_FILE:${TEST_NAME}>
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 30)
