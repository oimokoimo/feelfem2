cmake_minimum_required(VERSION 3.20)
project(feelfem2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(feelfem2 INTERFACE)
target_include_directories(feelfem2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(hello_scheme apps/hello_scheme.cpp)
target_link_libraries(hello_scheme PRIVATE feelfem2)

