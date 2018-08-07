cmake_minimum_required(VERSION 2.8.12)

project(genetic)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} "main.cpp")

add_subdirectory(world)
add_subdirectory(unit)

target_link_libraries(${PROJECT_NAME} PUBLIC worldLib)
