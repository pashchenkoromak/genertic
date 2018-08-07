cmake_minimum_required(VERSION 2.8.12)

project(worldLib)

add_library(worldLib include/world.hpp src/world.cpp)

target_link_libraries(worldLib PUBLIC unitLib)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
