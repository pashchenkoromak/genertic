cmake_minimum_required(VERSION 2.8.12)

add_subdirectory(test)

project(unitLib)

add_library(unitLib include/operation.hpp include/genom.hpp include/IUnit.hpp src/IUnit.cpp include/unit.hpp src/operation.cpp src/unit.cpp src/genom.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
