project(gmock_example LANGUAGES CXX)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(submodules)
