cmake_minimum_required(VERSION 2.8.12)

project(genetic)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include(_cmake/coverage.cmake)

add_executable(${PROJECT_NAME} "main.cpp")

add_subdirectory(world)
add_subdirectory(actor)

target_link_libraries(${PROJECT_NAME} PUBLIC world_lib)