cmake_minimum_required(VERSION 3.15)
project(To-Do_List VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(To-Do_List
    src/main.cpp
)

set_target_properties(To-Do_List PROPERTIES
    OUTPUT_NAME "To-Do CLIST"
)