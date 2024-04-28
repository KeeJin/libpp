message(STATUS "Building tests with gtest.")
add_subdirectory(extern/googletest)

## Add unit tests
add_executable(utests
    unit/utest_search_space.cpp
    unit/utest_node.cpp
)
target_link_libraries(utests
    gtest_main
    ${PROJECT_NAME}
)

## Add integration tests
add_executable(test_search_space
    test_search_space.cpp
)
target_link_libraries(test_search_space
    ${PROJECT_NAME}
    spdlog::spdlog
)

## Add performance tests

gtest_discover_tests(utests)