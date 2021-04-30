cmake_minimum_required(VERSION 2.8)
project(startProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(lib)

add_subdirectory(lib)
add_subdirectory(app)

set_property(TARGET ClientApp ClientLib PROPERTY CMAKE_CXX_CLANG_TIDY)
