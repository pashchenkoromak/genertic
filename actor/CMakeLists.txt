cmake_minimum_required(VERSION 2.8.12)

project(actor_lib)

set(HEADERS include/operation.hpp include/genom.hpp include/actor.hpp)
set(SOURCES src/operation.cpp src/actor.cpp src/genom.cpp)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)

if(${COVERAGE_ENABLE})
    enable_coverage(${PROJECT_NAME})
endif()

add_subdirectory(test)