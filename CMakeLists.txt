# 统一管理所有项目

cmake_minimum_required(VERSION 3.26.4)
project(my_solution)

add_subdirectory("${PROJECT_SOURCE_DIR}/code_1/c--test" "${PROJECT_SOURCE_DIR}/code_1/c--test")
add_subdirectory("${PROJECT_SOURCE_DIR}/code_2" "${PROJECT_SOURCE_DIR}/code_2")