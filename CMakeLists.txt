cmake_minimum_required(VERSION 2.8)
project(SKPS_Project)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(SKPS_Project draw.cpp)
target_link_libraries(SKPS_Project ${OpenCV_LIBS})