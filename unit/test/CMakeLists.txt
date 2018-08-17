cmake_minimum_required(VERSION 2.8.12)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

add_executable(runUnitTests unittest.cpp)
target_link_libraries(runUnitTests PUBLIC gtest gtest_main pthread)
target_link_libraries(runUnitTests PUBLIC unitLib)
