cmake_minimum_required(VERSION 2.8.12)

project(world_lib)

add_library(${PROJECT_NAME} include/world.hpp src/world.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC actor_lib)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
