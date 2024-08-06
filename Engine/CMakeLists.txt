cmake_minimum_required(VERSION 3.26.4)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

add_library(Engine STATIC
        include/Engine.h
        include/Engine.cpp)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
