cmake_minimum_required(VERSION 2.8.12)

project(unitLib)

add_library(unitLib include/operation.hpp include/unit.hpp src/operation.cpp src/unit.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
