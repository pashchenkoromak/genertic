cmake_minimum_required(VERSION 2.8.12)

project(actor_tests)

add_library(common_lib common/common.hpp common/common.cpp)
target_link_libraries(common_lib actor_lib)

set(TEST_SOURCES actor_test.cpp expression_test.cpp bool_test.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_GTEST} actor_lib common_lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} common/)
enable_testing()
