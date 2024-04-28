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

## Add performance tests

gtest_discover_tests(utests)