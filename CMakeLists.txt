cmake_minimum_required(VERSION 2.8)
project(SKPS_Project)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${OpenCV_INCLUDE_DIRS} lib)

add_subdirectory(lib)
add_subdirectory(producer)
#add_subdirectory(consumer)

set_property(TARGET ProducerApp CommunicationLib PROPERTY CMAKE_CXX_CLANG_TIDY)
#set_property(TARGET ConsumerApp CommunicationLib PROPERTY CMAKE_CXX_CLANG_TIDY)
