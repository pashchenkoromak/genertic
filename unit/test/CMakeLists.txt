cmake_minimum_required(VERSION 2.8.12)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

add_library(commonLib common/common.hpp common/common.cpp)

add_executable(runUnitTests unittest.cpp expressionTest.cpp boolTest.cpp)

target_include_directories(runUnitTests PUBLIC common/)
target_link_libraries(commonLib PUBLIC unitLib)
target_link_libraries(runUnitTests PUBLIC gtest gtest_main pthread commonLib)
