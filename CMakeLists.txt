cmake_minimum_required(VERSION 3.15)

project(data_structure)

add_library(project_compile_flags INTERFACE)
target_compile_features(project_compile_flags INTERFACE cxx_std_11)

add_subdirectory(SqList)