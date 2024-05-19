cmake_minimum_required(VERSION 3.25)
project(YADROTestTask VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

link_directories(lib)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)
