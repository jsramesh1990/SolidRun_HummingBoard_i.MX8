cmake_minimum_required(VERSION 3.10)
project(UnitTests)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/../../applications/data-structures/include
    ${GTEST_INCLUDE_DIRS}
)

set(SOURCES
    test_linkedlist.cpp
    test_stack.cpp
    test_queue.cpp
    test_bst.cpp
)

add_executable(unit_tests ${SOURCES})

target_link_libraries(unit_tests
    gtest
    gtest_main
    pthread
)

add_test(NAME UnitTests COMMAND unit_tests)
